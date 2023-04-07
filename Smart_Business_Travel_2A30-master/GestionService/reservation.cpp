#include "reservation.h"
#include "GestionService.h"
#include <QSqlQuery>
#include <QObject>
reservation::reservation()
{

}
reservation::reservation(QString ch1,QDate d1,QDate d2,int x,QString ch2,float y)
{
this->nom_service=ch1;
this->starting_date=d1;
this->ending_date=d2;
this->nb_personnes=x;
this->res_type=ch2;
this->price=y;
}
bool reservation::reserver()
{
    QSqlQuery query;
    QString res1=QString::number(nb_personnes);
    QString res2=QString::number(price);
    query.prepare("INSERT INTO RESERVATIONS (NOM_SERVICE,STARTING_DATE,ENDING_DATE,NB_PERSONNES,RESERVATION_TYPE,RESERVATION_PRICE)" "VALUES (:NOM,:sdate,:edate,:nb,:restype,:resprice)");
    query.bindValue(":NOM",nom_service);
    query.bindValue(":sdate",starting_date);
    query.bindValue(":edate",ending_date);
    query.bindValue(":nb",res1);
    query.bindValue(":restype",res_type);
    query.bindValue(":resprice",res2);
    return query.exec();                   //exec() envoie la requete pour l'éxecuter
}
