addiu $t0, $t0,3
sll $t0,$t0,28
lui $t3,0xF321

sw $t3, 4($t0)
srl $t3,$t3,8
sw $t3, 4($t0)
srl $t3,$t3,8
sw $t3, 4($t0)
srl $t3,$t3,8
sw $t3, 4($t0)
jr   $0
