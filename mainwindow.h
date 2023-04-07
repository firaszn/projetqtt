#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"employe.h"
#include <QTextStream>
#include <QPainter>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include <QPieSeries>
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
#include <QSystemTrayIcon>
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
#include <QMessageBox>
#include "QIntValidator"
#include <QDateEdit>
#include <QPlainTextEdit>
#include <QPrinter>
//#include <QPrinterInfo>
//#include <QPrintDialog>
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
#include "stat_categorie.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_supprimer_clicked();
    void on_rechercher_clicked();
void on_radioButton_clicked();
void on_pdf_clicked();




void on_tableView_clicked(const QModelIndex &index);





void on_pushButton_2_clicked();




void on_pushButton_3_clicked();

void on_pushButton_4_clicked();

void on_pushButton_5_clicked();


void on_chat_clicked();

void on_stat_clicked();

void on_gotometiers_clicked();

void on_back_2_clicked();

void on_back_clicked();

void on_back_3_clicked();

void on_pushButton_9_clicked();

void on_pushButton_7_clicked();

void on_pushButton_8_clicked();

void on_pushButton_6_clicked();

void on_back_4_clicked();

private:
    Ui::MainWindow *ui;
    employe Etmp;
     QTcpSocket*mSocket;
     stat_categorie *s;

};
#endif // MAINWINDOW_H
