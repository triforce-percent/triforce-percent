#include "ultra64.h"
#include "z64.h"
#include "macros.h"
#include "command_macros_base.h"
#include "z64cutscene_commands.h"

#include "HyruleFieldFlyover.h"

s32 HyruleFieldFlyover[] = {
	CS_BEGIN_CUTSCENE(7, 5000),
	CS_TERMINATOR(84, 260, 261),
	CS_TEXT_LIST(3),
		CS_TEXT_DISPLAY_TEXTBOX(0x0F00, 5, 85, 0x0000, 0x0000, 0x0000),
		CS_TEXT_DISPLAY_TEXTBOX(0x0F01, 90, 170, 0x0000, 0x0000, 0x0000),
		CS_TEXT_DISPLAY_TEXTBOX(0x0F02, 175, 260, 0x0000, 0x0000, 0x0000),
	CS_PLAY_BGM_LIST(1),
		CS_PLAY_BGM(0x76 + 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0),
	CS_CAM_POS_LIST(0, 421),
		CS_CAM_POS(0, 0, 0, 0x42700000, -6045, -133, 957, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, -4999, -163, 1382, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, -4540, -258, 1827, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, -2530, 88, 1351, 0),
		CS_CAM_POS(0, 0, 0, 0x42480000, -2315, 164, 1357, 0),
		CS_CAM_POS(0, 0, 0, 0x42480000, -1535, 156, 1177, 0),
		CS_CAM_POS(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_POS_LIST(175, 536),
		CS_CAM_POS(0, 0, 0, 0x42700000, -1040, -367, 12645, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, -915, -365, 12538, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, -142, -304, 11466, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, -231, -316, 11280, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, -298, -321, 11189, 0),
		CS_CAM_POS(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_FOCUS_POINT_LIST(0, 490),
		CS_CAM_FOCUS_POINT(0, 0, 70, 0x42700000, -6044, -127, 902, 0),
		CS_CAM_FOCUS_POINT(0, 0, 70, 0x42700000, -5003, -151, 1328, 0),
		CS_CAM_FOCUS_POINT(0, 0, 40, 0x42700000, -4518, -258, 1775, 0),
		CS_CAM_FOCUS_POINT(0, 0, 70, 0x42700000, -2571, 86, 1313, 0),
		CS_CAM_FOCUS_POINT(0, 0, 100, 0x42480000, -2362, 146, 1334, 0),
		CS_CAM_FOCUS_POINT(0, 0, 70, 0x42480000, -1591, 156, 1174, 0),
		CS_CAM_FOCUS_POINT(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_FOCUS_POINT_LIST(175, 575),
		CS_CAM_FOCUS_POINT(0, 0, 100, 0x42700000, -1006, -368, 12689, 0),
		CS_CAM_FOCUS_POINT(0, 0, 60, 0x42700000, -872, -375, 12573, 0),
		CS_CAM_FOCUS_POINT(0, 0, 100, 0x42700000, -87, -304, 11477, 0),
		CS_CAM_FOCUS_POINT(0, 0, 60, 0x42700000, -185, -315, 11248, 0),
		CS_CAM_FOCUS_POINT(0, 0, 40, 0x42700000, -246, -317, 11155, 0),
		CS_CAM_FOCUS_POINT(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_END(),
};

