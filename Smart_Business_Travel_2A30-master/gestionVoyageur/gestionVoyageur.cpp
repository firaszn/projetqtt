#include "gestionVoyageur.h"
#include "ui_gestionVoyageur.h"
#include "voyageur.h"
#include "camera.h"
#include <QtCharts>
#include "dialog_menu.h"
#include "mybutton.h"
gestionVoyageur::gestionVoyageur(QString nom,QString pass,QMainWindow *parent)
    : QMainWindow(parent)
    , ui(new Ui::gestionVoyageur)
{
    nom1=nom;
    pass1=pass;
    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
     //le slot update_label suite à la reception du signal readyRead (reception des données).
    ui->setupUi(this);
    //controle ajout
    ui->lineEdit_5->setValidator( new QIntValidator(1, 99999999, this));
    ui->lineEdit_4->setValidator( new QIntValidator(1, 99999999, this));
    QRegExp rx("\\b[a-zA-Z]{1,20}\\b");
    ui->lineEdit->setValidator( new QRegExpValidator(rx,this));
    ui->lineEdit_2->setValidator( new QRegExpValidator(rx,this));
    //controle modifier
    ui->lineEdit_10->setValidator( new QIntValidator(1, 99999999, this));
    ui->lineEdit_11->setValidator( new QIntValidator(1, 99999999, this));
    ui->lineEdit_9->setValidator( new QRegExpValidator(rx,this));
    ui->lineEdit_7->setValidator( new QRegExpValidator(rx,this));
    ui->tab_voyageur->setModel(v.afficher());
    style();
}

gestionVoyageur::~gestionVoyageur()
{
    delete ui;
}


void gestionVoyageur::on_pushButton_3_clicked()
{

    QString filename=QFileDialog::getOpenFileName(this, tr("choose"), "",tr("images(*.png *.jpg *.jpeg)"));
    if(QString::compare(filename,QString())!=0)
    {
        QImage image;
        bool valid=image.load(filename);

        if(valid)
        {

            image=image.scaledToWidth( ui->lbl_image->width(),Qt::SmoothTransformation);
            ui->lbl_image->setPixmap(QPixmap::fromImage(image));}
            else {
                //Error
            }
        }


    }


void gestionVoyageur::on_pushButton_clicked()
{ 
    int cin = ui->lineEdit_5->text().toInt();
    int phone = ui->lineEdit_4->text().toInt();
    QString name = ui->lineEdit->text();
    QString last_name = ui->lineEdit_2->text();
    QString mail = ui->lineEdit_3->text();
    QString gender="";
    if(ui->R->isChecked())
    {
       gender=ui->R->text();
    }else if(ui->R_2->isChecked())
    {
       gender=ui->R_2->text();
    }else
        {
           gender=ui->R_3->text();
        }
    QDate date_naiss=ui->dateEdit->date();


    Voyageur v(cin,phone,name,last_name,mail,gender,date_naiss);


    if(v.ajouter()){

    QMessageBox::information(nullptr,QObject::tr("message"),QObject::tr("voyageur ajouter avec succes.\n""Click Cancel to exist."),
                           QMessageBox::Cancel);
    ui->tab_voyageur->setModel(v.afficher());}

    else
    {
        QMessageBox::critical(nullptr,QObject::tr("message"),QObject::tr("voyageur non ajouter.\n""Click Cancel to exist."),
                              QMessageBox::Cancel);

    }

}

void gestionVoyageur::on_pushButton_4_clicked()
{
    if(v.supprimer(ui->lineEdit_6->text().toInt())){

     QMessageBox::information(nullptr,QObject::tr("message"),QObject::tr("voyageur supprimer avec succes.\n""Click Cancel to exist."),
                           QMessageBox::Cancel);
    ui->tab_voyageur->setModel(v.afficher());}

    else
    {
        QMessageBox::critical(nullptr,QObject::tr("message"),QObject::tr("voyageur non supprimer.\n""Click Cancel to exist."),
                              QMessageBox::Cancel);

    }
}



void gestionVoyageur::on_pushButton_6_clicked()
{
    int cin = ui->lineEdit_10->text().toInt();
    int phone = ui->lineEdit_11->text().toInt();
    QString name = ui->lineEdit_9->text();
    QString last_name = ui->lineEdit_7->text();
    QString mail = ui->lineEdit_8->text();
    QString gender="";
    if(ui->R_4->isChecked())
    {
       gender=ui->R_4->text();
    }else if(ui->R_5->isChecked())
    {
       gender=ui->R_5->text();
    }else

        {
           gender=ui->R_6->text();
        }
    QDate date_naiss=ui->dateEdit_2->date();
    Voyageur v(cin,phone,name,last_name,mail,gender,date_naiss);
    if(v.update(v,ui->lineEdit_10->text().toInt())){

     QMessageBox::information(nullptr,QObject::tr("message"),QObject::tr("voyageur modifier avec succes.\n""Click Cancel to exist."),
                           QMessageBox::Cancel);
    ui->tab_voyageur->setModel(v.afficher());}

    else
    {
        QMessageBox::critical(nullptr,QObject::tr("message"),QObject::tr("voyageur non modifier.\nClick Cancel to exist."),
                              QMessageBox::Cancel);

    }
}

void gestionVoyageur::on_pushButton_8_clicked()
{
    ui->tab_voyageur->setModel(v.tri());
}

void gestionVoyageur::on_pushButton_7_clicked()
{
    QPrinter p(QPrinter::ScreenResolution);
    p.setPaperSize(QPrinter::A4);
    p.setOrientation(QPrinter::Landscape);
    p.setOutputFormat(QPrinter::PdfFormat);
    p.setOutputFileName("fichier.pdf");
    QTextDocument doc;
        QVector<Voyageur> V = v.pdf();
        QString h("");
         h =     "<html>"
                 "<body>"
                 "<table border='1' cellspacing='10' width='100%' cellpadding='10'>"
                    "<tr>"
                        "<th>cin</th>"
                        "<th>name</th>"
                        "<th>last_name</th>"
                        "<th>phone</th>"
                        "<th>mail</th>"
                        "<th>date_nais</th>"
                        "<th>gender</th>"
                    "</tr>";
        for (int it = 0;it < V.size(); it++) {
            h +="<tr>"
                    "<td  align='center'>"+QString::number(V[it].get_cin())+"</td>"
                    "<td  align='center'>"+V[it].get_name()+"</td>"
                    "<td  align='center'>"+V[it].get_last_name()+"</td>"
                    "<td  align='center'>"+V[it].get_phone()+"</td>"
                    "<td  align='center'>"+V[it].get_mail()+"</td>"
                    "<td  align='center'>"+V[it].get_dt_naiss().toString("dd/MM/yyyy")+"</td>"
                    "<td  align='center'>"+V[it].get_gender()+"</td>"
                "</tr>";
        }

         h+= "</table>"
             "</body>"
             "</html>";
        doc.setHtml(h);
        doc.setPageSize(p.pageRect().size()); // This is necessary if you want to hide the page number
        doc.print(&p);
}

void gestionVoyageur::on_pushButton_9_clicked()
{
        QHBoxLayout *layout = new QHBoxLayout();
        QWidget *widget = new QWidget();
        qDeleteAll(widget->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));
        QPieSeries *series = new QPieSeries();
        QPieSlice *s1 = new QPieSlice();
        QPieSlice *s2 = new QPieSlice();
        QPieSlice *s3 = new QPieSlice();
        QSqlQuery q;
        QStringList S = {"male","female","custom"};
        q.prepare("SELECT GENDER FROM VOYAGEURS WHERE GENDER LIKE '"+S[0]+"%'");
        q.exec();
        int n_male = 0;
        while(q.next())
           n_male++;
        s1->setValue(n_male);
        s1->setLabel(S[0]);
        q.prepare("SELECT GENDER FROM VOYAGEURS WHERE GENDER LIKE '"+S[1]+"%'");
        q.exec();
        int n_female = 0;
        while(q.next())
            n_female++;
        s2->setValue(n_female);
        s2->setLabel(S[1]);
        q.prepare("SELECT GENDER FROM VOYAGEURS WHERE GENDER LIKE '"+S[2]+"%'");
        q.exec();
        int n_custom = 0;
        while(q.next())
            n_custom++;
        s3->setValue(n_custom);
        s3->setLabel(S[2]);
        series->append(s1);
        series->append(s2);
        series->append(s3);
         series->setLabelsVisible();
        series->setPieSize(n_male + n_female + n_custom);

        QChart *chart = new QChart();

        chart->removeAllSeries();
        chart->addSeries(series);
        chart->createDefaultAxes();
        chart->setTitle("Simple barchart example");
        chart->setAnimationOptions(QChart::AllAnimations);
        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignRight);

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->repaint();
        chartView->update();
        chartView->resize(460,230);
        layout->addWidget(chartView);
        widget->setLayout(layout);
        widget->layout()->deleteLater();
        widget->resize(400,400);
        widget->show();
}


void gestionVoyageur::on_lineEdit_12_textChanged(const QString &arg1)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM VOYAGEURS WHERE (NAME LIKE '"+arg1+"%')OR(LAST_NAME LIKE '"+arg1+"%')OR(CIN LIKE '"+arg1+"%')OR(PHONE LIKE '"+arg1+"%')OR(MAIL LIKE '"+arg1+"%')OR(GENDER LIKE '"+arg1+"%')OR(DATE_NAIS LIKE '"+arg1+"%')");
    ui->tab_voyageur->setModel(model);

}

void gestionVoyageur::on_pushButton_10_clicked()
{
    QWidget *w = new QWidget();
    w->resize(800,400);
    QTableView *t = new QTableView();
    t->setParent(w);
    t->setGeometry(0,0,800,400);
    t->setModel(v.Historique_Voyage(ui->lineEdit_10->text().toInt()));
    w->show();
}

void gestionVoyageur::on_pushButton_11_clicked()
{
  camera *c = new camera();
  c->show();
}

void gestionVoyageur::update_label()
{
    data=A.read_from_arduino();
    data.remove(0,data.length()-11);
    qDebug() << data;
    if(data != "" && data.length() > 10)
    {
        ui->lineEdit_rfid->setText(data);
    }

}
void gestionVoyageur::closeEvent(QCloseEvent *)
{        QMessageBox quitBox(
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


void gestionVoyageur::style()
{
    setStyleSheet(   "QMessageBox {"
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
