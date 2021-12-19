template <typename T>
void File <T> ::enfiler(const T& valeur)
{
    liste.inserer(liste.taille(), valeur);
}

template <typename T>
void File <T> ::defiler() {
    liste.supprimer(0);
}

template <typename T>
T& File <T> ::premier() const {
    return liste.getNoeud(0);
}

template <typename T>
bool File <T> ::estVide() const {
    if (liste.taille() == 0) { return true; }
    return false;
}

template <typename T>
int File <T> ::taille() const {
    return liste.taille();
}

template <typename T>
void File <T> ::afficher() const {
    liste.afficher();
}

