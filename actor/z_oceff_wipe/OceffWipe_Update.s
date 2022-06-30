.set noat
.set noreorder
.set gp=64

/* 
Have 24 instructions.
a0 = this, a1 = globalCtx
*/

/* Check and increment counter */
lh    $t0, 0x013C($a0) /* this->counter */
slti  $at, $t0, 99
beq   $at, $zero, lbl_endcount
addiu $t0, $t0, 0x0001
jr    $ra
sh    $t0, 0x013C($a0)

lbl_endcount:
/* Check if Zelda's Lullaby or Song of Time */
lh    $t3, 0x001C($a0) /* this->actor.params/variable */
beq   $t3, $zero, lbl_kill /* Zelda's is 0 */

/* Wait a little bit longer before triggering time travel */
lh    $t4, 0x013E($a0) /* unused halfword after counter */
slti  $at, $t4, 30
beq   $at, $zero, lbl_timetravel
addiu $t4, $t4, 0x0001
jr    $ra
sh    $t4, 0x013E($a0)

lbl_timetravel:
addiu $sp, $sp, -8
sw    $ra, 0($sp)
jal   Statics_TimeTravel
sw    $a0, 4($sp)
lw    $a0, 4($sp)
lw    $ra, 0($sp)
addiu $sp, $sp, 8

lbl_kill:
/* Tail call optimization--don't need stack */
j     0x80020EB4 /* Kill actor, arg a0 (this) */
nop
