#ifndef _LOGGER_H
#define _LOGGER_H

#include <chprintf.h>

extern BaseSequentialStream * const chout;

/**
 * Initializes the logger subsystem
 */
void loggerInit(void);

/**
 * Prints the system time in seconds to the serial port, as a prefix for log
 * lines.
 */
void loggerHeader(void);

/**
 * Locks the logger mutex to avoid mixing the output of multiple threads.
 */
void loggerLock(void);

/**
 * Unlocks the logger mutex to avoid mixing the output of multiple threads.
 */
void loggerUnlock(void);

/**
 * Logs to chout without any additions. Not thread safe.
 * @param format   printf-like formatted string
 * @param args     args for the formatted string
 */
void rlow(const char *format, ...);
#define rlog(format, args...) do { chprintf(chout, format, ## args); } while(0);

/**
 * Logs to chout with a header containing the current system time. Thread safe
 * @param format   printf-like formatted string
 * @param args     args for the formatted string
 */
#define log(format, args...) do { \
	loggerLock(); \
	loggerHeader(); \
	rlog(format, ## args); \
	loggerUnlock(); \
} while(0);

/**
 * Logs to chout with a header containing the current system time and an
 * included line return (CRLF). Thread safe.
 * @param format   printf-like formatted string
 * @param args     args for the formatted string
 */
#define lognl(format, args...) do { \
	loggerLock(); \
	loggerHeader(); \
	rlog(format, ## args); \
	chprintf(chout, "\r\n"); \
	loggerUnlock(); \
} while(0);

#endif

