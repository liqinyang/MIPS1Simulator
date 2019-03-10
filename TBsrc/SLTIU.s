addiu $t0, $t0,3
sll $t0,$t0,28

ori $t1,$t1,0xFFF0
sltiu $t2,$t1,0xF000
sw $t2,4($t0)

lui $t3,0xFFFF
sltiu $t2,$t3,0x1
sw $t2,4($t0)

lui $t4,0xFFFF
sltiu $t2,$t4,0xFFFF
sw $t2,4($t0)

jr $zero
