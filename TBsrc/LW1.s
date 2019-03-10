lui $t0,0x1100
lui $t1,0x2400

lw $t3,-4($t0)
lw $t3,-4($t1)

lui $t0,0x1000
lui $t1,0x2000
lw $t3,0($t1)
lw $t3,0($t0)

addiu $t0, $0,3
sll $t0,$t0,28
sw $t3, 4($t0)
srl $t3,$t3,8
sw $t3, 4($t0)
srl $t3,$t3,8
sw $t3, 4($t0)
srl $t3,$t3,8
sw $t3, 4($t0)

jr   $0
