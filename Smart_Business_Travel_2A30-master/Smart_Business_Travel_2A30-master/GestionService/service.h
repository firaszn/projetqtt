#ifndef SERVICE_H
#define SERVICE_H
#include <iostream>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
//#include <>
class service
{
private:
    int id;
    int nb_places;
    QString nom,type;
    QString disponibility;
public:
    //Constructors:
    service();
    service(int,QString,QString,QString,int);
    //Getters:
    int getId(){return id;}
    QString getNom(){return nom;}
    QString getDispo(){return disponibility;}
    int getNb_places(){return nb_places;}
    QString getType(){return type;}
    //Setters:
    void  setId(int ident){id=ident;}
    void setNom(QString n){nom=n;}
    void setDispo(QString d){ disponibility=d;}
    void setType(QString t){type=t;}
    void setNb(int nb){nb_places=nb;}
    bool ajouter();
    bool supprimer(int);
    QSqlQueryModel * afficher();
    QSqlQueryModel* chercher (QString rech);
    QSqlQueryModel* chercherSelonId (QString rech);
    bool modify();

};
class specification
{
QString service_name;
QString spec;
int vacancies;
float price;
public:
specification();
specification(QString,QString,int,float);
bool ajouter();
};

#endif // SERVICE_H
