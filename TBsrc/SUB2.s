addiu $1,$0,0x7FFF
sll  $1,$1,16
ori $3,$1,0xFFFF
ori $4,$1,0xFFFE
sub  $2,$3,$4
jr   $0
