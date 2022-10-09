TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    tcp-chat-server.cpp

INCLUDEPATH += /opt/homebrew/Cellar/boost/1.79.0_2/include
