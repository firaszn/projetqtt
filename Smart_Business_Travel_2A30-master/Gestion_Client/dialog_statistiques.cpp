#include "dialog_statistiques.h"
#include "ui_dialog_statistiques.h"
#include "gestion_client.h"

#include <map>
Dialog_Statistiques::Dialog_Statistiques(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Statistiques)
{
    ui->setupUi(this);
}

Dialog_Statistiques::~Dialog_Statistiques()
{
    delete ui;
}


//pie chart
    void Dialog_Statistiques::choix_pie()
    {
    QSqlQuery q;
    qreal tot=0;

    q.prepare("SELECT * FROM CLIENT");
    q.exec();


    tot=q.size();
    std::map<int, int> my_map;
    while (q.next()){
            std::map<int, int>::iterator it=my_map.find(q.value(4).toDate().year());
        if (it != my_map.end())
       it->second++;
        else
            my_map.insert({q.value(4).toDate().year(),1});
    }
                std::map<int, int>::iterator itr;
                    QPieSeries *series = new QPieSeries();
    for (itr = my_map.begin(); itr != my_map.end(); ++itr) {
                series->append(QString::number(itr->first),(itr->second/tot));
        }







    // Create the chart widget
    QChart *chart = new QChart();

    // Add data to chart with title and show legend
    chart->addSeries(series);
    chart->legend()->show();


    // Used to display the chart
    chartView = new QChartView(chart,ui->label_stats);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(500,500);

    chartView->show();
}

void Dialog_Statistiques::on_closebutton_clicked()
{
    close();
}
