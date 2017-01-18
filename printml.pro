TEMPLATE = lib
TARGET = PrintML
QT += qml quick printsupport
CONFIG += qt plugin C++11

TARGET = $$qtLibraryTarget($$TARGET)
uri = org.storyml.print

# Input
SOURCES += \
    Printer.cpp \
    PrintMLPlugin.cpp \
    PageSize.cpp \
    MiniPage.cpp \
    QuickItemPainter.cpp \
    StyledText.cpp

HEADERS += \
    Printer.h \
    PrintMLPlugin.h \
    PageSize.h \
    MiniPage.h \
    QuickItemPainter.h \
    StyledText.h

OTHER_FILES = qmldir \
    examples/PrintML.qml \
    examples/MiniPage.qml \
    examples/Efficient.qml

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir
unix {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}

