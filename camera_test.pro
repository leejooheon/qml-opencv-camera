QT += quick widgets qml multimedia # for qml
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        camera.cpp \
        videomanager.cpp \
        videoproducer.cpp

HEADERS += \
    camera.h \
    videomanager.h \
    videoproducer.h

RESOURCES += qml.qrc

# using pkgconfig
unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += opencv

# your own opencv
#INCLUDEPATH += '/path/to/opencv/include' \
#               '/path/to/opencv/include/opencv'
#DEPENDPATH += '/path/to/opencv/include' \
#              '/path/to/opencv/include/opencv'
#LIBS += -L'/path/to/opencv/lib' -lopencv_core -lopencv_imgproc -lopencv_imgcodecs -lopencv_videoio
