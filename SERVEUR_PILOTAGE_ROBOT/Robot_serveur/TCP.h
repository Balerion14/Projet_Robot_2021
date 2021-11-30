#ifndef TCP_H
#define TCP_H

// Librairies utilis�es
#include <iostream>
#include <unistd.h>
#include <cerrno>
#include <sys/un.h>
#include <arpa/inet.h>
#include <array>
#include "Robot.h"

//structure de donn�es
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

	int time_start{};
	int time_end{};
	int time_total{};
};

//CLasse serveur TCP
class TCP
{
private:
	int sd_serveur{};
	int sd_client{};
	int _port{};
	std::string reponse{};
	char key_cryptage{ 'x' };
	Robot* robot;
	Donnee* donnee;
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
	* Methode de la classe "TCP"
	* Allocation dynamique des objets de la classe "TCP".
	* Aucun param�tre
	*/
	void init();

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

	/**
	* M�thode de la classe "TCP"
	* Cryptage message en XOR "TCP".
	* string reponse
	*/
	std::string crypte_reponse(std::string reponse);

	/**
	* M�thode de la classe "TCP"
	* D�cryptage message en XOR "TCP".
	* string reponse
	*/
	std::string Decrypte_message(std::string message);

	/**
	* M�thode de la classe "TCP"
	* Demarage du timer en fonction de certaines situations "TCP".
	*/
	void Start_timer(std::string reponse);

	/**
	* M�thode de la classe "TCP"
	*Arret du timer en fonction de certaines situations "TCP".
	*/
	void End_timer();
};
#endif
