;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

.ORIG x3000 

LD R6, STACK_PTR    ;R6 = x6000 mains return value

LEA R0, PROMPT
PUTS

GETC
OUT
ADD R1, R0, #0      ; R1 = input
LD R2, ASCIITODEC
ADD R1, R1, R2

ADD R6, R6, #-1     ; R6 = x5FFF int n
STR R1, R6, #0
ADD R5, R6, #0      ; R5 = x5FFF

LD R0, NEWLINE
OUT

ADD R6, R6, #-1     ; R6 = 5FFE int result

ADD R6, R6, #-1     ; R6 = 5FFD int n input
STR R1, R6, #0

JSR FIBONACCI ; Get fiboinacci number

LDR R3, R6, #0 ; R3 = result
STR R3, R5, #1 ; main return value

LD R2, DECTOASCII ; input to ascii
ADD R1, R1, R2

LEA R0, OUTPUT1
PUTS

ADD R0, R1, #0
OUT

LEA R0, OUTPUT2
PUTS

; Get ASCII form of result

; Tens digit
ADD R0, R3, #0
LD R4, TENS
AND R1, R1, #0 
ADD R1, R1, #-1
DIGIT1
ADD R1, R1, #1
ADD R3, R0, #0
ADD R0, R0, R4
BRp DIGIT1

ADD R0, R1, R2
OUT

; Ones digit
ADD R0, R3, R2
OUT

HALT

STACK_PTR .FILL x6000
PROMPT .STRINGZ "Please enter a number n: "
OUTPUT1 .STRINGZ "F("
OUTPUT2 .STRINGZ ") = "
NEWLINE .FILL x000A
RESULT .FILL x0000
ASCIITODEC .FILL #-48
DECTOASCII .FILL #48
TENS .FILL #-10

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

FIBONACCI

ADD R6, R6, #-1     ; Return value

ADD R6, R6, #-1     ; Return address
STR R7, R6, #0

ADD R6, R6, #-1     ; Frame pointer
STR R5, R6, #0

ADD R6, R6, #-1     ; Store R0
STR R0, R6, #0

ADD R6, R6, #-1     ; Store R1
STR R1, R6, #0

ADD R6, R6, #-1     ; Store R2
STR R2, R6, #0

ADD R6, R6, #-1     ; Store R3
STR R3, R6, #0

ADD R5, R6, #0      ; Set frame pointer

LDR R0, R5, #7      ; Load int n input

ADD R1, R0, #0      ; Check base case 0
BRz ZERO

ADD R1, R0, #-1     ; Check base case 1
BRz ONE

GENERALCASE
    ADD R2, R0, #-1     ; n-1
    ADD R6, R6, #-1     ; input n-1
    STR R2, R6, #0

    JSR FIBONACCI

    LDR R2, R6, #0

    ADD R6, R6, #1

    ADD R3, R0, #-2     ; n-2
    ADD R6, R6, #-1     ; input n-2
    STR R3, R6, #0

    JSR FIBONACCI

    LDR R3, R6, #0

    ADD R0, R2, R3 ; result
    STR R0, R5, #6

    ADD R6, R6, #1
    ADD R6, R6, #1
    BRnzp END

ZERO ; Zero base case
    AND R0, R0, #0
    STR R0, R5, #6
    ADD R6, R6, #-1
    BRnzp END

ONE ; One base case
    AND R0, R0, #0
    ADD R0, R0, #1
    STR R0, R5, #6
    ADD R6, R6, #-1

END
ADD R6, R6, #1    ; Restore R3
LDR R3, R6, #0     

ADD R6, R6, #1      ; Restore R2
LDR R2, R6, #0

ADD R6, R6, #1      ; Restore R1
LDR R1, R6, #0      

ADD R6, R6, #1      ; Restore R0
LDR R0, R6, #0      

ADD R6, R6, #1      ; Restore frame pointer
LDR R5, R6, #0

ADD R6, R6, #1      ; Restore return address
LDR R7, R6, #0

ADD R6, R6, #1      ; Return value

RET


.END