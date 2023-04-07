#ifndef DIALOG_MENU_H
#define DIALOG_MENU_H

#include <QDialog>

#include<QTimer>
#include<QDebug>
#include<QDateTime>
namespace Ui {
class Dialog_menu;
}

class Dialog_menu : public QDialog
{
    Q_OBJECT

public:
    Dialog_menu(QString nom,QString pass,QWidget *parent = nullptr);
    ~Dialog_menu();
    QString Get_Role_Menu(QString nom,QString pass);

private slots:
    void on_Buttonemploye_clicked();

    void on_Buttonclient_clicked();

    void on_Buttonvouyage_clicked();

    void on_Buttonvoyageur_clicked();


private slots:
    void Timer_TimeOut_Event_Slot();
    void Timer_TimeOut_Event_Slot1();
    void on_Buttonservice_clicked();

private:
    Ui::Dialog_menu *ui;
    QTimer *Timer;
    bool forceclose = false;
protected:
    void closeEvent(QCloseEvent *);

};

#endif // DIALOG_MENU_H
