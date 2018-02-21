// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.

(BEGINNING)

// Put screen into memory
@SCREEN
D=A
@0
M=D

(KBDCHECK)

@KBD
D=M
@BLACK
D; JGT
@WHITE
D; JEQ

@KBDCHECK // If it gets here, it needs to check to loop again because it should never get here
0; JMP

(WHITE)
@1
M=0 // The color will equal 0000...
@CHANGELOOP
0; JMP

(BLACK)
@1
M=-1 // The color will equal 1111...
@CHANGELOOP
0; JMP


// Now change each pixel!

(CHANGELOOP)

@1
D=M // get what the pixel should be (black/white)

@0
A=M
M=D // change the pixel to whatever it should be

@0 // Still at 0, just making sure
D=M+1 // inc pixel chosen
@KBD
D=A-D

@0
M=M+1
A=M


@CHANGELOOP
A; JGT

@BEGINNING
0; JMP