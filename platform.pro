INCLUDEPATH += source

HEADERS += \
    source/mylogger.h \
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
    source/platform.h

SOURCES += \
    main.cpp \
    source/mylogger.c \
    source/buffer.c \
    source/http.c \
    source/logger.c \
    source/test.c \
    source/parson.c \
    source/shell.c \
    source/utility.c \
    source/config.c \
    test/test.c \
    source/platform.c

LIBS +=  -lcurl -lcrypto
#QMAKE_CFLAGS += -lssh -lcurl -lcrypto
