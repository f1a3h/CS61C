.globl factorial

.data
n: .word 8

.text
main:
    la t0, n
    lw a0, 0(t0)
    jal ra, factorial

    addi a1, a0, 0
    addi a0, x0, 1
    ecall # Print Result

    addi a1, x0, '\n'
    addi a0, x0, 11
    ecall # Print newline

    addi a0, x0, 10
    ecall # Exit

factorial:
    # YOUR CODE HERE
    # BEGIN PROLOGUE
    addi sp, sp, -8
    sw s0, 0(sp)
    sw ra, 4(sp)
    # END PROLOGUE

    add s0, x0, a0 # save argument to s0

    addi t0, x0, 1
    beq s0, t0, exit # if n=1 then exit
    
    addi a0, s0, -1
    jal ra, factorial # calculate (n-1)!
    mul a0, s0, a0 # n! = n * (n-1)!
    
exit:
    # BEGIN PROLOGUE
    lw ra, 4(sp)
    lw s0, 0(sp)
    addi sp, sp, 8
    # END PROLOGUE
    jr ra
    