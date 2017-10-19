/*
 * Message: header file, define public macros and structures and methods.
 *
 * Module: Common
 *
 * Author:
 *
 * Created 2016.07.23
 *
 * Update Histories:
 *     None
 */
#ifndef COMMON_H
#define COMMON_H
#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define watcher_tracer      printf
#define watcher_malloc      malloc
#define watcher_calloc      calloc
#define watcher_realloc     realloc
#define watcher_free        free

#ifndef BOOL
typedef unsigned char       BOOL;
#endif
#if defined(TRUE)
#undefine TRUE
#endif
#define TRUE    1
#if defined(FALSE)
#undefine FALSE
#endif
#define FALSE   0

#define AGENT_CURRENT_PATH          "/overlay/work/agent/"
#define AGENT_CURRENT_DATA_PATH     "/overlay/work/agent/data/"
#define AGENT_BACKUP_PATH           "/overlay/work/agent_backup/"
#define AGENT_BACKUP_DATA_PATH      "/overlay/work/agent_backup/data/"
#define AGENT_TMP_PATH              "/overlay/work/agent_tmp/agent/"

#define AGENT_VERSION_FILE          "/overlay/work/agent/version"
#define AGENT_BINARY_FILE           "/overlay/work/agent/agent"
#define APP_BINARY_FILE             "/overlay/work/MFP_MGR/MFP_MGR_APP"
#define AGENT_UPGRADE_DATA          "/overlay/work/agent/data/upgrades"
#define AGENT_CHECK_DATA            "/overlay/work/agent/data/check"

#define AGENT_TMP_MD5_FILE          "/overlay/work/agent_tmp/agent/md5.data"
#define SHELL_TMP_FILE              "/overlay/work/agent_tmp/shell/upgrade.sh"
#define SHELL_TMP_PATH              "/overlay/work/agent_tmp/shell"

#define AGENT_VERSION_DEFAULT       "0.0.0"
#define WATCHER_UNPACK_PATH         "/overlay/work/agent_tmp/"
#define WATCHER_DOWNLOAD_PATH       "/overlay/work/download/"
#define WATCHER_DOWNLOAD_FILE       "/overlay/work/download/agent.tar.gz"
#define WATCHER_CONF_FILE           "/overlay/work/watcher/conf/watcher.conf.json"
#define WATCHER_LOG_FILE            "/overlay/work/watcher/log/watcher.log"

#ifdef __cplusplus
}
#endif
#endif
