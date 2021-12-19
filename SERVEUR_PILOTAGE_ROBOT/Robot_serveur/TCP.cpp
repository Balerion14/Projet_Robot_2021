#include "TCP.h"

TCP::TCP(int port)
{
	//Initialisation pointeur
	init();

	//Message debug
	std::cout << "entrer programme" << endl;

	//Save port dans classe
	_port = port;
	int resultat{};

	// Création de la socket serveur
	sd_serveur = socket(AF_INET, SOCK_STREAM, 0);

	//Non reutilisation de la socket après un arret sauvage
	//Empecher que le serveur se ferme apres la deconnexion d'un client avec "SO_NOSIGPIPE"
	int option = 1;
	setsockopt(sd_serveur, SOL_SOCKET, SO_NOSIGPIPE, &option, sizeof(option));//SO_REUSEADDR


	// Configuration de la socket, notamment le port d'écoute
	struct sockaddr_in cfg_serveur;
	cfg_serveur.sin_family = AF_INET;
	cfg_serveur.sin_addr.s_addr = htonl(INADDR_ANY);

	//Boucle pour tester tous les port en cas de dysfonctionnement
	do
	{
		//Choix du port
		cfg_serveur.sin_port = htons(++port);

		// Attachement de la socket au port défini
	    resultat = bind(sd_serveur, (struct sockaddr*)&cfg_serveur, sizeof(cfg_serveur));
	} 
	while (resultat < 0);
	
	//Condition en cas d'erreur
	if (resultat < 0)
	{
		std::cout << "ERREUR DE PORT" << endl;
		exit(-1);
	}

	//Message debug
	std::cout << "Creation du serveur" << endl;

	//Message debug
	std::cout << port << endl;

	// Création une file d'attente de connexion
	listen(sd_serveur, 5);
}

void TCP::init()
{
	robot = new Robot();
	donnee = new Donnee();
	processus = new thread_();
}

void TCP::wait_client()
{
	//Tant que le bouton centrale n'est pas enfonce
	while (donnee->activation == false)
	{
		//Message debug
		std::cout << "Serveur-Attente-client" << endl;

		// Dès qu’un nouveau client se connecte à notre serveur,
		// une nouvelle socket est créée pour gérer le client
		//accept fonction bloquante et tant qu'il n'y a personne en file d'attente, il attent ?
		sd_client = accept(sd_serveur, NULL, NULL);

	    //-------------------------------Demarage threads client
		// Identifiants des threads
		pthread_t t1;

		// Initialisation du mutex rotatif client
		pthread_spin_init(&processus->slock_client, PTHREAD_PROCESS_PRIVATE);


		// Affichage du nombre de client
		printf("Nombre client : \n", ++donnee->compteur_tour);

		// Affichage thread lancement
		printf("Ouverture du thread client\n");

		// Creation  thread avec chacune une fonction à embarquer qui gere un client
		pthread_create(&t1, NULL, nouveau_client, this);

		// Attente de la fin du thread
		pthread_join(t1, NULL);

		// Affichage de la fin du thread
		printf("Fermeture du thread client\n");

		// Destruction du mutex rotatif client
		pthread_spin_destroy(&processus->slock_client);
		printf("Destruction du mutex\n");

		//---------------------------------Fin thread client
		
		//Reactivation de activation2 pour re-rentrer dans boucle
		donnee->activation2 = false;

		//Reactivation de activation3 pour re faire le test de la premiere connexion
		donnee->activation3 = false;

		//Remise a 0 du compteur tour
		donnee->compteur_tour = 0;

		//fermeture client pour en attendre un autre
		close_socket_client();

		//Message debug
		std::cout << "serveur-deco-client  " << "_" << endl;

		//Condition pour deconnecter socket serveur
		if (robot->recupererEtatBoutonCentral() == true)
		{
			//Sortir de la boucle principale
			donnee->activation = true;

			//Message pour le debug
			std::cout << "deconnexion-serveur  " << "_" << endl;

			//Fermeture socket serveur
			close_socket_serveur();
		}//v15
	}
}

void TCP::new_client()
{
	// Verrouillage du mutex rotatif : P()
	pthread_spin_lock(&processus->slock_client);
	printf("Verroulliage du mutex : P() ->new-client\n");

	//Tant qu'il y a un client on reste dans la boucle 
	while (donnee->activation2 == false)
	{
		// Identifiants des threads
		pthread_t t1, t2, t0;

		// Initialisation du générateur de nombres aléatoires
		srand(time(NULL));

		//--------------------------------------------------------------------------------------

		//Initialisation du semaphore 0 pour la gestion du tampon memoire
		sem_init(&processus->mon_semaphore_tampon, 0, 1);
		printf("Initialisation du sémaphore à 0(tampon)\n");

		// Initialisation du sémaphore à 1(producteur)
		sem_init(&processus->mon_semaphore_productueur, 0, 0);
		printf("Initialisation du sémaphore à 1(producteur)\n");

		// Initialisation du sémaphore à 2(consomateur)
		sem_init(&processus->mon_semaphore_consomateur, 0, 0);
		printf("Initialisation du sémaphore à 2(consomateur)\n");

		//--------------------------------------------------------------------------------------

		//Initialisation du mutex 0 tampon memoire
		pthread_spin_init(&processus->slock_tampon, PTHREAD_PROCESS_PRIVATE);
		printf("Initialisation du mutex rotatif 0(tampon)\n");

		// Initialisation du mutex rotatif 1 producteur
		pthread_spin_init(&processus->product, NULL);
		printf("Initialisation du mutex 1 producteur\n");

		// Initialisation du mutex 2 consomateur
		pthread_spin_init(&processus->conso, NULL);
		printf("Initialisation du mutex 2 consomateur\n");

		//--------------------------------------------------------------------------------------

		// Creation des 2 threads avec chacune une fonction à embarquer
		pthread_create(&t0, NULL, tampon_receveid, this);
		pthread_create(&t1, NULL, traiter_donnee, this);
		pthread_create(&t2, NULL, consommer_donnee, this);
		
		// Attente de la fin de chaque thread
		pthread_join(t0, NULL);
		pthread_join(t1, NULL);
		pthread_join(t2, NULL);

		//--------------------------------------------------------------------------------------

		// Destruction du sémaphore tampon memoire 0
		sem_destroy(&processus->mon_semaphore_tampon);
		printf("Destruction du sémaphore tampon memoire 0\n");


		// Destruction du sémaphore producteur 1
		sem_destroy(&processus->mon_semaphore_productueur);
		printf("Destruction du sémaphore producteur 1\n");

		// Destruction du sémaphore 2 consomateur
		sem_destroy(&processus->mon_semaphore_consomateur);
		printf("Destruction du sémaphore 2 consomateur\n");

		//--------------------------------------------------------------------------------------

		//Destrcution du mutex 0 rotatif
		pthread_spin_destroy(&processus->slock_tampon);
		printf("Destruction du mutex tampon rotatif 0\n");

		// Destruction du mutex producteur 1
		pthread_spin_destroy(&processus->product);
		printf("Destruction du mutex producteur 1\n");

		// Destruction du mutex 2 consomateur
		pthread_spin_destroy(&processus->conso);
		printf("Destruction du mutex 2 consomateur\n");
	}
	
	// Déverrouillage du mutex rotatif : V()
	pthread_spin_unlock(&processus->slock_client);
	printf("Déverrouillage du mutex : V() ->new-client\n");
}

void TCP::received_message()
{
	// Prise du sémaphore : Producteur()
	sem_wait(&processus->mon_semaphore_tampon);
	std::cout << "Prise du sémaphore : tampon() -> received:  " << std::endl;

	//Recevoir message
	//Traitement robot avec le tampon pour le resultat
	std::cout << "1: " << donnee->activation3 << endl;
	std::cout << "2: " << donnee->activation2 << endl;

	//Message debug
	std::cout << "Serveur-trouve-client  " << endl;

	//Blocage avec un mutex rotatif
	pthread_spin_lock(&processus->slock_tampon);

	// Réception de la requête du client(decrypte)
	std::string _reponse = reception_requete_client();

	//Decrypte reponse
	_reponse = Decrypte_message(_reponse);

	// Insertion de  noeud dans la file(gestion file attente)
	file.enfiler(_reponse);

	//Aller recuperer le premier de la liste
	reponse = file.premier();

	//Supression du noeud
	file.defiler();

	//Affichage file attente
	file.afficher();

	//Deblocage mutex rotatif
	pthread_spin_unlock(&processus->slock_tampon);

	//Message debug
	std::cout << "Message-recu-serveur-par-IHM:  " << reponse << "_" << endl;

	// Vente du sémaphore : Vente semaphore Producteur()
	sem_post(&processus->mon_semaphore_productueur);
	std::cout << " Vente du sémaphore : Vente semaphore producteur() ->received" << std::endl;
}

void TCP::producteur_traitement_data()
{
	// Prise du sémaphore : Producteur()
	sem_wait(&processus->mon_semaphore_productueur);
	std::cout << "Prise du sémaphore : Producteur() -> process:  "<< std::endl;

	// Verrouillage du mutex : P()
	pthread_spin_lock(&processus->product);
	std::cout << "Verrouillage du mutex : P() : Producteur() -> process:  " << std::endl;

	//-------------------------------------------------------
	//-------------------------------------------------------

	//erreur a false
	donnee->erreur = false;

	// Identifiants des threads
	pthread_t t1, t2, t0, t4;

	// Initialisation du générateur de nombres aléatoires
	srand(time(NULL));

	//--------------------------------------------------------------------------------------

	//Initialisation du semaphore 0 pour la gestion des donnee du robot
	sem_init(&processus->mon_semaphore_robot, 0, 1);
	printf("Initialisation du semaphore 0 pour la gestion des donnee du robot\n");

	// Initialisation du sémaphore à 1 connexion
	sem_init(&processus->mon_semaphore_connexion, 0, 0);
	printf("Initialisation du sémaphore à 1 connexion\n");

	// Initialisation du sémaphore à 2 deconnexion
	sem_init(&processus->mon_semaphore_deconnexion, 0, 0);
	printf("Initialisation du sémaphore à 2 deconnexion\n");

	// Initialisation du sémaphore  3 erreur
	sem_init(&processus->mon_semaphore_erreur, 0, 0);
	printf("Initialisation du sémaphore  3: erreur\n");


	//--------------------------------------------------------------------------------------

	//Initialisation du mutex 0 data infos
	pthread_spin_init(&processus->robot, PTHREAD_PROCESS_PRIVATE);
	printf("Initialisation du mutex rotatif 0 des donnees robot\n");

	// Initialisation du mutex rotatif 1 connexion
	pthread_spin_init(&processus->connexion, NULL);
	printf("Initialisation du mutex 1 connexion\n");

	// Initialisation du mutex 2 deconnexion
	pthread_spin_init(&processus->deconnexion, NULL);
	printf("Initialisation du mutex 2 deconnexion\n");

	// Initialisation du mutex 3 erreur
	pthread_spin_init(&processus->erreur, NULL);
	printf("Initialisation du mutex 3 erreur\n");

	//--------------------------------------------------------------------------------------

	// Creation des 4 threads avec chacune une fonction à embarquer
	pthread_create(&t0, NULL, traiter_donnee_robot, this);
	pthread_create(&t1, NULL, traiter_donnee_connexion, this);
	pthread_create(&t2, NULL, traiter_donnee_deconnexion, this);
	pthread_create(&t4, NULL, traiter_donnee_erreur, this);

	// Attente de la fin de chaque thread
	pthread_join(t0, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t4, NULL);

	//--------------------------------------------------------------------------------------

	// Destruction du sémaphore robot memoire 0
	sem_destroy(&processus->mon_semaphore_robot);
	printf("Destruction du sémaphore robot memoire 0\n");


	// Destruction du sémaphore connexion 1
	sem_destroy(&processus->mon_semaphore_connexion);
	printf("Destruction du sémaphore connexion 1\n");

	// Destruction du sémaphore 2 deconnexion
	sem_destroy(&processus->mon_semaphore_deconnexion);
	printf("Destruction du sémaphore 2 deconnexion\n");

	// Destruction du sémaphore 2 erreur
	sem_destroy(&processus->mon_semaphore_erreur);
	printf("Destruction du sémaphore 3 erreur\n");

	//--------------------------------------------------------------------------------------

	//Destrcution du mutex 0 rotatif
	pthread_spin_destroy(&processus->robot);
	printf("Destruction du mutex tampon rotatif 0\n");

	// Destruction du mutex connexion 1
	pthread_spin_destroy(&processus->connexion);
	printf("Destruction du mutex connexion 1\n");

	// Destruction du mutex 2 deconnexion
	pthread_spin_destroy(&processus->deconnexion);
	printf("Destruction du mutex 2 deconnexion\n");

	// Destruction du mutex 3 erreur
	pthread_spin_destroy(&processus->erreur);
	printf("Destruction du mutex 3 erreur\n");

	//------------------------------------------------------
	//------------------------------------------------------

	// Déverrouillage du mutex : V()
	pthread_spin_unlock(&processus->product);
	std::cout << " Déverrouillage du mutex producteur : V() ->Partie_process" << std::endl;

	// Vente du sémaphore : Vente semaphore consomateur()
	sem_post(&processus->mon_semaphore_consomateur);
	std::cout << " Vente du sémaphore : Vente semaphore consomateur() ->Partie_process" << std::endl;
}

void TCP::gestion_info_robot()
{
	// Prise du sémaphore : gestion robot()
	sem_wait(&processus->mon_semaphore_robot);
	std::cout << "Prise du sémaphore : gestion robot() ->process" << std::endl;

	// Verrouillage du mutex : gestion robot()
	pthread_spin_lock(&processus->robot);
	std::cout << " Verrouillage du mutex : gestion robot() ->process" << std::endl;

	if (donnee->activation3 == true && (reponse[0] == 'Z' || reponse[0] == 'S' || reponse[0] == 'Q' || reponse[0] == 'D' || reponse[0] == 'C' || reponse[0] == 'A' || reponse[0] == 'E' || reponse[0] == 'T'))//
	{
		//Passage erreur a true pour bloquer erreur
		donnee->erreur = true;

		//Message debug
		std::cout << "Serveur-confirme-commande-robot-action  " << "_" << endl;

		//Appel fonction qui va determiner quel action faire(bouger robot ou envoyer donnee)
		donnee->message = robot->evaluate_action_robot(reponse[0]);

		//Message debug
		std::cout << "Message-genere-par-serveur-choix-action-infCpateur  " << donnee->message << "_" << endl;

		//Si message vaut "action_effectue" alors on envoi action effectue sinon le format csv crypter
		if (donnee->message == "-action_effectue")
		{
			//Envoie reponse au client, penser à peut etre renvoyer un autre message que les commandes mais pour test c est ok
			//envoi_reponse_client(donnee->message);

			//Message pour le debug
			std::cout << "action-effectue   _" << endl;
		}
		else
		{
			//donnee->message_crypte = crypte_reponse(donnee->message);
			//envoi_reponse_client(donnee->message_crypte);

			//Message pour le debug
			std::cout << "envoi-trame-crypte:  " << donnee->message << "_" << endl;
		}
	}

	// Deverrouillage du mutex : gestion robot()
	pthread_spin_unlock(&processus->robot);
	std::cout << " Deverrouillage du mutex : gestion robot() ->process" << std::endl;

	// Vente du sémaphore : Vente semaphore connexion
	sem_post(&processus->mon_semaphore_connexion);
	std::cout << " Vente du sémaphore : Vente semaphore connexion() ->Partie_process" << std::endl;
}

void TCP::gestion_connexion()
{
	// Prise du sémaphore : connexion
	sem_wait(&processus->mon_semaphore_connexion);
	std::cout << "Prise du sémaphore : connexion ->process" << std::endl;

	// Verrouillage du mutex : connexion
	pthread_spin_lock(&processus->connexion);
	std::cout << " Verrouillage du mutex : connexion ->process" << std::endl;

	//Condition pour la connexion du client
	if (reponse == "alpha-go" && donnee->activation3 == false)
	{
		//Passage erreur a true pour bloquer erreur
		donnee->erreur = true;

		//Message debug
		std::cout << "Serveur-confirme-connexion-client  " << "_" << endl;

		//Envoyer la réponse au client(deconnecte)
		donnee->message = "-connection";

		//Message debug
		std::cout << "Message-envoye-a-IHM:  " << donnee->message << "_" << endl;

		//premiere connexion effectue
		donnee->activation3 = true;

		//Envoyer la réponse au client
		//envoi_reponse_client(envoi);
	}

	// Deverrouillage du mutex : connexion
	pthread_spin_unlock(&processus->connexion);
	std::cout << " Deverrouillage du mutex : connexion ->process" << std::endl;

	// Vente du sémaphore : Vente semaphore deconnexion
	sem_post(&processus->mon_semaphore_deconnexion);
	std::cout << " Vente du sémaphore : Vente semaphore deconnexion() ->Partie_process" << std::endl;
}

void TCP::gestion_deconnexion()
{
	// Prise du sémaphore : deconnexion
	sem_wait(&processus->mon_semaphore_deconnexion);
	std::cout << "Prise du sémaphore : deconnexion ->process" << std::endl;

	// Verrouillage du mutex : deconnexion
	pthread_spin_lock(&processus->deconnexion);
	std::cout << " Verrouillage du mutex : deconnexion ->process" << std::endl;

	//Condition pour la deconnexion du client
	if (reponse == "deconnexion")
	{
		//Passage erreur a true pour bloquer erreur
		donnee->erreur = true;

		//Message debug
		std::cout << "Serveur-deconnecte-client  " << "_" << endl;

		//Envoyer la réponse au client(deconnecte)
		donnee->message = "-deconnexion";

		//Message debug
		std::cout << "Message-envoye-a-IHM:  " << donnee->message << "_" << endl;

		//sortir boucle
		donnee->activation2 = true;

		//Envoyer la réponse au client
		//envoi_reponse_client(donnee->message);
	}

	// Deverrouillage du mutex : deconnexion
	pthread_spin_unlock(&processus->deconnexion);
	std::cout << " Deverrouillage du mutex : deconnexion ->process" << std::endl;

	// Vente du sémaphore : Vente semaphore erreur
	sem_post(&processus->mon_semaphore_erreur);
	std::cout << " Vente du sémaphore : Vente semaphore erreur() ->Partie_process" << std::endl;
}

void TCP::gestion_erreur()
{
	// Prise du sémaphore : erreur
	sem_wait(&processus->mon_semaphore_erreur);
	std::cout << "Prise du sémaphore : erreur ->process" << std::endl;

	// Verrouillage du mutex : erreur
	pthread_spin_lock(&processus->erreur);
	std::cout << " Verrouillage du mutex : erreur ->process" << std::endl;

	if(donnee->erreur == false)
	{
		//Message pour le debug
		std::cout << "Envoi-message-IHM-erreur:  " << "_" << endl;

		//remplir message erreur
		donnee->message = "-erreur";

		//Message pour le debug
		std::cout << "Envoi-message-IHM-erreur:  " << donnee->message << std::endl;

		//Envoi message au client
		//envoi_reponse_client(donnee->message);
	}

	// Deverrouillage du mutex : erreur
	pthread_spin_unlock(&processus->erreur);
	std::cout << " Deverrouillage du mutex : erreur ->process" << std::endl;

	// Vente du sémaphore : Vente semaphore robot
	sem_post(&processus->mon_semaphore_robot);
	std::cout << " Vente du sémaphore : Vente semaphore robot() ->Partie_process" << std::endl;
}

void TCP::consomateur_lecture_envoi_data()
{
	// Prise du sémaphore : consomateur()
	sem_wait(&processus->mon_semaphore_consomateur);
	std::cout << "Prise du sémaphore : consomateur() ->Partie_envoi" << std::endl;

	// Verrouillage du mutex : consomateur()
	pthread_spin_lock(&processus->conso);
	std::cout << " Verrouillage du mutex : consomateur() ->Partie_envoi" << std::endl;

	//Recup tampon pour mettre dans message et envoie en message crypte
	donnee->message_after_process = donnee->message;
	std::cout << " Message recu du tampon vers message apres process : " <<"donne-message : "<< donnee->message << "donnee-message-after-process : " << donnee->message_after_process <<  std::endl;

	donnee->message_crypte = crypte_reponse(donnee->message_after_process);
	std::cout << " Message crypte : " << "donne-message-crypte : " << donnee->message_crypte << std::endl;

	envoi_reponse_client(donnee->message_crypte);
	std::cout << " Message envoye : " << donnee->message_crypte << std::endl;

	// Déverrouillage du mutex : V()
	pthread_spin_unlock(&processus->conso);
	std::cout << " Déverrouillage du mutex consomateur : V() ->Partie_envoi" << std::endl;

	// Vente du sémaphore : Vente semaphore tampon()
	sem_post(&processus->mon_semaphore_tampon);
	std::cout << " Vente du sémaphore : Vente semaphore tampon() ->Partie_envoi" << std::endl;
}

std::string TCP::reception_requete_client()
{
	// Réception de la requête du client
	char buffer[1024];
	memset(buffer, 0x00, 1024);
	int nbOctets = recv(sd_client, buffer, sizeof(buffer), 0);
	std::string reponse(buffer);
	std::cout << reponse << std::endl;
	return reponse;
}

void TCP::envoi_reponse_client(std::string requetes)
{
	std::cout << "10" << endl;
	// Envoi de la réponse au client
	std::string requete = requetes;
	std::cout << "11" << endl;
	send(sd_client, requete.c_str(), requete.size(), 0);
	std::cout << "12" << endl;
}

void TCP::close_socket_client()
{
	// Fermeture de la socket client
	close(sd_client);
}

void TCP::close_socket_serveur()
{
	// Fermeture de la socket client
	close(sd_serveur);
}

std::string TCP::crypte_reponse(std::string reponse)
{
	//Declarations variables
	std::string enc;

	for (int i = 0; i < reponse.size(); i++)
	{
		enc += reponse[i] ^ (int(key_cryptage) + i) % 20;
	}

	//Retourner valeur crypte
	return enc;
}

std::string TCP::Decrypte_message(std::string message)
{
	//Declarations variables
	std::string dec;

	for (int i = 0; i < message.size(); i++)
	{
		dec += message[i] ^ (int(key_cryptage) + i) % 20;
	}

	//Retourner valeur crypte
	return dec;
}

void TCP::Start_timer(std::string reponse)
{
	//Declaration du timer de commencencement
	clock_t start;

	//Si je ne suis pas connecte
	if (donnee->activation3 == false)
	{
		start = clock();
		donnee->time_start = start;
		donnee->activation5 = true;
	}

	//Si je suis connecte
	else
	{
		//On s' assure que la reponse ne soit pas egale à une commande connu et que on est pas active la connexion force
		if (reponse != "alpha-go" && reponse != "deconnexion" && reponse != "connexion-force" && donnee->activation4 == false && reponse != "Z" && reponse != "S" && reponse != "Q" && reponse != "D" && reponse != "C" && reponse != "A" && reponse != "E" && reponse != "T")
		{
			start = clock();
			donnee->time_start = start;
			donnee->activation5 = true;
		}

		//Si la reponse est correcte alors on desactive la securite pour pouvoir reset le temps
		else
		{
			donnee->activation5 = false;
			donnee->time_total = 0;
		}
	}
}

void TCP::End_timer()
{
	//Declaration du timer de fin
	clock_t end;

	//Fin temps
	end = clock();
	donnee->time_total += end - donnee->time_start;
}

TCP::~TCP()
{
	delete robot;
	delete donnee;
	delete processus;
}



