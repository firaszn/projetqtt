//#ifndef MAINWINDOW_H
//#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include "service.h"
#include <QSortFilterProxyModel>
#include <QTextDocument>
#include <QTextTableFormat>
#include <QStandardItemModel>
#include <QDesktopWidget>
#include <QSettings>
#include <QPrinter>
#include <QTextStream>
#include <QFile>
#include <QDataStream>
#include "QRCodeGenerator.h"
#include <QEvent>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QLabel>
#include <QDate>
#include "arduino.h"
#include "reservation.h"
namespace Ui {
class GestionService;
}

class GestionService : public QMainWindow
{
    Q_OBJECT

public:
    explicit GestionService(QString nom,QString pass,QWidget *parent = nullptr);
    ~GestionService();
    QSortFilterProxyModel *proxy;
    void style();

private slots:
    void on_pb_add_clicked();
    void on_pb_delete_clicked();
    void handleButton();
    void handleButton1();
    void on_pb_update_clicked();
    void on_pb_updConfirm_clicked();    
    void on_pb_sort_clicked();
    void on_pb_pdf_clicked();
    void on_le_chercher_textChanged(const QString &arg1);
    void on_QRgenerate_clicked();
    void updateQRImage();
    void setScale(int);
    void on_ButtonSave_clicked();
    void on_sBoxScale_3_valueChanged(int arg1);
    void on_pTextEditQRText_3_textChanged();
    void on_pButtonQuit_2_clicked();
    void update_label();
    void on_comboBox_currentTextChanged(const QString &arg1);
    void on_comboBox_2_currentTextChanged(const QString &arg1);
    void on_pb_book_clicked();

    void on_pushButton_clicked();

private:
    Ui::GestionService *ui;
    service serv;
    specification s;
    reservation res;
    QLineEdit* le_confirm;
    CQR_Encode qrEncode;
    bool successfulEncoding;
    int encodeImageSize;
    QPoint lastPos;
    QString nom1,pass1;
    bool forcequit=false;
    //arduino:
    QByteArray data; // variable contenant les données reçues
    arduino A; // objet temporaire
     QString idA=QStringLiteral("");
     int index=0;
    // void fillTable(QString serialString);
     void load_services();
     void load_services_name(QString type);
     float lineargradx = 1;
     float lineargrady = 1;
protected:
    void closeEvent(QCloseEvent *);
    bool eventFilter( QObject * object, QEvent * event );
};

//#endif // MAINWINDOW_H

