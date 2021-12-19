#ifndef LISTE_H
#define LISTE_H

#include <iostream>
#include <cassert>

using namespace std;

// Définition du noeud en tant que struct
template <typename T>
struct Noeud
{
    T donnees;
    Noeud <T>* suivant;
};

// Définition du modèle de la classe Liste
template <typename T>
class Liste
{
private:
    Noeud <T>* entete;
    int compteur;
    Noeud <T>* CreerNoeud(const T& valeur);

public:

    /**
     * Constructeur de la classe liste pour l'initialisation
     * @param aucun
     * @return rien
     */
    Liste();

    /**
     * Destructeur de la classe liste pour l'initialisation
     * @param aucun
     * @return rien
     */
    ~Liste();

    /**
     * Methode pour inserer un noeud
     * @param postion
     * @param valeur
     * @return rien
     */
    void inserer(int pos, const T& valeur);

    /**
     * Methode pour supprimer un noeud
     * @param postion
     * @return rien
     */
    void supprimer(int pos);

    /**
     * Methode pour recuperer un noeud
     * @param postion
     * @return rien
     */
    T& getNoeud(int pos) const;

    /**
     * Methode pour afficher tous les noeuds
     * @param postion
     * @return rien
     */
    void afficher() const;

    /**
     * Methode pour recuperer la taille
     * @param postion
     * @return rien
     */
    int taille() const;
};

//Importation du fichier liste.inl à la fin pour l'implementation des methodes de la classe generique liste
#include "liste.inl"

#endif

