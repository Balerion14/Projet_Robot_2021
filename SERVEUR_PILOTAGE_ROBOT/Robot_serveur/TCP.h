#ifndef TCP_H
#define TCP_H

// Librairies utilisées
#include <iostream>
#include <unistd.h>
#include <cerrno>
#include <sys/un.h>
#include <arpa/inet.h>
#include <array>
#include <cstdlib>		// pour srand() et rand()
#include <ctime>		// pour time()
#include <pthread.h>
#include <semaphore.h>
#include "Robot.h"
#include "file.h"

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
	bool erreur{ false };

	int compteur_tour{0};

	std::string message { "" };
	std::string message_crypte{ "" };
	std::string message_after_process{ "" };

	int time_start{};
	int time_end{};
	int time_total{};
};

//Structure pour les threads
typedef struct thread_
{
	//Partie tampon
	sem_t mon_semaphore_tampon;
	pthread_spinlock_t slock_tampon;

	//Partie producteur
	sem_t mon_semaphore_productueur;
	pthread_spinlock_t product;

	//-------------------------------------
	
	//Partie gestion robot
	sem_t mon_semaphore_robot;
	pthread_spinlock_t robot;

	//Partie gestion connexion
	sem_t mon_semaphore_connexion;
	pthread_spinlock_t connexion;

	//Partie gestion deconnexion
	sem_t mon_semaphore_deconnexion;
	pthread_spinlock_t deconnexion;

	//Partie gestion erreur
	sem_t mon_semaphore_erreur;
	pthread_spinlock_t erreur;

	//------------------------------------

	//Partie consomateur
	sem_t mon_semaphore_consomateur;
	pthread_spinlock_t conso;

	//Partie new client
	pthread_spinlock_t slock_client;
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
	thread_* processus;
	File <string> file;
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
	* Attente client de la classe "TCP".
	* Auncun paramètre
	*/
	void wait_client();

	/**
	* Méthode de la classe "TCP"
	* recevoir message pour la mise en tampon client de la classe "TCP".
	* Auncun paramètre
	*/
	void received_message();

	/**
	* Méthode de la classe "TCP"
	* gestion deconnexion avec thread de la classe "TCP".
	* Auncun paramètre
	*/
	void gestion_deconnexion();

	/**
	* Méthode de la classe "TCP"
	* gestion connexion avec thread de la classe "TCP".
	* Auncun paramètre
	*/
	void gestion_connexion();

	/**
	* Méthode de la classe "TCP"
	* gestion information robot avec thread de la classe "TCP".
	* Auncun paramètre
	*/
	void gestion_info_robot();

	/**
	* Méthode de la classe "TCP"
	* gestion erreur avec thread de la classe "TCP".
	* Auncun paramètre
	*/
	void gestion_erreur();

	/**
	* Méthode de la classe "TCP"
	* Nouveau client de la classe "TCP".
	* Auncun paramètre
	*/
	void new_client();//

	/**
	* Méthode de la classe "TCP"
	* Recevoir et traiter donnees de la classe "TCP" avec la creation de differents threads.
	* Auncun paramètre
	*/
	void producteur_traitement_data();//

	/**
	* Méthode de la classe "TCP"
	* lecture et envoie les donnees de la classe "TCP".
	* Auncun paramètre
	*/
	void consomateur_lecture_envoi_data();//

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
	void envoi_reponse_client(std::string requetes);

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

	/**
	* Méthode de la classe "TCP"
	* Cryptage message en XOR "TCP".
	* string reponse
	*/
	std::string crypte_reponse(std::string reponse);

	/**
	* Méthode de la classe "TCP"
	* Décryptage message en XOR "TCP".
	* string reponse
	*/
	std::string Decrypte_message(std::string message);

	/**
	* Méthode de la classe "TCP"
	* Demarage du timer en fonction de certaines situations "TCP".
	*/
	void Start_timer(std::string reponse);

	/**
	* Méthode de la classe "TCP"
	*Arret du timer en fonction de certaines situations "TCP".
	*/
	void End_timer();
};

/**
* Fonction pour new client avec appel du thread
* pointe sur la methode qui va traiter les donnee en argument.
* return void *
*/
inline void* nouveau_client(void* arg)
{
	TCP* new_clt = static_cast<TCP*>(arg);
	new_clt->new_client();
}

/**
* Fonction pour la gestion du tampon avec appel du thread
* pointe sur la methode qui va traiter les donnee en argument.
* return void *
*/
inline void* tampon_receveid(void* arg)
{
	TCP* new_clt = static_cast<TCP*>(arg);
	new_clt->received_message();
}

/**
* Fonction pour traitement donnee avec appel  thread
* pointe sur la methode qui va traiter les donnee en argument.
* return void *
*/
inline void* traiter_donnee(void* arg)
{
	TCP* process = static_cast<TCP*>(arg);
	process->producteur_traitement_data();
}

//----------------------------------------------------------

/**
* Fonction pour traitement donnee deconnexion avec appel  thread
* pointe sur la methode qui va traiter les donnee en argument.
* return void *
*/
inline void* traiter_donnee_deconnexion(void* arg)
{
	TCP* process = static_cast<TCP*>(arg);
	process->gestion_deconnexion();
}

/**
* Fonction pour traitement donnee connexion avec appel  thread
* pointe sur la methode qui va traiter les donnee en argument.
* return void *
*/
inline void* traiter_donnee_connexion(void* arg)
{
	TCP* process = static_cast<TCP*>(arg);
	process->gestion_connexion();
}

/**
* Fonction pour traitement donnee robot avec appel  thread
* pointe sur la methode qui va traiter les donnee en argument.
* return void *
*/
inline void* traiter_donnee_robot(void* arg)
{
	TCP* process = static_cast<TCP*>(arg);
	process->gestion_info_robot();
}

/**
* Fonction pour traitement donnee erreur avec appel  thread
* pointe sur la methode qui va traiter les donnee en argument.
* return void *
*/
inline void* traiter_donnee_erreur(void* arg)
{
	TCP* process = static_cast<TCP*>(arg);
	process->gestion_erreur();
}

//-----------------------------------------------------------

/**
* Fonction pour consommer donnee avec appel  thread
* pointe sur la methode qui va traiter les donnee en argument.
* return void *
*/
inline void* consommer_donnee(void* arg)
{
	TCP* consommer = static_cast<TCP*>(arg);
	consommer->consomateur_lecture_envoi_data();
}
#endif
