#include "ultra64.h"
#include "z64.h"
#include "macros.h"
#include "command_macros_base.h"
#include "z64cutscene_commands.h"

#include "gerudoway_cs.h"

s32 NabooruPanAwayCS[] = {
	CS_BEGIN_CUTSCENE(4, 184),
	CS_TERMINATOR(79, 182, 183),
	CS_TEXT_LIST(1),
		CS_TEXT_DISPLAY_TEXTBOX(0x0B66, 5, 181, 0x0000, 0x0000, 0x0000),
	CS_CAM_POS_LIST(0, 321),
		CS_CAM_POS(0, 0, 0, 0x42700000, 1997, 44, -657, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 1997, 44, -657, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 2106, 77, -606, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 2244, 56, -708, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 2201, 67, -701, 0),
		CS_CAM_POS(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_FOCUS_POINT_LIST(0, 340),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 1950, 32, -699, 0),
		CS_CAM_FOCUS_POINT(0, 0, 100, 0x42700000, 1950, 32, -699, 0),
		CS_CAM_FOCUS_POINT(0, 0, 80, 0x42700000, 1950, 32, -699, 0),
		CS_CAM_FOCUS_POINT(0, 0, 100, 0x42700000, 1950, 33, -686, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 1950, 32, -686, 0),
		CS_CAM_FOCUS_POINT(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_END(),
};

s32 NabooruSecondHalfCS[] = {
	CS_BEGIN_CUTSCENE(17, 437),
	CS_TEXT_LIST(6),
		CS_TEXT_DISPLAY_TEXTBOX(0x0B68, 20, 105, 0x0000, 0x0000, 0x0000),
		CS_TEXT_DISPLAY_TEXTBOX(0x0B69, 115, 235, 0x0000, 0x0000, 0x0000),
		CS_TEXT_DISPLAY_TEXTBOX(0x0B6C, 265, 270, 0x0000, 0x0000, 0x0000),
		CS_TEXT_LEARN_SONG(12, 275, 280, 0xFFFF),
		CS_TEXT_LEARN_SONG(25, 290, 295, 0x086D),
		CS_TEXT_DISPLAY_TEXTBOX(0x00D5, 430, 435, 0x0000, 0x0000, 0x0000),
	CS_FADE_BGM_LIST(1),
		CS_FADE_BGM(0x0000, 255, 275, 0, 0, 0, 0, 0, 0, 0, 0),
	CS_PLAY_BGM_LIST(2),
		CS_PLAY_BGM(0x003D + 1, 300, 1, 0, 0, 0, 0, 0, 0, 0, 0),
		CS_PLAY_BGM(0x0018 + 1, 436, 1, 0, 0, 0, 0, 0, 0, 0, 0),
	CS_CAM_POS_LIST(0, 241),
		CS_CAM_POS(0, 0, 0, 0x42700000, 2103, 135, -670, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 2103, 135, -670, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 1980, 57, -683, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 1848, 7, -781, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 1848, 7, -780, 0),
		CS_CAM_POS(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_POS_LIST(110, 391),
		CS_CAM_POS(0, 0, 0, 0x42700000, 1932, 33, -670, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 1932, 33, -670, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 1940, 33, -671, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 1945, 33, -677, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 1945, 33, -677, 0),
		CS_CAM_POS(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_POS_LIST(240, 321),
		CS_CAM_POS(0, 0, 0, 0x42700000, 1973, 37, -651, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 1973, 37, -651, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 1973, 37, -651, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 1973, 37, -651, 0),
		CS_CAM_POS(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_POS_LIST(250, 331),
		CS_CAM_POS(0, 0, 0, 0x42700000, 1956, 38, -684, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 1956, 38, -684, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 1956, 38, -684, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 1956, 38, -684, 0),
		CS_CAM_POS(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_POS_LIST(285, 366),
		CS_CAM_POS(0, 0, 0, 0x42700000, 1945, 36, -702, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 1945, 36, -702, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 1945, 36, -702, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 1945, 36, -702, 0),
		CS_CAM_POS(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_POS_LIST(300, 533),
		CS_CAM_POS(0, 0, 0, 0x42700000, 1723, 115, -784, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 1723, 115, -784, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 1835, 129, -907, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 2022, 115, -915, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 2162, 76, -756, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 2015, 41, -664, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 1936, 32, -663, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 1935, 33, -663, 0),
		CS_CAM_POS(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_FOCUS_POINT_LIST(0, 260),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 2157, 140, -655, 0),
		CS_CAM_FOCUS_POINT(0, 0, 30, 0x42700000, 2157, 140, -655, 0),
		CS_CAM_FOCUS_POINT(0, 0, 40, 0x42700000, 2033, 71, -665, 0),
		CS_CAM_FOCUS_POINT(0, 0, 130, 0x42700000, 1876, 15, -751, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 1876, 15, -751, 0),
		CS_CAM_FOCUS_POINT(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_FOCUS_POINT_LIST(110, 410),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 1938, 33, -690, 0),
		CS_CAM_FOCUS_POINT(0, 0, 100, 0x42700000, 1938, 33, -690, 0),
		CS_CAM_FOCUS_POINT(0, 0, 40, 0x42700000, 1930, 33, -689, 0),
		CS_CAM_FOCUS_POINT(0, 0, 100, 0x42700000, 1925, 33, -683, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 1925, 33, -683, 0),
		CS_CAM_FOCUS_POINT(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_FOCUS_POINT_LIST(240, 340),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 1939, 29, -696, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 1939, 29, -696, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 1939, 29, -696, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 1939, 29, -696, 0),
		CS_CAM_FOCUS_POINT(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_FOCUS_POINT_LIST(250, 350),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 1949, 35, -740, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 1949, 35, -740, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 1949, 35, -740, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 1949, 35, -740, 0),
		CS_CAM_FOCUS_POINT(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_FOCUS_POINT_LIST(285, 385),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 1891, 28, -685, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 1891, 28, -685, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 1891, 28, -685, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 1891, 28, -685, 0),
		CS_CAM_FOCUS_POINT(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_FOCUS_POINT_LIST(300, 552),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 1941, 34, -698, 0),
		CS_CAM_FOCUS_POINT(0, 0, 30, 0x42700000, 1941, 34, -698, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 1938, 34, -697, 0),
		CS_CAM_FOCUS_POINT(0, 0, 17, 0x42700000, 1935, 34, -698, 0),
		CS_CAM_FOCUS_POINT(0, 0, 25, 0x42700000, 1935, 34, -700, 0),
		CS_CAM_FOCUS_POINT(0, 0, 30, 0x42700000, 1961, 32, -704, 0),
		CS_CAM_FOCUS_POINT(0, 0, 70, 0x42700000, 1899, 29, -688, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 1898, 29, -687, 0),
		CS_CAM_FOCUS_POINT(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_PLAYER_ACTION_LIST(4),
		CS_PLAYER_ACTION(0x0005, 0, 290, 0x0, 0x5c72, 0x0, 1908, 0, -689, 1908, 0, -689, 0, 0, 0),
		CS_PLAYER_ACTION(0x0011, 290, 300, 0x0, 0x5c72, 0x0, 1908, 0, -689, 1908, 0, -689, 0, 0, 0),
		CS_PLAYER_ACTION(0x0042, 300, 435, 0x0, 0x5c72, 0x0, 1908, 0, -689, 1908, 0, -689, 0, 0, 0),
		CS_PLAYER_ACTION(0x0005, 435, 1000, 0x0, 0x5c72, 0x0, 1908, 0, -689, 1908, 0, -689, 0, 0, 0),
	CS_NPC_ACTION_LIST(40, 4),
		CS_NPC_ACTION(0x0001, 245, 255, 0x0, 0x0, 0x0, -19, 0, 10, -19, 0, 0, 0, 0, 0),
		CS_NPC_ACTION(0x0002, 255, 274, 0x0, 0x0, 0x0, -19, 0, 0, -19, 0, -10, 0, 0, 0),
		CS_NPC_ACTION(0x0003, 274, 290, 0x0, 0x0, 0x0, -19, 0, -10, -19, 0, -20, 0, 0, 0),
		CS_NPC_ACTION(0x0004, 290, 1000, 0x0, 0x0, 0x0, -19, 0, -20, -19, 0, -30, 0, 0, 0),
	CS_END(),
};

