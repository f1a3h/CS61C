.globl matmul

.text
# =======================================================
# FUNCTION: Matrix Multiplication of 2 integer matrices
# 	d = matmul(m0, m1)
# Arguments:
# 	a0 (int*)  is the pointer to the start of m0 
#	a1 (int)   is the # of rows (height) of m0
#	a2 (int)   is the # of columns (width) of m0
#	a3 (int*)  is the pointer to the start of m1
# 	a4 (int)   is the # of rows (height) of m1
#	a5 (int)   is the # of columns (width) of m1
#	a6 (int*)  is the pointer to the the start of d
# Returns:
#	None (void), sets d = matmul(m0, m1)
# Exceptions:
#   Make sure to check in top to bottom order!
#   - If the dimensions of m0 do not make sense,
#     this function terminates the program with exit code 72.
#   - If the dimensions of m1 do not make sense,
#     this function terminates the program with exit code 73.
#   - If the dimensions of m0 and m1 don't match,
#     this function terminates the program with exit code 74.
# =======================================================
matmul:
    # Error checks
    li t0, 1
    ebreak
    blt a1, t0, error_72
    blt a2, t0, error_72
    blt a4, t0, error_73
    blt a5, t0, error_73
    bne a2, a4, error_74

    # Prologue
    addi sp, sp, -24
    sw ra, 0(sp)
    sw s0, 4(sp)
    sw s1, 8(sp)
    sw s2, 12(sp)
    sw s3, 16(sp)
    sw s4, 20(sp)

    add s0, zero, a6 # pointer to d
    add s1, zero, a0 # pointer to m0
    add s2, zero, a3 # pointer to m1

    mul s3, a1, a5 # number of outer iterations

    addi t0, zero, 0 # counter of outer loop

outer_loop_start:
    beq t0, s3, outer_loop_end

    div t1, t0, a5 # row index of m0 & d
    rem t2, t0, a5 # column index of m1 & d

    addi t3, zero, 0 # counter of inner loop

    addi s4, zero, 0 # dot result of d[t1][t2]

inner_loop_start:
    beq t3, a2, inner_loop_end

    mul t4, t1, a2
    add t4, t4, t3 # index of m0
    slli t4, t4, 2
    add t4, s1, t4 # address of m0
    lw t4, 0(t4)

    mul t5, t3, a5
    add t5, t5, t2 # index of m1
    slli t5, t5, 2
    add t5, s2, t5 # address of m1
    lw t5, 0(t5)

    mul t4, t4, t5
    add s4, s4, t4 # calculate dot result

    addi t3, t3, 1 # increment inner loop counter

    j inner_loop_start

inner_loop_end:
    slli t4, t0, 2
    add t4, s0, t4
    sw s4, 0(t4) # store dot result to d

    addi t0, t0, 1 # increment outer loop counter

    j outer_loop_start

outer_loop_end:
    # Epilogue
    lw s4, 20(sp)
    lw s3, 16(sp)
    lw s2, 12(sp)
    lw s1, 8(sp)
    lw s0, 4(sp)
    lw ra, 0(sp)
    addi sp, sp, 24
    
    ret

error_72:
    li a1, 72
    j exit2

error_73:
    li a1, 73
    j exit2

error_74:
    li a1, 74
    j exit2