addiu $t0, $t0,3
sll $t0,$t0,28
addiu $t2,$0,0xFFFF
sll $t2,$t2,16
ori $t2,$t2,0xF07B
ori $t1,$0,0x7FE1
srlv $t2,$t2,$t1
sw $t2, 4($t0)
addiu $t1,$0,0xFFFF
srlv $t2,$t2,$t1
sw $t2, 4($t0)
jr $zero
