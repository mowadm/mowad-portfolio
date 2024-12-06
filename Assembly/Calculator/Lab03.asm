.ORIG x3000
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
PROGSTART
LEA R0, PROMPT1		; Load the first number prompt and display to the user
PUTS

JSR GETNUM ; Jump to getnum subroutine and get first num in R4
ST R4, NUM1 ; Store R4 to NUM1 in memory

LD R0, NEWLINE
OUT

LEA R0, PROMPT2		; Load the operation prompt and display to the user
PUTS

JSR GETOP ; Jump to GETOP subroutine

LD R0, NEWLINE
OUT

LEA R0, PROMPT3		; Load the second number prompt and display to the user
PUTS

JSR GETNUM ; Jump to getnum subroutine to get second num in R4
ST R4, NUM2 ; Store R4 to NUM2 in memory

LD R0, NEWLINE
OUT

LEA R0, PROMPT4		; Load the results prompt and display to the user
PUTS

JSR CALC ; Jump to CALC subroutine
ST R0, RESULT 
JSR DISPLAY

LD R0, NEWLINE
OUT

BRnzp PROGSTART ; Loop program

HALT
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

PROMPT1 .STRINGZ "Enter first number (0 - 99): "
PROMPT2 .STRINGZ "Enter an operation (+, -, *): "
PROMPT3 .STRINGZ "Enter second number (0 - 99): "
PROMPT4 .STRINGZ "Result: "
NEWLINE .FILL x000A
ASCIITODEC .FILL #-48
TEN .FILL #10
OPID .FILL xFFD5
TENS .FILL #-10
HUNDREDS .FILL #-100
THOUSANDS .FILL #-1000
NEG .FILL x002D

NUM1 .BLKW #1
NUM2 .BLKW #1
OP .BLKW #1
RESULT .BLKW #1
RETURN .BLKW #1

RESULTSTRING .BLKW #6

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
GETNUM

ADD R6, R7, #0 ; Save return address to R6

GETC ; Get first digit to R0
OUT
ADD R1, R0, #0 ; Copy to R1

GETC ; Get second digit to R0
OUT

ADD R7, R6, #0 ; Restore return address to R7

; Convert each from ASCII to decimal values
LD R5, ASCIITODEC
ADD R1, R1, R5
ADD R0, R0, R5

; Convert R1 to tens value
LD R3, TEN ; Load counter
AND R2, R2, #0 ; Clear R2
TENSLOOP ADD R2, R2, R1 ; Add R1 + R2 to R2
ADD R3, R3, #-1 ; Decrement counter
BRp TENSLOOP ; Loop if R3 > 0

ADD R4, R2, R0 ; Add tens digit and ones digit in R4

RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
GETOP

ADD R6, R7, #0 ; Save return address to R6

GETC ; Get operator to R0
OUT

ST R0, OP ; Store R0 to OP in memory

ADD R7, R6, #0 ; Reload return address to R7

RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
CALC

LD R6, OP ; Load operator
LD R5, OPID ; Load constant to determine operator
LD R1, NUM1 ; Load num1
LD R2, NUM2 ; Load num2
AND R0, R0, #0 ; Clear R0


ADD R5, R6, R5 ; Add R6 and R5

; In ASCII + is 2B, * 2A, - 2D.
; Therefore by subtracting 2B from operator, a cc of z means +, p means -, and n means *

BRp SUBTRACTION
BRn MULTIPLICATION

ADDITION

ADD R0, R1, R2 ; Add values and save to R0

RET

SUBTRACTION

NOT R2, R2 ; Invert R2
ADD R2, R2, #1 ; Add one to make twos comp of Num2

ADD R0, R1, R2 ; Add values and save to R0

RET

MULTIPLICATION

; If num 2 is 0, branch to return statement
ADD R2, R2, #0
BRz DONE

ADD R0, R0, R1 ; Add R1 to R0 and save to R0
ADD R2, R2, #-1 ; Decrement multiplcation counter for one repitition
BRp MULTIPLICATION ; If R2 is positive, loop

DONE
RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
DISPLAY

ST R7, RETURN ; Store return address

; R1, R2, R3, R4 will represent each digit of result
; clear registers
AND R1, R1, #0
AND R2, R2, #0
AND R3, R3, #0
AND R4, R4, #0

;Initialize to -1
ADD R1, R1, #-1
ADD R2, R2, #-1
ADD R3, R3, #-1
ADD R4, R4, #-1

LEA R7, RESULTSTRING ; Load starting address of string

; Test if negative
ADD R5, R0, #0
BRzp CONTINUE ; Branch to continue if not negative
NOT R5, R5
ADD R0, R5, #1 ; Perform two's comp to get positive number
LD R5, NEG ; Load ASCII - to R5
STR R5, R7, #0 ; Store to address in R7
ADD R7, R7, #1 ; Increment R7 to next address

CONTINUE
; Determine thousands digit
ADD R5, R0, #0 ; Copy R0 to R5
LD R6, THOUSANDS ; Load digit denomination
DIGIT1 ADD R0, R5, #0 ; Copy R5 to R0
ADD R1, R1, #1 ; Increment digit counter
ADD R5, R5, R6 ; Add -1000 to R0 save in R5
BRzp DIGIT1 ; If zero or positive, loop to back

; Determine hundreds digit
ADD R5, R0, #0
LD R6, HUNDREDS
DIGIT2 ADD R0, R5, #0
ADD R2, R2, #1
ADD R5, R5, R6 ; Add -100 to R0 save in R5
BRzp DIGIT2

; Determine tens digit
ADD R5, R0, #0
LD R6, TENS
DIGIT3 ADD R0, R5, #0
ADD R3, R3, #1
ADD R5, R5, R6 ; Add -10 to R0 save in R5
BRzp DIGIT3

; Determine ones digit
ADD R5, R0, #0
DIGIT4 ADD R0, R5, #0
ADD R4, R4, #1
ADD R5, R5, #-1 ; Add -1 to R0 save in R5
BRzp DIGIT4

; Load ASCIITODEC -48 and perform twos comp to 48
LD R5, ASCIITODEC 
NOT R5, R5 
ADD R5, R5, #1 

; Convert each demical digit to ASCII
ADD R1, R1, R5
ADD R2, R2, R5
ADD R3, R3, R5
ADD R4, R4, R5

; Store results in RESULTSTRING block
STR R1, R7, #0
STR R2, R7, #1
STR R3, R7, #2
STR R4, R7, #3
AND R5, R5, #0 ; Set R5 to zero to store as null terminate
STR R5, R7, #4 ;


LEA R0, RESULTSTRING ; Load string address to R0
PUTS ; Print result

LD R7, RETURN ; Load return address

RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

.END