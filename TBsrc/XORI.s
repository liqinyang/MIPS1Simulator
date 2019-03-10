addiu $t0, $t0,3
sll $t0,$t0,28

addiu $t1,$t1,28
xori $t1,$t1,0xFF7A
sw $t1, 4($t0)
srl $t1,$t1,24
sw $t1,4($t0)
jr $zero
