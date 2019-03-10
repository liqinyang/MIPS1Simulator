addiu $t1,$t1,0xFFFF
sll $t1,$t1,16
ori $t1,$t1,0xFF00

slti $2,$t1,0xFFFF

jr $zero
