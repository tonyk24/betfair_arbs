#-------------------------------------------------
#
# Project created by QtCreator 2016-10-11T16:25:53
#
#-------------------------------------------------

QT       += core gui network multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Better
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    form.cpp \
    gamedialog.cpp \
    soccergame.cpp \
    resmat.cpp \
    arbcalculator.cpp \
    widgets/bfbetstablewidget.cpp \
    extsites/extsitesp.cpp \
    widgets/arbbetstablewidget.cpp \
    models/currentbetsmodel.cpp \
    extarbcalculator.cpp \
    ..\qcustomplot\qcustomplot.cpp \
    widgets/betplottingwidget.cpp

HEADERS  += mainwindow.h \
    form.h \
    gamedialog.h \
    soccergame.h \
    resmat.h \
    arbcalculator.h \
    types/extbet.h \
    widgets/bfbetstablewidget.h \
    types/bfpricesimlaysize.h \
    extsites/extsitesp.h \
    widgets/arbbetstablewidget.h \
    models/currentbetsmodel.h \
    extarbcalculator.h \
    models/currentbetsmodellisttype.h \
    types/bfarbbet.h \
    ..\qcustomplot\qcustomplot.h \
    widgets/betplottingwidget.h

FORMS    += mainwindow.ui \
    form.ui \
    gamedialog.ui


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../BetLib/release/ -lBetLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../BetLib/debug/ -lBetLib
else:unix: LIBS += -L$$OUT_PWD/../BetLib/ -lBetLib

INCLUDEPATH += $$PWD/../BetLib
DEPENDPATH += $$PWD/../BetLib

DISTFILES += \
    sounds/whistle.wav \
    sounds/Pling-KevanGC-1485374730.wav

RESOURCES += \
    resources.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../bfapingqtcpp/BetfairLib/release/ -lBetfairLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../bfapingqtcpp/BetfairLib/debug/ -lBetfairLib
else:unix: LIBS += -L$$OUT_PWD/../../../bfapingqtcpp/BetfairLib/ -lBetfairLib

INCLUDEPATH += $$PWD/../../../bfapingqtcpp/BetfairLib
DEPENDPATH += $$PWD/../../../bfapingqtcpp/BetfairLib
