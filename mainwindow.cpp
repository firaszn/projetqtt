#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"employe.h"
#include "stat_categorie.h"
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QFileDialog>
#include <QPushButton>
#include<QString>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QIntValidator>
#include <QFileDialog>
#include <QTextStream>
#include <QPainter>
#include <QTextStream>
#include <QFileDialog>
#include <QTextDocument>
#include <QtPrintSupport/QPrinter>
#include <QFileDialog>
#include <QTextDocument>
#include <QSystemTrayIcon>
#include <QRegExpValidator>
#include <QDesktopServices>
#include <QUrl>
#include <QGuiApplication>
//#include <QQmlApplicationEngine>
#include <QTcpSocket>
//#include <QQuickItem>
#include <QSystemTrayIcon>
#include <QIntValidator>
#include <QDebug>
#include "notification.h"

#include <QMessageBox>
#include "QIntValidator"
#include <QDateEdit>
#include <QPlainTextEdit>
#include <QPrinter>
#include <QPrinterInfo>
#include <QPrintDialog>
#include <QTextStream>
#include <QPainter>
#include <QTextStream>
#include <QFileDialog>
#include <QTextDocument>
#include <QtPrintSupport/QPrinter>
#include <QFileDialog>
#include <QTextDocument>
#include <QSystemTrayIcon>
#include <QRegExpValidator>
#include <QDesktopServices>
#include <QUrl>
#include <QGuiApplication>
//#include <QQmlApplicationEngine>
#include <QTcpSocket>
//#include <QQuickItem>
#include <QSystemTrayIcon>
#include <QIntValidator>
//#include <QQmlApplicationEngine>
#include <QTcpSocket>
//#include <QQuickItem>
#include <QSystemTrayIcon>
#include <QPixmap>
#include <QDesktopServices>
#include <QImage>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //chat
       mSocket=new QTcpSocket(this);
           mSocket->connectToHost("localhost",2000);
           if (mSocket->waitForConnected(3000))
           {
               ui->plainTextEdit_2->appendPlainText("se connecter correctement");
           }
           else
           {
               ui->plainTextEdit->appendPlainText("connected");
           }
           connect(mSocket,SIGNAL(readyRead()),this,SLOT(leer()));
           // fin chat

    ui->email->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z,@,.]+"), parent));

    ui->tableView->setModel(Etmp.afficher());


    // Obtenez le QTabWidget
    QTabWidget *tabWidget = ui->tabWidget_2;

    // Changer le nom de la première colonne
    tabWidget->setTabText(0, "crud ");
    tabWidget->setTabText(1, "metiers ");
    tabWidget->setTabText(2, "stat ");
    tabWidget->setTabText(3, "chat box ");
    tabWidget->setTabText(4, "arduino ");


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
       bool test1=true;
       QString nom = ui->nom->text();
       QString prenom=ui->prenom->text();
       QString poste=ui->poste->currentText();
       int salaire=ui->salaire->text().toInt();
       QString email=ui->email->text();
       QString mdp = ui->mdp->text();
       QString role=ui->role->currentText();
       QString etat=ui->etat->currentText();
       QRegExp re("\\d*");
       if (!re.exactMatch(ui->salaire->text())){
          qDebug() << "salaire not digits";
          test1=false;}

       if(!re.exactMatch(ui->cin->text())){
           qDebug() << "cin not digits";
          test1=false;}
       for(int i=0;i<prenom.length();i++){
       if(re.exactMatch(prenom.at(i))){
           test1=false;
           qDebug()<< "prenom digit";
       }
       }
       for(int i=0;i<nom.length();i++){
       if(re.exactMatch(nom.at(i))){
           test1=false;
           qDebug()<< "nom digit";
       }
       }
       for(int i=0;i<poste.length();i++){
       if(re.exactMatch(poste.at(i))){
           test1=false;
           qDebug()<< "poste digit";
       }
       }


            int cin = ui->cin->text().toInt();
bool test;
           if(test1){
           employe e (cin,nom,prenom,poste,salaire,email,mdp,role,etat);
            test = e.ajouter();
           }else{ qDebug()<<"wrong input";test=false; };




         if( test){
             ui->tableView->setModel(Etmp.afficher());


              QMessageBox::information(nullptr, QObject::tr("ok"),
                          QObject::tr("ajout effectué .\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
              ui->cin->clear();
                             ui->nom->clear();
                             ui->prenom->clear();
                             ui->salaire->clear();
                             ui->email->clear();
                             ui->mdp->clear();

                             notification ok;

                             if(ui->etat->currentText()=="present"){
                             ok.notification_presence();
                             }
                             else if(ui->etat->currentText()=="absent"){
                                 ok.notification_absence();
                                 }




      }
          else
              QMessageBox::critical(nullptr, QObject::tr("not ok"),
                          QObject::tr("ajout non effectué .\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
}



void MainWindow::on_supprimer_clicked()
{
    int cin = ui->cin->text().toInt();

             bool test = Etmp.supprimer(cin);

        if (test)
        {



              QMessageBox::information(nullptr, QObject::tr("ok"),
                          QObject::tr("suppression effectué .\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);


              ui->tableView->setModel(Etmp.afficher());

              ui->cin->clear();
                             ui->nom->clear();
                             ui->prenom->clear();
                             ui->salaire->clear();
                             ui->email->clear();
                             ui->mdp->clear();







      }
          else
              QMessageBox::critical(nullptr, QObject::tr("not ok"),
                          QObject::tr("suppression non effectué .\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);


}







void MainWindow::on_rechercher_clicked()
{

    QString cas = ui->lineEditcin->text();


            ui->tableView_2->setModel(Etmp.recherche( cas));


}



void MainWindow:: on_radioButton_clicked()
{


    ui->tableView_2->setModel(Etmp.tricin());


}



void MainWindow::on_pdf_clicked()
{
    QPdfWriter pdf(qApp->applicationDirPath()+"//listeemployee.pdf");

       QPainter painter(&pdf);



       int i = 4000;


                        painter.drawText(4500,1500,"LISTE DES EMPLOYEE");
                        painter.setPen(Qt::blue);
                        painter.setFont(QFont("Arial", 50));
                        painter.drawRect(2000,200,6300,2600);
                        painter.setPen(Qt::black);



                        QSqlQuery query;
                        query.prepare("select * from employee");
                        query.exec();
                        while (query.next())

                        {
                            painter.setPen(Qt::red);
                            painter.setPen(Qt::black);
                            painter.setFont(QFont("Arial", 9));
                            painter.drawRect(-50,1000+i,3600,2500);
                            painter.drawText(0,1300+i,"CIN");
                            painter.drawText(0,1600+i,"NOM");
                            painter.drawText(0,1900+i,"PRENOM");
                            painter.drawText(0,2200+i,"POSTE");
                            painter.drawText(0,2500+i,"SALAIRE");
                            painter.drawText(0,2800+i,"EMAIL");
                            painter.drawText(0,3100+i,"MDP");
                            painter.drawText(0,3400+i,"ROLE");
                            painter.drawText(0,3700+i,"ETAT");



                            painter.drawText(1600,1300+i,query.value(0).toString());
                            painter.drawText(1600,1600+i,query.value(1).toString());
                            painter.drawText(1600,1900+i,query.value(2).toString());
                            painter.drawText(1600,2200+i,query.value(3).toString());
                            painter.drawText(1600,2500+i,query.value(4).toString());
                            painter.drawText(1600,2800+i,query.value(5).toString());
                            painter.drawText(1600,3100+i,query.value(6).toString());
                            painter.drawText(1600,3400+i,query.value(7).toString());
                            painter.drawText(1600,3700+i,query.value(8).toString());


                            i = i +3000;
                        }

                        int reponse = QMessageBox::question(this, "PDF généré", "Afficher le PDF ?", QMessageBox::Yes |  QMessageBox::No);
                        if (reponse == QMessageBox::Yes)
                        {
                            QDesktopServices::openUrl(QUrl::fromLocalFile(qApp->applicationDirPath()+"//listeemployee.pdf"));

                            painter.end();
                        }
                        if (reponse == QMessageBox::No)
                        {
                            painter.end();
                        }




}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    QString val=ui->tableView->model()->data(index).toString();
        QSqlQuery qry;
        qry.prepare("select * from employee where cin='"+val+"'");
       if (qry.exec())
       {
           while(qry.next())
           {
              ui->cin->setText(qry.value(0).toString());
              ui->nom->setText(qry.value(1).toString());

              ui->prenom->setText(qry.value(2).toString());
              ui->poste->setCurrentText(qry.value(3).toString());
              ui->salaire->setText(qry.value(4).toString());

               ui->email->setText(qry.value(5).toString());
               ui->mdp->setText(qry.value(6).toString());

               ui->role->setCurrentText(qry.value(7).toString());

                ui->etat->setCurrentText(qry.value(8).toString());



           }
       }
       else
       {
           QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                   QObject::tr("Echec"),
                   QMessageBox::Cancel);
       }

}














void MainWindow::on_pushButton_2_clicked()
{
    int cin = ui->cin->text().toInt();
    QString nom = ui->nom->text();
    QString prenom=ui->prenom->text();
    QString poste=ui->poste->currentText();
    int salaire=ui->salaire->text().toInt();
    QString email=ui->email->text();
    QString mdp = ui->mdp->text();
    QString role=ui->role->currentText();
    QString etat=ui->etat->currentText();


       bool test;
      employe e (cin,nom,prenom,poste,salaire,email,role,etat,mdp);
      test = e.modifier();



      if( test){


              QMessageBox::information(nullptr, QObject::tr("ok"),
                          QObject::tr("modification effectué .\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
              ui->tableView->setModel(Etmp.afficher());

              ui->cin->clear();
                             ui->nom->clear();
                             ui->prenom->clear();
                             ui->salaire->clear();
                             ui->email->clear();
                             ui->mdp->clear();










      }
          else
              QMessageBox::critical(nullptr, QObject::tr("not ok"),
                          QObject::tr("modification non effectué .\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
}




void MainWindow::on_pushButton_3_clicked()
{

 QString username1 = ui->username1->text();
 QString message = QString("%1: %2").arg(username1).arg(ui->write1->text());
    mSocket->write(message.toLatin1().data(), message.size());
    ui->plainTextEdit->appendPlainText(message);

       ui->write1->clear();

    }

void MainWindow::on_pushButton_4_clicked()
{
    QString username2 = ui->username2->text();
    QString message = QString("%1: %2").arg(username2).arg(ui->write2->text());
       mSocket->write(message.toLatin1().data(), message.size());
       ui->plainTextEdit_2->appendPlainText(message);



       ui->write2->clear();

}

void MainWindow::on_pushButton_5_clicked()
{
    QPixmap screen_shot = ui->tableView->grab();
            QImage img = screen_shot.toImage();
            img.save("Capture.png");
              QDesktopServices::openUrl(QUrl("Capture.png"));
}



void MainWindow::on_chat_clicked()
{
    if (ui->tabWidget_2->count() > 1) {
              ui->tabWidget_2->setCurrentIndex( (ui->tabWidget_2->currentIndex()+2) % ui->tabWidget_2->count() );
           }

}

void MainWindow::on_stat_clicked()
{

    vector<QString> liste_cat;
    vector<qreal> count;
    QSqlQuery q1,q2;
    qreal tot=0,c;
    q1.prepare("SELECT DISTINCT poste FROM employee");
    q1.exec();
    while (q1.next()){
        liste_cat.push_back(q1.value(0).toString());
    }

    q1.prepare("SELECT * FROM employee");
    q1.exec();
    while (q1.next()){
        tot++;
    }

    for (auto i = liste_cat.begin(); i != liste_cat.end(); ++i) {
         q2.prepare("SELECT * FROM employee where poste = :m");
         q2.bindValue(":m", *i);
         q2.exec();
         c=0;
         while (q2.next()){c++;}
         count.push_back(c/tot);

    }


// Define slices and percentage of whole they take up
QPieSeries *series = new QPieSeries();

for(unsigned int i = 0; i < liste_cat.size(); i++){
    QString label = QString("%1 (%2%)").arg(liste_cat[i]).arg(QString::number(count[i] * 100, 'f', 2));
    series->append(label, count[i]);
}




// Create the chart widget
QChart *chart = new QChart();

// Add data to chart with title and show legend
chart->addSeries(series);
chart->legend()->show();
chart->setTitle("statistiques par poste ");



// Used to display the chart
 QChartView *chartView ;
chartView = new QChartView(chart,ui->label_3);
chartView->setRenderHint(QPainter::Antialiasing);
chartView->setMinimumSize(600,600);

chartView->show();
if (ui->tabWidget_2->count() > 1) {
          ui->tabWidget_2->setCurrentIndex( (ui->tabWidget_2->currentIndex()+1) % ui->tabWidget_2->count() );
       }
}





void MainWindow::on_gotometiers_clicked()
{
    if (ui->tabWidget_2->count() > 1) {
              ui->tabWidget_2->setCurrentIndex( (ui->tabWidget_2->currentIndex()+1) % ui->tabWidget_2->count() );
           }


}

void MainWindow::on_back_2_clicked()
{
    if (ui->tabWidget_2->count() > 1) {
        ui->tabWidget_2->setCurrentIndex( (ui->tabWidget_2->currentIndex()-1) % ui->tabWidget_2->count() );
     }

}

void MainWindow::on_back_clicked()
{
    if (ui->tabWidget_2->count() > 1) {
              ui->tabWidget_2->setCurrentIndex( (ui->tabWidget_2->currentIndex()-1) % ui->tabWidget_2->count() );
           }

}

void MainWindow::on_back_3_clicked()
{
    if (ui->tabWidget_2->count() > 1) {
        ui->tabWidget_2->setCurrentIndex( (ui->tabWidget_2->currentIndex()-1) % ui->tabWidget_2->count() );
     }

}
void MainWindow::on_back_4_clicked()
{
    if (ui->tabWidget_2->count() > 1) {
        ui->tabWidget_2->setCurrentIndex( (ui->tabWidget_2->currentIndex()-1) % ui->tabWidget_2->count() );
     }


}


void MainWindow::on_pushButton_9_clicked()
{

}

void MainWindow::on_pushButton_7_clicked()
{

}

void MainWindow::on_pushButton_8_clicked()
{

}

void MainWindow::on_pushButton_6_clicked()
{

}

