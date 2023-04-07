#include "gestion_client.h"
#include "ui_gestion_client.h"
#include <QMessageBox>
#include <QString>
#include "smtp.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QHttpMultiPart>
#include <QUrl>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTimer>
#include <QEventLoop>
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QInputDialog>
#include "dialog_statistiques.h"
#include "dialog_menu.h"
#include "mybutton.h"
Gestion_Client::Gestion_Client(QString nom,QString pass,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Gestion_Client)
{
    nom1=nom;
    pass1=pass;
    ui->setupUi(this);
    int ret=A.connect_arduino();
    switch(ret){
    case(0):qDebug()<<"arduino is available and connected to :" << A.getarduino_port_name();
        break;
    case(1):qDebug()<<"arduino is available but not connected to :" << A.getarduino_port_name();
        break;
    case(-1):qDebug()<<"arduino is not avaialable";
    }
    //QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));
    style();
}

Gestion_Client::~Gestion_Client()
{
    delete ui;

}



void Gestion_Client::on_createbutton_clicked()
{
    QRegExp numREX("^\\+?(216)[0-9]{8}$");
    QRegExp mailREX("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
    mailREX.setCaseSensitivity(Qt::CaseInsensitive);
    mailREX.setPatternSyntax(QRegExp::RegExp);
    QString nom=ui->lineEdit_name->text();
    QString email=ui->lineEdit_email->text();
    QString numtel=ui->lineEdit_numtel->text();
    bool added=false;

    if ((mailREX.exactMatch(email)) && (numREX.exactMatch(numtel)) && (nom.size()<50))
    {
    client e(0,nom,email,numtel);
    added=e.ajouter_client();
    }
    if (added)
    {
            Smtp* smtp = new Smtp("zerofurygaming@gmail.com", "hlzsoavdheqokqbs", "smtp.gmail.com", 465);
        QMessageBox::information(this,"Ajouter avec succées","Client ajouté");
        QString msg="Welcome "+nom+"\n Vous etes inscrit a notre application Smart Business Travel.\nVotre numero de telephone est :"+numtel;
                        smtp->sendMail("zerofurygaming@gmail.com", email , "Welcome to our dashboard",msg);

    } else
    {
        QString error = "";
        if (!mailREX.exactMatch(email))
        {
            error = error + "\n" + "Email is not in the correct form";
        }
        if (!numREX.exactMatch(numtel))
        {
            error = error + "\n" + "Phone Number is not in the correct form";
        }
        if (!(nom.size()<50))
        {
            error = error + "\n" + "Name too long";
        }
        QMessageBox::information(this,"ERROR","Erreur d'ajout"+error);
    }
    ui->affiche->setModel(unusableclient.afficher_client());
}
void Gestion_Client::closeEvent(QCloseEvent *)
{
    QMessageBox quitBox(
                    QMessageBox::Question,
                    tr("Select Action"),
                    tr("Select your action ?"),
                    QMessageBox::Yes | QMessageBox::No);
        quitBox.setButtonText(QMessageBox::Yes, tr("Menu"));
        quitBox.setButtonText(QMessageBox::No, tr("Quit"));
        if (quitBox.exec() == QMessageBox::Yes) {
    Dialog_menu *dialog_menu=new Dialog_menu(nom1,pass1);
    dialog_menu->show();
        }
                A.close_arduino();
    this->close();
    //qApp->quit();

}
void Gestion_Client::on_tabWidget_currentChanged(int index)
{
    if(index==1)
    {
            ui->affiche->setModel(unusableclient.afficher_client());
    }
    if(index==2)
    {
            ui->afficheread->setModel(unusableclient.afficher_client());
    }
    if(index==3)
    {
            ui->affichemodif->setModel(unusableclient.afficher_client());
    }
    if(index==4)
    {
            ui->affichedelete->setModel(unusableclient.afficher_client());
    }
}
void Gestion_Client::update()
{

            ui->affiche->setModel(unusableclient.afficher_client());

            ui->afficheread->setModel(unusableclient.afficher_client());

            ui->affichemodif->setModel(unusableclient.afficher_client());

            ui->affichedelete->setModel(unusableclient.afficher_client());

                //Smtp* smtp = new Smtp("zerofurygaming@gmail.com", "hlzsoavdheqokqbs", "smtp.gmail.com", 465);
            //smtp->sendMail("zerofurygaming@gmail.com", "mohamedyassinebenmiled@gmail.com" , "Database Connected","Database Connected Successfully\nQT Application");

}
void Gestion_Client::on_trinom_clicked()
{
    ui->afficheread->setModel(unusableclient.AfficherT("nom"));
}

void Gestion_Client::on_triemail_clicked()
{
    ui->afficheread->setModel(unusableclient.AfficherT("email"));
}


QString GetRandomString()
{
   const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
   const int randomStringLength = 4; // assuming you want random strings of 12 characters

   QString randomString;
   for(int i=0; i<randomStringLength; ++i)
   {
       int index = qrand() % possibleCharacters.length();
       QChar nextChar = possibleCharacters.at(index);
       randomString.append(nextChar);
   }
   return randomString;
}
void Gestion_Client::on_modifybutton_clicked()
{

    QRegExp numREX("^\\+?(216)[0-9]{8}$");
    QRegExp mailREX("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
    mailREX.setCaseSensitivity(Qt::CaseInsensitive);
    mailREX.setPatternSyntax(QRegExp::RegExp);
        QString id=ui->lineEdit_edit_id->text();
    QString nom=ui->lineEdit_edit_name->text();
    QString email=ui->lineEdit_edit_email->text();
    QString numtel=ui->lineEdit_edit_numtel->text();
    bool modified=false;
    unusableclient.setnom(nom);
    unusableclient.setemail(email);
    unusableclient.setnumtel(numtel);
    unusableclient.setid(ui->lineEdit_edit_id->text().toInt());
            bool ok;
    if ((mailREX.exactMatch(email)) && (numREX.exactMatch(numtel)) && (nom.size()<50))
    {
        ok=true;
        QString code = GetRandomString();
        QString msg = "Your verification code to update account is : "+code;
        client numerotel;
        if (numerotel.GetClient(id))
            {
                        if(postrequest(msg,numerotel.getnumtel()))
                        {
                        QString text = QInputDialog::getText(0, "Modification dialog",
                                                             "Confirmation Code:", QLineEdit::Normal,
                                                             "", &ok);
                        if (code == text)
                        {
                                modified=unusableclient.modifier_client();
                        }
                        else
                        {
                                        ok=false;
                                        QMessageBox::information(this, "Code Incorrecte", "Code saisi incorrecte");
                        }
                        }
            }



    }
    if(modified){
            QMessageBox::information(this, "Modifié avec succéss", "Client modifié");
        }
        else
        {
        QString error = "";
        if (!mailREX.exactMatch(email))
        {
            error = error + "\n" + "Email is not in the correct form";
        }
        if (!numREX.exactMatch(numtel))
        {
            error = error + "\n" + "Phone Number is not in the correct form";
        }
        if (!(nom.size()<50))
        {
            error = error + "\n" + "Name too long";
        }
        if (!ok)
        {
            error = error + "\n" + "Inserted code is incorrect";
        }
        if (ok)
        {
            error = error + "\n" + "Message was not sent\nCheck your sms balance.";

        }
        qDebug() << error;
        QMessageBox::information(this,"ERROR","Erreur de modification"+error);
        }
    ui->affichemodif->setModel(unusableclient.afficher_client());


}

void Gestion_Client::on_lineEdit_edit_id_editingFinished()
{
    QString id=ui->lineEdit_edit_id->text();
    if (unusableclient.GetClient(id))
    {
    ui->lineEdit_edit_email->setText(unusableclient.getemail());
    ui->lineEdit_edit_name->setText(unusableclient.getnom());
    ui->lineEdit_edit_numtel->setText(unusableclient.getnumtel());
    }
}

void Gestion_Client::on_deletebutton_clicked()
{
    QString id = ui->lineEdit_delete_id->text();

   bool test=unusableclient.supprimer_client(id);
   QMessageBox msBox;
   if (test)
   {


       msBox.setText("Effacer avec succées");
                     msBox.exec();
   } else
   {
       msBox.setText("ERROR");
                     msBox.exec();
   }
    ui->affichedelete->setModel(unusableclient.afficher_client());

}

void Gestion_Client::on_lineEdit_delete_id_editingFinished()
{
    QString id=ui->lineEdit_delete_id->text();
    if (unusableclient.GetClient(id))
    {
    ui->lineEdit_delete_email->setText(unusableclient.getemail());
    ui->lineEdit_delete_name->setText(unusableclient.getnom());
    ui->lineEdit_delete_numtel->setText(unusableclient.getnumtel());
    }
}

bool Gestion_Client::postrequest(QString smsmsg,QString phonenumber)
{
    if (A.isrunning())
    {
    QString cmd = "S"+phonenumber+smsmsg;
    A.write_to_arduino(cmd.toUtf8());
    A.getserial()->waitForReadyRead(1000);
    if (A.read_from_arduino()=="W")
    {
        return true;
    }
    else
    {
        return false;
    }
    }
    else
    {

    // create custom temporary event loop on stack
       QEventLoop eventLoop;

       // "quit()" the event-loop, when the network request "finished()"
       QNetworkAccessManager mgr;
       QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

       // the HTTP request
       QNetworkRequest req( QUrl( QString("https://api.orange.com/smsmessaging/v1/outbound/tel%3A%2B322804/requests") ) );

      req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");


        QString api= "Bearer " + apikey;
        req.setRawHeader("Authorization", api.toUtf8());
        QJsonObject msg;
        msg["message"] = smsmsg;
        QJsonObject obj;
        obj["address"] = "tel:"+phonenumber;
        obj["senderAddress"] = "tel:+322804";
        obj["outboundSMSTextMessage"] = msg;
        QJsonObject body;
        body["outboundSMSMessageRequest"] = obj;
        QJsonDocument doc(body);
        QByteArray data = doc.toJson();
       QNetworkReply *reply = mgr.post(req,data);
       eventLoop.exec(); // blocks stack until "finished()" has been called

       if (reply->error() == QNetworkReply::NoError) {
           //success
           qDebug() << "Success" ;
           delete reply;
           return true;
       }
       else {
           //failure
           qDebug() << "Failure" << reply->error();
           if (reply->errorString()=="Host requires authentication")
           {
               if (!tried)
               {
               apikey = QInputDialog::getText(0, "API Key dialog",
                                              "API Key expired, Set a new one :", QLineEdit::Normal,
                                              "", nullptr);
               if (postrequest(smsmsg,phonenumber))
               {
                   return true;
               }

               }
               tried = true;

           }
           delete reply;
           return false;
       }
    }
}



void Gestion_Client::on_PDF_Button_clicked()
{
    QPdfWriter pdf(qApp->applicationDirPath()+"//ListeClient.pdf");
        QPainter painter(&pdf);
        int i = 4000;
        painter.setPen(Qt::black);
        painter.setFont(QFont("Arial", 30));
        painter.drawPixmap(QRect(100,100,3000,3000),QPixmap(":/new/prefix1/tayarni.png"));
        painter.drawText(3000,1500,"LISTE DES CLIENTS");
        painter.setPen(Qt::blue);
        painter.setFont(QFont("Arial", 50));
        //painter.drawRect(2700,200,6300,2600);
        painter.drawRect(0,3000,9600,500);
        painter.setPen(Qt::black);
        painter.setFont(QFont("Arial", 9));
        painter.drawText(300,3300,"ID");
        painter.drawText(600,3300,"NOM");
        painter.drawText(3300,3300,"EMAIL");
        painter.drawText(6300,3300,"NUMTEL");
        painter.drawText(8300,3300,"DATE");
        QSqlQuery query;
        time_t tt;
        struct tm* ti;
        time(&tt);
        ti=localtime(&tt);
        asctime(ti);
        painter.drawText(500,300, asctime(ti));
        query.prepare("select * from CLIENT");
        query.exec();
        while (query.next())
        {
            painter.drawText(300,i,query.value(0).toString());
            painter.drawText(600,i,query.value(1).toString());
            painter.drawText(3300,i,query.value(2).toString());
            painter.drawText(6300,i,query.value(3).toString());
            painter.drawText(8300,i,query.value(4).toDate().toString());
            i = i +500;
        }
        int reponse = QMessageBox::question(this, "PDF generated", "Show PDF ?", QMessageBox::Yes |  QMessageBox::No);
        if (reponse == QMessageBox::Yes)
        {
            QDesktopServices::openUrl(QUrl::fromLocalFile(qApp->applicationDirPath()+"//ListeClient.pdf"));
            painter.end();
        }
        if (reponse == QMessageBox::No)
        {
            painter.end();
        }
}

void Gestion_Client::on_DeleteHome_clicked()
{
    ui->tabWidget->setCurrentIndex(4);
}

void Gestion_Client::on_CreateHome_clicked()
{
        ui->tabWidget->setCurrentIndex(1);
}

void Gestion_Client::on_ReadHome_clicked()
{
        ui->tabWidget->setCurrentIndex(2);
}

void Gestion_Client::on_UpdateHome_clicked()
{
        ui->tabWidget->setCurrentIndex(3);
}

void Gestion_Client::on_statistique_clicked()
{
        Dialog_Statistiques *DS;
    DS = new Dialog_Statistiques();

  DS->setWindowTitle("Stats");
  DS->choix_pie();
  DS->show();
}

void Gestion_Client::on_pushButton_clicked()
{
    QString id=ui->lineEdit_edit_id->text();
    unusableclient.ajouter_voyageur_client(id);
}

void Gestion_Client::on_afficheread_doubleClicked(const QModelIndex &index)
{
    if (unusableclient.GetClient(index.data().toString()))
    {
        ui->afficheread->setModel(unusableclient.afficher_client_voyageurs(index.data().toString()));
    }
}


void Gestion_Client::style()
{
    setStyleSheet(  "QMessageBox {"
                        "background-color:#05187A;"
                        "}"
                    "QMainWindow {"
                     "background-color:#05187A;"
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
    foreach(MyButton *button, findChildren<MyButton *>())
        {
        button->setStyleSheet("");
        button->SetColor(QColor(255,255,255));
        }
    setFont(QFont("Outfit"));
    foreach(QTableView *table, findChildren<QTableView *>())
        {
        table->setStyleSheet(" QTableView { color: #f5f5f5; border: none; border-radius:20px; gridline-color: #f5f5f5; background-color: qlineargradient(spread:pad, x1:0.349, y1:0.336364, x2:1, y2:1, stop:0 rgba(5, 24, 122, 200), stop:1 rgba(5, 24, 255, 125)); selection-color: #1b3774; selection-background-color: #adc5ed; padding: 0px; margin: 0px; } QTableView::item:hover { background: #abb0b7; } QTableView::item:disabled { color: #e6e6e6; } QTableView::item:selected { color: #1b3774; background-color: #7cabf9; } /* when editing a cell: */ QTableView QLineEdit { color: #f5f5f5; border: none; background-color: rgba(255, 255, 255,50); border-radius: 0px; margin: 0px; padding: 0px; } QHeaderView { border: none; border-radius:20px; background-color: rgba(255, 255, 255,50); margin: 0px; padding: 0px; } QHeaderView::section { background-color: transparent; color: #ffffff; border: none; text-align: center; } QHeaderView::section::vertical { padding: 0px 6px 0px 6px; } QHeaderView::section::horizontal { padding: 0px 0px 0px 6px; } QHeaderView::section:checked { border: none; color: #1b3774; background-color: #7cabf9; } QTableCornerButton::section { background-color: #1b3774; border: none; } ");
        table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        table->verticalHeader()->setVisible(false);
        table->setShowGrid(false);
    }
}
