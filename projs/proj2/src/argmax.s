.globl argmax

.text
# =================================================================
# FUNCTION: Given a int vector, return the index of the largest
#	element. If there are multiple, return the one
#	with the smallest index.
# Arguments:
# 	a0 (int*) is the pointer to the start of the vector
#	a1 (int)  is the # of elements in the vector
# Returns:
#	a0 (int)  is the first index of the largest element
# Exceptions:
# - If the length of the vector is less than 1,
#   this function terminates the program with error code 77.
# =================================================================
argmax:
    li t0, 1
    blt a1, t0, error_77

    # Prologue
    addi sp, sp, -12
    sw ra, 0(sp)
    sw s0, 4(sp)
    sw s1, 8(sp)

    # Save arguments
    mv s0, a0
    mv s1, a1

    addi t0, zero, 0 # max index
    addi t1, zero, 0 # current index

loop_start:
    beq t1, s1, loop_end

    slli t2, t1, 2
    add t2, s0, t2
    lw t2, 0(t2) # current element

    slli t3, t0, 2
    add t3, s0, t3
    lw t3, 0(t3) # max element

    bge t3, t2, loop_continue

    mv t0, t1

loop_continue:
    addi t1, t1, 1
    j loop_start

loop_end:
    # Epilogue
    lw s1, 8(sp)
    lw s0, 4(sp)
    lw ra, 0(sp)
    addi sp, sp, 12

    mv a0, t0

    ret

error_77:
    li a1, 77
    j exit2