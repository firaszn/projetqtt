#include "employe.h"
#include<QString>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>

employe::employe(int cin,QString nom,QString prenom,QString poste,int salaire,QString email,QString mdp,QString role,QString etat)
{
     this->cin=cin;
     this->nom=nom;
     this->prenom=prenom;
     this->poste=poste;
     this->salaire=salaire;
     this->email=email;
    this->mdp=mdp;
    this->role=role;
    this->etat=etat;

}
int employe:: getCIN(){return cin;}
QString employe:: getNom(){return nom ;}
QString employe::getPrenom(){return prenom ;}
QString employe:: getPoste(){return poste ;}
int employe:: getSalaire(){return salaire;}
QString employe::getEmail(){return email ;}
QString employe:: getmdp(){return mdp ;}
QString employe::getrole(){return role ;}
QString employe:: getetat(){return etat ;}

void employe:: setCIN(int cin){this->cin=cin;}
void employe:: setNom(QString nom){this->nom=nom;}
void employe:: setPrenom(QString prenom){this->prenom=prenom;}
void employe:: setPoste(QString poste){this->poste=poste;}
void employe:: setSalaire(int salaire){this->salaire=salaire;}
void employe:: setEmail(QString email){this->email=email;}
void employe:: setmdp(QString mdp){this->mdp=mdp;}
void employe:: setrole(QString role){this->role=role;}
void employe:: setetat(QString etat){this->etat=etat;}

bool employe :: ajouter()
{
    QSqlQuery query;
   QString res=QString::number(cin);

    query.prepare("insert into employee (cin, nom, prenom,poste,salaire,email,mdp,role,etat)" " VALUES (:cin, :nom, :prenom,:poste,:salaire, :email,:mdp,:role,:etat)");

    query.bindValue(":cin", res);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":poste",poste);
    query.bindValue(":salaire", salaire);
    query.bindValue(":email",email);
    query.bindValue(":mdp",mdp);
    query.bindValue(":role", role);
    query.bindValue(":etat",etat);
    return    query.exec();
        //affiche error
}
QSqlQueryModel * employe ::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM employee");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("cin"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("poste"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("salaire"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("email"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("mdp"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("role"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("etat"));






    return model;
}
bool employe :: supprimer (int cin )
{
    QSqlQuery query;
    QString res =QString::number(cin);
    query.prepare("Delete from employee where cin = :cin ");
    query.bindValue(":cin", res);
    return    query.exec();
}
bool employe::modifier(){

    QSqlQuery query;


    query.prepare(" UPDATE employee SET NOM=:NOM, PRENOM=:PRENOM,POSTE=:POSTE ,SALAIRE=:SALAIRE, EMAIL=:EMAIL , MDP=:MDP,ROLE=:ROLE,ETAT=:ETAT where CIN='"+QString::number(cin)+"'");

    query.bindValue(":CIN",QString::number(cin));
    query.bindValue(":NOM",nom);
    query.bindValue(":PRENOM",prenom);
    query.bindValue(":POSTE",poste);
    query.bindValue(":SALAIRE",salaire);
    query.bindValue(":EMAIL",email);
    query.bindValue(":MDP",mdp);
    query.bindValue(":ROLE", role);
    query.bindValue(":ETAT",etat);
    return query.exec();

}





QSqlQueryModel* employe::recherche(QString cas)
{
  QSqlQueryModel* model=new QSqlQueryModel();
QSqlQuery query;

 model->setQuery("SELECT * FROM EMPLOYEE WHERE (NOM LIKE '%"+cas+"%')");

   model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("poste"));
   model->setHeaderData(4, Qt::Horizontal, QObject::tr("salaire"));
   model->setHeaderData(5, Qt::Horizontal, QObject::tr("email"));
   model->setHeaderData(6,Qt::Horizontal,QObject::tr("mdp"));
   model->setHeaderData(7,Qt::Horizontal,QObject::tr("role"));
   model->setHeaderData(8,Qt::Horizontal,QObject::tr("etat"));

query.exec();
  return  model;




}


QSqlQueryModel *employe::tricin()
{
  QSqlQueryModel *model=new QSqlQueryModel();
  model->setQuery("SELECT * FROM EMPLOYEE ORDER BY cin");
  model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
  model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
  model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
  model->setHeaderData(3, Qt::Horizontal, QObject::tr("poste"));
  model->setHeaderData(4, Qt::Horizontal, QObject::tr("salaire"));
  model->setHeaderData(5, Qt::Horizontal, QObject::tr("email"));
  model->setHeaderData(6,Qt::Horizontal,QObject::tr("mdp"));
  model->setHeaderData(7,Qt::Horizontal,QObject::tr("role"));
  model->setHeaderData(8,Qt::Horizontal,QObject::tr("etat"));
        return model;
}






