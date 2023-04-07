#include "client.h"
#include <QComboBox>
#include <QDebug>
client::client()
{

}
client::client(int i,QString n,QString e,QString nb)
{
    id=i;
    nom=n;
    email=e;
    numtel=nb;
}
void client::setid(int i)
{
    id=i;
}
void client::setnom(QString n)
{
    nom=n;
}
void client::setemail(QString e)
{
    email=e;
}
void client:: setnumtel(QString nb)
{
    numtel=nb;
}
void client:: setdatetime(QDateTime date)
{
    datetime=date;
}
int client:: getid()
{
    return  id;
}
QString client:: getnom()
{
    return nom;
}
QString client:: getemail()
{
    return email;
}
QString client:: getnumtel()
{
    return numtel;
}
QDateTime client:: getdatetime()
{
    return datetime;
}

bool client:: ajouter_client()
{
    QSqlQuery query;
    QDateTime dateTime = dateTime.currentDateTime();
    query.prepare("INSERT INTO client (nom,email,numtel,datecreation) " "VALUES (:nom,:email,:numtel,:date)");
    query.bindValue(":nom",nom);
    query.bindValue(":email",email);

  query.bindValue(":numtel", numtel);
    query.bindValue(":date",dateTime);

    return    query.exec();

}
bool client::modifier_client()
{
    QSqlQuery query;

          query.prepare("UPDATE client SET  nom=:nom , email=:email , numtel=:numtel WHERE id_client=:id_client  " );
           query.bindValue(":id_client", id);
           query.bindValue(":nom", nom);
           query.bindValue(":email", email);
           query.bindValue(":numtel", numtel);

          return query.exec();

}

bool client::supprimer_client(QString id)
{

    QSqlQuery query;
    QString res =id;
    query.prepare("DELETE from client where id_client = :id ");
    query.bindValue(":id",res);
    return    query.exec();

}
QSqlQueryModel * client:: afficher_client()
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from client");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Email"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Numero"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date Creation"));
if (model->rowCount()==0)
{
    QSqlQuery query; query.exec("DROP SEQUENCE CLIENT_SEQ");
    query.exec("CREATE SEQUENCE CLIENT_SEQ START WITH 1 INCREMENT BY 1 MINVALUE 0;");
}
    return model;
}
QSqlQueryModel * client:: afficher_client_voyageurs(QString id)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QString query = "select * from voyageurs where id_client = "+id;
model->setQuery(query);
model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("name"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("last_name"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("phone"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("gender"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("date_nais"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("mail"));
model->setHeaderData(7, Qt::Horizontal, QObject::tr("photo"));

    return model;
}
QSqlQueryModel * client:: afficher_nomclient()
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select nom from client");


    return model;
}
bool client::GetClient(QString id)
{
    QSqlQuery * query = new QSqlQuery();
    query->prepare("select * from client where id_client = :id");
    query->bindValue(":id",id);
    bool test=query->exec();
    if (test)
    {
        if (query->next())
        {
            this->setid(query->value("id_client").toInt());
            this->setnom(query->value("nom").toString());
            this->setemail(query->value("email").toString());
            this->setnumtel(query->value("numtel").toString());
            this->setdatetime(query->value("datecreation").toDateTime());
            return true;
           }
        return false;
    }
       else return test;
}
bool client::ajouter_voyageur_client(QString id)
{
    if (GetClient(id))
    {
    QSqlQuery * query = new QSqlQuery();
    query->prepare("select * from voyageurs WHERE id_client IS NULL");
        query->prepare("select * from employee WHERE cin=:cin AND NOT EXISTS(superviser.cin=:cin)");
    bool test=query->exec();
    if (test)
    {
    QStringList namelist;
    QMap<QString,int> voyageurs;

        while (query->next())
        {
            voyageurs.insert(query->value("name").toString()+" "+query->value("last_name").toString(),query->value("cin").toInt());
            namelist << (query->value("name").toString()+" "+query->value("last_name").toString());
        }
        if (!namelist.empty())
        {
        CustomDialog dialog(namelist);
        if (dialog.exec() == QDialog::Accepted)
        {
                QSqlQuery * sendadd = new QSqlQuery();
                sendadd->prepare("UPDATE voyageurs SET id_client=:id_client WHERE cin=:cin" );
                    sendadd->bindValue(":id_client",id);
                     sendadd->bindValue(":cin",voyageurs[dialog.comboBox()->currentText()]);

                     sendadd->exec();

            // take proper action here
            //qDebug() << dialog.comboBox()->currentText();
        }
        }




        return test;
    }
       else return test;
    }
    else return false;
}
QSqlQueryModel * client::AfficherT(QString order="nom")
{

    QSqlQueryModel * model = new QSqlQueryModel();
    QString query = "select * from client order by "+order;
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_client"));
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Numero"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date Creation"));
            return model;
}
QSqlQueryModel * client::AfficherTS(int)
{

    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from client where id_client = :id_client ");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Numero"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date Creation"));
            return model;
}
QSqlQueryModel * client::AfficherTA(int)
{

    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from client where id_client = :id_client ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Numero"));
                model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date Creation"));
            return model;
}
