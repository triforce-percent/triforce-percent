/**
 * @file flower.c
 * @author zel.
 * @brief Silent Princess flower for ending scene
 * @date 2021-12-31
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "ootmain.h"
#include "SilentPrincessMesh.h"
#include "../statics/statics.h"

typedef struct {
    Actor actor;
} Entity;

#define OBJ_ID 123
#define FLAGS 0x00000030
#define OBJ_SCALE 0.007f
#define MAX_FLOWERS 20

void SilentPrincess_Init(Actor* thisx, GlobalContext* globalCtx);
void SilentPrincess_Destroy(Actor* thisx, GlobalContext* globalCtx);
void SilentPrincess_Update(Actor* thisx, GlobalContext* globalCtx);
void SilentPrincess_Draw(Actor* thisx, GlobalContext* globalCtx);

static Vec3f posList[MAX_FLOWERS];
static s16 posHead = 0;
static Actor* flowerParent = NULL;

typedef enum {
    REG_SUCCESS,
    REG_ERROR
} RegisterResult;

RegisterResult SilentPrincess_RegisterPosition(Actor* thisx) {
    // Check if enough entries remain
    if (posHead > MAX_FLOWERS - 1) {
        return REG_ERROR;
    }

    // Register the flower's position in the list
    posList[posHead] = thisx->world.pos;
    posHead++;

    // Kill any actors besides the first one the game spawns
    if (flowerParent == NULL) {
        flowerParent = thisx;
    } else {
        Actor_Kill(thisx);
    }

    return REG_SUCCESS;
}

void SilentPrincess_Init(Actor* thisx, GlobalContext* globalCtx) {
    SilentPrincess_RegisterPosition(thisx);
}

void SilentPrincess_Update(Actor* thisx, GlobalContext* globalCtx) {
    // no op
}

void SilentPrincess_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    // no op
}

void SilentPrincess_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 i;
    s32 matInitialized = false;

    for (i = 0; i < posHead; i++) {
        // Check if the flower is on screen or not
        if (Statics_UncullObject(globalCtx, &posList[i], 7.0f, 0, 15.0f, 0.0f, 900.0f)) {
            if (!matInitialized) {
                // Reset RDP state for OPA drawing
                func_80093D18(globalCtx->state.gfxCtx);
                // Load material for the flower
                gSPDisplayList(POLY_OPA_DISP++, mat_SilentPrincessMesh_SilentPrincessMatl_layerOpaque);
                matInitialized = true;
            }
            
            // Translate the position of the flower
            Matrix_Translate(posList[i].x, posList[i].y, posList[i].z, MTXMODE_NEW);
            // Rotate the flower to face the camera
            Matrix_RotateY((s16)(Camera_GetCamDirYaw(GET_ACTIVE_CAM(globalCtx)) - 0x4000) *
                            (M_PI / 32768.0f),
                        MTXMODE_APPLY);
            // Scale the flower
            Matrix_Scale(OBJ_SCALE, OBJ_SCALE, OBJ_SCALE * ((i & 1) ? -1.0f : 1.0f), MTXMODE_APPLY);

            // Apply the matrix to the RSP
            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx, "", 0), G_MTX_MODELVIEW | G_MTX_LOAD);

            // Draw the flower geometry
            gSPDisplayList(POLY_OPA_DISP++, SilentPrincessMesh_Plane_mesh_layer_Opaque_tri_0);
        }
    }
    
    if(matInitialized){
        // Reset RDP state afterwards since we used single-cycle mode
        func_80093D18(globalCtx->state.gfxCtx);
    }
}

const ActorInitExplPad init_vars = {
    .id = 0xDEAD, .padding = 0xBEEF, // <-- magic values, do not change
    .category = ACTORCAT_PROP,
	.flags = FLAGS,
	.objectId = OBJ_ID,
	.instanceSize = sizeof(Entity),
	.init = (ActorFunc)SilentPrincess_Init,
	.destroy = (ActorFunc)SilentPrincess_Destroy,
	.update = (ActorFunc)SilentPrincess_Update,
	.draw = (ActorFunc)SilentPrincess_Draw
};
