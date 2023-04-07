#include "Gestion_Employee/gestion_employee.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include "login.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Connection c;
    bool test=c.createconnect();
    login l;

   if(test)
    {
          l.show();
          /*
        QMessageBox::information(nullptr, QObject::tr("data base is open"),
                             QObject::tr("connection successful.\nClique cancel to exit."),QMessageBox::Cancel);
            */
    }

    else
   {

        QMessageBox::information(nullptr, QObject::tr("data base is not open"),
                             QObject::tr("connection failed.\nClique cancel to exit."),QMessageBox::Cancel);
        exit(1);
                             }
    return a.exec();
}
