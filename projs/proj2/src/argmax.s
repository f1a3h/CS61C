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
    # Prologue
    addi t0, zero, 0 # max index
    addi t1, zero, 0 # current index

    blt zero, a1, loop_start

    li a1, 77
    j exit2

    addi a1, a1, -1

loop_start:
    beq t1, a1, loop_end

    slli t2, t1, 2
    add t2, a0, t2
    lw t2, 0(t2) # current element

    slli t3, t0, 2
    add t3, a0, t3
    lw t3, 0(t3) # max element

    blt t2, t3, loop_continue

    mv t0, t1

loop_continue:
    addi t1, t1, 1
    j loop_start

loop_end:
    # Epilogue
    mv a0, t0

    ret
