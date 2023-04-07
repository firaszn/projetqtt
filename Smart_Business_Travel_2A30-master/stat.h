#ifndef STAT_H
#define STAT_H
#include <QDialog>
#include "QtPrintSupport"


namespace Ui {
class stat;
}

class STAT : public QDialog
{
    Q_OBJECT

public:
    explicit stat(QWidget  *parent = nullptr);
    ~STAT();

private slots:
    void on_pushButton_Fermer_clicked();

private:
    Ui::stat *ui;
    void MakeStat();
    void statistiques(QVector<double>* ticks,QVector<QString> *labels);
};


#endif // STAT_H
