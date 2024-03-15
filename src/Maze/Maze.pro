QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../backend/controller.cc \
    ../backend/data.cc \
    ../backend/maze.cc \
    ../backend/mazegenerator.cc \
    ../backend/parser.cc \
    main.cpp \
    mainwindow.cpp 
    

HEADERS += \
    ../backend/controller.h \
    ../backend/data.h \
    ../backend/maze.h \
    ../backend/mazegenerator.h \
    ../backend/parser.h \
    mainwindow.h 

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
