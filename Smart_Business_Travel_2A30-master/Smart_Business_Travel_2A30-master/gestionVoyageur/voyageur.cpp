#include "voyageur.h"
Voyageur::
 Voyageur::Voyageur()
{
 cin=0;name="";last_name="";phone=0;
 mail="";date_nais=QDate::currentDate();gender="";
}
Voyageur::Voyageur(int cin,int phone,QString name,QString last_name,QString mail,QString gender,QDate date_nais)
{
this->cin=cin;
this->phone=phone;
this->name=name;
this->last_name=last_name;
this->mail=mail;
this->date_nais=date_nais;
this->gender=gender;
}
int Voyageur::get_cin(){return cin;}
int Voyageur::get_phone(){return phone;}
QString Voyageur::get_name(){return name;}
QString Voyageur::get_last_name(){return last_name;}
QString Voyageur::get_mail(){return mail;}
QDate Voyageur::get_dt_naiss(){return date_nais;}
QString Voyageur::get_gender(){return gender;}
void Voyageur::set_cin(int cin){this->cin=cin;}
void Voyageur::set_phone(int phone){this->phone=phone;}
void Voyageur::set_name(QString name){this->name=name;}
void Voyageur::set_last_name(QString last_name){this->last_name=last_name;}
void Voyageur::set_mail(QString mail){this->mail=mail;}
void Voyageur::set_dt_naiss(QDate date_nais){this->date_nais=date_nais;}
void Voyageur::set_gender(QString gender){this->gender=gender;}
bool Voyageur::ajouter()
{

    QSqlQuery query;
    QString res= QString::number(get_cin());
    QString res1= QString::number(phone);
    query.prepare("INSERT INTO VOYAGEURS (cin,name,last_name,phone,mail,date_nais,gender)"
                  "VALUES(:cin,:name,:last_name,:phone,:mail,:date_nais,:gender)");
    query.bindValue(":cin",res);
    query.bindValue(":phone",res1);
    query.bindValue(":name",name);
    query.bindValue(":last_name",last_name);
    query.bindValue(":mail",mail);
    query.bindValue(":gender",gender);
    query.bindValue(":date_nais",date_nais);
    return query.exec();
}
QSqlQueryModel *Voyageur::afficher()
{
    QSqlQueryModel *model=new QSqlQueryModel();

          model->setQuery("SELECT* FROM VOYAGEURS ");

          model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("name"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("last_name"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("phone"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("gender"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("date_nais"));
          model->setHeaderData(6, Qt::Horizontal, QObject::tr("mail"));
          model->setHeaderData(7, Qt::Horizontal, QObject::tr("photo"));
          return  model;
}
bool Voyageur::supprimer(int cin)
{
    QSqlQuery query;
    query.prepare("DELETE FROM VOYAGEURS WHERE CIN=:cin");
    query.bindValue(":cin",cin);
    return query.exec();
}

bool Voyageur::update(Voyageur &v,int cin)
{

    QSqlQuery query;
    query.prepare("UPDATE VOYAGEURS SET name=:name,last_name=:last_name,phone=:phone,gender=:gender,date_nais=:date_nais,mail=:mail WHERE CIN=:cin");
    query.bindValue(":cin",QString::number(cin));
    query.bindValue(":phone",QString::number(phone));
    query.bindValue(":name",name);
    query.bindValue(":last_name",last_name);
    query.bindValue(":mail",mail);
    query.bindValue(":gender",gender);
    query.bindValue(":date_nais",date_nais);
    return query.exec();
}

QSqlQueryModel *Voyageur::tri()
{
    QSqlQueryModel *model=new QSqlQueryModel();

          model->setQuery("SELECT* FROM VOYAGEURS ORDER BY NAME");

          model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("name"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("last_name"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("phone"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("gender"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("date_nais"));
          model->setHeaderData(6, Qt::Horizontal, QObject::tr("mail"));
          model->setHeaderData(7, Qt::Horizontal, QObject::tr("photo"));
          return  model;


}
QVector<Voyageur> Voyageur::pdf()
{
    QVector<Voyageur> V={};

    QSqlQuery q;
    q.exec("SELECT * FROM VOYAGEURS");
    int size=0;
    while(q.next())
        size++;
    int it=0;
    q.first();
    while(it<size)
    {
        cin=q.value(0).toInt();
        name=q.value(1).toString();
        last_name=q.value(2).toString();
        phone=q.value(3).toInt();
        mail=q.value(4).toString();
        date_nais=q.value(5).toDate();
        gender=q.value(6).toString();
        V.append(Voyageur(cin,phone,name,last_name,mail,gender,date_nais));
        q.next();
        it++;
    }
    return V;
}

QSqlQueryModel *Voyageur::Historique_Voyage(int cin_v)
{

          QSqlQueryModel *model=new QSqlQueryModel();
          model->setQuery("SELECT * FROM VOYAGES WHERE FLIGHTREF= '"+QString::number(cin_v)+"'");

         // query.bindValue(":CIN", cin_v);

         /* model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("name"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("last_name"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("phone"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("gender"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("date_nais"));
          model->setHeaderData(6, Qt::Horizontal, QObject::tr("mail"));
          model->setHeaderData(7, Qt::Horizontal, QObject::tr("photo"));*/
          return  model;
}
