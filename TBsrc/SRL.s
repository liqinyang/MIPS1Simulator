addiu $t0, $t0,3
sll $t0,$t0,28
addiu $t2,$0,0xFFFF
sll $t2,$t2,16
ori $t2,$t2,0xF07B
srl $t2,$t2,1
sw $t2, 4($t0)
srl $t2,$t2,31
sw $t2, 4($t0)
jr $zero
