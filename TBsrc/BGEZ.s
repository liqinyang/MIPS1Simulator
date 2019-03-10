addiu $t1,$t1,5
top:addiu  $t1,$t1,-1
addi $t3,$t3,1
bgez $t1,top
add  $2,$0,$t3
jr   $0
