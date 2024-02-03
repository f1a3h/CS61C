.globl dot

.text
# =======================================================
# FUNCTION: Dot product of 2 int vectors
# Arguments:
#   a0 (int*) is the pointer to the start of v0
#   a1 (int*) is the pointer to the start of v1
#   a2 (int)  is the length of the vectors
#   a3 (int)  is the stride of v0
#   a4 (int)  is the stride of v1
# Returns:
#   a0 (int)  is the dot product of v0 and v1
# Exceptions:
# - If the length of the vector is less than 1,
#   this function terminates the program with error code 75.
# - If the stride of either vector is less than 1,
#   this function terminates the program with error code 76.
# =======================================================
dot:
    # Prologue
    addi t0, zero, 1
    blt a2, t0, error_75
    blt a3, t0, error_76
    blt a4, t0, error_76

    add t0, zero, a0 # pointer to v0
    add t1, zero, a1 # pointer to v1
    addi t2, zero, 0 # counter
    addi a0, zero, 0 # result
    slli a3, a3, 2 # stride of v0
    slli a4, a4, 2 # stride of v1

loop_start:
    beq t2, a2, loop_end

    lw t3, 0(t0)
    lw t4, 0(t1) 

    ebreak

    mul t3, t3, t4
    add a0, a0, t3

    add t0, t0, a3
    add t1, t1, a4

    addi t2, t2, 1

    j loop_start

loop_end:
    # Epilogue
    ret

error_75:
    li a1, 75
    j exit2

error_76:
    li a1, 76
    j exit2