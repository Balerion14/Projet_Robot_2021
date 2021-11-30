#include "TCP.h"

TCP::TCP(int port)
{
	//Initialisation pointeur
	init();

	//Save port dans classe
	_port = port;
	int resultat{};

	// Création de la socket serveur
	sd_serveur = socket(AF_INET, SOCK_STREAM, 0);

	//Non reutilisation de la socket après un arret sauvage
	int option = 1;
	setsockopt(sd_serveur, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));


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
		cout << "ERREUR DE PORT" << endl;
		exit -1;
	}

	// Création une file d'attente de connexion
	listen(sd_serveur, 5);
}

void TCP::init()
{
	robot = new Robot();
	donnee = new Donnee();
}

void TCP::creation_new_socket()
{
	//Tant que le bouton centrale n'est pas enfonce
	while (donnee->activation == false)
	{
		// Dès qu’un nouveau client se connecte à notre serveur,
		// une nouvelle socket est créée pour gérer le client
		//accept fonction bloquante et tant qu'il n'y a personne en file d'attente, il attent ?
		sd_client = accept(sd_serveur, NULL, NULL);

		while (donnee->activation2 == false)
		{
			// Réception de la requête du client(decrypte)
			std::string _reponse = reception_requete_client();
			reponse = _reponse;

			//Verification de la connexion de chaque client avec une requetes specifique "alpha-go"
			if (donnee->activation3 == false && reponse == "alpha-go")
			{
					donnee->activation3 == true;

					//Message pour le debug
					cout << "demande connexion active" << endl;
			}

			//Verification si le robot veut une connexion en continu(connexion force->IHM), (peut etre rajout de active 3 = true)
			if (reponse == "connexion-force" && donnee->activation4 == false && donnee->activation3 == true)
			{
				donnee->activation4 == true;

				//Message pour le debug
				cout << "demande connexion force active" << endl;
			}

			//Appel methode pour savoir si on doit ou pas activer le timer ou bien si on doit le reset
			Start_timer(reponse);

			//verification si l'utilisateur appui sur deconnexion et donc qu'il m'envoi une trame == "deconnecte", on verifie aussi qu'il a bien effectue la premiere connexion 
			if (reponse == "deconnecte" && donnee->activation3 == true)
			{
				//Envoyer la réponse au client(deconnecte)
				reponse = "-deconnexion";

				//Envoyer la réponse au client(informations capteurs)
				envoi_reponse_client(reponse);

				//Faire parler le robot en disant"deconnection"
				robot->parler(reponse, true);

				//Sortir de la boucel while
				donnee->activation2 = true;

				//Message pour le debug
				cout << "deconnexion" << endl;

				//Sortie boucle
				break;
			}

			//on verifie aussi qu'il a bien effectue la premiere connexion 
			else if(donnee->activation3 == true && reponse != "alpha-go" && reponse != "" && reponse != "connexion-force" && donnee->activation2 != true)
			{
	            //Appel fonction qui va determiner quel action faire(bouger robot ou envoyer donnee)
				std::string message = robot->evaluate_action_robot(reponse);

				//Si message vaut "action_effectue" alors on envoi action effectue sinon le format csv crypter
				if (message == "action_effectue")
				{
					//Envoie reponse au client, penser à peut etre renvoyer un autre message que les commandes mais pour test c est ok
					envoi_reponse_client(reponse);

					//Message pour le debug
					cout << "action effectue" << endl;
				}
				else
				{
					std::string message_crypte = crypte_reponse(message);
					envoi_reponse_client(message_crypte);

					//Message pour le debug
					cout << "envoi trame" << endl;
				}		
			}

			//Si reponse est egale à alpha-go et activation3 vaut true 
			else if (donnee->activation3 == true && reponse == "alpha-go")
			{
				//Envoi reponse pour dire qu'il est connecter
				reponse = "-connection";
				envoi_reponse_client(reponse);

				//Faire parler le robot en disant"connection"
				robot->parler(reponse, true);

				//Message pour le debug
				cout << "connexion" << endl;
			}

			//Si il ne se passe aucune action donc que aucune des conditions n'est été utilisé alors on attend 20 seconde
			else
			{
		
				//Verification globale si il veut ou pas une connnexion en continue
				if (donnee->activation4 == false)
				{

					//Calcule du temps avec le cumule
					End_timer();

					//Si le compteur est entre 1 inclut et 5 exclut alors on fait des threads attente 10s, + un message pour prevenir l'utilisateur que le socket client va etre detruit dans peu de temps pour laisser la place aux autre et eviter de surcharger la bande passante
					if (donnee->time_total < 30)
					{
						//Envoi reponse client adapté entre autre, attention deconnexion proche à cause d'une inactivite
						reponse = "-Inactivite-detecte";
						envoi_reponse_client(reponse);

						//Faire parler le robot en disant"Inactivite-detecte"
						robot->parler(reponse, true);

						//Message pour le debug
						cout << "inactivite detecte" << endl;
					}

					//si jamais aucune trame n'est envoye le socket client se detruit pour eviter de surcharger la bande passante au bout d'un certains temps
					else
					{
						//Envoi reponse client adapté entre autre, attention deconnexion_delai_depasse à cause d'une inactivite
						reponse = "-deconnexion-delai-depasse";
						envoi_reponse_client(reponse);

						//Faire parler le robot en disant"deconnection"
						robot->parler(reponse, true);

						//Message pour le debug
						cout << "deconnexion delai depasse" << endl;

						//sortir boucle while pour detruire socket client à cause d'inactivite trop repete
						break;
					}
				}

				//Si c est à true alors on envoi reponse comme quoi on est bien en mode connexion force
				else
				{
					reponse = "-connexion_force_active";
					envoi_reponse_client(reponse);

					//Message pour le debug
					cout << "connexion force" << endl;
				}
			}
		}

		//Reactivation de activation2 pour re-rentrer dans boucle
		donnee->activation2 = false;

		//Reactivation de activation3 pour re faire le test de la premiere connexion
		donnee->activation3 = false;

		//Reactivation du bouton force connexion
		donnee->activation4 = false;

		//remise à 0 du mode reset du timer apres une deconnexion d'un client
		donnee->activation5 = false;

		//fermeture client pour en attendre un autre
		close_socket_client();

		//Message pour le debug
		cout << "deconnexion client" << endl;

		//Si le bouton centrale est enfonce alors on ferme le socket et fin
		if (robot->recupererEtatBoutonCentral() == true)
		{
			close_socket_serveur();
			donnee->activation = true;

			//Message pour le debug
			cout << "deconnexion serveur" << endl;

			//voir pour afficher sur ecran robot que socket reseau serveur ferme donc on peut eteindre robot
			//Si on le reutilise il faut le rallumer pour remettre à 0
			//...123v4v5v6.1.1v7v8v9.5
		}
	}
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

std::string TCP::envoi_reponse_client(std::string requetes)
{
	// Envoi de la réponse au client
	std::string requete = requetes;
	send(sd_client, requete.c_str(), requete.size(), 0);
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
}



