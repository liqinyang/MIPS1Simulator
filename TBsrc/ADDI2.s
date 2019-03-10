addiu $t0, $t0,3
sll $t0,$t0,28

addiu $1,$0,0xFFFF
sll  $1,$1,16
addiu $1,$1,0xFFFF
addi  $5,$1,2
sw $5, 4($t0)
jr   $0
