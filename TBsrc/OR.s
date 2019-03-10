addiu $t0, $t0,3
sll $t0,$t0,28

addiu $t1,$t1,28
addiu $t2,$t2,122
or $t1,$t2,$t1
sw $t1, 4($t0)
jr $zero
