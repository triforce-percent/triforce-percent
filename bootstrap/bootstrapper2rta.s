.set noat
.set noreorder
.set gp=64

.include "bootstrapper2common.s"

/* Stop ACE and return */

/* Old real live version via seed rotation 0x801FC000:
Write jr $ra; instruction 0x03E00008
lui   $gp, 0x03E0
addiu $gp, $gp, 0x0008
lui   $v0, %hi(0x801FC000)
sw    $gp, %lo(0x801FC000)($v0) 
Normal return (got here via jal)
jr    $ra
lw    $v0, -0x20($sp) */

/* New real live version via wonder item:
Write 0002 to 801f73c6. This was changed via SRM to a branch
to Link's rotation, this restores the original code.
*/
addiu $gp, $zero, 0x0002
lui   $v0, %hi(0x801f73c6)
sh    $gp, %lo(0x801f73c6)($v0) 
/*
Jump to the end of a function which restores the stack correctly
(could do the restore manually, but this saves some instructions)
*/
j 0x80020850
lw $v0, -0x20($sp)
