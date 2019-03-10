addiu $t0, $t0,3
sll $t0,$t0,28
lui $t2,0x2000
lui $t3,0xFECD
ori $t3,0x1234
sw $t3,0($t2)
addiu $t1,0x8123
sh $t1,0($t2)
lw $t3,0($t2)


sw $t3, 4($t0)
srl $t3,$t3,8
sw $t3, 4($t0)
srl $t3,$t3,8
sw $t3, 4($t0)
srl $t3,$t3,8
sw $t3, 4($t0)
jr   $0
