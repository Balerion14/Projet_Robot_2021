#ifndef FILE_H
#define FILE_H

#include "liste.h"

using namespace std;

// D�finition du modele de la classe File
template <typename T>
class File
{
private:
    Liste <T> liste;

public:

    /**
     * M�thode pour ajouter un element dans la file d'attente
     * @param valeur noeud(n'importe quel type)
     * @return rien
     */
    void enfiler(const T& valeur);

    /**
     * M�thode pour supprimer un element en tete de liste dans la file d'attente
     * @param aucun
     * @return rien
     */
    void defiler();

    /**
     * M�thode pour afficher l'element en tete de liste dans la file d'attente
     * @param aucun
     * @return la valeur du noeud en tete de liste selon le type choisit
     */
    T& premier() const;

    /**
     * M�thode qui retourne la taille de la file d'attente
     * @param aucun
     * @return valeur int
     */
    int taille() const;

    /**
     * M�thode qui permet de savoir si la liste est vide ou non
     * @param aucun
     * @return true ou false(vide ou pas)
     */
    bool estVide() const;

    /**
     * M�thode qui permet d'afficher l'entierte de la file d'attente
     * @param aucun
     * @return rien
     */
    void afficher() const;
};

//Importation du fichier file.inl � la fin pour l'implementation des methodes de la classe generique file
#include "file.inl"

#endif


