addiu $t0, $t0,3
sll $t0,$t0,28
lui $t3,0x1000
addiu $t3,$t3,0x0020
addiu $t1,$t1,1
jalr $t3
addiu  $t1,$t1,1
addiu  $t1,$t1,1
bottom:addiu  $t1,$t1,1
addiu  $t1,$t1,1
addiu  $t1,$t1,1
addiu $t3,$t3,28
jalr $t5,$t3
addiu  $t1,$t1,1
B:addiu  $t1,$t1,1
addiu  $t1,$t1,1
sw $t1, 4($t0)

sw $31, 4($t0)
srl $31,$31,8
sw $31, 4($t0)
srl $31,$31,8
sw $31, 4($t0)
srl $31,$31,8
sw $31, 4($t0)

sw $t5, 4($t0)
srl $t5,$t5,8
sw $t5, 4($t0)
srl $t5,$t5,8
sw $t5, 4($t0)
srl $t5,$t5,8
sw $t5, 4($t0)
jr   $0
