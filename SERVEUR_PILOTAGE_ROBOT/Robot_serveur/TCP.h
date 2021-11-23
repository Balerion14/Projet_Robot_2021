// Librairies utilisées
#include <iostream>
#include <unistd.h>
#include <cerrno>
#include <sys/un.h>
#include <arpa/inet.h>

//CLasse serveur TCP
class TCP
{
private:
	int sd_serveur{};
	int sd_client{};
	int port{};
	bool activation{ false };
	bool activation2{false};
	bool activation3{ false };
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

