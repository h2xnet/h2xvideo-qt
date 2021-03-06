QT += quick

CONFIG += c++11

DEFINES += H2XCOMPONENT_BUILD
DEFINES += WIN32
DEFINES += H2XBASE_IMPLEMENTATION
DEFINES += H2XCORE_IMPLEMENTATION

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH +=  ../ \
                ../h2xbase  \
                ../h2xcore \
                ../bin  \
                ../third_party  \
                ../third_party/ffmpeg   \
                ../third_party/ffmpeg/include   \
                ../plugins

CONFIG(debug, debug|release) {
#debug active
DESTDIR = $$PWD/../bin/debug

win32: LIBS += $$PWD/../bin/debug/h2xbase.lib
win32: LIBS += $$PWD/../bin/debug/h2xcore.lib

win32: LIBS += $$PWD/../third_party/ffmpeg/lib/avformat.lib
win32: LIBS += $$PWD/../third_party/ffmpeg/lib/avutil.lib
win32: LIBS += $$PWD/../third_party/ffmpeg/lib/avcodec.lib

}
else {
#release active
DESTDIR = $$PWD/../bin/release

win32: LIBS += $$PWD/../bin/release/h2xbase.lib
win32: LIBS += $$PWD/../bin/release/h2xcore.lib

win32: LIBS += $$PWD/../third_party/ffmpeg/lib/avformat.lib
win32: LIBS += $$PWD/../third_party/ffmpeg/lib/avutil.lib
win32: LIBS += $$PWD/../third_party/ffmpeg/lib/avcodec.lib

}

SOURCES += \
        api/h2xvideo_api.cpp \
        app.cpp \
        app_cache.cpp \
        app_config.cpp \
        cache/router_cache.cpp \
        main.cpp \
        main_view_handler.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    api/h2xvideo_api.h \
    app.h \
    app_cache.h \
    app_config.h \
    cache/router_cache.h \
    main_view_handler.h

DISTFILES +=
