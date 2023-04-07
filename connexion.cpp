#include "connexion.h"
#include<QString>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
Connexion::Connexion()
{

}


bool Connexion::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Source_Projet2A");
db.setUserName("firass");//inserer nom de l'utilisateur
db.setPassword("firass");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;

    return  test;
}
