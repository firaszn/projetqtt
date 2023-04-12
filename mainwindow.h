#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QSqlQueryModel>
#include <QMainWindow>
#include <QTableView>
#include <nourhene.h>
#include <QGraphicsView>

#include "SMTPClient/email.h"
#include "SMTPClient/emailaddress.h"
#include "SMTPClient/smtpclient.h"

namespace Ui {

class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    QSqlQueryModel* print_table(QString table);

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_pushButton_4_clicked();

    void generatePdfFile(QString path,QString collumn1,QString collumn2,QString collumn3,QString collumn4,QString collumn5, QString budget, QString date, QString id, QString type, QString condition);

    void on_pushButton_5_clicked();

    QSqlQueryModel * sortbydown(QString table);

    QSqlQueryModel * sortbyup(QString table);

    QSqlQueryModel * search_table(QString table ,QString search);

    void on_pushButton_6_clicked();

    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

    void displaystatistiques(QGraphicsView* view,QString table,QString collumn);

    void on_pushButton_7_clicked();

    Email createEmail(/*QString liblle, QString prix, QString quantite*/);

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
