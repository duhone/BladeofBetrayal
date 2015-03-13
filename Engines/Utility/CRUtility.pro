# -------------------------------------------------
# Project created by QtCreator 2010-02-02T09:15:50
# -------------------------------------------------
QT -= gui
TARGET = CRUtility
TEMPLATE = lib
CONFIG += staticlib
SOURCES += Timer.cpp \
    StringUtil.cpp \
    Guid.cpp \
    BinaryWriter.cpp \
    BinaryReader.cpp
HEADERS += ZlibOutBufer.h \
    Timer.h \
    StringUtil.h \
    Sorting.h \
    Singleton.h \
    Property.h \
    PowerOf2.h \
    LowContentionLock.h \
    ISerializable.h \
    Guid.h \
    FunctionObjects.h \
    FSM.h \
    ForwardDeclarations.h \
    Exceptions.h \
    Event.h \
    CriticalSection.h \
    ClassFactory.h \
    CacheAlignedArray.h \
    BTreeNode.h \
    BTree.h \
    BinaryWriterFO.h \
    BinaryWriter.h \
    BinaryReader.h \
    AutoRelease.h \
    AutoLock.h \
    AutoCriticalSection.h
