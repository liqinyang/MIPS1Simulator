addiu $t0, $t0,3
sll $t0,$t0,28

lb $t3,0($t0)
sw $t3, 4($t0)
srl $t3,$t3,8
sw $t3, 4($t0)
srl $t3,$t3,8
sw $t3, 4($t0)
srl $t3,$t3,8
sw $t3, 4($t0)

lb $t3,1($t0)
sw $t3, 4($t0)
srl $t3,$t3,8
sw $t3, 4($t0)
srl $t3,$t3,8
sw $t3, 4($t0)
srl $t3,$t3,8
sw $t3, 4($t0)

lb $t3,2($t0)
sw $t3, 4($t0)
srl $t3,$t3,8
sw $t3, 4($t0)
srl $t3,$t3,8
sw $t3, 4($t0)
srl $t3,$t3,8
sw $t3, 4($t0)

lb $t3,3($t0)
sw $t3, 4($t0)
srl $t3,$t3,8
sw $t3, 4($t0)
srl $t3,$t3,8
sw $t3, 4($t0)
srl $t3,$t3,8
sw $t3, 4($t0)

lb $t3,3($t0)
sw $t3, 4($t0)
srl $t3,$t3,8
sw $t3, 4($t0)
srl $t3,$t3,8
sw $t3, 4($t0)
srl $t3,$t3,8
sw $t3, 4($t0)

lb $t3,0($t0)
sw $t3, 4($t0)
srl $t3,$t3,8
sw $t3, 4($t0)
srl $t3,$t3,8
sw $t3, 4($t0)
srl $t3,$t3,8
sw $t3, 4($t0)

jr   $0
