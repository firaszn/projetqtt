/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QPushButton *pushButton_4;
    QStackedWidget *stackedWidget;
    QWidget *crud;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *id;
    QLabel *label_5;
    QLabel *label_4;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QLineEdit *prix;
    QLineEdit *quantite;
    QLineEdit *libelle;
    QLabel *label_6;
    QLineEdit *id_services;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout;
    QTableView *tableView;
    QPushButton *pushButton;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QPushButton *pushButton_6;
    QToolButton *toolButton;
    QToolButton *toolButton_2;
    QWidget *login;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QPushButton *pushButton_7;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QWidget *metiers;
    QTableView *tableView_2;
    QPushButton *pushButton_5;
    QGraphicsView *graphicsView;
    QWidget *Mailing;
    QPushButton *pushButton_9;
    QWidget *layoutWidget2;
    QGridLayout *gridLayout_2;
    QLabel *label_12;
    QLineEdit *to;
    QLabel *label_10;
    QLineEdit *subjecy;
    QLabel *label_11;
    QPlainTextEdit *content;
    QPushButton *pushButton_8;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(742, 425);
        MainWindow->setStyleSheet(QStringLiteral(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        centralwidget->setStyleSheet(QStringLiteral("QLineEdit{border-radius:5px;}"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setEnabled(true);
        label->setGeometry(QRect(0, 0, 741, 411));
        label->setPixmap(QPixmap(QString::fromUtf8(":/ui.png")));
        label->setScaledContents(true);
        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(150, 80, 75, 23));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(40, 110, 671, 271));
        crud = new QWidget();
        crud->setObjectName(QStringLiteral("crud"));
        layoutWidget = new QWidget(crud);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 20, 331, 241));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        id = new QLineEdit(layoutWidget);
        id->setObjectName(QStringLiteral("id"));

        gridLayout->addWidget(id, 0, 1, 1, 1);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 3, 0, 1, 1);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 5, 0, 1, 2);

        pushButton_3 = new QPushButton(layoutWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        gridLayout->addWidget(pushButton_3, 6, 0, 1, 2);

        prix = new QLineEdit(layoutWidget);
        prix->setObjectName(QStringLiteral("prix"));

        gridLayout->addWidget(prix, 2, 1, 1, 1);

        quantite = new QLineEdit(layoutWidget);
        quantite->setObjectName(QStringLiteral("quantite"));

        gridLayout->addWidget(quantite, 3, 1, 1, 1);

        libelle = new QLineEdit(layoutWidget);
        libelle->setObjectName(QStringLiteral("libelle"));

        gridLayout->addWidget(libelle, 1, 1, 1, 1);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 4, 0, 1, 1);

        id_services = new QLineEdit(layoutWidget);
        id_services->setObjectName(QStringLiteral("id_services"));

        gridLayout->addWidget(id_services, 4, 1, 1, 1);

        layoutWidget_2 = new QWidget(crud);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(340, 50, 331, 211));
        verticalLayout = new QVBoxLayout(layoutWidget_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tableView = new QTableView(layoutWidget_2);
        tableView->setObjectName(QStringLiteral("tableView"));

        verticalLayout->addWidget(tableView);

        pushButton = new QPushButton(layoutWidget_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);

        layoutWidget1 = new QWidget(crud);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(340, 20, 331, 25));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit = new QLineEdit(layoutWidget1);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        pushButton_6 = new QPushButton(layoutWidget1);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        horizontalLayout->addWidget(pushButton_6);

        toolButton = new QToolButton(layoutWidget1);
        toolButton->setObjectName(QStringLiteral("toolButton"));

        horizontalLayout->addWidget(toolButton);

        toolButton_2 = new QToolButton(layoutWidget1);
        toolButton_2->setObjectName(QStringLiteral("toolButton_2"));

        horizontalLayout->addWidget(toolButton_2);

        stackedWidget->addWidget(crud);
        login = new QWidget();
        login->setObjectName(QStringLiteral("login"));
        lineEdit_2 = new QLineEdit(login);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(280, 80, 113, 20));
        lineEdit_3 = new QLineEdit(login);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(280, 120, 113, 20));
        pushButton_7 = new QPushButton(login);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setGeometry(QRect(300, 160, 75, 23));
        label_7 = new QLabel(login);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(190, 90, 47, 14));
        label_8 = new QLabel(login);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(190, 120, 47, 14));
        label_9 = new QLabel(login);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(280, 60, 111, 20));
        stackedWidget->addWidget(login);
        metiers = new QWidget();
        metiers->setObjectName(QStringLiteral("metiers"));
        tableView_2 = new QTableView(metiers);
        tableView_2->setObjectName(QStringLiteral("tableView_2"));
        tableView_2->setGeometry(QRect(330, 20, 256, 192));
        pushButton_5 = new QPushButton(metiers);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(420, 230, 75, 23));
        graphicsView = new QGraphicsView(metiers);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(20, 10, 281, 251));
        stackedWidget->addWidget(metiers);
        Mailing = new QWidget();
        Mailing->setObjectName(QStringLiteral("Mailing"));
        pushButton_9 = new QPushButton(Mailing);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));
        pushButton_9->setGeometry(QRect(550, 210, 75, 23));
        layoutWidget2 = new QWidget(Mailing);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(50, 20, 581, 181));
        gridLayout_2 = new QGridLayout(layoutWidget2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label_12 = new QLabel(layoutWidget2);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout_2->addWidget(label_12, 0, 0, 1, 1);

        to = new QLineEdit(layoutWidget2);
        to->setObjectName(QStringLiteral("to"));

        gridLayout_2->addWidget(to, 0, 1, 1, 1);

        label_10 = new QLabel(layoutWidget2);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_2->addWidget(label_10, 1, 0, 1, 1);

        subjecy = new QLineEdit(layoutWidget2);
        subjecy->setObjectName(QStringLiteral("subjecy"));

        gridLayout_2->addWidget(subjecy, 1, 1, 1, 1);

        label_11 = new QLabel(layoutWidget2);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout_2->addWidget(label_11, 2, 0, 1, 1);

        content = new QPlainTextEdit(layoutWidget2);
        content->setObjectName(QStringLiteral("content"));

        gridLayout_2->addWidget(content, 2, 1, 1, 1);

        stackedWidget->addWidget(Mailing);
        pushButton_8 = new QPushButton(centralwidget);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));
        pushButton_8->setGeometry(QRect(250, 80, 75, 23));
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        statusbar->setSizeGripEnabled(false);
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label->setText(QString());
        pushButton_4->setText(QApplication::translate("MainWindow", "PDF/stats", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "ID", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "LIBELLE", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "Quantity", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "PRIX", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "EDIT", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("MainWindow", "ADD", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "ID_SERVICE", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "supprimer", Q_NULLPTR));
        pushButton_6->setText(QApplication::translate("MainWindow", "recherche", Q_NULLPTR));
        toolButton->setText(QApplication::translate("MainWindow", "asc", Q_NULLPTR));
        toolButton_2->setText(QApplication::translate("MainWindow", "desc", Q_NULLPTR));
        pushButton_7->setText(QApplication::translate("MainWindow", "login", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "User", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "Password", Q_NULLPTR));
        label_9->setText(QString());
        pushButton_5->setText(QApplication::translate("MainWindow", "generate pdf", Q_NULLPTR));
        pushButton_9->setText(QApplication::translate("MainWindow", "Send", Q_NULLPTR));
        label_12->setText(QApplication::translate("MainWindow", "To : ", Q_NULLPTR));
        label_10->setText(QApplication::translate("MainWindow", "Subject", Q_NULLPTR));
        label_11->setText(QApplication::translate("MainWindow", "Description", Q_NULLPTR));
        pushButton_8->setText(QApplication::translate("MainWindow", "Mail", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
