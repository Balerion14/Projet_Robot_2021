/**
 * @file robot.h
 * @brief D�finition de la classe Robot
 * @author David SALLE
 * @date 25/02/2019
 * @version 0.2
 *
 * Cette classe Robot formera une sur-couche � l'ensemble des classes ev3dev
 * et facilitera ainsi le d�veloppement des programmes pour  les "challenges"
 */
#ifndef ROBOT_H
#define ROBOT_H

 // Librairies utilis�es
#include <iostream>
#include <chrono>
#include <thread>
#include "ev3dev.h"

// Espaces de noms utilis�s
using namespace std;
using namespace ev3dev;

//Creation de macro associer � des valeurs qui correspondent � des actions
#define AVANCER Z;
#define RECULER S;
#define GAUCHES Q;
#define DROITES D;
#define STOP C;
#define RAISE_ARM A;
#define GO_DOWN_ARM E;
#define SEND_INFOS capteur;


// D�finition de la classe
class Robot
{
public:
	/**
	 * M�thode constructeur pour initialiser l'objet Robot
	 * @param aucun
	 * @return rien
	 *
	 * La m�thode v�rifie la pr�sence de tous les capteurs et actionneurs
	 * et signale d'�ventuels probl�me par un message sur la console
	 */
	Robot();

	/**
	 * M�thode destructeur
	 * @param aucun
	 * @return rien
	 */
	~Robot();

	/**
	 * M�thode pour attendre pendant un certain temps exprim� en millisecondes
	 * @param delai_en_millisecondes
	 * @return rien
	 */
	void attendre(int delai_en_millisecondes);



	/**
	* M�thode pour initialiser le capteur gyroscopique et remettre l'angle � 0
	* @param aucun
	* @return rien
	*/
	void initialiserGyroscope();

	/**
	 * M�thode pour r�cup�rer l'angle issu du capteur gyroscopique
	 * @param aucun
	 * @return l'angle du robot
	 */
	int recupererGyroscopeAngle();

	/**
	 * M�thode pour r�cup�rer la vitesse angulaire issue du capteur gyroscopique
	 * @param aucun
	 * @return la vitesse angulaire du robot
	 */
	int recupererGyroscopeVitesse();



	/**
	 * M�thode pour r�cup�rer l'�tat du capteur de contact
	 * @param aucun
	 * @return true si le capteur est enfonc�, false sinon
	 */
	bool recupererEtatCapteurContact();



	/**
	 * M�thode pour r�cup�rer la lumi�re r�fl�chie issue du capteur de couleur
	 * @param aucun
	 * @return la lumi�re r�fl�chie (0=noir � 100=blanc)
	 */
	int recupererLumiereReflechie();

	/**
	 * M�thode pour r�cup�rer la lumi�re ambiante issue du capteur de couleur
	 * @param aucun
	 * @return la lumi�re ambiante (0=noir � 100=blanc)
	 */
	int recupererLumiereAmbiante();

	/**
	 * M�thode pour r�cup�rer la couleur mesur�e par le capteur de couleur
	 * @param aucun
	 * @return la couleur (0=inconnue, 1=black, 2=blue, 3=green, 4=yellow, 5=red 6=white, 7=brown)
	 */
	int recupererCouleurCode();

	/**
	 * M�thode pour r�cup�rer la composante rouge mesur�e par le capteur de couleur
	 * @param aucun
	 * @return la composante rouge mesur�e par le capteur (0 � 1020)
	 */
	int recupererCouleurRouge();

	/**
	 * M�thode pour r�cup�rer la composante verte mesur�e par le capteur de couleur
	 * @param aucun
	 * @return la composante verte mesur�e par le capteur (0 � 1020)
	 */
	int recupererCouleurVerte();

	/**
	 * M�thode pour r�cup�rer la composante bleue mesur�e par le capteur de couleur
	 * @param aucun
	 * @return la composante bleue mesur�e par le capteur (0 � 1020)
	 */
	int recupererCouleurBleue();



	/**
	 * M�thode pour r�cup�rer la distance mesur�e en centim�tres
	 * @param aucun
	 * @return la distance en centim�tres
	 */
	float recupererDistance();



	/**
	 * M�thode pour r�cup�rer la tension dans la batterie
	 * @param aucun
	 * @return la tension en Volts
	 */
	float recupererBatterieTension();

	/**
	 * M�thode pour r�cup�rer l'intensit� dans la batterie
	 * @param aucun
	 * @return l'intensit� en Amp�res
	 */
	float recupererBatterieIntensite();



	/**
	 * M�thode pour allumer un pixel de l'�cran en x,y
	 * @param x
	 * @param y
	 * @return rien
	 */
	void allumerPixel(int x, int y);

	/**
	 * M�thode pour �teindre un pixel de l'�cran en x,y
	 * @param x
	 * @param y
	 * @return rien
	 */
	void eteindrePixel(int x, int y);



	/**
	 * M�thode pour r�cup�rer l'�tat du bouton du haut
	 * @param aucun
	 * @return true si le bouton est enfonc�, false sinon
	 */
	bool recupererEtatBoutonHaut();

	/**
	 * M�thode pour r�cup�rer l'�tat du bouton du bas
	 * @param aucun
	 * @return true si le bouton est enfonc�, false sinon
	 */
	bool recupererEtatBoutonBas();

	/**
	 * M�thode pour r�cup�rer l'�tat du bouton de droite
	 * @param aucun
	 * @return true si le bouton est enfonc�, false sinon
	 */
	bool recupererEtatBoutonDroite();

	/**
	 * M�thode pour r�cup�rer l'�tat du bouton de gauche
	 * @param aucun
	 * @return true si le bouton est enfonc�, false sinon
	 */
	bool recupererEtatBoutonGauche();

	/**
	 * M�thode pour r�cup�rer l'�tat du bouton central
	 * @param aucun
	 * @return true si le bouton est enfonc�, false sinon
	 */
	bool recupererEtatBoutonCentral();

	/**
	 * M�thode pour r�cup�rer l'�tat du bouton retour
	 * @param aucun
	 * @return true si le bouton est enfonc�, false sinon
	 */
	bool recupererEtatBoutonRetour();



	/**
	 * Enum�ration pour repr�senter l'emplacement d'une led/moteur du robot
	 *   GAUCHE=0
	 *   CENTRE=1
	 *   DROITE=2
	 */
	enum Emplacement { GAUCHE, CENTRE, DROITE };

	/**
	 * Enum�ration pour repr�senter la couleur d'une led du robot
	 *   ROUGE=0
	 *   VERTE=1
	 */
	enum Couleur { ROUGE, VERTE };

	/**
	 * M�thode pour allumer une led
	 * @param e emplacement de la led (GAUCHE ou DROITE)
	 * @param c couleur de la led (ROUGE ou VERTE)
	 * @return rien
	 */
	void allumerLed(Emplacement e, Couleur c);

	/**
	 * M�thode pour �teindre une led
	 * @param e emplacement de la led (GAUCHE ou DROITE)
	 * @param c couleur de la led (ROUGE ou VERTE)
	 * @return rien
	 */
	void eteindreLed(Emplacement e, Couleur c);



	/**
	 * M�thode pour �mettre un son
	 * @param frequence du son en Hertz
	 * @param dur�e du son en millisecondes
	 * @param synchrone : true=robot bloqu� pendant son, false=robot peut faire autre chose pendant son
	 * @return rien
	 */
	void emettreSon(float frequence, float duree, bool synchrone);

	/**
	 * M�thode pour faire parler le robot (avec une accent anglophone)
	 * @param phrase � prononcer
	 * @param synchrone : true=robot bloqu� pendant son, false=robot peut faire autre chose pendant son
	 * @return rien
	 */
	void parler(string phrase, bool synchrone);

	/**
	 * M�thode pour �mettre un son
	 * @param nomFichier � lire. Format MP3 accept�. Il faut t�l�verser le fichier MP3 dans le robot
	 * @param synchrone : true=robot bloqu� pendant son, false=robot peut faire autre chose pendant son
	 * @return rien
	 *
	 * Pour t�l�verser un fichier MP3 dans le robot on pourra utiliser la commande scp :
	 * $ scp meuh.mp3 robot@192.168.0.167:/home/robot/snir1/
	 */
	void lireFichierSon(string nomFichier, bool synchrone);



	/**
	 * M�thode pour initialiser les moteurs
	 * @param aucun
	 * @return rien
	 */
	void initialiserMoteurs();

	/**
	 * M�thode pour changer la puissance des 3 moteurs
	 * @param gauche puissance du moteur gauche (-100 � 100)
	 * @param centrale puissance du moteur central (-100 � 100)
	 * @param droite puissance du moteur droit (-100 � 100)
	 * @return rien
	 *
	 * L'utilisation des moteurs ce cette mani�re permet de faire autre chose
	 * en m�me temps (lire capteurs, faire calculs...) car le changement est tr�s bref.
	 * Les valeurs des puissances en pourcentage sont seuill�es entre -100 et 100
	 *
	 * Les emplacements des moteurs gauche et droit s'entendent avec le robot
	 * positionn� face � vous, boule directionnelle de votre c�t� et �cran
	 * lisible facilement (� l'endroit)
	 */
	void changerPuissanceMoteurs(int gauche, int centrale, int droite);

	/**
	 * M�thode pour r�cup�rer la position d'un moteur
	 * @param moteur (GAUCHE, CENTRE ou DROITE)
	 * @return la position en degr�s
	 */
	int recupererPositionDuMoteur(Emplacement e);

	/**
	 * M�thode pour r�cup�rer les positions des 3 moteurs
	 * @param positionGauche (pass�e par r�f�rence pour pouvoir r�cup�rer la valeur)
	 * @param positionCentre (pass�e par r�f�rence pour pouvoir r�cup�rer la valeur)
	 * @param positionDroite (pass�e par r�f�rence pour pouvoir r�cup�rer la valeur)
	 * @return rien
	 */
	void recupererPositionsDesMoteurs(int& positionGauche, int& positionCentre, int& positionDroite);

	/**
	* M�thode de la classe "Robot"
	* Renvoi les infos des capteurs dans un tableau "Robot".
	* return un std::array
	*/
	std::array<int, 5>& Renvoi_infos_capteur();

	/**
	* M�thode de la classe "Robot"
	* Effectue action robot de classe "Robot".
	* param�tre string requete
	* return rien
	*/
	void do_action_robot(std::string requete);

	/**
	* M�thode de la classe "Robot"
	* Transforme sous format CSV de la classe "Robot".
	* std::array
	* return rien
	*/
	std::string transforme_CSV(std::array<int, 5> & const);

	/**
	* M�thode de la classe "Robot"
	* Determine l'action du robot(renvoie d'infos ou bien action(avancee...)) "Robot".
	* string requete
	* return true == action(avance..) et false == renvoi infos capteur
	*/
	bool evaluate_action_robot(std::string requete);
	
	/**
	 * M�thode pour r�cup�rer attribut frequence
	 * @auncun parametre
	 * @return la frequence
	 */
	float recup_frequence(float _frequence);

private:
	// Attributs capteurs
	gyro_sensor capteurAngle;			// sur port 4
	touch_sensor capteurContact;		// sur port 1
	color_sensor capteurCouleur;		// sur port 3
	ultrasonic_sensor capteurDistance;	// sur port 2

	// Attributs �cran
	lcd ecran;

	// Attributs moteurs (voir constructeur)
	large_motor* pMoteurGauche;		// sur port A
	large_motor* pMoteurDroit;		// sur port C
	medium_motor* pMoteurCentral;	// sur port B

	//Attribut 
	float frequence{};
};


#endif


