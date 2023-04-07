#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDateTime>
#include <QDialog>
#include <QHBoxLayout>
#include <QComboBox>
#include <QPushButton>
class client
{
public:
    client();
    client(int,QString,QString,QString);
    void setid(int);
    void setnom(QString);
    void setemail(QString);
    void setnumtel(QString);
    void setdatetime(QDateTime);
    int getid();
    QString getnom();
    QString getemail();
    QString getnumtel();
    QDateTime getdatetime();

    bool ajouter_client();
    bool ajouter_voyageur_client(QString);
    bool modifier_client();
    bool supprimer_client(QString);
    bool GetClient(QString);
    QSqlQueryModel * afficher_client();
    QSqlQueryModel * afficher_client_voyageurs(QString);
    QSqlQueryModel * afficher_nomclient();
    QSqlQueryModel * AfficherT(QString);
    QSqlQueryModel * AfficherTS(int);
    QSqlQueryModel * AfficherTA(int);


private:
    QString nom,email,numtel;
    int id;
    QDateTime datetime;
};
class CustomDialog : public QDialog
{
public:
    CustomDialog(const QStringList& items)
    {
        setLayout(new QHBoxLayout());

        box = new QComboBox;
        box->addItems(items);
        layout()->addWidget(box);
        QPushButton* ok = new QPushButton("ok");
        layout()->addWidget(ok);
        connect(ok, &QPushButton::clicked, this, [this]()
        {
           accept();
        });
    }

    QComboBox* comboBox() { return box; }

private:
    QComboBox* box;
};
#endif // CLIENT_H
