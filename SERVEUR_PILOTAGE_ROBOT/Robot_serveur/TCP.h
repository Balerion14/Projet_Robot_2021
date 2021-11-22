// Librairies utilisées
#include <iostream>
#include <unistd.h>
#include <cerrno>
#include <sys/un.h>
#include <arpa/inet.h>

class TCP
{
private:

public:

	/**
	* Constructeur de la classe "TCP"
	* Initialisation du serveur tcp.
	* Auncun paramètre
	*/
	TCP();

	/**
	* Destructeur de la classe "TCP"
	* Destruction des objets de la classe "TCP".
	* Auncun paramètre
	*/
	~TCP();

	/**
	* Méthode de la classe "TCP"
	* Configuration des paramètres de connexions de la classe "TCP".
	* Auncun paramètre
	*/
	void Configuration_settings();


};

