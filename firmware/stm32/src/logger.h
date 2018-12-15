#ifndef _LOGGER_H
#define _LOGGER_H

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
 * Logs to chout without any additions.
 * @param format   printf-like formatted string
 * @param args     args for the formatted string
 */
#define rlog(format, args...) do { chprintf(chout, format, ## args); } while(0);

/**
 * Logs to chout with a header containing the current system time.
 * @param format   printf-like formatted string
 * @param args     args for the formatted string
 */
#define log(format, args...) do { \
	loggerHeader(); \
	rlog(format, ## args); \
} while(0);

/**
 * Logs to chout with a header containing the current system time and an
 * included line return (CRLF).
 * @param format   printf-like formatted string
 * @param args     args for the formatted string
 */
#define lognl(format, args...) do { \
	log(format, ## args); \
	chprintf(chout, "\r\n"); \
} while(0);

#endif

