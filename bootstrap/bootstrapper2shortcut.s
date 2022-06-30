.set noat
.set noreorder
.set gp=64

.include "bootstrapper2common.s"

/* Stop ACE and return */

/* Old shortcut via fake seed rotation 0x801C8004:
Write jr $ra; instruction 0x03E00008
lui   $gp, 0x03E0
addiu $gp, $gp, 0x0008
lui   $v0, %hi(0x801C8004)
sw    $gp, %lo(0x801C8004)($v0)
Normal return (got here via jal)
jr    $ra
lw    $v0, -0x20($sp) */

/* New shortcut:
Write 0xA5 to global->lighting.pad_00_[1] to signal ACE done */
addiu $gp, $zero, 0x00A5
lui   $v0, %hi(0x801C84A0+0x7A8+0xF)
sb    $gp, %lo(0x801C84A0+0x7A8+0xF)($v0) 
/* Normal return (got here via jal) */
jr    $ra
lw    $v0, -0x20($sp)
