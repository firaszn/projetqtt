#include "notification.h"
#include <QSystemTrayIcon>
#include <QString>
void notification::notification_presence()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->setIcon(QIcon("C:/Users/admin/Downloads/téléchargement.png"));
    //notifyIcon->setVisible(1);
    notifyIcon->show();
    notifyIcon->showMessage("notification","Employé présent !",QSystemTrayIcon::Information,15000);

}
void notification::notification_absence()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->setIcon(QIcon("C:/Users/admin/Downloads/téléchargement.png"));
    //notifyIcon->setVisible(1);
    notifyIcon->show();
    notifyIcon->showMessage("notification","Employé absent !",QSystemTrayIcon::Information,15000);

}
