OPAT(func_800ECB7C, 0x800C2104, 1,
    //Removing sNoteValueIndexMap
    "sb $a0, 0x006D($t3)\n"
)

OPAT(func_800ED200, 0x800C28E4, 1,
    //Removing sOcarinaNoteValues
    "or $t6, $t8, $zero\n"
)

OPAT(func_800EDD68, 0x800C3284, 1,
    //Removing set semitone to 0xC0 of note flags
    "or $t8, $zero, $zero\n"
)

//func_800EE318 = Audio_OcaUpdateDisplayedStaff
OPAT(func_800EE318_1, 0x800C3770, 1,
    //Removing Audio_OcaMapNoteValue
    "or $v0, $a0, $zero\n"
)

OPAT(func_800EE318_2, 0x800C37A4, 1,
    //Make condition checking for not Pierre's song never happen, so that playback
    //always happens like Pierre's song (multi-screen)
    "or $t9, $t8, $zero\n"
)

OPAT(func_800EE5EC_1, 0x800C3A58, 1,
    //Change range of note generation from 5 to 0x12 (memory game now MUCH harder)
    "addiu $t0, $zero, 0x0012\n"
)

OPAT(func_800EE5EC_2, 0x800C3A8C, 1,
    //Removing sOcarinaNoteValues
    "or $a1, $t8, $zero\n"
)

OPAT(func_800EE5EC_3, 0x800C3ABC, 1,
    //Removing sOcarinaNoteValues
    "or $a1, $t5, $zero\n"
)

OPAT(func_800ED458, 0x800C2ABC, 66,
    // t1 = &sCurOcarinaBtnVal = 80102210 (leave at end)
    // a1 = &sCurOcarinaBtnIdx
    // a2 = sCurOcarinaBtnPress
    // a3 must be 0x00FF at end
    // at = 1.0f (can overwrite after use) //done
    // All other temp registers are fair game
    // 80102B54 = sOcaMode //done
    // 80102220 = sCurOcaPitchCooked //done
    // 80102228 = sCurOcaPitchRaw //done
    // 80102230 = sCurOcaVibrato //done
    // 80121F20 = sCurOcaStick.x //done
    // 80121F21 = sCurOcaStick.y
    "ori   $a3, $zero, 0x00FF\n"
    "lbu   $t2, 0x0000($t1)\n" //sCurOcarinaBtnVal
    "sb    $t2, 0x0000($a1)\n" //sCurOcarinaBtnIdx
    "lui   $t0, 0x8010\n"
    "sw    $at, 0x2220($t0)\n" //sCurOcaPitchCooked = 1.0f
    "sb    $zero, 0x2228($t0)\n" //sCurOcaPitchRaw = 0
    "lbu   $t4, 0x2B54($t0)\n" //sOcaMode
    "ori   $t3, $zero, 0x0002\n" //2
    "beq   $t4, $t3, plbl_done\n"
    "lui   $t9, 0x8012\n"
    "beq   $t2, $a3, plbl_afterbtns\n"
    "lb    $t6, 0x1F21($t9)\n" //sCurOcaStick.y
    "andi  $t5, $a2, 0x0010\n" //sCurOcarinaBtnPress & BTN_R
    "bnel  $t5, $zero, plbl_postr\n"
    "addiu $t2, $t2, 0x0001\n" //++sCurOcarinaBtnVal
"plbl_postr:\n"
    "andi  $t5, $a2, 0x2000\n" //sCurOcarinaBtnPress & BTN_Z
    "bnel  $t5, $zero, plbl_postz\n"
    "addiu $t2, $t2, 0xFFFF\n" //--sCurOcarinaBtnVal
"plbl_postz:\n"
    "andi  $t5, $a2, 0x0800\n" //sCurOcarinaBtnPress & BTN_DUP
    "bne   $t5, $zero, plbl_up\n"
    "slti  $t7, $t6, 20\n"
    "bne   $t7, $zero, plbl_postup\n"
    "nop\n"
"plbl_up:\n"
    "addiu $t2, $t2, 0x0002\n" //sCurOcarinaBtnVal += 2
"plbl_postup:\n"
    "andi  $t5, $a2, 0x0400\n" //sCurOcarinaBtnPress & BTN_DDOWN
    "bne   $t5, $zero, plbl_dn\n"
    "slti  $t7, $t6, -20\n"
    "beq   $t7, $zero, plbl_postdn\n"
    "nop\n"
"plbl_dn:\n"
    "addiu $t2, $t2, 0xFFFE\n" //sCurOcarinaBtnVal -= 2
"plbl_postdn:\n"
    "sb    $t2, 0x0000($t1)\n" //sCurOcarinaBtnVal
    "sb    $t2, 0x0000($a1)\n" //sCurOcarinaBtnIdx
"plbl_afterbtns:\n"
    "lb    $a1, 0x1F20($t9)\n" //sCurOcaStick.x
    "blezl $a1, plbl_nonneg\n"
    "sub   $a1, $zero, $a1\n" //only executed if branch taken (t4 <= 0)
"plbl_nonneg:\n"
    "sra   $a1, $a1, 2\n"
    "sb    $a1, 0x2230($t0)\n" //sCurOcaVibrato
    "lui   $a0, 0x0602\n"
    "jal   Audio_QueueCmdS8\n" //func_800BB0E0
    "addiu $a0, $a0, 0x0D06\n"
    "lui   $t1, 0x8010\n"
    "ori   $a3, $zero, 0x00FF\n" //restore a3
    "addiu $t1, $t1, 0x2210\n" //restore t1
"plbl_done:\n"
    //43 instructions above this, need 66: add 23
    "nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n "
    "nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n "
    "nop\n nop\n nop\n"
)

OPAT(func_8010C39C_1, 0x800E04AC, 20,
    //0x140(sp) = gfx
    //t3, t5, ra: magic values
    //s0 = &static ctx
    //v1 = counter
    //going in t2 = x, coming out v0 = x
    //t4 = notes pointer (add 1)
    //s1, s3 free
    "or $s1, $v1, $zero\n"
    "sw $t2, 0x0004($sp)\n"
    "sw $t3, 0x0008($sp)\n"
    "sw $t4, 0x000C($sp)\n"
    "sw $t5, 0x0010($sp)\n"
    "or $s3, $ra, $zero\n"
    "lw $a0, 0x0140($sp)\n"
    "addu $a1, $t4, $v1\n"
    "lbu $a1, 0x0001($a1)\n"
    "or $a2, $t2, $zero\n"
    "jal PatchOcaButtons\n"
    "ori $a3, $zero, 0x0001\n"
    "sw $v0, 0x0140($sp)\n"
    "or $v1, $s1, $zero\n"
    "lw $v0, 0x0004($sp)\n"
    "lw $t3, 0x0008($sp)\n"
    "lw $t4, 0x000C($sp)\n"
    "lw $t5, 0x0010($sp)\n"
    "j func_8010C39C_1_ret\n"
    "or $ra, $s3, $zero\n"
)

OPAT(func_8010C39C_2, 0x800E084C, 13,
    //going in t2 = x, coming out v0 = x (stored in s2)
    //v1 = counter (stored in s1)
    //t3 = magic value (stored in s3)
    //s0 = &static ctx
    //0x140(sp) = gfx
    //going in v0 = gfx
    //going in a3 = &sOcaBuff[i]
    //s1, s2, s3 available
    //stack 00-28 available
    //Gfx* PatchOcaButtons(Gfx* gfx, u8 note, s16 x, u8 shadow)
    "or $s1, $v1, $zero\n"
    "or $s2, $t2, $zero\n"
    "or $s3, $t3, $zero\n"
    "or $a0, $v0, $zero\n"
    "lbu $a1, 0x0000($a3)\n"
    "or $a2, $t2, $zero\n"
    "jal PatchOcaButtons\n"
    "ori $a3, $zero, 0x0000\n"
    "sw $v0, 0x0140($sp)\n"
    "or $t3, $s3, $zero\n"
    "or $v0, $s2, $zero\n"
    "j func_8010C39C_2_ret\n"
    "or $v1, $s1, $zero\n"
)

OPAT(func_8010C39C_3, 0x800E06F0, 2, //only copy two instrs
    "slti $at, $t7, 0x0005\n"
    "beq $at, $zero, plbl_color\n"
    "nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n "
    "nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n "
    "nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n "
    "nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n "
    "nop\n nop\n nop\n nop\n"
    "plbl_color:\n"
    "nop\n"
)
    
