/* Bootstrapper 2 (new version) */
sw $v0, -0x20($sp) /*v0 contains 0x7FFF so unlikely to be useful*/

/* Detect whether running from the ACE context or the padmgr context
If padmgr, need normal return, not special stack restore
(but don't need to actually execute the rest of the bootstrapper)
During ACE context, s1 is global context 0x801C84A0*/
lui   $v0,      %hi(0x801C84A0)
addiu $v0, $v0, %lo(0x801C84A0)
beq   $v0, $s1, in_ace_context
lui   $gp,      0x0C00 /* First instruction of Cache Time below */

/* If not in ACE context, return */
jr $ra
lw $v0, -0x20($sp)

in_ace_context:
/*
Cache Time!
Setting the 6 instructions at 800A2630 to:
jal 0x80003440 (osWritebackDCache) = 0C000D10
addiu $a1, $zero, 0x7FFF           = 24057FFF
jal 0x800041A0 (osInvalICache)     = 0C001068
addiu $a1, $zero, 0x7FFF           = 24057FFF (actually not needed, a1 is not touched
    by osWritebackDCache, but we have to put something in the branch delay slot)
jal 0x8011D790 (pad 1)             = 0C0475E4
lui $a0, 0x8070                    = 3C048070
*/
lui   $v0,      0x800A

/*lui   $gp,      0x0C00 -- in branch delay slot above*/
addiu $gp, $gp, 0x0D10
sw    $gp,      0x2630($v0)
addiu $gp, $gp, (0x1068 - 0x0D10)
sw    $gp,      0x2638($v0)

lui   $gp,      %hi(0x24057FFF)
addiu $gp, $gp, %lo(0x24057FFF)
sw    $gp,      0x2634($v0)
sw    $gp,      0x263C($v0)

lui   $gp,      %hi(0x0C0475E4)
addiu $gp, $gp, %lo(0x0C0475E4)
sw    $gp,      0x2640($v0)

lui   $gp,      %hi(0x3C048070)
addiu $gp, $gp, %lo(0x3C048070)
sw    $gp,      0x2644($v0)

/*
Write 0x80400000 (address of start of TerusTheBird's fast_loader payload)
to address counter 0x80700000
*/
lui   $gp, 0x8040
lui   $v0, %hi(0x80700000)
sw    $gp, %lo(0x80700000)($v0)
