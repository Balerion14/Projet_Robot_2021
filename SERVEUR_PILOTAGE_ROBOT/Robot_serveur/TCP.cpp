#include "TCP.h"

TCP::TCP(int port)
{
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

void TCP::creation_new_socket()
{
	while (1)
	{
		//Si activation == false, sa veut dire que c est la premiere connexion donc on attent un mot de passe specifique pour se connecter au serveur afin de controler le robot
		//tant que ce n est pas welcome, alors le serveur sera en ecoute mais renverrant en reponse "erreur"
		//Si c est bon alors il renverra "connecte" et on quitera la boucle pour un session normale
		while (this->activation == false)
		{
			//Passage à false pour la remise à 0 de la valeur 
			this->activation3 = false;

			// une nouvelle socket est créée pour gérer le client
			//accept fonction bloquante et tant qu'il n'y a personne en file d'attente, il attent ?
			sd_client = accept(sd_serveur, NULL, NULL);

			// Réception de la requête du client(decrypte)
			std::string reponse = this->reception_requete_client();

			//si reponse == welcome alors activation == true
			if (reponse == "welcome")
			{
				this->activation == true;
				std::cout << "Connexion etabli entre le serveur et le client" << std::endl;

				//Envoyer la réponse au client(informations capteurs)
				reponse = "connecte";
				this->envoi_reponse_client(reponse);

				//Fermeture du socket client pour etre en attente d'un nouveau
				this->close_socket_client();

				break;
			}

			//Envoyer la réponse au client(informations capteurs)
			reponse = "erreur";
			this->envoi_reponse_client(reponse);

			//Fermeture du socket client pour etre en attente d'un nouveau
			this->close_socket_client();
		}

		//Si la premiere connexion est passée alors on peut effectue ces actions
		if (this->activation2 == true)//
		{
		    // Dès qu’un nouveau client se connecte à notre serveur,
			// une nouvelle socket est créée pour gérer le client
			//accept fonction bloquante et tant qu'il n'y a personne en file d'attente, il attent ?
			sd_client = accept(sd_serveur, NULL, NULL);

			// Réception de la requête du client(decrypte)
			std::string reponse = this->reception_requete_client();

			//Si la trame vaut "quite" alors c est la déconnexion et donc il faudra se reconnecter avec welcome
			if (reponse == "quit")
			{
				this->activation3 = true;
				this->activation2 = false;
				this->activation = false;
				reponse = "deconnecte";
				std::cout << "Connexion interrrompu entre le serveur et le client" << std::endl; 
				this->close_socket_client();
			}

			//Traduire la réponse pour savoir ce que doit faire le robot(appel classe robot)
			//...

			//Récuperers informations des capteurs et les stockers dans la variables locale "reponse" en remplacant sa valeurs d'origine
			//...

			//Envoyer la réponse au client(informations capteurs)
			this->envoi_reponse_client(reponse);

			//Fermeture du socket client pour etre en attente d'un nouveau
			this->close_socket_client();

			//Rebouclage en attente de clients(socket serveur fermer)
		}

		//Verification pour voir si l'utilisateur vient de quiter, alors
		if (this->activation3 != true)
		{
			//Passage à true apres avoir effectué la premiere connection
			this->activation2 == true;
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
	std::string requete = "Hello world!";
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
}



