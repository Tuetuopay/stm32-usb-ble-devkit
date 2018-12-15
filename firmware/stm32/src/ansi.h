/**
 * ANSI
 *
 * Ansi color codes and escape codes
 */

#ifndef _ANSI_H
#define _ANSI_H

// Color codes
#define CBLACK   "30"
#define CRED     "31"
#define CGREEN   "32"
#define CYELLOW  "33"
#define CBLUE    "34"
#define CMAGENTA "35"
#define CCYAN    "36"
#define CWHITE   "37"
#define CRST     "0"

// Escape ANSI character
#define ESC   "\033["

// Normal colors
#define BLACK    ESC CBLACK "m"
#define RED      ESC CRED "m"
#define GREEN    ESC CGREEN "m"
#define YELLOW   ESC CYELLOW "m"
#define BLUE     ESC CBLUE "m"
#define MAGENTA  ESC CMAGENTA "m"
#define CYAN     ESC CCYAN "m"
#define WHITE    ESC CWHITE "m"
// Bright colors
#define BBLACK   ESC CBLACK ";1m"
#define BRED     ESC CRED ";1m"
#define BGREEN   ESC CGREEN ";1m"
#define BYELLOW  ESC CYELLOW ";1m"
#define BBLUE    ESC CBLUE ";1m"
#define BMAGENTA ESC CMAGENTA ";1m"
#define BCYAN    ESC CCYAN ";1m"
#define BWHITE   ESC CWHITE ";1m"
// Reset to normal
#define RST      ESC CRST "m"

#endif
