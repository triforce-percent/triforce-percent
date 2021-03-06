#include "ultra64.h"
#include "z64.h"
#include "macros.h"
#include "command_macros_base.h"
#include "z64cutscene_commands.h"

#include "spot11cs.h"

s32 NbColossusCS[] = {
	CS_BEGIN_CUTSCENE(10, 1000),
	CS_TERMINATOR(80, 530, 540),
	CS_TEXT_LIST(1),
		CS_TEXT_DISPLAY_TEXTBOX(0x0B67, 20, 1000, 0x0000, 0x0000, 0x0000),
	CS_FADE_BGM_LIST(2),
		CS_FADE_BGM(0x0000, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0),
		CS_FADE_BGM(0x0000, 500, 580, 0, 0, 0, 0, 0, 0, 0, 0),
	CS_PLAY_BGM_LIST(1),
		CS_PLAY_BGM(0x003F + 1, 30, 1, 0, 0, 0, 0, 0, 0, 0, 0),
	CS_SCENE_TRANS_FX(1, 525, 540),
	CS_CAM_POS_LIST(0, 466),
		CS_CAM_POS(0, 0, 0, 0x42700000, 10842, 46, -691, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 9842, 50, -652, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 5842, 99, -344, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 3566, 140, -253, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 1234, 219, -22, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, 691, 327, -22, 0),
		CS_CAM_POS(0, 0, 0, 0x42a00000, 100, -17, 12, 0),
		CS_CAM_POS(0, 0, 0, 0x42a00000, -733, -29, 12, 0),
		CS_CAM_POS(0, 0, 0, 0x42a00000, -753, -29, 12, 0),
		CS_CAM_POS(0, 0, 0, 0x42a00000, -743, -29, 12, 0),
		CS_CAM_POS(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_POS_LIST(385, 546),
		CS_CAM_POS(0, 0, 0, 0x42700000, -1238, 872, -115, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, -1238, 872, -117, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, -1238, 872, -119, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, -1238, 771, 97, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, -1238, 771, 91, 0),
		CS_CAM_POS(0, 0, 0, 0x42700000, -1238, 771, 86, 0),
		CS_CAM_POS(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_FOCUS_POINT_LIST(0, 485),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, 10786, 0, -691, 0),
		CS_CAM_FOCUS_POINT(0, 0, 60, 0x42700000, 9786, 4, -652, 0),
		CS_CAM_FOCUS_POINT(0, 0, 60, 0x42700000, 5786, 78, -344, 0),
		CS_CAM_FOCUS_POINT(0, 0, 65, 0x42700000, 3510, 119, -253, 0),
		CS_CAM_FOCUS_POINT(0, 0, 65, 0x42700000, 1178, 227, -22, 0),
		CS_CAM_FOCUS_POINT(0, 0, 40, 0x42700000, 635, 330, -22, 0),
		CS_CAM_FOCUS_POINT(0, 0, 45, 0x42a00000, 44, -24, 12, 0),
		CS_CAM_FOCUS_POINT(0, 0, 60, 0x42a00000, -789, 8, 12, 0),
		CS_CAM_FOCUS_POINT(0, 0, 30, 0x42a00000, -809, 8, 12, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42a00000, -799, 8, 12, 0),
		CS_CAM_FOCUS_POINT(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_CAM_FOCUS_POINT_LIST(385, 565),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, -1636, 742, 398, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, -1644, 737, 403, 0),
		CS_CAM_FOCUS_POINT(0, 0, 35, 0x42700000, -1643, 740, 386, 0),
		CS_CAM_FOCUS_POINT(0, 0, 35, 0x42700000, -1641, 765, -353, 0),
		CS_CAM_FOCUS_POINT(0, 0, 30, 0x42700000, -1641, 765, -359, 0),
		CS_CAM_FOCUS_POINT(0, 0, 20, 0x42700000, -1641, 765, -364, 0),
		CS_CAM_FOCUS_POINT(-1, 0, 0, 0x0, 0, 0, 0, 0),
	CS_PLAYER_ACTION_LIST(1),
		CS_PLAYER_ACTION(0x0005, 0, 1000, 0x0, 0x0, 0x0, 1746, 77, 2517, 1746, 77, 2517, 0, 0, 0),
	CS_END(),
};

