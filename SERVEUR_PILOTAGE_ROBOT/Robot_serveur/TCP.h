// Librairies utilis�es
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
	* param�tre int qui correspond au num�ro de port
	*/
	TCP(int port);

	/**
	* Destructeur de la classe "TCP"
	* Destruction des objets de la classe "TCP".
	* Aucun param�tre
	*/
	~TCP();

	/**
	* M�thode de la classe "TCP"
	* Cr�ation d'une socket de la classe "TCP".
	* Auncun param�tre
	*/
	void creation_new_socket();

	/**
	* M�thode de la classe "TCP"
	* Reception de la requete du client de la classe "TCP".
	* Auncun param�tre
	*/
	std::string reception_requete_client();

	/**
	* M�thode de la classe "TCP"
	* Envoi du message au client de la classe "TCP".
	* Auncun param�tre
	*/
	std::string envoi_reponse_client(std::string requetes);

	/**
	* M�thode de la classe "TCP"
	* Fermer socket  client de la classe "TCP".
	* Auncun param�tre
	*/
	void close_socket_client();

	/**
	* M�thode de la classe "TCP"
	* Fermer socket  serveur de la classe "TCP".
	* Auncun param�tre
	*/
	void close_socket_serveur();
};

