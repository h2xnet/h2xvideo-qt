CONFIG -= qt

TEMPLATE = lib

DEFINES += H2XBASE_LIBRARY
DEFINES += H2XCOMPONENT_BUILD
DEFINES += WIN32
DEFINES += H2XBASE_IMPLEMENTATION

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

win32: LIBS += Shell32.lib
win32: LIBS += Dbghelp.lib
win32: LIBS += user32.lib

INCLUDEPATH +=  ../ \
                ../third_party

SOURCES += \
    crash/crash_win.cpp \
    file/file.cpp \
    file/file_path.cpp \
    h2xbase.cpp \
    hardware/cpu.cpp \
    logger/h2x_logger.cpp \
    string/string_builder.cpp \
    string/string_util.cpp \
    sync/lock_win.cpp \
    sync/semaphore_win.cpp \
    sync/waitable_event_win.cpp \
    task/default_message_pump.cpp \
    task/message_loop.cpp \
    task/message_loop_proxy.cpp \
    task/message_pump.cpp \
    thread/framework_thread.cpp \
    thread/thread_local_win.cpp \
    thread/thread_manager.cpp \
    thread/thread_win.cpp \
    time/time.cpp \
    time/time_win.cpp \
    util/at_exit.cpp

HEADERS += \
    btype.h \
    crash/crash_handler.h \
    crash/crash_win.h \
    file/file.h \
    file/file_path.h \
    h2x_base_export.h \
    h2x_error_code.h \
    h2x_macros.h \
    h2x_map_table.h \
    h2x_observer_list.h \
    h2xbase_global.h \
    h2xbase.h \
    hardware/cpu.h \
    logger/h2x_logger.h \
    memory/lazy_instance.h \
    memory/singleton.h \
    string/string_builder.h \
    string/string_result.h \
    string/string_util.h \
    sync/lock.h \
    sync/semaphore.h \
    sync/waitable_event.h \
    task/callback.h \
    task/default_message_pump.h \
    task/message_loop.h \
    task/message_loop_proxy.h \
    task/message_pump.h \
    task/task.h \
    third_party/chrome/atomicops.h \
    third_party/chrome/atomicops_internals_x86_msvc.h \
    thread/framework_thread.h \
    thread/thread.h \
    thread/thread_local.h \
    thread/thread_manager.h \
    time/time.h \
    util/at_exit.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
