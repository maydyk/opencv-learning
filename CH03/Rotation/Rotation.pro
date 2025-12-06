TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

INCLUDEPATH += E:\OpenCV_3.0.a\build4QT\install\include

LIBS += -L"E:\OpenCV_3.0.a\build4QT\install\x64\mingw\lib" \
-lopencv_calib3d300 \
-lopencv_core300 \
-lopencv_features2d300 \
-lopencv_flann300 \
-lopencv_highgui300 \
-lopencv_imgcodecs300 \
-lopencv_imgproc300 \
-lopencv_ml300 \
-lopencv_objdetect300 \
-lopencv_photo300 \
-lopencv_shape300 \
-lopencv_stitching300 \
-lopencv_superres300 \
-lopencv_video300 \
-lopencv_videoio300 \
-lopencv_videostab300 \

