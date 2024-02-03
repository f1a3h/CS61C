.globl relu

.text
# ==============================================================================
# FUNCTION: Performs an inplace element-wise ReLU on an array of ints
# Arguments:
# 	a0 (int*) is the pointer to the array
#	a1 (int)  is the # of elements in the array
# Returns:
#	None
# Exceptions:
# - If the length of the vector is less than 1,
#   this function terminates the program with error code 78.
# ==============================================================================
relu:
    # Prologue

	add t0, zero, a0
	addi t1, zero, 0

	blt zero, a1, loop_start

    li a1, 78
    j exit2

loop_start:
    beq t1, a1, loop_end

    lw t2, 0(t0)
    bge t2, zero, loop_continue

    addi t2, zero, 0

loop_continue:
	sw t2, 0(t0)

	addi t0, t0, 4
    addi t1, t1, 1
	j loop_start

loop_end:
    # Epilogue

	ret
