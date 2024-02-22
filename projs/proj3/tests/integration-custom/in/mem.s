addi t0, x0, 114
addi t1, x0, 514
addi t2, x0, 1919
addi t3, x0, 810

sw t2, 0(t0)
sh t2, 5(t0)
sb t2, 10(t0)

lw t3, 0(t0)
lw t3, 4(t0)
lw t3, 8(t0)

lh t3, 2(t0)
lh t3, 6(t0)

lb t3, 1(t0)
lb t3, 9(t0)
