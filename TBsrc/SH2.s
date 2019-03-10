addiu $t0, $t0,3
sll $t0,$t0,28
addiu $t1,0x8123
sh $t1,4($t0)
sh $t1,6($t0)
jr   $0
