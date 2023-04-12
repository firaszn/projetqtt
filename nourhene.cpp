#include "nourhene.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <QDebug>
#include <QSqlError>

comptabilite::comptabilite()
{

}

QSqlQueryModel* MainWindow::print_table(QString table){
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("Select * from NOURHENE."+table);
    ui->tableView->setModel(model);
    return model;
}
