#include "dialog_verriffication.h"
#include "ui_dialog_verriffication.h"
#include "login.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QTime>

void delay( int millisecondsToWait )
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}
Dialog_verriffication::Dialog_verriffication(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_verriffication)
{
    ui->setupUi(this);
    int ret=A.connect_arduino();
        switch(ret){
        case(0):qDebug()<<"arduino is available and connected to :" << A.getarduino_port_name();
            break;
        case(1):qDebug()<<"arduino is available but not connected to :" << A.getarduino_port_name();
            break;
        case(-1):qDebug()<<"arduino is not avaialable";
        }
        QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update()));
}

Dialog_verriffication::~Dialog_verriffication()
{
    delete ui;
}
void Dialog_verriffication::update()
{

//    QString data=QString(A.read_from_arduino());
r=QString(A.read_from_arduino());
qDebug() <<r;
/*    if(data.contains("+216"))
    {
        numtelarduino= data.mid(6,12);
        qDebug() << numtelarduino;
    }
*/
}
void Dialog_verriffication::on_pushButton_clicked()
{
    bool ok ;
        E=E.recherche(ui->LECIN_ver->text().toInt());
        QString helpmessage = "Envoyez un message avec le numero "+E.getNUM_TEL()+"sur le numero +21652957571";
        QMessageBox::information(nullptr, QObject::tr("Forgotten password"),
                            helpmessage,QMessageBox::Ok );
        QString cmd="V"+E.getNUM_TEL();
        qDebug()<<cmd;
        A.write_to_arduino(cmd.toUtf8());
       if (r=="W")
          {
          qDebug() <<r;
          A.getserial()->waitForReadyRead(2000);
          }

       delay(6000);
        if (r=="Y")
        {
            QString text = QInputDialog::getText(0, "Modification dialog",
                                                                         "change password:", QLineEdit::Normal,
                                                                         "", &ok);
            if(text!="")
            {
            E.setMODE_PASS(text);
            E.modifierE(E.getCIN());
            QMessageBox::information(nullptr, QObject::tr(" password changed"),
                                 QObject::tr(" password changed suucesfuly"),QMessageBox::Ok );
} else {            QMessageBox::information(nullptr, QObject::tr(" password changed"),
                                             QObject::tr(" password did not change"),QMessageBox::Ok );}
        }
        else
        {
            QMessageBox::information(this, "Code Incorrecte", "Code saisi incorrecte");

        }
}
void Dialog_verriffication::closeEvent(QCloseEvent *)
{

    login *log=new login();
    log->show();

        A.close_arduino();
    this->close();
    //qApp->quit();

}
