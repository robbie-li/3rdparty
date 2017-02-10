QT += qml quick xml #scxml

CONFIG += c++11

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    buildcontroller.h \
    buildenvironment.h \
    buildprocess.h \
    buildstep.h \
    buildworker.h \
    library.h \
    libraryfactory.h \
    librarymodel.h

SOURCES += \
    main.cpp \
    buildenvironment.cpp \
    buildprocess.cpp \
    buildstep.cpp \
    buildworker.cpp \
    buildcontroller.cpp \
    library.cpp \
    libraryfactory.cpp \
    librarymodel.cpp

RESOURCES += \
    qml.qrc

#STATECHARTS += \
#    buildstatemachine.scxml

#load(qscxmlc)
