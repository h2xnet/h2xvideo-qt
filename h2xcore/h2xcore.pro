CONFIG -= qt

TEMPLATE = lib
DEFINES += H2XCORE_LIBRARY

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

INCLUDEPATH +=  ../ \
                ../h2xbase  \
                ../bin \
                ../third_party  \
                ../plugins

CONFIG(debug, debug|release) {
#debug active
win32: LIBS += ../h2xbase/debug/h2xbase.lib
}
else {
#release active
win32: LIBS += ../h2xbase/release/h2xbase.lib
}

SOURCES += \
    h2x_application.cpp \
    h2x_cache.cpp \
    h2x_config.cpp \
    h2x_context.cpp \
    h2x_controller.cpp \
    h2x_cpu_controller.cpp \
    h2x_error.cpp \
    h2x_exception.cpp \
    h2x_helper.cpp \
    h2x_io_controller.cpp \
    h2x_listen.cpp \
    h2x_listen_table.cpp \
    h2x_loader.cpp \
    h2x_message.cpp \
    h2x_message_service.cpp \
    h2x_middleware.cpp \
    h2x_model.cpp \
    h2x_object.cpp \
    h2x_option.cpp \
    h2x_plugin.cpp \
    h2x_request.cpp \
    h2x_response.cpp \
    h2x_router.cpp \
    h2x_schedule.cpp \
    h2x_sequelize.cpp \
    h2x_service.cpp \
    h2x_session.cpp \
    h2x_subscription.cpp \
    h2x_view.cpp \
    h2xcore.cpp

HEADERS += \
    h2x_application.h \
    h2x_cache.h \
    h2x_config.h \
    h2x_context.h \
    h2x_controller.h \
    h2x_core_export.h \
    h2x_cpu_controller.h \
    h2x_error.h \
    h2x_exception.h \
    h2x_helper.h \
    h2x_io_controller.h \
    h2x_listen.h \
    h2x_listen_table.h \
    h2x_loader.h \
    h2x_message.h \
    h2x_message_service.h \
    h2x_middleware.h \
    h2x_model.h \
    h2x_object.h \
    h2x_option.h \
    h2x_plugin.h \
    h2x_request.h \
    h2x_response.h \
    h2x_router.h \
    h2x_schedule.h \
    h2x_sequelize.h \
    h2x_service.h \
    h2x_session.h \
    h2x_subscription.h \
    h2x_view.h \
    h2xcore_global.h \
    h2xcore.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
