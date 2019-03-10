addiu $t0, $t0,3
sll $t0,$t0,28
sll $t1,$t0,2
sll $t2,$t0,1
addiu $t1,$t1,91
addu $t1,$t0,$t1
sw $t1, 4($t0)
