#ifndef Gestion_Client_H
#define Gestion_Client_H
#include "client.h"
#include <QMainWindow>
#include <connection.h>
#include "arduino.h"
#include <QMainWindow>
QT_BEGIN_NAMESPACE
namespace Ui { class Gestion_Client; }
QT_END_NAMESPACE

class Gestion_Client : public QMainWindow
{
    Q_OBJECT

public:
    Gestion_Client(QString nom,QString pass,QWidget *parent = nullptr);
    ~Gestion_Client();
    void update();
    void style();
private slots:
    void on_createbutton_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_trinom_clicked();

    void on_triemail_clicked();

    void on_modifybutton_clicked();

    void on_lineEdit_edit_id_editingFinished();

    void on_deletebutton_clicked();

    void on_lineEdit_delete_id_editingFinished();
    bool postrequest(QString smsmsg,QString phonenumber);

    void on_PDF_Button_clicked();

    void on_DeleteHome_clicked();

    void on_CreateHome_clicked();

    void on_ReadHome_clicked();

    void on_UpdateHome_clicked();

    void on_statistique_clicked();

    void on_pushButton_clicked();

    void on_afficheread_doubleClicked(const QModelIndex &index);

private:
    Ui::Gestion_Client *ui;
    client unusableclient;
    arduino A;
    QString nom1,pass1;
    QString apikey="9dLMZ7TtKWbjBzaCqgGL46GgPUEs";
    bool tried=false;
    float lineargradx = 1;
    float lineargrady = 1;
protected:
    void closeEvent(QCloseEvent *);
};
#endif // Gestion_Client_H
