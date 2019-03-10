addiu $t1,$t1,1
addiu $t2,$t2,10
top:addiu  $t1,$t1,1
bne $t1,$t2,top
add  $2,$t2,$t1
jr   $0
