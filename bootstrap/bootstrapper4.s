.set noat
.set noreorder
.set gp=64
/* 
Controller 2: stick Y bits 0 and 1 are bits 22 and 23 of D1
              stick Y bits 2 and 3 are bits 22 and 23 of D2
              This forms instruction `sll $zero, $???, 0` for some register, which is a nop
Controller 3: data word D1, except with bits 22 and 23 as zero
Controller 4: data word D2, except with bits 22 and 23 as zero

Once their zeroing instructions are nopped in BS2, controllers are located at:
1: 8011D790
2: 8011D796 (stick bytes in D798 and D799)
3: 8011D79C
4: 8011D7A2

Since we are now executing from the padmgr context (0x800A2640 to be exact),
we can clobber a0-a3 freely (actually probably t0-t9 and v0-v1 too)
bzero, which was the call there, clobbers a0, a1, a3, v1, and at

0x8011D790 = address of controllers
0x80700000 = address counter

*/
/*Address of controllers -> v0*/
lui   $v0, %hi(0x8011D790)
/*Controller 2 (stick bytes) -> a0*/
lhu   $a0, (%lo(0x8011D790)+0x08)($v0)
andi  $at, $a0, 0x03
sll   $at, $at, 22   /* bits 1:0 -> 23:22 */
andi  $a0, $a0, 0x0C
sll   $a0, $a0, 20   /* bits 3:2 -> 23:22 */
/*Controller 3 -> a1*/
lwu   $a1, (%lo(0x8011D790)+0x0C)($v0)
or    $a1, $a1, $at
/*Controller 4 -> a2*/
lwl   $a2, (%lo(0x8011D790)+0x12)($v0) /* word isn't aligned */
lwr   $a2, (%lo(0x8011D790)+0x15)($v0)
or    $a2, $a2, $a0      /* extra 2 bits from controller 2 */
/*Address counter + 8 -> v1 */
lui   $at, %hi(0x80700000)
lw    $v1, %lo(0x80700000)($at)
sw    $a1, 0($v1)
sw    $a2, 4($v1)
addiu $v1, $v1, 8
sw    $v1, %lo(0x80700000)($at)
/*Zero controllers*/
sh    $zero, (%lo(0x8011D790)+0x06)($v0) /*zero*/
sw    $zero, (%lo(0x8011D790)+0x08)($v0) /*them*/
sh    $zero, (%lo(0x8011D790)+0x12)($v0)
jr $ra
sw    $zero, (%lo(0x8011D790)+0x14)($v0)
