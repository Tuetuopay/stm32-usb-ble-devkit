#include <stdint.h>

#include "util/hid_keys.h"

const char codeToChar[][3] = {
	{KEY_A, 'a', 'A'},
	{KEY_B, 'b', 'B'},
	{KEY_C, 'c', 'C'},
	{KEY_D, 'd', 'D'},
	{KEY_E, 'e', 'E'},
	{KEY_F, 'f', 'F'},
	{KEY_G, 'g', 'G'},
	{KEY_H, 'h', 'H'},
	{KEY_I, 'i', 'I'},
	{KEY_J, 'j', 'J'},
	{KEY_K, 'k', 'K'},
	{KEY_L, 'l', 'L'},
	{KEY_M, 'm', 'M'},
	{KEY_N, 'n', 'N'},
	{KEY_O, 'o', 'O'},
	{KEY_P, 'p', 'P'},
	{KEY_Q, 'q', 'Q'},
	{KEY_R, 'r', 'R'},
	{KEY_S, 's', 'S'},
	{KEY_T, 't', 'T'},
	{KEY_U, 'u', 'U'},
	{KEY_V, 'v', 'V'},
	{KEY_W, 'w', 'W'},
	{KEY_X, 'x', 'X'},
	{KEY_Y, 'y', 'Y'},
	{KEY_Z, 'z', 'Z'},

	{KEY_1, '1', '!'},
	{KEY_2, '2', '@'},
	{KEY_3, '3', '#'},
	{KEY_4, '4', '$'},
	{KEY_5, '5', '%'},
	{KEY_6, '6', '^'},
	{KEY_7, '7', '&'},
	{KEY_8, '8', '*'},
	{KEY_9, '9', '('},
	{KEY_0, '0', ')'},

	{KEY_ENTER, '\n', '\n'},
	{KEY_TAB, '\t', '\t'},
	{KEY_SPACE, ' ', ' '},
	{KEY_MINUS, '-', '_'},
	{KEY_EQUAL, '=', '+'},
	{KEY_LEFTBRACE, '[', '{'},
	{KEY_RIGHTBRACE, ']', '}'},
	{KEY_BACKSLASH, '\\', '|'},
	{KEY_HASHTILDE, '#', '~'},
	{KEY_SEMICOLON, ';', ':'},
	{KEY_APOSTROPHE, '\'', '"'},
	{KEY_GRAVE, '`', '~'},
	{KEY_COMMA, ',', '<'},
	{KEY_DOT, '.', '>'},
	{KEY_SLASH, '/', '?'},

	{KEY_KPSLASH, '/', '/'},
	{KEY_KPASTERISK, '*', '*'},
	{KEY_KPMINUS, '-', '-'},
	{KEY_KPPLUS, '+', '+'},
	{KEY_KPENTER, '\n', '\n'},
	{KEY_KP1, '1', '1'},
	{KEY_KP2, '2', '2'},
	{KEY_KP3, '3', '3'},
	{KEY_KP4, '4', '4'},
	{KEY_KP5, '5', '5'},
	{KEY_KP6, '6', '6'},
	{KEY_KP7, '7', '7'},
	{KEY_KP8, '8', '8'},
	{KEY_KP9, '9', '9'},
	{KEY_KP0, '0', '0'},
	{KEY_KPDOT, '.', '.'},

	{KEY_102ND, '<', '>'},
	{KEY_KPEQUAL, '=', '='},

	{KEY_KPLEFTPAREN, '(', '('},
	{KEY_KPRIGHTPAREN, ')', ')'},
	{0, 0, 0}
};

char code2char(uint8_t c, int shift) {
	int i = 0;

	while (codeToChar[i][0]) {
		if (codeToChar[i][0] == c)
			return codeToChar[i][shift ? 2 : 1];
		i++;
	}

	return 0;
}
