addiu $t0, $t0,3
sll $t0,$t0,28
addiu $t1,$t1,-5
top:addiu  $t1,$t1,1
addi $t3,$t3,1
bltzal $t1,top
add  $t2,$0,$t3
sw $t2, 4($t0)
sw $31, 4($t0)
srl $31,$31,8
sw $31, 4($t0)
srl $31,$31,8
sw $31, 4($t0)
srl $31,$31,8
sw $31, 4($t0)
jr   $0
