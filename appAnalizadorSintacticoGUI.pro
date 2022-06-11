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
    sintactico.cpp \
#<<<<<<< HEAD
#=======

#>>>>>>> f1d1d2f5047b714c642fbc238b252afff4b6f748
HEADERS += \
    analizadorlexico.h \
    archivos.h \
    dialog.h \
#<<<<<<< HEAD
 #   sintactico.h \
#=======
    pila.h \
    sintactico.h

#>>>>>>> ec1d35b0d614b04edd53a97ca2b3b8c443d2af2d
FORMS += \
    dialog.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
