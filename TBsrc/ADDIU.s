addiu $t0, $t0,3
sll $t0,$t0,28

addiu $t1,$t1,0xFFFF
srl $t1,$t1,24
sw $t1, 4($t0)
jr $zero
