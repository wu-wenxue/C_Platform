#ifndef UTILITY_H
#define UTILITY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>

void       getWirelessIp(char* ip, int len);
long long  getMicroSeconds();
int        getMSTime();
short      generateTimeHexString(char* buffer, int size);
char*      getCurrentTimeString();
char*      getCurrentTimeString_New();

/*
 * Function:  convert hex to character.
 * Arguments:
 *            s    -- input, string to be copied.
 * Return:    return copy of s on success, NULL on error.
 */
char hexToChar(char hex);

void stringRelease(char* s);
/*
 * Function:  make a copy of string s.
 * Arguments:
 *            s    -- input, string to be copied.
 * Return:    return copy of s on success, NULL on error.
 */
char* stringCopy(const char* s);

/*
 * Function:  make a copy sLen of s
 * Arguments:
 *            s    -- input, string to be copied.
 *            sLen -- input, length of s.
 * Return:    return copy of s on success, NULL on error.
 */
char* stringLenCopy(const char* s, size_t sLen);

/*
 * Function:  concatenate two strings, and return a new string. Return value must
 *            be release by caller manually.
 * Arguments:
 *            first  -- input, the starting part
 *            second -- input, the second part.
 *
 * Return:    return a new string on success, NULL on error.
 */
char* stringCat2(const char* first, const char* second);

/*
 * Function:  concatenate three strings, and return a new string. Return value must
 *            be release by caller manually.
 * Arguments:
 *            first  -- input, the starting part
 *            second -- input, the second part.
 *            last   -- input, the last part.
 *
 * Return:    return a new string on success, NULL on error.
 */
char* stringCat3(const char* first, const char* second, const char* last);

#ifdef __cplusplus
}
#endif

#endif // UTILITY_H

