QT       += core gui sql  printsupport network multimedia multimediawidgets serialport charts
QtPLUGIN += gif
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GestionService/GestionService.cpp \
    GestionService/QRCodeGenerator.cpp \
    GestionService/globals.cpp \
    GestionService/reservation.cpp \
    GestionService/service.cpp \
    Gestion_Client/client.cpp \
    Gestion_Client/dialog_statistiques.cpp \
    Gestion_Client/gestion_client.cpp \
    Gestion_Client/smtp.cpp \
    Gestion_Employee/employee.cpp \
    Gestion_Employee/gestion_employee.cpp \
    Gestion_Employee/messengerserver.cpp \
    Gestion_Employee/messengersocket.cpp \
    arduino.cpp \
    camera.cpp \
    connection.cpp \
    dialog_menu.cpp \
    dialog_stats.cpp \
    dialog_verriffication.cpp \
    exportexcelobject.cpp \
    gestionVoyage/gestionVoyage.cpp \
    gestionVoyage/voyage.cpp \
    gestionVoyageur/gestionVoyageur.cpp \
    gestionVoyageur/voyageur.cpp \
    login.cpp \
    main.cpp \
    messengerclient.cpp \
    messengerconnection.cpp \
    mybutton.cpp \
    qcustomplot.cpp

HEADERS += \
    GestionService/GestionService.h \
    GestionService/QRCodeGenerator.h \
    GestionService/globals.h \
    GestionService/reservation.h \
    GestionService/service.h \
    GestionService/sketch_clavier/sketch_clavier.ino \
    Gestion_Client/client.h \
    Gestion_Client/dialog_statistiques.h \
    Gestion_Client/gestion_client.h \
    Gestion_Client/smtp.h \
    Gestion_Employee/employee.h \
    Gestion_Employee/gestion_employee.h \
    Gestion_Employee/messengerserver.h \
    Gestion_Employee/messengersocket.h \
    arduino.h \
    camera.h \
    connection.h \
    dialog_menu.h \
    dialog_stats.h \
    dialog_verriffication.h \
    exportexcelobject.h \
    gestionVoyage/gestionVoyage.h \
    gestionVoyage/voyage.h \
    gestionVoyageur/gestionVoyageur.h \
    gestionVoyageur/voyageur.h \
    login.h \
    messengerclient.h \
    messengerconnection.h \
    mybutton.h \
    qcustomplot.h

FORMS += \
    GestionService/GestionService.ui \
    Gestion_Client/dialog_statistiques.ui \
    Gestion_Client/gestion_client.ui \
    Gestion_Employee/gestion_employee.ui \
    camera.ui \
    dialog_menu.ui \
    dialog_stats.ui \
    dialog_verriffication.ui \
    gestionVoyage/gestionVoyage.ui \
    gestionVoyageur/gestionVoyageur.ui \
    login.ui \
    messengerclient.ui \
    messengerconnection.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
RC_ICONS = tayarni.ico
RESOURCES += \
    Gestion_Client/images/pushbuttons.qrc \
    photo.qrc
