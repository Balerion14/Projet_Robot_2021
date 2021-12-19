/**
 * @file hello_world.cpp
 * @brief Le classique des classiques
 * @author Benaitier Loris
 * @date 18/12/2021
 * @version 0.2
 *
 * Affiche un message dans la console.
 * Il sert surtout à valider l'installation de la chaîne de développement croisée
 */

#include <iostream>
#include "Robot.h"
#include "TCP.h"

using namespace std;

int main()
{
    //declaration variable
    int port = 1664;

    //Creation objet pour le serveur
    TCP serveur(port);

    //Lancement socket serveur
    serveur.wait_client();
    
    // Fin du programme
    return 0;
}
