#include <iostream>
#include "mybutton.h"
#include "GestionService.h"
#include "service.h"
#include <QApplication>
#include <QMessageBox>
#include <QIntValidator>
#include <QTableView>
#include <QTabWidget>
#include <QDebug>
#include <QString>
#include <QLineEdit>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QLabel>
#include "globals.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "QRCodeGenerator.h"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMouseEvent>
#include <QScrollArea>
#include <QImageWriter>
#include <QScrollBar>
#include <QSettings>
#include <QtPrintSupport/QPrintDialog>
#include <QtSql/QSqlError>
#include <QCloseEvent>
#include <QPushButton>
#include <QFileDialog>
#include <QTextStream>
#include <QTextDocument>
#include <QSystemTrayIcon>
#include <QPrinter>
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QtCharts>
#include <QSqlQuery>
#include <QSplitter>
#include <QSettings>
#include "ui_GestionService.h"
#include <QImage>
#include <QFileDialog>
#include <QTextCodec>
#include <QSqlRecord>
#include <vector>
#include<QComboBox>
#include <QAbstractItemView>
#include "reservation.h"
#include "dialog_menu.h"
#include <QPrintDialog>
#include <QPrintPreviewDialog>

using namespace std;
GestionService::GestionService(QString nom,QString pass,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GestionService)
{
    nom1=nom;
    pass1=pass;
    ui->setupUi(this);
    ui->le_places->setValidator(new QIntValidator(0,99999,this));
    ui->service_tab->setModel(serv.afficher());
    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
        QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));
        load_services();
        style();
}
GestionService::~GestionService()
{
    delete ui;
}

void GestionService::on_pb_add_clicked()
{
     i=i+1;
    QString nom= ui->le_name->text();
    QString type=ui->le_type->text();
    int nb_places=ui->le_places->text().toInt();
    QString disponibility;
   if (ui->radioButton->isChecked())
       disponibility="available";
   else if (ui->radioButton_2->isChecked())
       disponibility="not available";

QString spec1_text=ui->lineEdit_3->text();
int nb1=ui->lineEdit_6->text().toInt();
float price1=ui->lineEdit_7->text().toInt();
QString spec2_text=ui->lineEdit_4->text();
int nb2=ui->lineEdit_8->text().toInt();
float price2=ui->lineEdit_9->text().toInt();
QString spec3_text=ui->lineEdit_5->text();
int nb3=ui->lineEdit_10->text().toInt();
float price3=ui->lineEdit_11->text().toInt();
service Ser(i,type,nom,disponibility,nb_places);
specification spec1(nom,spec1_text,nb1,price1);
bool test=Ser.ajouter();
spec1.ajouter();
specification spec2(nom,spec2_text,nb2,price2);
spec2.ajouter();
specification spec3(nom,spec3_text,nb3,price3);
spec3.ajouter();
if(test)
{
   ui->service_tab->setModel(serv.afficher());

            QMessageBox::information(nullptr, QObject::tr("OK"),
                        QObject::tr("Ajout effectué\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
            load_services();

}
else
    QMessageBox::critical(nullptr, QObject::tr("not OK"),
                QObject::tr("Ajout non effectué\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

}
void GestionService::on_pb_delete_clicked()
{
ui->tabWidget->insertTab(6,new QTabWidget(),"Delete"); //Creation d'un nouveau Tab Widget pour la suppression
ui->tabWidget->setCurrentWidget(ui->tabWidget->widget(6));
//Create a Line Edit:
QHBoxLayout *layout = new QHBoxLayout;
ui->tabWidget->widget(6)->setLayout(layout);
QLineEdit *le = new QLineEdit;
le->setMaximumWidth(100);
le->setObjectName("le_idd");
le->setText("");
ui->tabWidget->widget(6)->layout()->addWidget(le);
//Fin
//Create a push button confirm:
QPushButton *pb = new QPushButton;
pb->setMaximumWidth(100);
pb->setObjectName("pb_confirm");
pb->setText("Confirm");
ui->tabWidget->widget(6)->layout()->addWidget(pb);
//connect(pb, SIGNAL(clicked()()), s_map, SLOT(map()));
connect(pb, &QPushButton::pressed, this,&GestionService::handleButton);
//Fin
//Create a push button cancel:
QPushButton *pbc = new QPushButton;
pbc->setMaximumWidth(100);
pbc->setObjectName("pb_cancel");
pbc->setText("Cancel");
ui->tabWidget->widget(6)->layout()->addWidget(pbc);
connect(pbc, &QPushButton::pressed, this,&GestionService::handleButton1);
//Fin
//Create a label:
QLabel *txt= new QLabel();
txt->setAlignment(Qt::AlignTop | Qt::AlignLeft);
txt->setText("Please write the service's ID below:");
ui->tabWidget->widget(6)->layout()->addWidget(txt);
 //Fin
le_confirm=le;

}
void GestionService::handleButton()
{
int id=le_confirm->text().toInt();
    bool test=false;
          test=  serv.supprimer(id);
    if(test)
    {
        ui->service_tab->setModel(serv.afficher());
                QMessageBox::information(nullptr, QObject::tr("OK"),
                            QObject::tr("Suppression effectuée\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
                load_services();
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                    QObject::tr("Suppression non effectuée\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    ui->tabWidget->widget(6)->deleteLater();
    ui->tabWidget->setCurrentWidget(ui->tabWidget->widget(1));
}
void GestionService::handleButton1()
{
    ui->tabWidget->widget(6)->deleteLater();
    ui->tabWidget->setCurrentWidget(ui->tabWidget->widget(1));
}

void GestionService::on_pb_update_clicked()
{
ui->tabWidget->setCurrentWidget(ui->tabWidget->widget(2));
}

void GestionService::on_pb_updConfirm_clicked()
{
int id=ui->le_id_upd->text().toInt();
QString nom= ui->le_name_upd->text();
QString type=ui->le_type_upd->text();
QString disponibility;
if (ui->radioButton_3->isChecked())
    disponibility="available";
else if (ui->radioButton_4->isChecked())
    disponibility="not available";
int nb_places=ui->le_places_upd->text().toInt();
service S(id,type,nom,disponibility,nb_places);
bool test=S.modify();
if(test)
{
    ui->service_tab->setModel(serv.afficher());
            QMessageBox::information(nullptr, QObject::tr("OK"),
                        QObject::tr("Mise à jour effectué\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
}
else
    QMessageBox::critical(nullptr, QObject::tr("not OK"),
                QObject::tr("Mise à jour non effectué\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}

void GestionService::on_pb_sort_clicked()
{
        proxy = new QSortFilterProxyModel();     //masque du tableau
        proxy->setDynamicSortFilter(true);
        proxy->setFilterKeyColumn(1);
        proxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
        proxy->setSourceModel(serv.afficher());
proxy->sort(5,Qt::DescendingOrder);
ui->service_tab->setModel(proxy);
}

void GestionService::on_pb_pdf_clicked()
{
    QString strStream;
                QTextStream out(&strStream);
                const int rowCount = ui->service_tab->model()->rowCount();
                const int columnCount =ui->service_tab->model()->columnCount();

                out <<  "<style>.styled-table { border-collapse: collapse; margin: 25px 0; font-size: 0.9em; font-family: sans-serif; min-width: 400px; box-shadow: 0 0 20px rgba(0, 0, 0, 0.15); } .styled-table thead tr { background-color: #009879; color: #ffffff; text-align: left; } .styled-table th, .styled-table td { padding: 12px 15px; } .styled-table tbody tr { border-bottom: 1px solid #dddddd; } .styled-table tbody tr:nth-of-type(even) { background-color: #f3f3f3; } .styled-table tbody tr:last-of-type { border-bottom: 2px solid #009879; } .styled-table tbody tr.active-row { font-weight: bold; color: #009879; }</style>";
                out <<  "<html>\n"
                        "<head>\n"
                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                        <<  QString("<title>%1</title>\n").arg("service")
                       <<  "<img src='photo.jpg'>\n"
                        <<  "</head>\n"
                        "<body>\n"
                            "<h1>Liste des Services:</h1>"

                            "<table class='styled-table'>\n";

                // headers
                    out << "<thead><tr>";
                    for (int column = 0; column < columnCount; column++)
                        if (!ui->service_tab->isColumnHidden(column))
                            out << QString("<th>%1</th>").arg(ui->service_tab->model()->headerData(column, Qt::Horizontal).toString());
                    out << "</tr></thead>\n";
                    // data table
                       for (int row = 0; row < rowCount; row++) {
                           out << "<tr>";
                           for (int column = 0; column < columnCount; column++) {
                               if (!ui->service_tab->isColumnHidden(column)) {
                                   QString data = ui->service_tab->model()->data(ui->service_tab->model()->index(row, column)).toString().simplified();
                                   out << QString("<td>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                               }
                           }
                           out << "</tr>\n";
                       }
                       out <<  "</table>\n"
                           "</body>\n"
                           "</html>\n";



        QTextDocument *document = new QTextDocument();
        document->setHtml(strStream);
        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName("services.pdf");
        document->print(&printer);
}

void GestionService::on_le_chercher_textChanged(const QString &arg1)
{
 ui->service_tab->setModel(serv.chercher(arg1));
}
void GestionService::on_QRgenerate_clicked()
{
ui->scrollArea_6->installEventFilter(this);
    QSettings ini( "", QSettings::IniFormat );
    ui->splitter_4->restoreState( ini.value( ui->splitter_4->objectName() ).toByteArray() );
    ui->splitter_5->restoreState( ini.value( ui->splitter_5->objectName() ).toByteArray() );
    ui->sBoxScale_3->setValue( ini.value( ui->sBoxScale_3->objectName(), 4 ).toInt() );
    restoreState( ini.value( "State" ).toByteArray() );
    restoreGeometry( ini.value( "Geometry" ).toByteArray() );

    setScale( ui->sBoxScale_3->value() );
    updateQRImage();
}
void GestionService::updateQRImage()
{
    int sizeText = ui->pTextEditQRText_3->toPlainText().size();
    ui->labelSizeText_3->setText( QString::number( sizeText ) );

    int levelIndex = 1;
    int versionIndex = 0;
    bool bExtent = true;
    int maskIndex = -1;
    QString encodeString = ui->pTextEditQRText_3->toPlainText();

    successfulEncoding = qrEncode.EncodeData( levelIndex, versionIndex, bExtent, maskIndex, encodeString.toUtf8().data() );
    if ( !successfulEncoding )
    {
        ui->image_label_3->clear();
        ui->image_label_3->setText( tr("QR Code...") );
        ui->labelSize_3->clear();
        ui->ButtonSave->setEnabled( successfulEncoding );
        return;
    }

    int qrImageSize = qrEncode.m_nSymbleSize;

    encodeImageSize = qrImageSize + ( QR_MARGIN * 2 );
    QImage encodeImage( encodeImageSize, encodeImageSize, QImage::Format_Mono );
    encodeImage.fill( 1 );


    for ( int i = 0; i < qrImageSize; i++ )
        for ( int j = 0; j < qrImageSize; j++ )
            if ( qrEncode.m_byModuleData[i][j] )
                encodeImage.setPixel( i + QR_MARGIN, j + QR_MARGIN, 0 );

    ui->image_label_3->setPixmap( QPixmap::fromImage( encodeImage ) );

    setScale(ui->sBoxScale_3->value());
    ui->ButtonSave->setEnabled( successfulEncoding );
}
void GestionService::setScale(int scale)
{
    if ( successfulEncoding )
    {
        int scale_size = encodeImageSize * scale;

        const QPixmap & scale_image = ui->image_label_3->pixmap()->scaled( scale_size, scale_size );
        ui->image_label_3->setPixmap( scale_image );

        const QString & size_info = QString( "%1x%2" ).arg( scale_size ).arg( scale_size );
        ui->labelSize_3->setText( size_info );
    }
}



void GestionService::closeEvent(QCloseEvent *)
{
    if (!forcequit)
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
    }
                A.close_arduino();
    this->close();
    //qApp->quit();

}
bool GestionService::eventFilter( QObject * object, QEvent * event )
{
    QScrollArea * scrollArea = ui->scrollArea_6;

    if ( object == scrollArea )
    {
        if ( event->type() == QEvent::MouseButtonPress )
        {
            QMouseEvent * mouseEvent = static_cast < QMouseEvent * > ( event );
            if ( mouseEvent->button() == Qt::LeftButton )
            {
                lastPos = mouseEvent->pos();

                if( scrollArea->horizontalScrollBar()->isVisible()
                        || scrollArea->verticalScrollBar()->isVisible() )
                    scrollArea->setCursor( Qt::ClosedHandCursor );
                else
                    scrollArea->setCursor( Qt::ArrowCursor );
            }

        }else if ( event->type() == QEvent::MouseMove )
        {
            QMouseEvent *mouseEvent = static_cast < QMouseEvent * > ( event );

            if ( mouseEvent->buttons() == Qt::LeftButton )
            {
                lastPos -= mouseEvent->pos();

                int hValue = scrollArea->horizontalScrollBar()->value();
                int vValue = scrollArea->verticalScrollBar()->value();

                scrollArea->horizontalScrollBar()->setValue( lastPos.x() + hValue );
                scrollArea->verticalScrollBar()->setValue( lastPos.y() + vValue );

                lastPos = mouseEvent->pos();
            }

        }else if ( event->type() == QEvent::MouseButtonRelease )
            scrollArea->setCursor( Qt::ArrowCursor );
    }

    return QWidget::eventFilter(object, event);
}

void GestionService::on_ButtonSave_clicked()
{
    const QString & path = QFileDialog::getSaveFileName( this, QString() , "qrcode");
    if ( path.isNull() )
        return;

    ui->image_label_3->pixmap()->save( path );
}

void GestionService::on_sBoxScale_3_valueChanged(int arg1)
{
     setScale( arg1 );
}

void GestionService::on_pTextEditQRText_3_textChanged()
{
    updateQRImage();
}

void GestionService::on_pButtonQuit_2_clicked()
{
      close();
}
void GestionService::update_label()
{

data=A.read_from_arduino();
qDebug()<<data;
if(data=="1")
{
    idA=idA+"1";
}
else if(data=="2")
{
    idA=idA+"2";
}
else if(data=="3")
{
    idA=idA+"3";
}
else if(data=="4")
{
    idA=idA+"4";
}
else if(data=="5")
{
    idA=idA+"5";
}
else if(data=="6")
{
    idA=idA+"6";
}
else if(data=="7")
{
    idA=idA+"7";
}
else if(data=="8")
{
    idA=idA+"8";
}
else if(data=="9")
{
    idA=idA+"9";
}
else if(data=="0")
{
    idA=idA+"0";
}
else if(data=="A")
{
    qDebug()<<idA;
    index=ui->tabWidget->currentIndex();
    ui->tabWidget->setCurrentWidget(ui->tabWidget->widget(6));
    if(idA=="")
    {
        QSqlQueryModel *model= new QSqlQueryModel();
         ui->tableView->setModel(model);
    }
    else
ui->tableView->setModel(serv.chercherSelonId(idA));
}
else if(data=="B")
{
ui->tabWidget->setCurrentWidget(ui->tabWidget->widget(index));
}
else if(data=="C")
{
     QSqlQueryModel *model= new QSqlQueryModel();
    idA=QStringLiteral("");
    ui->tableView->setModel(model);
}
else if(data=="D")
{
idA.chop(1);
}
else if(data=="#")
{
    ui->lineEdit->setEchoMode(QLineEdit::Normal);
}
else if (data=="##")
{
    forcequit=true;
close();
}
else if (data=="*")
{
ui->lineEdit->setEchoMode(QLineEdit::Password);
}
ui->lineEdit->setText(idA);
}

void GestionService::load_services()
{
    ui->comboBox->clear();
      ui->comboBox->setCurrentIndex(-1);
ui->comboBox->insertItem(-1,"--Select Service--");
QSqlQuery query("SELECT TYPE FROM SERVICES");
vector <QString> vs;
int typeID = query.record().indexOf("TYPE");
while (query.next()) {
    QString aux=query.value(typeID).toString();
    vs.push_back(aux);
     // ui->comboBox->addItem(query.value(typeID).toString());
    }
for(unsigned int i=0;i<vs.size();i++)
{
    bool test=true;
    for(unsigned int j=0;j<i;j++)
    {
        if (vs[i]==vs[j])
            test=false;
    }
    if (test==true)
      ui->comboBox->addItem(vs[i]);
}
}
void GestionService::load_services_name(QString type)
{
    QString ch;
    ui->comboBox_2->clear();
QSqlQuery query("SELECT NOM FROM SERVICES WHERE TYPE like'"+type+"'");
int nameID = query.record().indexOf("NOM");
while (query.next()) {
    ch=query.value(nameID).toString();
    if (ch!="")
    ui->comboBox_2->addItem(ch);
    }
}
void GestionService::on_comboBox_currentTextChanged(const QString &arg1)
{
    qDebug()<<arg1;
    load_services_name(arg1);
}
void GestionService::on_comboBox_2_currentTextChanged(const QString &arg1)
{
QSqlQueryModel* model=new QSqlQueryModel();
model->clear();
model->setQuery("SELECT SERVICE_SPEC,NB_PLACES,PRICE FROM SPECIFICATIONS WHERE SERVICE_NAME like'"+arg1+"'");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Specification"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nb Places"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Price"));
ui->tableView_2->setModel(model);
QSqlQuery query("SELECT SERVICE_SPEC FROM SPECIFICATIONS WHERE SERVICE_NAME like'"+arg1+"'");
int nameID = query.record().indexOf("SERVICE_SPEC");
while (query.next()) {
ui->comboBox_3->addItem(query.value(nameID).toString());
}
}
void GestionService::on_pb_book_clicked()
{
    QSqlQueryModel *model= new QSqlQueryModel();
    int x;
    float price,sum;
int n_perso=ui->le_book->text().toInt();
qDebug()<<n_perso;
QDate sd=ui->startDateEdit_2->date();
QDate ed=ui->startDateEdit_3->date();
QString spec=ui->comboBox_3->currentText();
QString service_name=ui->comboBox_2->currentText();
qDebug()<<spec;
QSqlQuery query("SELECT * FROM SPECIFICATIONS WHERE SERVICE_SPEC like'"+spec+"'");
int placeID = query.record().indexOf("NB_PLACES");
int priceID = query.record().indexOf("PRICE");
while (query.next()) {
x=query.value(placeID).toInt();
price=query.value(priceID).toFloat();
}
if ((n_perso<=x)&&(n_perso>0))
{
    reservation r(service_name,sd,ed,x,spec,price);
bool test=r.reserver();
if(test)
   {
    x=x-n_perso;
    QString reste=QString::number(x);
model->setQuery("UPDATE SPECIFICATIONS SET NB_PLACES='"+reste+"'  WHERE SERVICE_SPEC like'"+spec+"'");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Specification"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nb Places"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Price"));
ui->tableView_2->setModel(model);
sum=price*n_perso;
QString p=QString::number(sum);
ui->lineEdit_2->setText(p);
   QMessageBox::information(nullptr, QObject::tr("OK"),
                QObject::tr("Reservation effectué\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);}
else
   { QMessageBox::critical(nullptr, QObject::tr("not OK"),
                QObject::tr("Reservation non effectuée\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}
}
}

void GestionService::style()
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

void GestionService::on_pushButton_clicked()
{
    QString strStream;
                QTextStream out(&strStream);

                out <<  "<html>\n"
                        "<head>\n"
                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                        <<  QString("<title>%1</title>\n").arg("service")
                        <<  "</head>\n"
                        "<body>\n"
                            "<style> h1 { color: #059CDE; }</style><h1><center>Payment Receipt</center></h1>"
"<p>Tayarni Travel Agency"
"<br> 22, Avenue Newton"
"<br>Tunis"
"<br>Tel: (+216) 28 607 951</p>"
                            "<table border=1 cellspacing=2 cellpadding=5>\n";

                // headers
                    out << "<thead><tr bgcolor=#f0f0f0>";
                    for (int column = 0; column <2; column++)
                        if (!ui->service_tab->isColumnHidden(column))
                            out << QString("<th>%1</th>").arg(ui->service_tab->model()->headerData(column, Qt::Horizontal).toString());
                    out << "</tr></thead>\n";
                    // data table
                       for (int row = 0; row < 6; row++) {
                           out << "<tr>";
                           for (int column = 0; column < 2; column++) {
                               if (!ui->service_tab->isColumnHidden(column)) {
                                   QString data = ui->service_tab->model()->data(ui->service_tab->model()->index(row, column)).toString().simplified();
                                   out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                               }
                           }
                           out << "</tr>\n";
                       }
                       out <<  "</table>\n"
                           "</body>\n"
                           "</html>\n";

        QTextDocument *document = new QTextDocument();
        document->setHtml(strStream);

        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName("recu");
        QPrintPreviewDialog *dlg = new QPrintPreviewDialog(&printer,this);
        dlg->setWindowTitle(QObject::tr("Print Document"));
        if(dlg->exec() == QDialog::Accepted) {
            document->print(&printer);
                }
                delete dlg;

}
