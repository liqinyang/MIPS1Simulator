addiu $t0, $t0,3
sll $t0,$t0,28
addiu $t1,$t1,1
sw $31, 4($t0)
jal bottom
addiu  $t1,$t1,1
addiu  $t1,$t1,1
addiu  $t1,$t1,1
addiu  $t1,$t1,1
addiu  $t1,$t1,1
bottom:addiu  $t1,$t1,1
addiu  $t1,$t1,1
addiu  $t1,$t1,1
sw $t1, 4($t0)
srl $31,$31,8
sw $31, 4($t0)
srl $31,$31,8
sw $31, 4($t0)
srl $31,$31,8
sw $31, 4($t0)
jr   $0
