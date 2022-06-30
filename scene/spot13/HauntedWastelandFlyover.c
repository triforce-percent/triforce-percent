#include "ultra64.h"
#include "z64.h"
#include "macros.h"
#include "command_macros_base.h"
#include "z64cutscene_commands.h"

#include "HauntedWastelandFlyover.h"

s32 HauntedWastelandFlyover[] = {
	CS_BEGIN_CUTSCENE(4, 5000),
	CS_TERMINATOR(92, 200, 201),
	CS_TEXT_LIST(2),
		CS_TEXT_DISPLAY_TEXTBOX(0x0F80, 26, 100, 0x0000, 0x0000, 0x0000),
		CS_TEXT_DISPLAY_TEXTBOX(0x0F81, 106, 180, 0x0000, 0x0000, 0x0000),
	CS_CAM_POS_LIST(0, 561),
		CS_CAM_POS(0, 0, 0, 0x42700000, -231, 294, -571, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, -230, 294, -630, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 197, 289, -3320, 0),
		CS_CAM_POS(0, 0, 0, 0x42f00000, 2282, 287, -2547, 0),
		CS_CAM_POS(0, 0, 0, 0x42f00000, 3804, 292, -1971, 0),
		CS_CAM_POS(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_FOCUS_POINT_LIST(0, 680),
		CS_CAM_FOCUS_POINT(0, 0, 100, 0x42700000, -231, 294, -627, 0),
		CS_CAM_FOCUS_POINT(0, 0, 80, 0x42700000, -230, 294, -686, 0),
		CS_CAM_FOCUS_POINT(0, 0, 120, 0x42700000, 249, 289, -3298, 0),
		CS_CAM_FOCUS_POINT(0, 0, 140, 0x42f00000, 2338, 288, -2548, 0),
		CS_CAM_FOCUS_POINT(0, 0, 120, 0x42f00000, 3860, 293, -1973, 0),
		CS_CAM_FOCUS_POINT(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_END(),
};

