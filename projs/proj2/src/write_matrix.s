.globl write_matrix

.text
# ==============================================================================
# FUNCTION: Writes a matrix of integers into a binary file
# FILE FORMAT:
#   The first 8 bytes of the file will be two 4 byte ints representing the
#   numbers of rows and columns respectively. Every 4 bytes thereafter is an
#   element of the matrix in row-major order.
# Arguments:
#   a0 (char*) is the pointer to string representing the filename
#   a1 (int*)  is the pointer to the start of the matrix in memory
#   a2 (int)   is the number of rows in the matrix
#   a3 (int)   is the number of columns in the matrix
# Returns:
#   None
# Exceptions:
# - If you receive an fopen error or eof,
#   this function terminates the program with error code 93.
# - If you receive an fwrite error or eof,
#   this function terminates the program with error code 94.
# - If you receive an fclose error or eof,
#   this function terminates the program with error code 95.
# ==============================================================================
write_matrix:

    # Prologue
    addi sp, sp, -28
    sw ra, 0(sp)
    sw s0, 4(sp)
    sw s1, 8(sp)
    sw s2, 12(sp)
    sw s3, 16(sp)
    sw s4, 20(sp)
    sw s5, 24(sp)

    # Save the arguments
    mv s0, a0
    mv s1, a1
    mv s2, a2
    mv s3, a3

    # Open the file
    mv a1, s0
    li a2, 1
    jal fopen
    li t0, -1
    beq a0, t0, error_93

    mv s4, a0 # Save the file descriptor

    # Write the number of rows and columns
    addi sp, sp, -8
    sw s2, 0(sp)
    sw s3, 4(sp)

    mv a1, s4
    mv a2, sp
    li a3, 2
    li a4, 4
    jal fwrite

    lw s3, 4(sp)
    lw s2, 0(sp)
    addi sp, sp, 8
    
    li t0, 2
    bne a0, t0, error_94

    # Write the matrix
    mul s5, s2, s3 # Calculate the number of elements in the matrix
    mv a1, s4
    mv a2, s1
    mv a3, s5
    li a4, 4
    jal fwrite
    bne a0, s5, error_94

    # Close the file
    mv a1, s4
    jal fclose
    bne a0, zero, error_95

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

error_93:
    li a1, 93
    j exit2

error_94:
    li a1, 94
    j exit2

error_95:
    li a1, 95
    j exit2