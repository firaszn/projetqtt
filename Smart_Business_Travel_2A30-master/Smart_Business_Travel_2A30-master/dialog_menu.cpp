#include "dialog_menu.h"
#include "ui_dialog_menu.h"
#include"Gestion_Employee/gestion_employee.h"
#include "Gestion_Client/gestion_client.h"
#include "gestionVoyage/gestionVoyage.h"
#include "gestionVoyageur/gestionVoyageur.h"
#include "GestionService/GestionService.h"
#include<QMessageBox>
#include<string>
#include"login.h"
#include"ui_login.h"
#include <QDebug>
#include <QTimer>

QTimer logintime;
QString nom1,pass1;
Dialog_menu::Dialog_menu(QString nom,QString pass,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_menu)
{
    nom1= nom;    pass1= pass;
    ui->setupUi(this);

    Timer_TimeOut_Event_Slot();

    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(Timer_TimeOut_Event_Slot1()));
    timer->start();


}
//const QTime Start_timer =QTime::currentTime();

Dialog_menu::~Dialog_menu()
{

  /*  const QTime End_timer=QTime::currentTime();
    int h=End_timer.hour()-Start_timer.hour();
    int m=End_timer.minute()-Start_timer.hour();
    int s=End_timer.second()-Start_timer.second();

    qDebug()<<h;
    qDebug()<<m;
    qDebug()<<s;
    QMessageBox::critical(nullptr, QObject::tr("ERROR"),
                                    QObject::tr(h,m,s), QMessageBox::Ok);
  */
    delete ui;

}

void Dialog_menu::on_Buttonemploye_clicked()
{
    QString role = Get_Role_Menu(nom1,pass1);
    if(role=="Employe" || role=="Admin")
    {
     Gestion_Employee *gestion_employee=new Gestion_Employee(nom1,pass1);
     gestion_employee->show();
             forceclose=true;
             this->close();
    }
    else {QMessageBox::critical(nullptr, QObject::tr("ERROR"),
                                QObject::tr("NOT ADMIN"), QMessageBox::Ok); }
}

void Dialog_menu::on_Buttonclient_clicked()
{
   QString role = Get_Role_Menu(nom1,pass1);
   if(role=="Client" || role=="Admin")
   {
    Gestion_Client *gestion_client=new Gestion_Client(nom1,pass1);
    gestion_client->show();
    gestion_client->update();
        forceclose=true;
            this->close();
   }
   else {QMessageBox::critical(nullptr, QObject::tr("ERROR"),
                               QObject::tr("NOT ADMIN"), QMessageBox::Ok); }
}

void Dialog_menu::on_Buttonvouyage_clicked()
{
   QString role = Get_Role_Menu(nom1,pass1);
   if(role=="Voyage" || role=="Admin")
   {
    gestionVoyage *gestion_voyage=new gestionVoyage(nom1,pass1);
    gestion_voyage->show();
            forceclose=true;
            this->close();
   }
   else {QMessageBox::critical(nullptr, QObject::tr("ERROR"),
                               QObject::tr("NOT ADMIN"), QMessageBox::Ok); }
}



void Dialog_menu::Timer_TimeOut_Event_Slot()
{


    QTime time=QTime::currentTime();
    QString time_text=time.toString("hh : mm : ss");
    ui->time->setText(time_text);

    //qDebug() << "Timer Event Called";
}

void Dialog_menu::Timer_TimeOut_Event_Slot1()
{
    QTime time=QTime::currentTime();
    QString time_text=time.toString("hh : mm : ss");
    ui->time1->setText(time_text);

}

void Dialog_menu::on_Buttonvoyageur_clicked()
{
    QString role = Get_Role_Menu(nom1,pass1);
   if(role=="voyageur" || role=="Admin")
   {
    gestionVoyageur *gestion_voyageur=new gestionVoyageur(nom1,pass1);
    gestion_voyageur->show();
        forceclose=true;
            this->hide();
   }
   else {QMessageBox::critical(nullptr, QObject::tr("ERROR"),
                               QObject::tr("NOT ADMIN"), QMessageBox::Ok); }
}

QString Dialog_menu::Get_Role_Menu(QString nom,QString pass)
    {
       QSqlQuery qry;
       qry.exec("SELECT ROLE FROM EMPLOYEE WHERE (NOM = '"+nom+"') AND (MODE_PASS = '"+pass+"')");
       qry.first();
       return qry.value(0).toString();
    }

void Dialog_menu::on_Buttonservice_clicked()
{

        QString role = Get_Role_Menu(nom1,pass1);
       if(role=="serveur" || role=="Admin")
       {

        GestionService *gestion_service=new GestionService(nom1,pass1);
        gestion_service->show();
        forceclose=true;
        this->close();

       }
       else {QMessageBox::critical(nullptr, QObject::tr("ERROR"),
                                   QObject::tr("NOT ADMIN"), QMessageBox::Ok); }


}
void Dialog_menu::closeEvent(QCloseEvent *)
{


    if (!forceclose)
    {
        QMessageBox quitBox(
                    QMessageBox::Question,
                    tr("Select Action"),
                    tr("Select your action ?"),
                    QMessageBox::Yes | QMessageBox::No);
        quitBox.setButtonText(QMessageBox::Yes, tr("Log out"));
        quitBox.setButtonText(QMessageBox::No, tr("Quit"));
        if (quitBox.exec() == QMessageBox::Yes) {
        login *l=new login();
        l->show();
        }
    }
    this->close();
    //qApp->quit();

}
