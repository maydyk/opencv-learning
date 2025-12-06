//detectFaces.pro
QT       += core
QT       -= gui

TARGET = detectFaces
CONFIG   += console
CONFIG   -= app_bundle


INCLUDEPATH += D:\\OpenCV3.0Beta\\build4OpenCL2\\install\\include

LIBS += -L"D:\\OpenCV3.0Beta\\build4OpenCL2\\install\\x64\\mingw\\lib" \
        -lopencv_core300 \
        -lopencv_imgproc300 \
        -lopencv_highgui300 \
        -lopencv_videoio300 \
        -lopencv_objdetect300 \


SOURCES += ./detectFaces.cpp


