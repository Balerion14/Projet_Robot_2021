/**
 * @file hello_world.cpp
 * @brief Le classique des classiques
 * @author Benaitier Loris
 * @date 25/02/2019
 * @version 0.2
 *
 * Affiche un message dans la console.
 * Il sert surtout � valider l'installation de la cha�ne de d�veloppement crois�e
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
    serveur.creation_new_socket();
    
    // Fin du programme
    return 0;
}
