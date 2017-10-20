INCLUDEPATH += source \
            += test

HEADERS += \
    source/buffer.h \
    source/http.h \
    source/common.h \
    source/errorcode.h \
    source/logger.h \
    source/parson.h \
    source/shell.h \
    source/utility.h \
    source/config.h \
    source/thread.h \
    test/test.h \
    source/platform.h \
    source/ipccommon.h \
    source/fmacros.h

SOURCES += \
    main.cpp \
    source/buffer.c \
    source/http.c \
    source/logger.c \
    source/parson.c \
    source/shell.c \
    source/utility.c \
    source/config.c \
    test/test.c \
    source/platform.c \
    source/ipccommon.c

LIBS +=  -lcurl -lcrypto
#QMAKE_CFLAGS += -lssh -lcurl -lcrypto
