addiu $t0, $t0,3
sll $t0,$t0,28
addiu $t1,0x8123
sb $t1,4($t0)
sb $t1,5($t0)
sb $t1,6($t0)
sb $t1,7($t0)
jr   $0
