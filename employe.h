#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
#include<QString>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QFile>
#include <QIntValidator>
#include <QMessageBox>
#include <QDesktopServices>
#include <QFileDialog>
#include <QPushButton>
class employe
{
private :
    QString nom ,prenom ,poste ,email,mdp,role,etat;
    int cin, salaire;
public:
    employe(int,QString,QString,QString,int,QString,QString,QString,QString) ;
    employe(){};
    int getCIN();
    QString getNom();
    QString getPrenom();
    QString getPoste();
    int getSalaire();
    QString getEmail();
    QString getmdp();
    QString getrole();
    QString getetat();

    void setCIN(int  );
    void setNom(QString );
    void setPrenom(QString );
    void setPoste(QString );
    void setSalaire(int );
    void setEmail(QString );
    void setmdp(QString );
    void setrole(QString );
    void setetat(QString );




    bool ajouter();
    bool modifier();
         QSqlQueryModel * afficher();
          bool supprimer(int cin);
QSqlQueryModel*recherche(QString cas);
QSqlQueryModel *tricin();



};

#endif // EMPLOYE_H
