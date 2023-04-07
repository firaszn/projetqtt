#ifndef DIALOG_VERRIFFICATION_H
#define DIALOG_VERRIFFICATION_H
#include "arduino.h"
#include "Gestion_Employee/employee.h"

#include <QDialog>

namespace Ui {
class Dialog_verriffication;
}

class Dialog_verriffication : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_verriffication(QWidget *parent = nullptr);
    ~Dialog_verriffication();

private slots:
    void on_pushButton_clicked();
    void update();
    void closeEvent(QCloseEvent *);
private:
    Ui::Dialog_verriffication *ui;
    arduino A;
    Employee E;
    QString r="W";
};

#endif // DIALOG_VERRIFFICATION_H
