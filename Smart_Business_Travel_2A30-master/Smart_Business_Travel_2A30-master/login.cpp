#include "login.h"
#include "ui_login.h"
#include "Gestion_Employee/gestion_employee.h"
#include "Gestion_Employee/employee.h"
#include <QMessageBox>
#include "dialog_menu.h"
#include "dialog_verriffication.h"
#include <QMovie>
#include <QDebug>


login::login(QWidget *employee) :
    QDialog(employee),
    ui(new Ui::login)
{
    ui->setupUi(this);
    QMovie* movie = new QMovie(":/gif4.gif");

    if (movie->isValid())
      {
        QLabel *label_gif= ui->label_gif;
       label_gif->setMovie(movie);
        movie->start();
      }
    style();


}

login::~login()
{
    delete ui;
}


void login::on_pushButton_LoginL_clicked()
{
     QString nom = ui->lineEdit_UsernameL->text();
     QString pass = ui->lineEdit_PasswordL->text();

         QSqlQuery query;

         if(query.exec("SELECT* from employee where NOM ='" + nom + "' and MODE_PASS ='" + pass + "' " ))
         {
             if(query.next())
             {
                 QMessageBox::information(nullptr, QObject::tr("DONE"),
                 QObject::tr("Logged In Successfully !"), QMessageBox::Ok);
                 dialog_menu=new Dialog_menu(nom,pass);
               // this->hide();
                 dialog_menu->show();
                 this->close();

             }
             else
             {
             QMessageBox::critical(nullptr, QObject::tr("ERROR"),
             QObject::tr("Login Failed !, Invalid username or MODE_PASS"), QMessageBox::Ok);
             }
         }

}

void login::on_oublier_clicked()
{
    D= new Dialog_verriffication();
    D->show();
    this->destroy();
}

void login::on_showpassword_clicked()
{
    if (ui->lineEdit_PasswordL->echoMode()==QLineEdit::Password)
    {
        ui->lineEdit_PasswordL->setEchoMode(QLineEdit::Normal);
    }
    else
    {
    ui->lineEdit_PasswordL->setEchoMode(QLineEdit::Password);
    }
}
void login::style()
{
    setStyleSheet(  "QMessageBox {"
                    "background-color:#05187A;"
                    "}"
                    "QDialog {"
                     "background-color:#1F408E;"
                     "}"
                        "QScrollArea #scrollAreaWidgetContents {"
                                     "background-color:#05187A;"
                                     "}"
                        "QWidget#Home,#Create,#Read,#Update,#Delete {"
                             "background-color:#1F408E;"
                             "}"
                    "QLabel {"
                         "color:white;"
                         "}");
    foreach(QLabel *label, findChildren<QLabel *>())
    {

    label->setFont(QFont("Outfit",-1,70,false));
    }
    foreach(QLineEdit *line, findChildren<QLineEdit *>())
    {
    line->setStyleSheet("QLineEdit {"
                         "border: none;"
                         "border-radius: 10px;"
                         "color:white;"
                         "background-color:#0C1B64;"
                         "}");
    }
    foreach(QGroupBox *group, findChildren<QGroupBox *>())
    {
    group->setStyleSheet("QGroupBox {"
                                "background-color: qlineargradient(spread:pad, x1:0.349, y1:0.336364, x2:"+QString::number(lineargradx)+", y2:"+QString::number(lineargrady)+", stop:0 rgba(5, 24, 122, 200), stop:1 rgba(5, 24, 255, 125));"
                                "border-radius:20px;"
                                "color:white;"
                                "}");
    lineargradx-=0.001;
    lineargrady-=0.001;

    if(lineargradx <= 0.8 && lineargrady <= 0.8)
      {
        lineargradx = 1;
        lineargrady = 1;
    } }

    QTimer *timer = new QTimer();
    connect(timer, &QTimer::timeout, [=](){
        foreach(QGroupBox *group, findChildren<QGroupBox *>())
        {
        group->setStyleSheet("QGroupBox {"
                                    "background-color: qlineargradient(spread:pad, x1:0.349, y1:0.336364, x2:"+QString::number(lineargradx)+", y2:"+QString::number(lineargrady)+", stop:0 rgba(5, 24, 122, 200), stop:1 rgba(5, 24, 255, 125));"
                                    "border-radius:20px;"
                                    "color:white;"
                                    "}");
        lineargradx-=0.001;
        lineargrady-=0.001;

        if(lineargradx <= 0.8 && lineargrady <= 0.8)
          {
            lineargradx = 1;
            lineargrady = 1;
        } }
    });
    timer->start(1000);

}
