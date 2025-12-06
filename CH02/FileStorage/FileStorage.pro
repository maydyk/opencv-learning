TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += c:\OpenCV3.0.0alpha\opencv\build\Qt\install\include
LIBS += -L"c:\OpenCV3.0.0alpha\opencv\build\Qt\lib" \
        -lopencv_core300 \
        -lopencv_highgui300 \
        -lopencv_imgproc300 \
        -lopencv_imgcodecs300

SOURCES += main.cpp

