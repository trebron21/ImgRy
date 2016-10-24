#-------------------------------------------------
#
# Project created by QtCreator 2015-11-13T09:37:36
#
#-------------------------------------------------

QT       += core gui

#DEPENDPATH += . d:\wrk\Utilities\ImageMagick-6.9.2-5\Magick++\lib\
#INCLUDEPATH += d:\wrk\Utilities\ImageMagick-6.9.2-5\ImageMagick\Magick++\lib\
#INCLUDEPATH += d:\wrk\Utilities\ImageMagick-6.9.2-5\ImageMagick\Magick++\lib\Magick++\magick
#INCLUDEPATH += d:\wrk\Utilities\ImageMagick-6.9.2-5\ImageMagick\magick\
#INCLUDEPATH += d:\wrk\InstalledPrograms\ImageMagick-6.9.2-Q16-HDRI\
##INCLUDEPATH += d:\wrk\InstalledPrograms\ImageMagick-6.9.2-Q16-HDRI\lib\
#DEPENDPATH += d:\wrk\InstalledPrograms\ImageMagick-6.9.2-Q16-HDRI\include\
#INCLUDEPATH += d:\wrk\InstalledPrograms\ImageMagick-6.9.2-Q16-HDRI\include\
#LIBS += -Ld:\wrk\InstalledPrograms\ImageMagick-6.9.2-Q16-HDRI\lib\ -lCORE_RL_magick_ -lCORE_RL_Magick++_ -lCORE_RL_Wand_

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImgRy
TEMPLATE = app


SOURCES += main.cpp\
        imgrymainwindow.cpp \
    workerthread.cpp

HEADERS  += imgrymainwindow.h \
    workerthread.h

FORMS    += imgrymainwindow.ui

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../InstalledPrograms/ImageMagick-6.9.2-Q16-HDRI/lib/ -lCORE_RL_magick_ -lCORE_RL_Magick++_ -lCORE_RL_Wand_
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../InstalledPrograms/ImageMagick-6.9.2-Q16-HDRI/lib/ -lCORE_DB_magick_ -lCORE_DB_Magick++_ -lCORE_DB_Wand_
#else:unix:!macx: LIBS += -L$$PWD/../../../InstalledPrograms/ImageMagick-6.9.2-Q16-HDRI/lib/ -lCORE_RL_magick_ -lCORE_RL_Magick++_ -lCORE_RL_Wand_

#INCLUDEPATH += $$PWD/../../../InstalledPrograms/ImageMagick-6.9.2-Q16-HDRI/include
#DEPENDPATH += $$PWD/../../../InstalledPrograms/ImageMagick-6.9.2-Q16-HDRI/include

#unix:!macx|win32: LIBS += -L$$PWD/../../../InstalledPrograms/ImageMagick-6.9.2-Q16-HDRI/lib/ -lCORE_RL_magick_

#INCLUDEPATH += $$PWD/../../../InstalledPrograms/ImageMagick-6.9.2-Q16-HDRI/include
#DEPENDPATH += $$PWD/../../../InstalledPrograms/ImageMagick-6.9.2-Q16-HDRI/include
