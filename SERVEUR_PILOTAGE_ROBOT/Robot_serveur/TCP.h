// Librairies utilis�es
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
	* Auncun param�tre
	*/
	TCP();

	/**
	* Destructeur de la classe "TCP"
	* Destruction des objets de la classe "TCP".
	* Auncun param�tre
	*/
	~TCP();

	/**
	* M�thode de la classe "TCP"
	* Configuration des param�tres de connexions de la classe "TCP".
	* Auncun param�tre
	*/
	void Configuration_settings();


};

