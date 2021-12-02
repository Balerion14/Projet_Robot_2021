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
}

void TCP::creation_new_socket()
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

	    //Tant qu'il y a un client on reste dans la boucle 
		while (donnee->activation2 == false)
		{
			std::cout << "1: " << donnee->activation3 << endl;
			std::cout << "2: " << donnee->activation2 << endl;

			//Message debug
			std::cout << "Serveur-trouve-client  " << endl;

			// Réception de la requête du client(decrypte)
			std::string _reponse = reception_requete_client();
			reponse = _reponse;

			//Message debug
			std::cout << "Message-recu-serveur-par-IHM:  " << reponse << "_" << endl;

			//Condition pour la deconnexion du client
			if (reponse == "deconnexion")
			{
				//Message debug
				std::cout << "Serveur-deconnecte-client  " << "_" << endl;

				//Envoyer la réponse au client(deconnecte)
				std::string envoi = "-deconnexion";

				//Message debug
				std::cout << "Message-envoye-a-IHM:  " << envoi << "_" << endl;

				//sortir boucle
				donnee->activation2 = true;

				//Envoyer la réponse au client
				envoi_reponse_client(envoi);
			}

			//Condition pour la connexion du client
			else if (reponse == "alpha-go" && donnee->activation3 == false)
			{
				//Message debug
				std::cout << "Serveur-confirme-connexion-client  " << "_" << endl;

				//Envoyer la réponse au client(deconnecte)
				std::string envoi = "-connection";

				//Message debug
				std::cout << "Message-envoye-a-IHM:  " << envoi << "_" << endl;

				//premiere connexion effectue
				donnee->activation3 = true;

				//Envoyer la réponse au client
				envoi_reponse_client(envoi);

			}
			else if (donnee->activation3 == true && (reponse[0] == 'Z' || reponse[0] == 'S' || reponse[0] == 'Q' || reponse[0] == 'D' || reponse[0] == 'C' || reponse[0] == 'A' || reponse[0] == 'E' || reponse[0] == 'T'))//
			{
				//Message debug
				std::cout << "Serveur-confirme-commande-robot-action  " << "_" << endl;

				//Appel fonction qui va determiner quel action faire(bouger robot ou envoyer donnee)
				std::string message = robot->evaluate_action_robot(reponse[0]);

				//Message debug
				std::cout << "Message-genere-par-serveur-choix-action-infCpateur  " << message << "_" << endl;

				//Si message vaut "action_effectue" alors on envoi action effectue sinon le format csv crypter
				if (message == "-action_effectue")
				{
					//Envoie reponse au client, penser à peut etre renvoyer un autre message que les commandes mais pour test c est ok
					envoi_reponse_client(message);

					//Message pour le debug
					std::cout << "action-effectue   _" << endl;
				}
				else
				{
					std::string message_crypte = crypte_reponse(message);
					envoi_reponse_client(message_crypte);

					//Message pour le debug
					std::cout << "envoi-trame-crypte:  " << message_crypte << "_" << endl;
				}
			}
			else
			{
				//Message pour le debug
				std::cout << "Envoi-message-IHM-erreur:  "<< "_" << endl;

				//Envoi message au client
				envoi_reponse_client("-erreur");
			}
		}

		//Reactivation de activation2 pour re-rentrer dans boucle
		donnee->activation2 = false;

		//Reactivation de activation3 pour re faire le test de la premiere connexion
		donnee->activation3 = false;

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
}



