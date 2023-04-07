#include "service.h"
#include <QSqlQuery>
#include <QObject>
#include <QtDebug>
#include <QString>
service::service()
{
id=0;
type="";
nom="";
disponibility="";
nb_places=0;
}
service::service(int id,QString type,QString nom,QString disponibility,int nb_places)
{
this->id=id;
this->type=type;
this->nom=nom;
this->disponibility=disponibility;
this->nb_places=nb_places;
}
bool service::ajouter()
{
    QSqlQuery query;
    QString res1=QString::number(nb_places);
    query.prepare("INSERT INTO SERVICES (SERVICE_ID,NOM,DISPONIBILITY,TYPE,NB_PLACES)" "VALUES (:id,:NOM,:DISPONIBILITY,:TYPE,:NB_PLACES)");
    query.bindValue(":id",id);
    query.bindValue(":NOM",nom);
    query.bindValue(":DISPONIBILITY",disponibility);
    query.bindValue(":TYPE",type);
    query.bindValue(":NB_PLACES",res1);
    return query.exec();                   //exec() envoie la requete pour l'éxecuter
}
bool specification::ajouter()
{
    QString  v=QString::number(vacancies);
    QString  p=QString::number(price);
QSqlQuery query;
query.prepare("INSERT INTO SPECIFICATIONS (SERVICE_NAME,SERVICE_SPEC,NB_PLACES,PRICE)" "VALUES (:name,:spec,:nb,:price)");
query.bindValue(":name",service_name);
query.bindValue(":spec",spec);
query.bindValue(":nb",v);
query.bindValue(":price",p);
return query.exec();
}
bool service::supprimer(int id)
{
QSqlQuery query;
QString res=QString::number(id);
query.prepare("DELETE from SERVICES where SERVICE_ID= :id");
query.bindValue(":id",res);
return query.exec();
}
QSqlQueryModel * service::afficher()
{
QSqlQueryModel* model=new QSqlQueryModel();
      model->setQuery("SELECT * FROM SERVICES");
      model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
      model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
      model->setHeaderData(2, Qt::Horizontal, QObject::tr("disponib"));
      model->setHeaderData(3, Qt::Horizontal, QObject::tr("Type"));
      model->setHeaderData(4, Qt::Horizontal, QObject::tr("Nombre de places"));
return model;
}
bool service::modify()
{
    QSqlQuery query;
        QString res= QString::number(id);
        QString res1=QString::number(nb_places);
        query.prepare("UPDATE SERVICES SET NOM=:NOM,PRICE=:PRICE,DISPONIBILITY=:DISPONIBILITY,TYPE=:TYPE,NB_PLACES=:NB_PLACES WHERE SERVICE_ID=:id");
        query.bindValue(":id",id);
        query.bindValue(":NOM",nom);
        query.bindValue(":DISPONIBILITY", disponibility );
        query.bindValue(":TYPE",type);
        query.bindValue(":NB_PLACES",res1);
        return query.exec();
}
QSqlQueryModel* service ::chercher (QString rech)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM SERVICES WHERE SERVICE_ID LIKE'%"+rech+"%' or NOM  LIKE'%"+rech+"%' or PRICE  LIKE'%"+rech+"%' or DISPONIBILITY  LIKE'%"+rech+"%' or TYPE  LIKE'%"+rech+"%' or NB_PLACES LIKE'%"+rech+"%' ");
    return model;
}
QSqlQueryModel* service ::chercherSelonId (QString rech)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM SERVICES WHERE SERVICE_ID LIKE'%"+rech+"%'");
    return model;
}
specification::specification()
{
service_name="";
spec="";
vacancies=0;
price=0;
}
specification::specification(QString ch1,QString ch2,int x,float z)
{
    this->service_name=ch1;
    this->spec=ch2;
    this->vacancies=x;
    this->price=z;
}
