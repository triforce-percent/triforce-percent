.set noat
.set noreorder
.set gp=64

/* To be injected at VRAM 800A2638 = VROM B18598. */
/* First instruction changes a1 from 6 to 18 to zero controllers 2-4
instead of just 2. This is the branch delay slot of bzero. */
addiu $a1, $zero, 18

/* Then we have three instructions to call rhstatics. */
jal Statics_Update
nop
nop
