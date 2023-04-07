#ifndef VOYAGE_H
#define VOYAGE_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include <QPrinter>
#include <QPainter>
#include <QPaintDevice>
#include <algorithm>

class Voyage
{
    QString flightref, lieudep, lieuarr, airline;
    QDate datedep, datearr;
    float montant;
    int nbper;

public:
    // Constructeurs
    Voyage();
    Voyage(QString, QString, QString, QDate, QDate, QString, float, int);

    // Getters
    QString getFlightref() { return flightref; }
    QString getLieudep() { return lieudep; }
    QString getLieuarr() { return lieuarr; }
    QString getAirline() { return airline; }
    QDate getDatedep() { return datedep; }
    QDate getDatearr() { return datearr; }
    float getMontant() { return montant; }
    int getNbper() { return nbper; }

    // Setters
    void setFlightref(QString f) { flightref = f; }
    void setLieudep(QString ld) { lieudep = ld; }
    void setLieuarr(QString la) { lieuarr = la; }
    void setAirline(QString a) { airline = a; }
    void setDatedep(QDate dd) { datedep = dd; }
    void setDatearr(QDate da) { datearr = da; }
    void setMontant(float m) { montant = m; }
    void setNbper(int n) { nbper = n; }

    // CRUD
    bool ajouter();
    QSqlQueryModel *afficher();
    bool supprimer(QString);
    bool update(QString ref);

    bool search(QString ref);
    QSqlQueryModel *sort(QString s);
    QList<Voyage> getDatabaseValues();
    QList<Voyage> getDatabaseValues_recherche(QString recher);
    QList<Voyage> getDatabaseValues_tri(QString order);
    int getDatabaseValue(QList<Voyage> Q, QString S);
    int getNeededDatabaseValue(QString s, QString condition);
    float calculerCoutMoyen(QString Sdep, QString Sarr);
    int row_number();
};

#endif // VOYAGE_H
