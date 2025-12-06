//checkOpenCL.pro
QT       += core
QT       -= gui

TARGET = checkOpenCL
CONFIG   += console
CONFIG   -= app_bundle


INCLUDEPATH += D:\\OpenCV3.0Beta\\build4OpenCL2\\install\\include

LIBS += -L"D:\\OpenCV3.0Beta\\build4OpenCL2\\install\\x64\\mingw\\lib" \
        -lopencv_core300 \
        -lopencv_imgproc300 \
        -lopencv_highgui300 \
        -lopencv_features2d300 \
        -lopencv_videoio300 \
        -lopencv_imgcodecs300 \
        -lopencv_stitching300 \


SOURCES += ./checkOpenCL.cpp


