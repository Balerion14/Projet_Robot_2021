/**
 * @file robot.cpp
 * @brief Impl�mentation de la classe Robot
 * @author David SALLE
 * @date 25/02/2010
 * @version 0.2
 *
 * Cette classe Robot formera une sur-couche � l'ensemble des classes ev3dev
 * et facilitera ainsi le d�veloppement des programmes pour les "challenges"
 */

 // Librairies utilis�es
#include "Robot.h"


//==============================================================================
// M�thodes constructeur et desctructeur
//==============================================================================
Robot::Robot()
{

	// Instanciations dynamiques des objets "moteurs" selon leurs ports de sortie respectifs
	pMoteurGauche = new large_motor("ev3-ports:outA");			// "outA"
	pMoteurCentral = new medium_motor("ev3-ports:outB");	// "outB"
	pMoteurDroit = new large_motor("ev3-ports:outC");			// "outC"

	// V�rifications de la pr�sence des moteurs
	if (pMoteurGauche->connected() == false)
	{
		cout << "ERREUR => Le moteur gauche ne semble pas pr�sent (port A)" << endl;
	}
	if (pMoteurCentral->connected() == false)
	{
		cout << "ERREUR => Le moteur central ne semble pas pr�sent (port B)" << endl;
	}
	if (pMoteurDroit->connected() == false)
	{
		cout << "ERREUR => Le moteur droit ne semble pas pr�sent (port C)" << endl;
	}

	// Initialisations des moteurs
	initialiserMoteurs();

	// V�rification de la pr�sence des capteurs
	if (capteurAngle.connected() == false)
	{
		cout << "ERREUR => Le capteur d'angle ne semble pas pr�sent" << endl;
	}
	else
	{
		initialiserGyroscope();
	}

	if (capteurContact.connected() == false)
	{
		cout << "ERREUR => Le capteur de contact ne semble pas pr�sent" << endl;
	}
	if (capteurCouleur.connected() == false)
	{
		cout << "ERREUR => Le capteur de couleur ne semble pas pr�sent" << endl;
	}
	if (capteurDistance.connected() == false)
	{
		cout << "ERREUR => Le capteur de distance ne semble pas pr�sent" << endl;
	}
}


Robot::~Robot()
{
	// Destruction des objets "moteurs"
	delete pMoteurGauche;
	delete pMoteurCentral;
	delete pMoteurDroit;
}


//==============================================================================
// M�thodes utilitaires
//==============================================================================
void Robot::attendre(int delai_en_millisecondes)
{
	this_thread::sleep_for(chrono::milliseconds(delai_en_millisecondes));
}


//==============================================================================
// M�thodes pour g�rer le gyroscope
//==============================================================================
int Robot::recupererGyroscopeAngle()
{
	return capteurAngle.angle();
}


int Robot::recupererGyroscopeVitesse()
{
	return capteurAngle.rate();
}


void Robot::initialiserGyroscope()
{
	capteurAngle.set_mode(capteurAngle.mode_gyro_cal);
	capteurAngle.set_mode(capteurAngle.mode_gyro_ang);
}


//==============================================================================
// M�thodes pour g�rer le capteur de contact
//==============================================================================
bool Robot::recupererEtatCapteurContact()
{
	return capteurContact.is_pressed();
}


//==============================================================================
// M�thodes pour g�rer le capteur de couleur
//==============================================================================
int Robot::recupererLumiereReflechie()
{
	return capteurCouleur.reflected_light_intensity();
}

int Robot::recupererLumiereAmbiante()
{
	return capteurCouleur.ambient_light_intensity();
}

int Robot::recupererCouleurCode()
{
	return capteurCouleur.color();
}

int Robot::recupererCouleurRouge()
{
	return capteurCouleur.red();
}

int Robot::recupererCouleurVerte()
{
	return capteurCouleur.green();
}

int Robot::recupererCouleurBleue()
{
	return capteurCouleur.blue();
}


//==============================================================================
// M�thodes pour g�rer le capteur de distance (ultrason)
//==============================================================================
float Robot::recupererDistance()
{
	return capteurDistance.distance_centimeters();
}


//==============================================================================
// M�thodes pour g�rer la batterie
//==============================================================================
float Robot::recupererBatterieTension()
{
	return power_supply::battery.measured_volts();
}

float Robot::recupererBatterieIntensite()
{
	return power_supply::battery.measured_amps();
}


//==============================================================================
// M�thodes pour g�rer l'�cran LCD
//==============================================================================
void Robot::allumerPixel(int x, int y)
{
	if ((x >= 0) && (x < 178) && (y >= 0) && (y < 128))
	{
		unsigned char* pFB = ecran.frame_buffer();
		pFB[(x / 8) + (y * 24)] = 1 << (x % 8);
	}
}

void Robot::eteindrePixel(int x, int y)
{
	if ((x >= 0) && (x < 178) && (y >= 0) && (y < 128))
	{
		unsigned char* pFB = ecran.frame_buffer();
		pFB[(x / 8) + (y * 24)] = 0 << (x % 8);
	}
}


//==============================================================================
// M�thodes pour g�rer les boutons
//==============================================================================
bool Robot::recupererEtatBoutonHaut()
{
	return button::up.pressed();
}

bool Robot::recupererEtatBoutonBas()
{
	return button::down.pressed();
}

bool Robot::recupererEtatBoutonDroite()
{
	return button::right.pressed();
}

bool Robot::recupererEtatBoutonGauche()
{
	return button::left.pressed();
}

bool Robot::recupererEtatBoutonCentral()
{
	return button::enter.pressed();
}

bool Robot::recupererEtatBoutonRetour()
{
	return button::back.pressed();
}


//==============================================================================
// M�thodes pour g�rer les leds
//==============================================================================
void Robot::allumerLed(Emplacement e, Couleur c)
{
	if ((e == GAUCHE) && (c == ROUGE))
	{
		led::red_left.on();
	}
	if ((e == GAUCHE) && (c == VERTE))
	{
		led::green_left.on();
	}
	if ((e == DROITE) && (c == ROUGE))
	{
		led::red_right.on();
	}
	if ((e == DROITE) && (c == VERTE))
	{
		led::green_right.on();
	}
}

void Robot::eteindreLed(Emplacement e, Couleur c)
{
	if ((e == GAUCHE) && (c == ROUGE))
	{
		led::red_left.off();
	}
	if ((e == GAUCHE) && (c == VERTE))
	{
		led::green_left.off();
	}
	if ((e == DROITE) && (c == ROUGE))
	{
		led::red_right.off();
	}
	if ((e == DROITE) && (c == VERTE))
	{
		led::green_right.off();
	}
}


//==============================================================================
// M�thodes pour g�rer le son
//==============================================================================
void Robot::emettreSon(float frequence, float duree, bool synchrone)
{
	sound::tone(frequence, duree, synchrone);
}

void Robot::parler(string phrase, bool synchrone)
{
	sound::speak(phrase, synchrone);
}

void Robot::lireFichierSon(string nomFichier, bool synchrone)
{
	sound::play(nomFichier, synchrone);
}


//==============================================================================
// M�thodes pour g�rer les moteurs
//==============================================================================
void Robot::initialiserMoteurs()
{
	// R�-initialisation des 3 moteurs
	pMoteurGauche->reset();
	pMoteurCentral->reset();
	pMoteurDroit->reset();
}

void Robot::changerPuissanceMoteurs(int puissanceGauche, int puissanceCentrale, int puissanceDroite)
{
	// Seuillage des puissances (au cas o�)
	if (puissanceGauche < -100)
	{
		puissanceGauche = -100;
	}
	if (puissanceCentrale < -100)
	{
		puissanceCentrale = -100;
	}
	if (puissanceDroite < -100)
	{
		puissanceDroite = -100;
	}
	if (puissanceGauche > 100)
	{
		puissanceGauche = 100;
	}
	if (puissanceCentrale > 100)
	{
		puissanceCentrale = 100;
	}
	if (puissanceDroite > 100)
	{
		puissanceDroite = 100;
	}

	// Modification de la puissance des moteurs...
	pMoteurGauche->set_duty_cycle_sp(puissanceGauche);
	pMoteurCentral->set_duty_cycle_sp(puissanceCentrale);
	pMoteurDroit->set_duty_cycle_sp(puissanceDroite);

	// ...et application
	pMoteurGauche->run_direct();
	pMoteurDroit->run_direct();
	pMoteurCentral->run_direct();
}

int Robot::recupererPositionDuMoteur(Emplacement e)
{
	if (e == GAUCHE)
	{
		return pMoteurGauche->position();
	}
	if (e == CENTRE)
	{
		return pMoteurCentral->position();
	}
	if (e == DROITE)
	{
		return pMoteurDroit->position();
	}
}

void Robot::recupererPositionsDesMoteurs(int& positionGauche, int& positionCentre, int& positionDroite)
{
	positionGauche = pMoteurGauche->position();
	positionCentre = pMoteurCentral->position();
	positionDroite = pMoteurDroit->position();
}

std::array<int, 5> Robot::Renvoi_infos_capteur()//&
{
	//Declaration tableau
	std::array<int, 5> tableau;

	//Ajout des informations des capteurs dans le tableau
    //Recuperer angle moteur
	tableau[0] = recupererPositionDuMoteur(GAUCHE);
	tableau[1] = recupererPositionDuMoteur(DROITE);

	//Distance obstacle(*10 : centimetre->milim�tre) et toux de snirium
	tableau[2] = recupererDistance() * 10;
	tableau[3] = recupererGyroscopeAngle();
	tableau[4] = recupererLumiereAmbiante();

	//Retourner tableau de valeur des capteurs
	return tableau;
}

void Robot::do_action_robot(std::string requete)
{
	//Choix de l'action � r�aliser en fonction de la requete
	switch (requete[0])
	{
	case AVANCER:

		//Puissance moteur pour aller tout droit
		changerPuissanceMoteurs(100, 0, 100);

		//Message debug
		cout << "avancer   _" << endl;

		//Sortir du cas
	    break;

	case RECULER:

		//Puissance moteur pour reculer
		changerPuissanceMoteurs(-100, 0, -100);

		//Message debug
		cout << "reculer   _" << endl;

		//Sortir du cas
		break;

	case GAUCHES:

		//Puissance moteur pour aller � gauche
		changerPuissanceMoteurs(-100, 0, 100);

		//Message debug
		cout << "gauche   _" << endl;

		//Sortir du cas
		break;

	case DROITES:

		//Puissance moteur pour aller � droite
		changerPuissanceMoteurs(100, 0, -100);

		//Message debug
		cout << "droit   _" << endl;

		//Sortir du cas
		break;
		
	case STOP:

		//Puissance moteur arreter le robot
		changerPuissanceMoteurs(0, 0, 0);

		//Message debug
		cout << "stop   _" << endl;

		//Sortir du cas
		break;

	case RAISE_ARM:

		//Puissance moteur pour monter bras
		changerPuissanceMoteurs(0, 100, 0);

		//Message debug
		cout << "monter bras   _" << endl;

		//Sortir du cas
		break;

	case GO_DOWN_ARM:

		//Puissance moteur pour descendre bras
		changerPuissanceMoteurs(0, -100, 0);

		//Message debug
		cout << "descendre bras   _" << endl;

		//Sortir du cas
		break;

	default:

		//Puissance moteur pour aller tout droit
		changerPuissanceMoteurs(0, 0, 0);

		//Message debug
		cout << "commande pas default stop   _" << endl;

		//Sortir du cas
		break;
	}
}

std::string Robot::transforme_CSV(const std::array<int, 5> & n)
{
	// Construction de la cha�ne de caract�res en m�moire
	ostringstream preparation;
	preparation << n.at(0) << ";" << n.at(1)<< ";"<< n.at(2)<< ";"<< n.at(3)<< ";" << n.at(4) << ";";

	// Transformation de la cha�ne pr�par�e en string
	string chaine = preparation.str();

	//Return la chaine avec les informations du capteur en csv
	return chaine;
}

std::string Robot::evaluate_action_robot(std::string requete)
{
	//Si la requetes est egale � 'T' alors on appelle la methode qui recup�re transforme csv et recup capteurs
	if (requete[0] == SEND_INFOS)
	{
		//Message debug
		std::cout << "transformation-csv   _" << endl;

		return transforme_CSV(Renvoi_infos_capteur());
	}
	//Sinon on fait appelle � la methode qui g�re les actions du robot
	else
	{
		//Message debug
		std::cout << "action-effectue-dans-robot   _" << endl;

		return "-action_effectue";
	}
}

float Robot::recup_frequence(float _frequence)
{
	frequence = _frequence;
	return frequence;
}

