#include "ultra64.h"
#include "global.h"

s16 MimicChestObjIdleAnimFrameData[3] = {
	0x0000, 0xecb8, 0x5346, };

JointIndex MimicChestObjIdleAnimJointIndices[3] = {
	{ 0x0000, 0x0000, 0x0000, },
	{ 0x0001, 0x0000, 0x0000, },
	{ 0x0002, 0x0000, 0x0000, },
};

AnimationHeader MimicChestObjIdleAnim = { { 2 }, MimicChestObjIdleAnimFrameData, MimicChestObjIdleAnimJointIndices, 3 };

