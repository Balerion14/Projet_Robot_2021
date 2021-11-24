// Librairies utilisées
#include <iostream>
#include <unistd.h>
#include <cerrno>
#include <sys/un.h>
#include <arpa/inet.h>
#include "Robot.h"

//structure de données
typedef struct Donnee
{
	bool activation{ false };
	bool activation2{ false };
	bool activation3{ false };
	bool activation4{ false };
	bool activation5{ false };
	bool activation6{ false };
	bool activation7{ false };
	int compteur_tour{0};
};

//CLasse serveur TCP
class TCP
{
private:
	int sd_serveur{};
	int sd_client{};
	int port{};
	std::string reponse{};
	Robot* robot;
	Donnee* donnee;
public:

	/**
	* Constructeur de la classe "TCP"
	* Initialisation du serveur tcp.
	* paramètre int qui correspond au numéro de port
	*/
	TCP(int port);

	/**
	* Destructeur de la classe "TCP"
	* Destruction des objets de la classe "TCP".
	* Aucun paramètre
	*/
	~TCP();

	/**
	* Methode de la classe "TCP"
	* Allocation dynamique des objets de la classe "TCP".
	* Aucun paramètre
	*/
	void init();

	/**
	* Méthode de la classe "TCP"
	* Création d'une socket de la classe "TCP".
	* Auncun paramètre
	*/
	void creation_new_socket();

	/**
	* Méthode de la classe "TCP"
	* Reception de la requete du client de la classe "TCP".
	* Auncun paramètre
	*/
	std::string reception_requete_client();

	/**
	* Méthode de la classe "TCP"
	* Envoi du message au client de la classe "TCP".
	* Auncun paramètre
	*/
	std::string envoi_reponse_client(std::string requetes);

	/**
	* Méthode de la classe "TCP"
	* Fermer socket  client de la classe "TCP".
	* Auncun paramètre
	*/
	void close_socket_client();

	/**
	* Méthode de la classe "TCP"
	* Fermer socket  serveur de la classe "TCP".
	* Auncun paramètre
	*/
	void close_socket_serveur();
};

