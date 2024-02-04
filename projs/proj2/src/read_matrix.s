.globl read_matrix

.text
# ==============================================================================
# FUNCTION: Allocates memory and reads in a binary file as a matrix of integers
#
# FILE FORMAT:
#   The first 8 bytes are two 4 byte ints representing the # of rows and columns
#   in the matrix. Every 4 bytes afterwards is an element of the matrix in
#   row-major order.
# Arguments:
#   a0 (char*) is the pointer to string representing the filename
#   a1 (int*)  is a pointer to an integer, we will set it to the number of rows
#   a2 (int*)  is a pointer to an integer, we will set it to the number of columns
# Returns:
#   a0 (int*)  is the pointer to the matrix in memory
# Exceptions:
# - If malloc returns an error,
#   this function terminates the program with error code 88.
# - If you receive an fopen error or eof, 
#   this function terminates the program with error code 90.
# - If you receive an fread error or eof,
#   this function terminates the program with error code 91.
# - If you receive an fclose error or eof,
#   this function terminates the program with error code 92.
# ==============================================================================
read_matrix:
    # Prologue
	addi sp, sp, -28
    sw ra, 0(sp)
    sw s0, 4(sp)
    sw s1, 8(sp)
    sw s2, 12(sp)
    sw s3, 16(sp)
    sw s4, 20(sp)
    sw s5, 24(sp)

    # Save arguments
    mv s0, a0
    mv s1, a1
    mv s2, a2

    # Open file
    mv a1, s0
    addi a2, zero, 0
    jal fopen
    li t0, -1
    beq a0, t0, error_90

    mv s3, a0 # Save file descriptor to s3

    # Read file
    # Read number of rows
    mv a1, s3
    mv a2, s1
    addi a3, zero, 4
    jal fread
    li t0, 4
    bne a0, t0, error_91

    # Read number of columns
    mv a1, s3
    mv a2, s2
    addi a3, zero, 4
    jal fread
    li t0, 4
    bne a0, t0, error_91

    # Allocate memory for matrix
    lw t0, 0(s1)
    lw t1, 0(s2)
    mul a0, t0, t1
    slli a0, a0, 2
    mv s5, a0 # Save size of matrix to s5
    jal malloc
    beq a0, zero, error_88

    mv s4, a0 # Save pointer to matrix to s4

    # Read matrix
    mv a1, s3
    mv a2, s4
    mv a3, s5
    jal fread
    bne a0, s5, error_91

    # Close file
    mv a1, s3
    jal fclose
    bne a0, zero, error_92

    # Save return value
    mv a0, s4

    # Epilogue
    lw s5, 24(sp)
    lw s4, 20(sp)
    lw s3, 16(sp)
    lw s2, 12(sp)
    lw s1, 8(sp)
    lw s0, 4(sp)
    lw ra, 0(sp)
    addi sp, sp, 28

    ret

error_88:
    li a1, 88
    j exit2

error_90:
    li a1, 90
    j exit2

error_91:
    li a1, 91
    j exit2

error_92:
    li a1, 92
    j exit2