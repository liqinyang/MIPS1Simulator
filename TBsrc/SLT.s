addiu $t0, $t0,3
sll $t0,$t0,28

addiu $t1,$t1,0xFFFF
sll $t1,$t1,16
addiu $t1,$t1,0xFFFF

addiu $t2,$t2,0x1FFF
sll $t2,$t2,16
addiu $t2,$t2,0xFFFF


slt $t3,$t1,$t2
sw $t3,4($t0)
jr $zero
