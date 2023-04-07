#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>

class Employee
{
public:
    Employee();
    Employee(int,QString,QString,QDate,int,QString,QString,QString,QString);
    int getCIN();
    QString getNOM();
    QString getPRENOM();
    QDate getDATE_NAISSANCE();
    int getAGE();
    QString getROLE();
    QString getEMAIL();
    QString getMODE_PASS();
    QString getNUM_TEL();

    void setCIN(int);
    void setNOM(QString);
    void setPRENOM(QString);
    void setDATE_NAISSANCE(QDate);
    void setAGE(int);
    void setROLE(QString);
    void setEMAIL(QString);
    void setMODE_PASS(QString);
    void setNUM_TEL(QString);

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifierE(int);
    Employee recherche(int);
    QSqlQueryModel* tri_cin();
    QSqlQueryModel* tri_nom();
    QSqlQueryModel* affichersuper(QString);
    bool superviser(QString,QString,QString);
    bool isAdmin(QString cin);
private:
    int CIN,AGE;
    QString NOM, PRENOM,  ROLE, EMAIL, MODE_PASS , NUM_TEL;
    QDate DATE_NAISSANCE;
};

#endif // EMPLOYEE_H
