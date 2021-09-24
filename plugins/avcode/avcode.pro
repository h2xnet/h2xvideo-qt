CONFIG -= qt

TEMPLATE = lib
DEFINES += AVCODE_LIBRARY
DEFINES += AVCODE_COMPONENT_BUILD
DEFINES += WIN32
DEFINES += AVCODE_IMPLEMENTATION

DEFINES += H2XCOMPONENT_BUILD
DEFINES += WIN32
DEFINES += H2XBASE_IMPLEMENTATION
DEFINES += H2XCORE_IMPLEMENTATION

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH +=  ../../ \
                ../../third_party   \
                ../../third_party/ffmpeg    \
                ../../third_party/ffmpeg/include    \
                ../../third_party/ffmpeg/lib

CONFIG(debug, debug|release) {
#debug active
DESTDIR = $$PWD/../../bin/debug

win32: LIBS += $$PWD/../../third_party/ffmpeg/lib/avformat.lib
win32: LIBS += $$PWD/../../third_party/ffmpeg/lib/avutil.lib
win32: LIBS += $$PWD/../../third_party/ffmpeg/lib/avcodec.lib

win32: LIBS += $$PWD/../../bin/debug/h2xbase.lib
win32: LIBS += $$PWD/../../bin/debug/h2xcore.lib

}
else {
#release active
DESTDIR = $$PWD/../../bin/release

win32: LIBS += $$PWD/../../third_party/ffmpeg/lib/avformat.lib
win32: LIBS += $$PWD/../../third_party/ffmpeg/lib/avutil.lib
win32: LIBS += $$PWD/../../third_party/ffmpeg/lib/avcodec.lib

win32: LIBS += $$PWD/../../bin/release/h2xbase.lib
win32: LIBS += $$PWD/../../bin/release/h2xcore.lib

}

SOURCES += \
    avcode.cpp \
    avcode_ffmpeg.cpp \
    avcode_interface.cpp \
    avcode_option.cpp

HEADERS += \
    avcode_export.h \
    avcode_ffmpeg.h \
    avcode_global.h \
    avcode.h \
    avcode_interface.h \
    avcode_option.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

