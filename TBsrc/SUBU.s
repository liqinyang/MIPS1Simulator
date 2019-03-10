addiu $t0, $t0,3
sll $t0,$t0,28

lw $t1,0($t0)
addu $t2,$t2,$t1
sll $t2,$t2,8

lw $t1,0($t0)
addu $t2,$t2,$t1

lw $t1,0($t0)
addu $t3,$t3,$t1
sll $t3,$t3,8

lw $t1,0($t0)
addu $t3,$t3,$t1

subu $t4,$t2,$t3
sw $t4, 4($t0)
srl $t4,$t4,16
sw $t4, 4($t0)
jr $zero
