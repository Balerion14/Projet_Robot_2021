#include "data_received.h"
#include <sstream>
#include <iomanip>
#include <stdlib.h>





data_received::data_received()
{

}



QStringList data_received::data_received::_liste()
{
    return liste;
}



QString data_received::decrypter_data(QString data_crypted)
{
    //Declarations variables
    QString dec;

    for (int i = 0; i < data_crypted.size(); i++)
    {
        dec += QChar(data_crypted[i].toLatin1() ^ (static_cast<int>(key_cryptage.toLatin1()) + i) % 20);
    }

    //Retourner valeur crypte
    return dec;
}



void data_received::separer_data(QString data_crypted)
{
    // Recuperer chaque information contenu dans le qstring pour le mettre dans une liste(separation virgule)
    liste = data_crypted.split(";");
}



QString data_received::parcour_liste(int position)
{
    // Prendre l'information en fonction de la position a laquelle elle se trouve dans la liste
        for (int i = 0; i < liste.size(); ++i)
        {
            if( i == position)
            {
                return liste[i];
            }
        }
        return 0;
}
