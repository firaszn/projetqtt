#ifndef gestionVoyageur_H
#define gestionVoyageur_H

#include <QMainWindow>
#include <QFileDialog>
#include <QRegExpValidator>
#include "voyageur.h"
#include <QPrinter>
#include <QPainter>
#include <QTextDocument>
#include <QHBoxLayout>
#include <QtCharts/QPieSlice>
#include <qpieseries.h>
#include <QtCharts/QChartView>
#include <QChart>
#include "arduino.h"
QT_BEGIN_NAMESPACE
namespace Ui { class gestionVoyageur; }
QT_END_NAMESPACE

class gestionVoyageur : public QMainWindow
{
    Q_OBJECT

public:
    gestionVoyageur(QString nom,QString pass,QMainWindow *parent = nullptr);
    ~gestionVoyageur();
    void style();
private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

    void on_lineEdit_12_textChanged(const QString &arg1);

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();
    void update_label();
private:
    Ui::gestionVoyageur *ui;
    Voyageur v;
    QByteArray data; // variable contenant les données reçues
    QString nom1,pass1;
    arduino A; // objet temporaire
    float lineargradx = 1;
    float lineargrady = 1;
protected:
    void closeEvent(QCloseEvent *);
};
#endif // gestionVoyageur_H
