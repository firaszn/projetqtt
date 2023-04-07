#ifndef VOYAGEUR_H
#define VOYAGEUR_H
#include <QImage>
#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include <QObject>
#include <QVector>



class Voyageur
{
public:
    Voyageur();
    Voyageur(int,int,QString,QString,QString,QString,QDate);
    int get_cin();
    int get_phone();
    QString get_name();
    QString get_last_name();
    QString get_mail();
    QDate get_dt_naiss();
    QString get_gender();
    void set_cin(int);
    void set_phone(int);
    void set_name(QString);
    void set_last_name(QString);
    void set_mail(QString);
    void set_dt_naiss(QDate);
    void set_gender(QString);
    bool ajouter();
    QSqlQueryModel *afficher();
    bool supprimer(int cin);
    bool update(    Voyageur &v,int cin);
    Voyageur search(int cin);
    QSqlQueryModel *tri();
    QVector<Voyageur> pdf();
    QSqlQueryModel *Historique_Voyage(int cin_v);
private:
    int cin;
    int phone;
    QString name,last_name,mail,gender;
    QDate date_nais;

};

#endif // VOYAGEUR_H
