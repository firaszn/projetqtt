#ifndef LOGIN_H
#define LOGIN_H
#include <QWidget>
#include <QDialog>
#include"dialog_menu.h"
#include"dialog_verriffication.h"

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *employee = nullptr);
    ~login();
private slots:
    void on_pushButton_LoginL_clicked();

    void on_oublier_clicked();

    void on_showpassword_clicked();
    void style();

private:
    Ui::login *ui;
   Dialog_menu *dialog_menu;
   float lineargradx = 1;
   float lineargrady = 1;
   Dialog_verriffication *D;
};

#endif // LOGIN_H
