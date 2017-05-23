#-------------------------------------------------
#
# Project created by QtCreator 2017-03-12T12:18:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = karavai-project
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    simplereplacement.cpp \
    keyvaluedialog.cpp \
    gammacypher.cpp \
    singleshift.cpp \
    doubletransposition.cpp \
    gronspheld.cpp \
    rsacrypt.cpp \
    rsakeydialog.cpp \
    bigint/BigInteger.cc \
    bigint/BigIntegerAlgorithms.cc \
    bigint/BigIntegerUtils.cc \
    bigint/BigUnsigned.cc \
    bigint/BigUnsignedInABase.cc \
    cardanokeydialog.cpp \
    cardano.cpp \
    symbolfreqanalysis.cpp \
    bigrammfreqanalysis.cpp \
    factorization.cpp \
    bruteforce.cpp

HEADERS  += mainwindow.h \
    simplereplacement.h \
    keyvaluedialog.h \
    gammacypher.h \
    singleshift.h \
    doubletransposition.h \
    gronspheld.h \
    rsacrypt.h \
    rsakeydialog.h \
    bigint/BigInteger.hh \
    bigint/BigIntegerAlgorithms.hh \
    bigint/BigIntegerLibrary.hh \
    bigint/BigIntegerUtils.hh \
    bigint/BigUnsigned.hh \
    bigint/BigUnsignedInABase.hh \
    bigint/NumberlikeArray.hh \
    cardanokeydialog.h \
    cardano.h \
    symbolfreqanalysis.h \
    bigrammfreqanalysis.h \
    factorization.h \
    bruteforce.h

FORMS    += mainwindow.ui \
    keyvaluedialog.ui \
    rsakeydialog.ui \
    cardanokeydialog.ui
CONFIG += c++17
