#ifndef Gestion_Employee_H
#define Gestion_Employee_H
#include "Gestion_Employee/employee.h"
#include <QProcess>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Gestion_Employee; }
QT_END_NAMESPACE

class Gestion_Employee : public QMainWindow
{
    Q_OBJECT

public:
    Gestion_Employee(QString nom,QString pass,QWidget *parent = nullptr);
    ~Gestion_Employee();
    void style();
private slots:
    void on_pt_Ajouter_clicked();

    void on_pt_Supprimer_clicked();

    void on_pt_modiffier_clicked();

    void on_pt_recherche_clicked();

    void on_pt_trinom_clicked();

    void on_pt_tricin_clicked();

 //   void on_pt_inserer_clicked();
    //void style_tableview();
    void on_pt_pdf_clicked();

    void on_pt_stat_clicked();

    void on_chat_box_clicked();

    void on_Excel_clicked();

    void on_tabemployee_doubleClicked(const QModelIndex &index);

    void on_tabWidget_currentChanged();

    void on_chat_box_2_clicked();

private:
    Ui::Gestion_Employee *ui;
    Employee E;
        QString nom1,pass1;
        float lineargradx = 1;
        float lineargrady = 1;
            QProcess p;
protected:
    void closeEvent(QCloseEvent *);
};
#endif // Gestion_Employee_H
