addiu $t0, $t0,3
sll $t0,$t0,28
lui $t1,0xFFFF
top:addiu  $t1,$t1,1
addi $t3,$t3,1
bgezal $t1,top
sw $t3, 4($t0)
sw $31, 4($t0)
srl $31,$31,8
sw $31, 4($t0)
srl $31,$31,8
sw $31, 4($t0)
srl $31,$31,8
sw $31, 4($t0)
jr   $0
