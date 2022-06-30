#include "ootmain.h"
#include "message.h"
#include "statics.h"
#include "../loader/debugger/debugger.h"

extern void Message_LoadJpnMsgInfo();
extern void Message_LoadEngMsgInfo();
extern void Message_LoadStaffMsgInfo();

extern MessageTableEntry *messageTableAddresses[3];

// typedef struct {
//     u8 unk[0x60];
//     s32 (*textCallback)(Font* message);
// } UnkN64DDStruct;
// 
// extern UnkN64DDStruct *n64ddStruct;
// UnkN64DDStruct localN64DDStruct;

// Message Symbol Declarations
#define DECLARE_MESSAGE(textId, type, yPos, message) \
    extern const char _message_ ## textId [];
#include "../text/messages.c"
#undef DECLARE_MESSAGE

// Message Table Declaration
MessageTableEntry hackMessageTable[] = {
    #define DECLARE_MESSAGE(textId, type, yPos, message) \
        { textId, (((type) << 4) | (yPos)), _message_ ## textId },
    #include "../text/messages.c"
    #undef DECLARE_MESSAGE
    { 0xFFFF, 0, NULL },
};

// static const u32 messageDataVROM[3] = {
//     0x008EB000, 0x0092D000, 0x00966000 //JP, US, staff
// };

void Statics_LoadMsgInfoPatched(GlobalContext *globalCtx, u16 textId, s32 type){
    Font *font = &globalCtx->msgCtx.font;
    MessageTableEntry *tbl;
    const char *baseSeg, *thisSeg, *nextSeg;
    u8 found = 0;
    
    //Try hack table first, for new messages or overrides of existing ones
    tbl = hackMessageTable;
    baseSeg = 0;
    while(tbl->textId != 0xFFFF){
        if(tbl->textId == textId){
            found = 1;
            break;
        }
        ++tbl;
    }
    
    //Handle conditional text patches
    if(
        (!(LONGOFTIME_VAR & LONGOFTIME_BIT) && (textId == 0x087A || textId == 0x089D)) ||
        (!(OVERTUREOFSAGES_VAR & OVERTUREOFSAGES_BIT) && 
            (textId == 0x0871 || textId == 0x0074 || textId == 0x0894 || textId == 0x088E)) 
    )
        found = 0;
    
    if(!found){
        //Use real table
        tbl = messageTableAddresses[type];
        baseSeg = tbl->segment;
        while(tbl->textId != 0xFFFF){
            if(tbl->textId == textId){
                found = 1;
                break;
            }
            ++tbl;
        }
        
        if(!found){
            //Text not found, default to Frog
            // if(sIsLiveRun) Debugger_Printf("No text %04X glbl %04X -> frog", 
            //     textId, (u16)globalCtx->msgCtx.unk_E2F8);
            tbl = messageTableAddresses[type];
            baseSeg = tbl->segment;
            tbl += 0xC;
        }
    }
    
    thisSeg = tbl->segment;
    font->unk_8[0] = tbl->typePos;
    ++tbl;
    nextSeg = tbl->segment;
    font->msgOffset = thisSeg - baseSeg;
    font->msgLength = nextSeg - thisSeg;
}

s32 Statics_N64DDTextCallback(Font *message){
    if(!(message->msgOffset & 0x80000000)) return 0; //Actual normal text
    if(message->msgLength > 1000){
        // if(sIsLiveRun) Debugger_Printf("Bad msg %08X %X -> frog",
        //     message->msgOffset, message->msgLength);
        //Something went wrong, default to Frog. Hope we're on US.
        message->msgOffset = messageTableAddresses[1][0xC].segment 
                           - messageTableAddresses[1][0x0].segment;
        message->msgLength = messageTableAddresses[1][0xD].segment 
                           - messageTableAddresses[1][0xC].segment;
        message->unk_8[0] = messageTableAddresses[1][0xC].typePos;
        return 0;
    }
    bcopy((const void*)message->msgOffset, message->msgBuf, message->msgLength);
    return 1;
}

/*
extern void Message_OpenText(GlobalContext* globalCtx, u16 textId);

void Message_OpenText_Print(s32 ra, u16 textId, s32 prevra){
    if(sIsLiveRun) Debugger_Printf("OpenText %04X < %08X < %08X", textId, ra, prevra);
}

void Message_OpenText_Wrapper(){
    asm(".set noat\n .set noreorder\n"
    "sw $a0, 0x0040($sp)\n"
    "or $a0, $ra, $zero\n"
    "jal Message_OpenText_Print\n"
    "lw $a2, 0x0054($sp)\n"
    "lw $ra, 0x0014($sp)\n"
    "lw $a0, 0x0040($sp)\n"
    "j Message_OpenText_4\n"
    "lw $a1, 0x0044($sp)\n"
    ".set at\n .set reorder");
}
*/

extern void Message_OpenTextCreditsPatchStart();
extern void Message_OpenTextCreditsPatchNotCredits();
extern void Message_OpenTextCreditsPatchIsCredits();

void Message_OpenTextCreditsPatch(){
    asm(".set noat\n .set noreorder\n"
    "slti $at, $v1, 0x0500\n"
    "bne  $at, $zero, Message_OpenTextCreditsPatchNo1\n"
    "slti $at, $v1, 0x1000\n"
    "beq  $at, $zero, Message_OpenTextCreditsPatchNo1\n"
    "slti $at, $v1, 0x0600\n"
    "bne  $at, $zero, Message_OpenTextCreditsPatchYes1\n"
    "slti $at, $v1, 0x0F00\n"
    "beq  $at, $zero, Message_OpenTextCreditsPatchYes1\n"
    "nop\n"
    "Message_OpenTextCreditsPatchNo1:\n"
    "j Message_OpenTextCreditsPatchNotCredits\n"
    "nop\n"
    "Message_OpenTextCreditsPatchYes1:\n"
    "j Message_OpenTextCreditsPatchIsCredits\n"
    "nop\n"
    ".set at\n .set reorder");
}

extern void Message_PostLoadStaffAddr();
extern void Message_PostLoadJpnAddr();
extern void Message_PostLoadEngAddr();

void Statics_MessageCodePatches(){
    //Text loader patches
    *( (u32*)Message_LoadJpnMsgInfo     ) = JUMPINSTR(Statics_LoadMsgInfoPatched);
    *(((u32*)Message_LoadJpnMsgInfo  )+1) = 0x34060000; //ori a2, zero, 0
    *( (u32*)Message_LoadEngMsgInfo     ) = JUMPINSTR(Statics_LoadMsgInfoPatched);
    *(((u32*)Message_LoadEngMsgInfo  )+1) = 0x34060001; //ori a2, zero, 1
    *( (u32*)Message_LoadStaffMsgInfo   ) = JUMPINSTR(Statics_LoadMsgInfoPatched);
    *(((u32*)Message_LoadStaffMsgInfo)+1) = 0x34060002; //ori a2, zero, 2
    //There's already some text patching system in place in the game,
    //presumably for the N64DD. Patch this to call our callback function.
    // if(n64ddStruct == NULL){
    //     n64ddStruct = &localN64DDStruct;
    // }
    // n64ddStruct->textCallback = Statics_N64DDTextCallback;
    *( (u32*)Message_PostLoadStaffAddr   ) = 0; //nop out first nullptr check
    *(((u32*)Message_PostLoadStaffAddr)+2) = 0; //nop out a load from nullptr
    *(((u32*)Message_PostLoadStaffAddr)+4) = 0; //nop out second nullptr check
    *(((u32*)Message_PostLoadStaffAddr)+7) = JALINSTR(Statics_N64DDTextCallback);
    *( (u32*)Message_PostLoadJpnAddr     ) = 0;
    *(((u32*)Message_PostLoadJpnAddr  )+2) = 0;
    *(((u32*)Message_PostLoadJpnAddr  )+4) = 0;
    *(((u32*)Message_PostLoadJpnAddr  )+7) = JALINSTR(Statics_N64DDTextCallback);
    *( (u32*)Message_PostLoadEngAddr     ) = 0;
    *(((u32*)Message_PostLoadEngAddr  )+2) = 0;
    *(((u32*)Message_PostLoadEngAddr  )+4) = 0;
    *(((u32*)Message_PostLoadEngAddr  )+7) = JALINSTR(Statics_N64DDTextCallback);
    //Credits patch
    *( (u32*)Message_OpenTextCreditsPatchStart   ) = JUMPINSTR(Message_OpenTextCreditsPatch);
    *(((u32*)Message_OpenTextCreditsPatchStart)+1) = 0;
    //Debugging
    //*(((u32*)Message_OpenText)+2) = JUMPINSTR(Message_OpenText_Wrapper);
}
