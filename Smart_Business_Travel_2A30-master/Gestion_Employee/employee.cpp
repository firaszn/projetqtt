#include "Gestion_Employee/employee.h"
#include <QSqlQuery>
#include <QDebug>
#include <QObject>
#include <QFile>
#include <QIntValidator>
#include <QMessageBox>
#include <QDesktopServices>
#include <QFileDialog>
#include <QPushButton>

Employee::Employee()
{
    CIN=0; NOM=""; PRENOM=""; DATE_NAISSANCE=QDate::currentDate(); AGE=0; ROLE=""; EMAIL="";MODE_PASS="";NUM_TEL="";
}
Employee::Employee(int CIN,QString NOM,QString PRENOM,QDate DATE_NAISSANCE,int AGE,QString ROLE,QString EMAIL,QString MODE_PASS, QString NUM_TEL)
{
    this->CIN=CIN;
    this->NOM=NOM;
    this->PRENOM=PRENOM;
    this->DATE_NAISSANCE=DATE_NAISSANCE;
    this->AGE=AGE;
    this->ROLE=ROLE;
    this->EMAIL=EMAIL;
    this->MODE_PASS=MODE_PASS;
    this->NUM_TEL=NUM_TEL;

}
int Employee::getCIN(){return CIN;}
QString Employee::getNOM(){return NOM;}
QString Employee::getPRENOM(){return PRENOM;}
QDate Employee::getDATE_NAISSANCE(){return DATE_NAISSANCE;}
int Employee::getAGE(){return AGE;}
QString Employee::getROLE(){return ROLE;}
QString Employee::getEMAIL(){return EMAIL;}
QString Employee::getMODE_PASS(){return MODE_PASS;}
QString Employee::getNUM_TEL(){return NUM_TEL;}

void Employee::setCIN(int CIN){this->CIN=CIN;}
void Employee::setNOM(QString NOM){this->NOM=NOM;}
void Employee::setPRENOM(QString PRENOM){this->PRENOM=PRENOM;}
void Employee::setDATE_NAISSANCE(QDate DATE_NAISSANCE){this->DATE_NAISSANCE=DATE_NAISSANCE;}
void Employee::setAGE(int AGE){this->AGE=AGE;}
void Employee::setROLE(QString ROLE){this->ROLE=ROLE;}
void Employee::setEMAIL(QString EMAIL){this->EMAIL=EMAIL;}
void Employee::setMODE_PASS(QString MODE_PASS){this->MODE_PASS=MODE_PASS;}
void Employee::setNUM_TEL(QString NUM_TEL){this->NUM_TEL=NUM_TEL;}

bool Employee::ajouter()
{
    QSqlQuery query;
    QString CIN_string= QString::number(CIN);
        query.prepare("INSERT INTO EMPLOYEE (CIN, NOM, PRENOM, DATE_NAISSANCE, AGE, ROLE, EMAIL,MODE_PASS,NUM_TEL) "
                      "VALUES (:CIN, :NOM, :PRENOM, :DATE_NAISSANCE, :AGE, :ROLE, :EMAIL, :MODE_PASS, :NUM_TEL)");
        query.bindValue(":CIN", CIN_string);
        query.bindValue(":NOM", NOM);
        query.bindValue(":PRENOM", PRENOM);
        query.bindValue(":DATE_NAISSANCE", DATE_NAISSANCE);
        query.bindValue(":AGE", AGE);
        query.bindValue(":ROLE", ROLE);
        query.bindValue(":EMAIL", EMAIL);
        query.bindValue(":MODE_PASS", MODE_PASS);
        query.bindValue(":NUM_TEL", NUM_TEL);

    return query.exec();
}

bool Employee::supprimer(int cin)
{
    QSqlQuery query;
    QString CIN_string= QString::number(cin);
        query.prepare("DELETE FROM EMPLOYEE WHERE CIN='"+QString::number(cin)+"'");
        query.bindValue(":cin", cin);

    return query.exec();



}
QSqlQueryModel* Employee::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
        model->setQuery("SELECT* FROM employee");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date de naissance"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Age"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("Role"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("E-Mail"));
        model->setHeaderData(8, Qt::Horizontal, QObject::tr("Numéro de téléphone"));

    return model;
}


bool Employee::modifierE(int cin)
{
    QSqlQuery query;

        query.prepare("UPDATE EMPLOYEE SET NOM=:NOM, PRENOM=:PRENOM, DATE_NAISSANCE=:DATE_NAISSANCE, AGE=:AGE, ROLE=:ROLE , EMAIL=:EMAIL,MODE_PASS=:MODE_PASS , NUM_TEL=:NUM_TEL WHERE CIN= '"+QString::number(cin)+"'");
        query.bindValue(":CIN", QString::number(cin));
        query.bindValue(":NOM", NOM);
        query.bindValue(":PRENOM", PRENOM);
        query.bindValue(":DATE_NAISSANCE", DATE_NAISSANCE);
        query.bindValue(":AGE", AGE);
        query.bindValue(":ROLE", ROLE);
        query.bindValue(":EMAIL", EMAIL);
        query.bindValue(":MODE_PASS", MODE_PASS);
        query.bindValue(":NUM_TEL", NUM_TEL);


    return query.exec();
}

Employee Employee::recherche(int cin)
{

    QSqlQuery query;
    Employee E;
        query.prepare("SELECT * FROM EMPLOYEE WHERE CIN='"+QString::number(cin)+"'");
        query.exec();
        query.next();
        E.CIN=query.value(0).toInt();
        E.NOM=query.value(1).toString();
        E.PRENOM=query.value(2).toString();
        E.DATE_NAISSANCE=query.value(3).toDate();
        E.AGE=query.value(4).toInt();
        E.ROLE=query.value(5).toString();
        E.EMAIL=query.value(6).toString();
        E.MODE_PASS=query.value(7).toString();
        E.NUM_TEL=query.value(8).toString();


        return E;

}
QSqlQueryModel * Employee::affichersuper(QString cin)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QString query = "SELECT * from EMPLOYEE WHERE EMPLOYEE.CIN IN (Select cin_emp FROM superviser where cin_admin="+cin+")";
        model->setQuery(query);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date de naissance"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Age"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("Role"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("E-Mail"));
        model->setHeaderData(8, Qt::Horizontal, QObject::tr("Numéro de téléphone"));

    return model;
}
QSqlQueryModel * Employee::tri_cin()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * from EMPLOYEE order by CIN");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date de naissance"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Age"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("Role"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("E-Mail"));
        model->setHeaderData(8, Qt::Horizontal, QObject::tr("Numéro de téléphone"));

    return model;
}
QSqlQueryModel * Employee::tri_nom()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * from EMPLOYEE order by NOM");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date de naissance"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Age"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("Role"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("E-Mail"));
        model->setHeaderData(8, Qt::Horizontal, QObject::tr("Numéro de téléphone"));

    return model;
}
bool Employee::isAdmin(QString cin)
{
    QSqlQuery query;
    query.prepare("Select * FROM employee where cin=:cin");
    query.bindValue(":cin",cin);
    query.exec();
    query.next();
    if (query.value("role").toString()=="Admin")
        return true;
    return false;
}

bool Employee::superviser (QString cin ,QString nom,QString pass)
{
    QSqlQuery query;
    QSqlQuery adminquery;
    query.prepare("Select * FROM employee where NOT EXISTS(Select cin_emp FROM superviser where cin_emp=:cin) AND cin=:cin");
    adminquery.prepare("SELECT* from employee where NOM ='" + nom + "' and MODE_PASS ='" + pass + "' " );
    query.bindValue(":cin",cin);
    adminquery.exec();
    if(adminquery.next())
    {
     query.exec();
      if(query.next())
      {
          QMessageBox ver_Box(
                              QMessageBox::Question,
                              QObject::tr("Select Action"),
                              QObject::tr("voulez vous superviser cette utilisateur?"),
                              QMessageBox::Yes | QMessageBox::No);
                  if (ver_Box.exec() == QMessageBox::Yes)
                  {
                      QSqlQuery insert;
                      insert.prepare("INSERT INTO SUPERVISER (CIN_EMP, CIN_ADMIN) "
                                    "VALUES (:CIN_EMP, :CIN_ADMIN)");
                      insert.bindValue(":CIN_EMP", cin );
                      insert.bindValue(":CIN_ADMIN", adminquery.value("cin").toString());
                      return insert.exec();

                  }
      }
    }
    return false;

}


