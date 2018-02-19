// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.

	// Initialize answer address to 0 first
	@2
	M=0

	@0
	D=M
	@END
	D;JEQ
	
	@1
	D=M
	@END
	D;JEQ
	
	// keep numbers multiplied
	@1 
	D=M
	@3
	M=D

(LOOP)
	
	@0
	D=M
	
	// Answer = answer plus the number
	@2
	M=M+D
	
	// The number of times this needs to be repeated -= 1
	@3
	M=M-1
	
	// D needs to equal M because... That is how it works
	D=M
	@LOOP
	D;JGT
(END)
	@END
	0;JMP