addiu $t1,$t1,10
top:addiu  $t3,$t3,10
beq $t1,$t3,top
add  $2,$t1,$t3
jr   $0
