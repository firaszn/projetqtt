#include "Gestion_Employee/gestion_employee.h"
#include "ui_gestion_employee.h"
#include "Gestion_Employee/employee.h"
#include <QIntValidator>
#include <QMessageBox>
#include <QDesktopServices>
#include <QFileDialog>
#include <QPushButton>
#include <QPdfWriter>
#include <QPainter>
#include"dialog_stats.h"
#include "messengerclient.h"
#include"exportexcelobject.h"
#include "dialog_menu.h"
#include "mybutton.h"
#include "Gestion_Employee/messengerserver.h"

Gestion_Employee::Gestion_Employee(QString nom,QString pass,QWidget *employee)
    : QMainWindow(employee)
    , ui(new Ui::Gestion_Employee)
{
    nom1=nom;
    pass1=pass;
    ui->setupUi(this);
    ui->LCIN->setValidator(new QIntValidator(0,99999999,this));
    ui->LNOM->setInputMask("AAAAAAAAAAAA");
    ui->LPRENOM->setInputMask("AAAAAAAAAAAAAAA");


    ui->LCIN_2->setValidator(new QIntValidator(0,99999999,this));
    ui->LNOM_2->setInputMask("AAAAAAAAAAAAAAA");
    ui->LPRENOM_2->setInputMask("AAAAAAAAAAAAAAA");



    ui->LSUPP->setValidator(new QIntValidator(0,99999999,this));


    ui->tabemployee->setModel(E.afficher());
    ui->tabemployee->hideColumn(7);
    style();

}

Gestion_Employee::~Gestion_Employee()
{
    delete ui;

}


void Gestion_Employee::on_pt_Ajouter_clicked()
{

    int CIN=ui->LCIN->text().toInt();
    QString NOM=ui->LNOM->text();
    QString PRENOM=ui->LPRENOM->text();
    QDate DATE_NAISSANCE=ui->LDATE_NAISSANCE->date();
    int AGE=ui->LAGE->text().toInt();
    QString ROLE=ui->LROLE->currentText();
    QString EMAIL=ui->LEMAIL->text();
    QString MODE_PASS=ui->LEMP->text();
    QString NUM_TEL=ui->LE_NUM_TEL->text();
    Employee E(CIN,NOM,PRENOM,DATE_NAISSANCE,AGE,ROLE,EMAIL,MODE_PASS,NUM_TEL);

    bool test=E.ajouter();

        if(test)
        {
            QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr("Ajout effectué"),QMessageBox::Cancel);
             ui->tabemployee->setModel(E.afficher());
        }
        else
            QMessageBox::critical(nullptr, QObject::tr("not ok"),
                                 QObject::tr("Ajout non effectué"),QMessageBox::Cancel);


}

void Gestion_Employee::on_pt_Supprimer_clicked()
{
    int cin=ui->LSUPP->text().toInt();
    bool test=E.supprimer(cin);

    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("ok"),
                             QObject::tr("Suppression effectué"),QMessageBox::Cancel);
        ui->tabemployee->setModel(E.afficher());
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                             QObject::tr("Suppression non effectué"),QMessageBox::Cancel);

}

void Gestion_Employee::on_pt_modiffier_clicked()
{
    int CIN=ui->LCIN_2->text().toInt();
    QString NOM=ui->LNOM_2->text();
    QString PRENOM=ui->LPRENOM_2->text();
    QDate DATE_NAISSANCE=ui->LDATE_NAISSANCE_2->date();
    int AGE=ui->LAGE_2->text().toInt();
    QString ROLE=ui->LROLE_2->currentText();
    QString EMAIL=ui->LEMAIL_2->text();
    QString MODE_PASS=ui->LEMP_2->text();
    QString NUM_TEL=ui->LE_NUM_TEL_2->text();

    Employee E(CIN,NOM,PRENOM,DATE_NAISSANCE,AGE,ROLE,EMAIL,MODE_PASS,NUM_TEL);

    bool test=E.modifierE(ui->LCIN_2->text().toInt());
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("ok"),
                             QObject::tr("Modiffication effectué"),QMessageBox::Cancel);
        ui->tabemployee->setModel(E.afficher());
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                             QObject::tr("Modiffication non effectué"),QMessageBox::Cancel);

}

void Gestion_Employee::on_pt_recherche_clicked()
{

    E=E.recherche(ui->LCIN_2->text().toInt());
    ui->LNOM_2->setText(E.getNOM());
    ui->LPRENOM_2->setText(E.getPRENOM());
    ui->LDATE_NAISSANCE_2->setDate(E.getDATE_NAISSANCE());
    ui->LAGE_2->setFrame(E.getAGE());
    ui->LROLE_2->setCurrentText(E.getROLE());
    ui->LEMAIL_2->setText(E.getEMAIL());
    ui->LEMP_2->setText(E.getMODE_PASS());
    ui->LE_NUM_TEL_2->setText(E.getNUM_TEL());


}



void Gestion_Employee::on_pt_tricin_clicked()
{
    QMessageBox::information(nullptr, QObject::tr("Ok"),
                             QObject::tr("tri_cin effectué.\n""Click Cancel to exit."), QMessageBox::Cancel);
        ui->tab_triemplyee->setModel(E.tri_cin());

}

void Gestion_Employee::on_pt_trinom_clicked()
{
    QMessageBox::information(nullptr, QObject::tr("Ok"),
                               QObject::tr("tri_nom effectué.\n""Click Cancel to exit."), QMessageBox::Cancel);
          ui->tab_triemplyee->setModel(E.tri_nom());
}

/*void Gestion_Employee::on_pt_inserer_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this,tr("choose"),"",tr("Image(*.png *.jpeg *.jpg *.bmp *.gif)"));
    if (QString::compare(filename,QString()) !=0)
    {
        QImage image;
        bool valid = image.load(filename);
        if(valid)
        {
            image=image.scaledToWidth(ui->image->width(), Qt::SmoothTransformation);
                    ui->image->setPixmap(QPixmap::fromImage(image));
        }
        else
        {
            //ERROR HANDLING
        }
    }
}
*/
void Gestion_Employee::on_pt_pdf_clicked()
{
    QPdfWriter pdf(qApp->applicationDirPath()+"//listeemployee.pdf");
/*
                     QPainter painter(&pdf);

                     int i = 4000;


                     painter.drawText(4500,1500,"LISTE DES EMPLOYEE");
                     painter.setPen(Qt::blue);
                     painter.setFont(QFont("Arial", 300));
                     painter.drawRect(2000,200,6300,2600);
                     painter.drawRect(0,3000,9600,500);
                     painter.setPen(Qt::black);
                     painter.setFont(QFont("Arial", 9));
                     painter.drawText(300,3300,"CIN");
                     painter.drawText(1000,3300,"NOM");
                     painter.drawText(2500,3300,"PRENOM");
                     painter.drawText(3500,3300,"DATE_NAISSANCE");
                     painter.drawText(5500,3300,"AGE");
                     painter.drawText(6500,3300,"ROLE");
                     painter.drawText(7500,3300,"EMAIL");

                     QSqlQuery query;
                     query.prepare("select * from EMPLOYEE");
                     query.exec();
                     while (query.next())
                     {
                         painter.drawText(300,i,query.value(0).toString());
                         painter.drawText(1000,i,query.value(1).toString());
                         painter.drawText(2500,i,query.value(2).toString());
                         painter.drawText(3500,i,query.value(3).toString());
                         painter.drawText(5500,i,query.value(4).toString());
                         painter.drawText(6500,i,query.value(5).toString());
                         painter.drawText(7500,i,query.value(6).toString());

                         i = i +500;
                     }
*/
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
                         painter.drawText(0,2200+i,"DATE_NAISSANCE");
                         painter.drawText(0,2500+i,"AGE");
                         painter.drawText(0,2800+i,"ROLE");
                         painter.drawText(0,3100+i,"EMAIL");


                         painter.drawText(1600,1300+i,query.value(0).toString());
                         painter.drawText(1600,1600+i,query.value(1).toString());
                         painter.drawText(1600,1900+i,query.value(2).toString());
                         painter.drawText(1600,2200+i,query.value(3).toString());
                         painter.drawText(1600,2500+i,query.value(4).toString());
                         painter.drawText(1600,2800+i,query.value(5).toString());
                         painter.drawText(1600,3100+i,query.value(6).toString());

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

void Gestion_Employee::on_pt_stat_clicked()
{ Dialog_stats stat;
    stat.setModal(true);
    stat.exec();

}

void Gestion_Employee::on_chat_box_clicked()
{
    MessengerClient MS;
    MS.exec();
}

void Gestion_Employee::on_Excel_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                        tr("Excel Files (*.xls)"));
        if (fileName.isEmpty())
            return;

        ExportExcelObject obj(fileName, "employee", ui->tabemployee);

        //colums to export
        obj.addField(0, "CIN", "char(20)");
        obj.addField(1, "NOM", "char(20)");
        obj.addField(2, "PRENOM", "char(20)");
        obj.addField(3, "DATE_NAISSANCE", "char(20)");
        obj.addField(4, "AGE", "char(20)");
        obj.addField(5, "ROLE", "char(20)");
        obj.addField(6, "EMAIL", "char(20)");
        obj.addField(8, "NUM_TEL", "char(20)");



        int retVal = obj.export2Excel();
        if( retVal > 0)
        {
            QMessageBox::information(this, tr("Done"),
                                     QString(tr("%1 records exported!")).arg(retVal)
                                     );
        }
}
void Gestion_Employee::closeEvent(QCloseEvent *)
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
     p.kill();
    this->close();
    //qApp->quit();

}

void Gestion_Employee::style()
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

void Gestion_Employee::on_tabemployee_doubleClicked(const QModelIndex &index)
{
    if (E.isAdmin(index.data().toString()))
        ui->tabemployee->setModel(E.affichersuper(index.data().toString()));
    else
        E.superviser(index.data().toString(),nom1,pass1);

}

void Gestion_Employee::on_tabWidget_currentChanged()
{
        ui->tabemployee->setModel(E.afficher());
}

void Gestion_Employee::on_chat_box_2_clicked()
{
/*
    MessengerServer msg;
    if (!msg.startServer(3333)) {
        QString errormessage = "Error Starting Server.\n"+msg.errorString();
        QMessageBox::information(nullptr, QObject::tr("Ok"),
                                   errormessage, QMessageBox::Cancel);
    }
    else

    {

            QMessageBox::information(nullptr, QObject::tr("Ok"),
                                       QObject::tr("Server Started"), QMessageBox::Cancel);

    }
    */

    p.start("MessengerLANServer.exe");
}
