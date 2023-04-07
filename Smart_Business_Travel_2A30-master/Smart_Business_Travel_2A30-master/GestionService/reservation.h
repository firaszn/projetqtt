#ifndef RESERVATION_H
#define RESERVATION_H

#include <QObject>
#include <QWidget>
#include <QString>
#include <QDate>
class reservation
{
QString nom_service;
QDate starting_date;
QDate ending_date;
int nb_personnes;
QString res_type;
float price;
public:
    reservation();
    reservation(QString,QDate,QDate,int,QString,float);
    bool reserver();
};

#endif // RESERVATION_H
