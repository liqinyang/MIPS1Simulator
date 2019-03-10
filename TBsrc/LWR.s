addiu $t0, $t0,3
sll $t0,$t0,28
lui $t2,0x2001
lui $t1,0xFECD
ori $t1,0x1234
lui $t3,0x8888
ori $t3,0x8888
sw $t1,-8($t2)

lwr $t3,-8($t2)
sw $t3, 4($t0)
srl $t3,$t3,8
sw $t3, 4($t0)
srl $t3,$t3,8
sw $t3, 4($t0)
srl $t3,$t3,8
sw $t3, 4($t0)

jr   $0
