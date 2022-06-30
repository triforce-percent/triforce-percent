#include "ultra64.h"
#include "z64.h"
#include "macros.h"
#include "command_macros_base.h"
#include "z64cutscene_commands.h"

#include "DekuTreeFlyover.h"

s32 DekuTreeFlyover[] = {
	CS_BEGIN_CUTSCENE(4, 5000),
	CS_TERMINATOR(87, 160, 161),
	CS_TEXT_LIST(2),
		CS_TEXT_DISPLAY_TEXTBOX(0x0F30, 6, 80, 0x0000, 0x0000, 0x0000),
		CS_TEXT_DISPLAY_TEXTBOX(0x0F31, 86, 160, 0x0000, 0x0000, 0x0000),
	CS_CAM_POS_LIST(0, 491),
		CS_CAM_POS(0, 0, 0, 0x42c80000, 1, 901, 1, 0),
		CS_CAM_POS(0, 0, 0, 0x42c80000, -5, 895, 3, 0),
		CS_CAM_POS(0, 0, 0, 0x42c80000, 12, 850, -3, 0),
		CS_CAM_POS(0, 0, 0, 0x42c80000, 3, 805, 25, 0),
		CS_CAM_POS(0, 0, 0, 0x42c80000, -10, 751, -1, 0),
		CS_CAM_POS(0, 0, 0, 0x42c80000, -13, 700, -28, 0),
		CS_CAM_POS(0, 0, 0, 0x42c80000, 3, 686, -25, 0),
		CS_CAM_POS(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_FOCUS_POINT_LIST(0, 610),
		CS_CAM_FOCUS_POINT(0, 0, 50, 0x42c80000, -1, 864, -41, 0),
		CS_CAM_FOCUS_POINT(0, 0, 50, 0x42c80000, 11, 867, -43, 0),
		CS_CAM_FOCUS_POINT(0, 0, 50, 0x42c80000, 54, 819, 18, 0),
		CS_CAM_FOCUS_POINT(0, 0, 50, 0x42c80000, 6, 759, 58, 0),
		CS_CAM_FOCUS_POINT(0, 0, 50, 0x42c80000, -44, 712, 19, 0),
		CS_CAM_FOCUS_POINT(0, 0, 120, 0x42c80000, -24, 645, -27, 0),
		CS_CAM_FOCUS_POINT(0, 0, 120, 0x42c80000, -9, 631, -24, 0),
		CS_CAM_FOCUS_POINT(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_END(),
};

