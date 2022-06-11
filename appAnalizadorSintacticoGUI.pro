QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    analizadorlexico.cpp \
    archivos.cpp \
    main.cpp \
    dialog.cpp \
    pila.cpp \
    sintactico.cpp #Aqui termina la carpeta sources
    #PD: No es necesario poner el "\" en el ultimo archivo de sources y headers, de esta forma se separan por carpetas...
    #bueno al menos en mi caso

HEADERS += \
    analizadorlexico.h \
    archivos.h \
    dialog.h \
    pila.h \
    sintactico.h
    #aplica igual aca, solo el ultimo no termina con "\"

FORMS += \
    dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
