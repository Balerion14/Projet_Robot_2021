#ifndef DATA_RECEIVED_H
#define DATA_RECEIVED_H

#include <QMainWindow>

class data_received
{
public:

    data_received();
    QString decrypter_data(QString data_crypted);

    QString parcour_liste(int position);

    // Separation en ;
    void separer_data(QString message_recu);
    QStringList _liste();

private:

    QStringList liste;
    QChar key = 'x';

};

#endif // DATA_RECEIVED_H
