addi t0, x0, 1
addi t0, x0, 42
addi t0, x0, 256
addi t0, x0, 2047

addi t0, x0, -1
addi s0, x0, -2048
addi t1, x0, -255
addi t2, t1, -16

addi t0, x0, 1
addi s0, x0, 2047
addi t1, x0, 255
addi t2, t1, 16



andi t0, x0, 1
andi t0, x0, 42
andi t0, x0, 256
andi t0, x0, 2047

andi t0, x0, -1
andi s0, x0, -2048
andi t1, x0, -255
andi t2, t1, -16

andi t0, x0, 1
andi s0, x0, 2047
andi t1, x0, 255
andi t2, t1, 16



ori t0, x0, 1
ori t0, x0, 42
ori t0, x0, 256
ori t0, x0, 2047

ori t0, x0, -1
ori s0, x0, -2048
ori t1, x0, -255
ori t2, t1, -16

ori t0, x0, 1
ori s0, x0, 2047
ori t1, x0, 255
ori t2, t1, 16


ori t0, x0, 1
ori t0, x0, 42
ori t0, x0, 256
ori t0, x0, 2047

ori t0, x0, -1
ori s0, x0, -2048
ori t1, x0, -255
ori t2, t1, -16

ori t0, x0, 1
ori s0, x0, 2047
ori t1, x0, 255
ori t2, t1, 16



xori t0, x0, 1
xori t0, x0, 42
xori t0, x0, 256
xori t0, x0, 2047

xori t0, x0, -1
xori s0, x0, -2048
xori t1, x0, -255
xori t2, t1, -16

xori t0, x0, 1
xori s0, x0, 2047
xori t1, x0, 255
xori t2, t1, 16



slli t0, x0, 1
addi t0, x0, 4
slli t0, t0, 7



srli t0, x0, 1
addi t0, x0, 128
srli t0, t0, 2



srai t0, x0, 1
addi t0, x0, 128
srai t0, t0, 2

slti t0, x0, 1
addi t0, x0, 4
slli t0, t0, 7
