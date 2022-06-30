#ifndef __DEBUGGER_H__
#define __DEBUGGER_H__

extern u32 sPerfCount;
extern u8 sDbgLagRepeat;
extern f32 sDbgLagPlaySpeed;

//extern void _memcpy(void* dest, const void* src, u32 size);
extern char *Debugger_GetNextMessageBuffer(u8 timeout);
extern void Debugger_ShowMessage(u8 timeout, const char *msg);

#define Debugger_Printf(format...) \
    sprintf(Debugger_GetNextMessageBuffer(255), format)

#endif //__DEBUGGER_H__
