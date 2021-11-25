#include "TCP.h"

TCP::TCP(int port)
{
	//Initialisation pointeur
	init();

	//Save port dans classe
	_port = port;

	// Création de la socket serveur
	sd_serveur = socket(AF_INET, SOCK_STREAM, 0);

	// Configuration de la socket, notamment le port d'écoute
	struct sockaddr_in cfg_serveur;
	cfg_serveur.sin_family = AF_INET;
	cfg_serveur.sin_addr.s_addr = htonl(INADDR_ANY);
	cfg_serveur.sin_port = htons(port);

	// Attachement de la socket au port défini
	bind(sd_serveur, (struct sockaddr*)&cfg_serveur, sizeof(cfg_serveur));

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
			while (donnee->activation3 == false)
			{
				if (reponse == "alpha-go")
				{
					donnee->activation3 == true;
					break;
				}
				else
				{
					reponse = "erreur";
					envoi_reponse_client(reponse);
					break;
				}
			}

			//verification si l'utilisateur appui sur deconnexion et donc qu'il m'envoi une trame == "deconnecte", on verifie aussi qu'il a bien effectue la premiere connexion
			if (reponse == "deconnecte" && donnee->activation3 == true)
			{
				//Envoyer la réponse au client(deconnecte)
				reponse = "deconnexion";

				//Envoyer la réponse au client(informations capteurs)
				envoi_reponse_client(reponse);

				//Faire parler le robot en disant"deconnection"
				robot->parler(reponse, true);

				//Sortir de la boucel while
				donnee->activation2 = true;

				//Sortie boucle
				break;
			}

			//on verifie aussi qu'il a bien effectue la premiere connexion
			else if(donnee->activation3 == true && reponse != "alpha-go" && reponse != "" && donnee->activation2 != true)
			{
					//Si c est egale à une des requetes qui correspond au actions du robot, appel fonction robot correspondante
				    //...
				    // Si ca c est bien passe, envoi "ok" sinon "erreur" + action effectue : "avance, recule, gauche, droite, tourner..." 
					envoi_reponse_client(reponse);

					//Si la requete correspond à une demande d'information, alors appele methode robot pour recuperer informations
					//...
					// Si ca c est bien passe, envoi "ok" sinon "erreur" + les donnees
					envoi_reponse_client(reponse);
				
			}

			//Si reponse est egale à alpha-go et activation3 vaut true
			else if (donnee->activation3 == true && reponse == "alpha-go")
			{
				//Envoi reponse pour dire qu'il est connecter
				reponse = "connection";
				envoi_reponse_client(reponse);

				//Faire parler le robot en disant"connection"
				robot->parler(reponse, true);
			}

			//Si il ne se passe aucune action donc que aucune des conditions n'est été utilisé alors on attend 20 seconde
			else
			{
				//Compteur tour pour gerer le temps
				donnee->compteur_tour++;

				//Si le compteur est entre 1 inclut et 5 exclut alors on fait des threads attente 10s, + un message pour prevenir l'utilisateur que le socket client va etre detruit dans peu de temps pour laisser la place aux autre et eviter de surcharger la bande passante
				if (donnee->compteur_tour >= 1 && donnee->compteur_tour < 5)
				{
					//Envoi reponse client adapté entre autre, attention deconnexion proche à cause d'une inactivite
					reponse = "deconnexion_proche";
					envoi_reponse_client(reponse);

					//Faire parler le robot en disant"deconnection"
					robot->parler(reponse, true);

					//Pause dans le programme grace à un thread
					robot->attendre(10);
				}

				//si jamais aucune trame n'est envoye le socket client se detruit pour eviter de surcharger la bande passante
				else
				{
					//Envoi reponse client adapté entre autre, attention deconnexion_delai_depasse à cause d'une inactivite
					reponse = "deconnexion_delai_depasse";
					envoi_reponse_client(reponse);

					//Faire parler le robot en disant"deconnection"
					robot->parler(reponse, true);

					//sortir boucle while pour detruire socket client à cause d'inactivite trop repete
					break;
				}
			}
		}

		//Reactivation de activation2 pour re-rentrer dans boucle
		donnee->activation2 = false;

		//Reactivation de activation3 pour re faire le test de la premiere connexion
		donnee->activation3 == false;

		//remise à 0 du compteur
		donnee->compteur_tour = 0;

		//fermeture client pour en attendre un autre
		close_socket_client();

		//Si le bouton centrale est enfonce alors on ferme le socket et fin
		if (robot->recupererEtatBoutonCentral() == true)
		{
			close_socket_serveur();
			donnee->activation = true;
			//voir pour afficher sur ecran robot que socket reseau serveur ferme donc on peut eteindre robot
			//Si on le reutilise il faut le rallumer pour remettre à 0
			//...123v4v5
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

TCP::~TCP()
{
	delete robot;
}



