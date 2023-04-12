#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QString>
#include <QDebug>
#include <QTableWidget>
#include <QSqlQuery>
#include <QMessageBox>
#include <QPdfWriter>
#include <QIntValidator>
#include <QCloseEvent>
#include <QFileDialog>
#include <QTextStream>
#include <QTextDocument>
#include <QtCore/qmath.h>
#include <qgraphicsitem.h>
#include <map>
#include "SMTPClient/email.h"
#include "SMTPClient/emailaddress.h"
#include "SMTPClient/smtpclient.h"
#include <QFileDialog>
#include <qdesktopservices.h>




Email MainWindow::createEmail()
{
    // Create the credentials EmailAddress
    EmailAddress credentials("nourhene.ouhichi@esprit.tn",
                             "ecikvjohchilpnmb");

    // Create the from EmailAddress
    EmailAddress from("nourhene.ouhichi@esprit.tn");

    // Create the to EmailAddress
    EmailAddress to(ui->to->text());

    // Create the email
    Email email(credentials,
                from,
                to,
                ui->subjecy->text(),
                ui->content->toPlainText());

    return email;
}

//issmani f stat ma tnajmch taamlha nom(libelle) par rapport quantitee????? wlh manaaref kifeh ok


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->id -> setValidator (new QIntValidator(0, 999999, this));
    ui->libelle->setInputMask("aaaaaaaaaaaaaaaaaa");
    ui->prix -> setValidator (new QIntValidator(0, 999999, this));
    ui->quantite -> setValidator (new QIntValidator(0, 999999, this));
    ui->id_services -> setValidator (new QIntValidator(0, 999999, this));


    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("test-bd");
    db.setUserName("nourhene");//inserer nom de l'utilisateur
    db.setPassword("nourhene");//inserer mot de passe de cet utilisateur
    if(db.open())qDebug()<< "opened the databs";
    ui->tableView->setModel(print_table("stocks"));
    ui->tableView_2->setModel(print_table("stocks"));
    displaystatistiques(ui->graphicsView,"stocks","quantite");
    ui->pushButton_4->hide();
    ui->stackedWidget->setCurrentIndex(1);
    ui->pushButton_8->hide();
}


void MainWindow::displaystatistiques(QGraphicsView* view,QString table,QString collumn){
    // Create a scene and add it to the view
       QGraphicsScene* scene = new QGraphicsScene();
       view->setScene(scene);

       // Query the database to get the data for the chart
       QSqlQuery query("SELECT "+collumn+" FROM "+table);


       // Count the number of occurrences of each type
       QMap<QString, int> typeCounts;
       while (query.next()) {
           QString type = query.value(0).toString();

           if (typeCounts.contains(type)) {
               typeCounts[type]++;
           } else {
               typeCounts.insert(type, 1);
           }
       }

       // Calculate the total count of all types
       int totalCount = 0;
       QMap<QString, int>::const_iterator i;
       for (i = typeCounts.constBegin(); i != typeCounts.constEnd(); ++i) {
           totalCount += i.value();
       }

       // Set up the colors for the chart slices
       QColor colors[] = {
           Qt::red,
           Qt::green,
           Qt::blue,
           Qt::yellow,
           Qt::cyan,
           Qt::magenta,
           Qt::gray,
       };
       int numColors = sizeof(colors) / sizeof(colors[0]);

       // Set up the chart parameters
       QRectF rect(50, 50, 200, 200);
       qreal startAngle = 0;
           QFont font("Arial", 12);
           QFontMetrics fm(font);
           qreal labelRadius = rect.width() * 0.5 + fm.height();
       // Draw the chart slices
       int colorIndex = 0;
       for (i = typeCounts.constBegin(); i != typeCounts.constEnd(); ++i) {
           QString type = i.key();
           int count = i.value();
           qreal angle = 360.0 * count / totalCount;

           // Set up the brush and pen for the slice
           QBrush brush(colors[colorIndex % numColors]);
           QPen pen(colors[colorIndex % numColors]);
           pen.setWidth(2);

           // Draw the slice
           QPainterPath path;
           path.moveTo(rect.center());
           path.arcTo(rect, startAngle, angle);
           path.lineTo(rect.center());
           path.closeSubpath();
           QGraphicsPathItem* item = scene->addPath(path, pen, brush);
           item->setToolTip(type + ": " + QString::number(count));

           // Draw the label for the slice
                   qreal labelAngle = startAngle + angle / 2.0;
                   qreal x = rect.center().x() + labelRadius * qCos(labelAngle * M_PI / 180.0) - fm.width(type) / 2.0;

                   qreal y = rect.center().y() - labelRadius * qSin(labelAngle * M_PI / 180.0) - fm.height() / 2.0;
                   QGraphicsTextItem* label = new QGraphicsTextItem(type);
                   label->setPos(x, y);
                   scene->addItem(label);

           // Update the start angle for the next slice
           startAngle += angle;
           colorIndex++;
       }

       // Set the view's background color
       view->setBackgroundBrush(QColor(240, 240, 240));

       // Set the scene rectangle and view alignment
       scene->setSceneRect(QRectF(0, 0, 300, 300));
       view->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    }

QSqlQueryModel * MainWindow::search_table(QString table ,QString search) {
  QSqlQueryModel * model = new QSqlQueryModel();
  if(search=="")model -> setQuery("Select * from " + table);
  else
  model -> setQuery("Select * from " + table+" WHERE LIBELLE LIKE '%"+search+"%';");
  ui -> tableView -> setModel(model);
  return model;
}
QSqlQueryModel * MainWindow::sortbyup(QString table) {
  QSqlQueryModel * model = new QSqlQueryModel();
  model -> setQuery("Select * from " + table+" ORDER BY ID ASC");
  ui -> tableView -> setModel(model);
  return model;
}
QSqlQueryModel * MainWindow::sortbydown(QString table) {
  QSqlQueryModel * model = new QSqlQueryModel();
  model -> setQuery("Select * from " + table+" ORDER BY ID DESC");
  ui -> tableView -> setModel(model);
  return model;
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    // Get the selection model of the table view
    QItemSelectionModel *selectionModel = ui->tableView->selectionModel();

    // Get the currently selected indexes
    QModelIndexList selectedIndexes = selectionModel->selectedIndexes();

    // Extract the primary keys of the selected rows
    QList<int> primaryKeys;
    foreach (const QModelIndex &index, selectedIndexes) {
        if (index.column() == 0) {
            primaryKeys.append(index.data().toInt());
        }
    }

    // Delete the selected rows from the SQL table
    QSqlQuery query;
    int primaryKey;
    foreach (primaryKey, primaryKeys) {
        query.prepare("DELETE FROM NOURHENE.STOCKS WHERE id = :id;");}
        qDebug() << primaryKey;
        query.bindValue(":id", primaryKey);
        if(!query.exec())QMessageBox::information(this, "Information", "erreur delete"); else QMessageBox::information(this, "Information", "delete done");
        ui->tableView->setModel(print_table("stocks"));
}


void MainWindow::on_pushButton_3_clicked()
{
    QString id1=ui->id->text();
    QString quantite1=ui->quantite->text();
    QString prix1=ui->prix->text();
    QString id_services1=ui->id_services->text();
    QString libelle1=ui->libelle->text();
    QString error;
    bool test1=true;
    QRegExp re("\\d*");
    if (!re.exactMatch(id1)){
           error = "id not digits";test1=false;}
        if(!re.exactMatch(prix1)){
            error = "prix not digits";
           test1=false;}
        if(!re.exactMatch(quantite1)){
            error = "quantite not digits";
           test1=false;}
        if(!re.exactMatch(id_services1)){
            error = "id services not digits";
           test1=false;}
        for(int i=0;i<libelle1.length();i++){
        if(re.exactMatch(libelle1.at(i))){
            test1=false;
            error = "libelle non chaine";
        }
    }
         int id = id1.toInt();
         int quantite = quantite1.toInt();
         int id_services=id_services1.toInt();
         int prix = prix1.toInt();

        if(test1){QSqlQuery qry;
            qry.prepare("INSERT INTO NOURHENE.STOCKS ( ID ,LIBELLE, PRIX, QUANTITE, ID_SERVICE) VALUES (:id, :libelle, :prix, :quantite, :idservice)");
            qry.bindValue(":id",id);
            qry.bindValue(":libelle",libelle1);
            qry.bindValue(":prix",prix);
            qry.bindValue(":quantite",quantite);
            qry.bindValue(":idservice",id_services);
            qDebug() << id_services<< id<<libelle1<<quantite<<prix;
            if(!qry.exec())QMessageBox::information(this, "Information", "execution erreur");
            //add table header
            ui->tableView->setModel(print_table("STOCKS"));
            QMessageBox::information(this, "Information", "ajout done");
        }else{ QMessageBox::information(this, "Information", error); };
        ui->tableView->setModel(print_table("stocks"));

}


void MainWindow::on_pushButton_2_clicked()
{
    QString id1=ui->id->text();
    QString quantite1=ui->quantite->text();
    QString prix1=ui->prix->text();
    QString id_services1=ui->id_services->text();
    QString libelle1=ui->libelle->text();
    QString error;
    bool test1=true;
    QRegExp re("\\d*");
    if (!re.exactMatch(id1)){
           error = "id not digits";test1=false;}
        if(!re.exactMatch(prix1)){
            error = "prix not digits";
           test1=false;}
        if(!re.exactMatch(quantite1)){
            error = "quantite not digits";
           test1=false;}
        if(!re.exactMatch(id_services1)){
            error = "id services not digits";
           test1=false;}
        for(int i=0;i<libelle1.length();i++){
        if(re.exactMatch(libelle1.at(i))){
            test1=false;
            error = "libelle non chaine";
        }
    }
         int id = id1.toInt();
         int quantite = quantite1.toInt();
         int id_services=id_services1.toInt();
         int prix = prix1.toInt();

        if(test1){QSqlQuery qry;
            qry.prepare("UPDATE STOCKS SET LIBELLE= :libelle, PRIX=:prix,QUANTITE= :quantite ,ID_SERVICE= :idservice where id= :id");
            qry.bindValue(":id",id);
            qry.bindValue(":libelle",libelle1);
            qry.bindValue(":prix",prix);
            qry.bindValue(":quantite",quantite);
            qry.bindValue(":idservice",id_services);
            qDebug() << id_services<< id<<libelle1<<quantite<<prix;
            if(!qry.exec())QMessageBox::information(this, "Information", "execution erreur");else QMessageBox::information(this, "Information", "modifier done");
            //add table header
            ui->tableView->setModel(print_table("STOCKS"));
        }else{ QMessageBox::information(this, "Information", error); };
        ui->tableView->setModel(print_table("stocks"));
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    if (index.isValid())
        {
            QVariant data = ui->tableView->model()->data(index);
            QString id = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 0)).toString();
            QString type = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 1)).toString();
            QString montant = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 2)).toString();
            QString date = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 3)).toString().left(10);
            QString id_mat = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 4)).toString();
            qDebug() << "Double-clicked on row " << index.row() << " with data: " << id << "First Name: " << montant << "Last Name: " << date;
            ui->id->setText(id);
            ui->libelle->setText(type);
            ui->prix->setText(montant);
            ui->quantite->setText(date);
            ui->id_services->setText(id_mat);
}
}

void MainWindow::on_pushButton_4_clicked()
{
    if(ui->stackedWidget->currentIndex()==2){
        ui->stackedWidget->setCurrentIndex(0);
    }
    else ui->stackedWidget->setCurrentIndex(2);
    ui->tableView_2->setModel(print_table("stocks"));
    displaystatistiques(ui->graphicsView,"stocks","prix");
}

void MainWindow::generatePdfFile(QString path,QString collumn1,QString collumn2,QString collumn3,QString collumn4,QString collumn5, QString budget, QString date, QString id, QString type, QString condition)
{
    // Create a QPdfWriter object with the specified path
    QPdfWriter pdfWriter(path);
    QPainter painter(&pdfWriter);

    // Set the page size and orientation
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setPageOrientation(QPageLayout::Portrait);

    // Draw the contents of the PDF file
        int y = 100;
        painter.drawText(100, y, collumn1+": " + budget);
        y += 200; // Add spacing between the lines
        painter.drawText(100, y, collumn2+": " + date);
        y += 200; // Add spacing between the lines
        painter.drawText(100, y, collumn3+ ": " + id);
        y += 200; // Add spacing between the lines
        painter.drawText(100, y, collumn4+": " + type);
        y += 200; // Add spacing between the lines
        painter.drawText(100, y, collumn5+": " + condition);

    // Finish painting
    painter.end();
}


void MainWindow::on_pushButton_5_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                                   "/home",
                                                                   QFileDialog::ShowDirsOnly
                                                                   | QFileDialog::DontResolveSymlinks);
                       qDebug()<<dir;
                       QPdfWriter pdf(dir+"/PdfList.pdf");
                                              QPainter painter(&pdf);
                                             int i = 4000;
                                             // Load the logo image from a file
                                             QImage logoImage("C:\\Users\\nourh\\Desktop\\nourhene\\logo.jpg");
                                             QPixmap logoPixmap = QPixmap::fromImage(logoImage);
                                             logoPixmap = logoPixmap.scaled(1500, 1500, Qt::KeepAspectRatio, Qt::SmoothTransformation);

                                             // Draw the logo in the top right corner
                                             int logoX = pdf.width() - logoPixmap.width();
                                             int logoY = 50;
                                             painter.drawPixmap(logoX, logoY, logoPixmap);
                                         painter.drawPixmap(QRect(100,100,2000,2000),QPixmap(""));
                                                 painter.drawText(900,650,"nourhene ouhichi");

                                                 // painter.drawPixmap(QRect(7600,100,2100,2700),QPixmap("C:/Users/Admin/Desktop/logo.png"));

                                                  painter.setPen(Qt::blue);
                                                  painter.setFont(QFont("Time New Roman", 25));
                                                  painter.drawText(3000,1400,"Liste Des stocks");
                                                  painter.setPen(Qt::black);
                                                  painter.setFont(QFont("Time New Roman", 15));
                                                  painter.drawRect(100,100,9400,2500);
                                                  painter.drawRect(100,3000,9400,500);
                                                  painter.setFont(QFont("Time New Roman", 9));
                                                  painter.drawText(300,3300,"id");
                                                  painter.drawText(2300,3300,"libelle");
                                                  painter.drawText(4300,3300,"prix");
                                                  painter.drawText(6300,3300,"quantité");
                                                  painter.drawText(7500,3300,"id-service");
                                               //painter.drawText(8400,3300,"poids ");
                                                //  painter.drawText(9500,3300,"Date Retour");
                                                  //painter.drawText(10500,3300,"Date Naissance");

                                                  painter.drawRect(100,3000,9400,10700);


                                                  QTextDocument previewDoc;
                                                  QString pdflist = QDate::currentDate().toString("'data_'MM_dd_yyyy'.txt'");


                                                  QTextCursor cursor(&previewDoc);



                                                  QSqlQuery query;
                                                  query.prepare("select * from STOCKS");
                                                  query.exec();
                                                  while (query.next())
                                                  {
                                                      painter.drawText(300,i,query.value(0).toString());
                                                      painter.drawText(2300,i,query.value(1).toString());
                                                      painter.drawText(4300,i,query.value(2).toString());
                                                      painter.drawText(6300,i,query.value(3).toString());
                                                      painter.drawText(7500,i,query.value(4).toString());
                                                      painter.drawText(8500,i,query.value(5).toString());
                                                     // painter.drawText(9500,i,query.value(6).toString());
                                                     // painter.drawText(10500,i,query.value(7).toString());*/




                                                     i = i +500;
                                                  }
                                                  int reponse = QMessageBox::question(this, "Générer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?",
                                                                                      QMessageBox::Yes|QMessageBox::No);
                                                      if (reponse == QMessageBox::Yes)
                                                      {
                                                          QDesktopServices::openUrl(QUrl::fromLocalFile(dir+"/PdfList.pdf"));

                                                          painter.end();
                                                      }
                                                      else
                                                      {
                                                           painter.end();
             }
}



void MainWindow::on_pushButton_6_clicked()
{
    ui->tableView->setModel(search_table("stocks",ui->lineEdit->text()));
}

void MainWindow::on_toolButton_clicked()
{
    ui->tableView->setModel(sortbyup("stocks"));
}

void MainWindow::on_toolButton_2_clicked()
{
    ui->tableView->setModel(sortbydown("stocks"));
}

void MainWindow::on_pushButton_7_clicked()
{
    QMap<QString, QString> users;

    // Execute a SELECT query on the login table
    QSqlQuery query("SELECT users, password FROM login");

    // Retrieve the values of the users and password columns and add them to the QMap
    while (query.next()) {
        QString user = query.value(0).toString();
        QString password = query.value(1).toString();
        users.insert(user, password);
    }

    if(users.count(ui->lineEdit_2->text()) && users[ui->lineEdit_2->text()] == ui->lineEdit_3->text()){
        ui->pushButton_4->show();
        ui->stackedWidget->setCurrentIndex(0);
        ui->pushButton_8->show();
    }
    else ui->label_9->setText("echec de login");
}

void MainWindow::on_pushButton_8_clicked()
{
    if(ui->stackedWidget->currentIndex()==3)ui->stackedWidget->setCurrentIndex(0);else
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pushButton_9_clicked()
{
    // Create the credentials EmailAddress
    EmailAddress credentials("nourhene.ouhichi@esprit.tn",
                             "snuxbcchojyaealm");

    // Create the email object
    Email email = createEmail();

    // Create the SMTPClient
    SMTPClient* client = new SMTPClient("smtp.gmail.com",
                             465);

    // Try to send the email
    client->sendEmail(email);

    QMessageBox::information(this, "Information", "message envoyée");
}
