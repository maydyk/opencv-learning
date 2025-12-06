//videoStabilizer.pro
QT       += core
QT       -= gui

TARGET = videoStabilizer
CONFIG   += console
CONFIG   -= app_bundle


INCLUDEPATH += C:\\OpenCV3.0Alpha\\build4Qt\\install\\include

LIBS += -L"C:\\OpenCV3.0Alpha\\build4Qt\\lib" \
        -lopencv_core300 \
        -lopencv_highgui300 \
        -lopencv_features2d300 \
        -lopencv_videoio300 \
        -lopencv_videostab300 \


SOURCES += ./videoStabilizer.cpp


