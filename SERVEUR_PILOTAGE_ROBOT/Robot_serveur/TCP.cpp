#include "TCP.h"

TCP::TCP(int port)
{
	//Initialisation pointeur
	init();

	// Cr�ation de la socket serveur
	sd_serveur = socket(AF_INET, SOCK_STREAM, 0);

	// Configuration de la socket, notamment le port d'�coute
	struct sockaddr_in cfg_serveur;
	cfg_serveur.sin_family = AF_INET;
	cfg_serveur.sin_addr.s_addr = htonl(INADDR_ANY);
	cfg_serveur.sin_port = htons(port);

	// Attachement de la socket au port d�fini
	bind(sd_serveur, (struct sockaddr*)&cfg_serveur, sizeof(cfg_serveur));

	// Cr�ation une file d'attente de connexion
	listen(sd_serveur, 5);
}

void TCP::init()
{
	robot = new Robot();
}

void TCP::creation_new_socket()
{
	//Tant que le bouton n'est pas enfonce
	while (this->activation == false)
	{

		// D�s qu�un nouveau client se connecte � notre serveur,
		// une nouvelle socket est cr��e pour g�rer le client
		//accept fonction bloquante et tant qu'il n'y a personne en file d'attente, il attent ?
		sd_client = accept(sd_serveur, NULL, NULL);

		while (this->activation2 == false)
		{
			// R�ception de la requ�te du client(decrypte)
			std::string _reponse = this->reception_requete_client();
			_reponse = this->reponse;

			//verification si l'utilisateur appui sur deconnexion et donc qu'il m'envoi une trame == "deconnecte"
			if (reponse == "deconnecte")
			{
				//Envoyer la r�ponse au client(deconnecte)
				reponse = "deconnexion";

				//Envoyer la r�ponse au client(informations capteurs)
				this->envoi_reponse_client(reponse);

				//Sortir de la boucel while
				this->activation2 = true;
			}
			else
			{
				//Si c est egale � une des requetes qui correspond au actions du robot, appel fonction robot correspondante
				//...
				// Si ca c est bien passe, envoi "ok" sinon "erreur" + action effectue : "avance, recule, gauche, droite, tourner..." 
				this->envoi_reponse_client(reponse);

				//Si la requete correspond � une demande d'information, alors appele methode robot pour recuperer informations
				//...
				// Si ca c est bien passe, envoi "ok" sinon "erreur" + les donnees
				this->envoi_reponse_client(reponse);
			}
		}

		//Reactivation de activation2 pour re-rentrer dans boucle
		this->activation2 = false;

		//fermeture client pour en attendre un autre
		this->close_socket_client();

		//Si le bouton centrale est enfonce alors on ferme le socket et fin
		if (robot->recupererEtatBoutonCentral() == true)
		{
			this->close_socket_serveur();
			this->activation = true;
			//voir pour afficher sur ecran robot que socket reseau serveur ferme donc on peut eteindre robot
			//Si on le reutilise il faut le rallumer pour remettre � 0
			//...12
		}
	}
}

std::string TCP::reception_requete_client()
{
	// R�ception de la requ�te du client
	char buffer[1024];
	memset(buffer, 0x00, 1024);
	int nbOctets = recv(sd_client, buffer, sizeof(buffer), 0);
	std::string reponse(buffer);
	std::cout << reponse << std::endl;
	return reponse;
}

std::string TCP::envoi_reponse_client(std::string requetes)
{
	// Envoi de la r�ponse au client
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

TCP::~TCP()
{
	delete robot;
}



