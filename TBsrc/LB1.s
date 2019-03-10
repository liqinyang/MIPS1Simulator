lui $t0,0x1100
lui $t1,0x2400

lb $t3,-1($t0)
lb $t3,-1($t1)

lui $t0,0x1000
lui $t1,0x2000
lb $t3,0($t1)
lb $t3,0($t0)

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
