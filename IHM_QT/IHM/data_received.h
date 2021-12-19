#ifndef DATA_RECEIVED_H
#define DATA_RECEIVED_H

//Importation de bibliotèque
#include <QMainWindow>
#include <QDebug>

//CLasse data_received
class data_received
{
public:

    /*!
     *  Methode de la classe mainWindos qui gere la reception des donnees
     *  Aucun parametre
     *  return rien
     */
    data_received();

    /*!
     *  Methode de la classe mainWindos pour decrypte message
     *  message à decrypte
     *  return message decrypte
     */
    QString decrypter_data(QString data_crypted);

    /*!
     *  Methode de la classe mainWindos pour crypte message
     *  message à crypte
     *  return message crypte
     */
    QString crypter_data(QString data_crypted);

    /*!
     *  Methode de la classe mainWindos qui parcour la liste contenant les infos et recupere l'info
     *  Position dans la liste
     *  return donnee recuperee
     */
    QString parcour_liste(int position);

    /*!
     *  Methode de la classe mainWindos pour separer chaque info de la liste(;)
     *  message à decrypte
     *  return rien
     */
    void separer_data(QString message_recu);

    /*!
     *  Methode de la classe mainWindos qui retourne la liste des infos
     *  aucun
     *  return liste
     */
    QStringList _liste();

private:

    //Attribut classe
    QStringList liste;
    QChar key_cryptage = 'x';
};

#endif // DATA_RECEIVED_H
