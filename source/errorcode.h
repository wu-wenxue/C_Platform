/* 
 * Message: header file, define public error codes the application used.
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
#ifndef ERRORCODE_H
#define ERRORCODE_H
#ifdef __cplusplus
extern "C" {
#endif

#define EC_OK                        0  /* no error                             */
#define EC_INVALID                  -1  /* invalid                              */
#define EC_ERROR                     1  /* error                                */
#define EC_NULL                      2  /* null                                 */
#define EC_DISCONN                   3  /* connection disconnected              */
#define EC_ARGINVALID                4  /* arguments invalid                    */
#define EC_OOM                       5  /* out of memory                        */
#define EC_OUTOFRANGE                6  /* out of range                         */
#define EC_FILEOPENERROR             7  /* open file failed                     */
#define EC_FILEIOERROR               8  /* read or write file error             */
#define EC_FILENOEXIST               9  /* file error                           */
#define EC_CONFIGERROR              10  /* configuration error                  */
#define EC_CONFIGLOADERROR          11  /* load config file error               */
#define EC_CONFIGSAVEERROR          12  /* save config file error               */
#define EC_URLERROR                 13  /* access URL error                     */
#define EC_SHELLERROR               14  /* shell failed                         */
#define EC_VERSIONERROR             15  /* version error                        */
#define EC_VERSIONSAME              16  /* versopm is the same                  */
#define EC_JSONPARSEERROR           17  /* parse json string error              */
#define EC_JSONDATAERROR            18  /* json data error                      */
#define EC_IMEIERROR                19  /* IMEI eror                            */
#define EC_HTTPCONNCREATEERROR      20  /* create http connection error         */
#define EC_HTTPACCESSERROR          21  /* access http error                    */
#define EC_HTTPARGERROR             22
#define EC_CHECKVERSIONERROR        23  /* check version failed                 */
#define EC_MD5ERROR                 24
#define EC_MD5FAILED                25
#define EC_COMGETATTRERROR          26
#define EC_COMSETATTRERROR          27
#define EC_COMCMDLENERROR           28
#define EC_IMSIERROR                29
#define EC_NODATA                   30
#define EC_COMMANDUNKOWN            31
#define EC_LOCATINGERROR            32
#define EC_ARGUMENT_DISABLED        33
#define EC_DISK_OVERLOAD            34

#ifdef __cplusplus
}
#endif
#endif
