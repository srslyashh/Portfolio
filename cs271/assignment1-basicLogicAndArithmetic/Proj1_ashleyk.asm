TITLE Project 1   (Proj1_ashleyk.asm)

; Author: Kathleen Ashley
; Last Modified: October 16 2021
; OSU email address: ashleyk@oregonstate.edu
; Course number/section:   CS271 Section 001
; Project Number:  1             Due Date:  17 October 2021
; Description: This is a simple arithmetic program that should compute
;				the sum and differences between the integers that are entered by user.
;
; EXTRA CREDIT DONE : repeat program until user chooses to quit & check if numbers are not in 
;					  strictly descending order.

INCLUDE Irvine32.inc

.data
introtoProg		BYTE	"Welcome to Elementary Arithmetic, by Kathleen Ashley", 13, 10, 
						"Enter 3 numbers, A < B < C. The sums and differences will be computed!",13, 10, 0
extraCreditD	BYTE	"**EC: Program checks whether or not the input is in ascending order and lets user to ", 13, 10,
						"keep on playing until they choose to quit.", 13, 10,0
computationM	BYTE	"Here's the computation: ", 0
firstNumber		BYTE	"First number: ", 0
secondNumber	BYTE	"Second number: ", 0
thirdNumber		BYTE	"Third number: ", 0
askToRepeat		BYTE	"Do you want to repeat the program again? (Type 0 for yes, 1 for no) : ",0

; other messages.
errDescending	BYTE	"ERROR: The numbers you entered are not in descending order!", 13, 10, 0
goodByeMessage	BYTE	"Thank you for playing the game and goodbye!", 0
plusSign		BYTE	" + ", 0
minusSign		BYTE	" - ", 0
equalSign		BYTE	" = ", 0


; the variables that will be used to store the computation.
firstVal		DWORD	?
secondVal		DWORD	?
thirdVal		DWORD	?
aPlusB			DWORD	?
aMinusB			DWORD	?
aPlusC			DWORD	?
aMinusC			DWORD	?
bPlusC			DWORD	?
bMinusC			DWORD	?
sumAllThree		DWORD	?
repeatVal		DWORD	?
trueVal			DWORD	0		; this value is later on used to compare the value entered by user. 


.code
main PROC

_mainProgram:
; 1. INTRODUCTION TO THE PROGRAM.

	mov EDX, OFFSET introtoProg
	call WriteString
	call CrLf
	mov EDX, OFFSET extraCreditD
	call WriteString
	call CrLf

; 2. GET THE VALUES FROM THE USER

	; get the first value
	mov EDX, OFFSET firstNumber
	call WriteString
	call ReadDec
	mov firstVal, EAX

	; get the second value
	mov EDX, OFFSET secondNumber
	call WriteString
	call ReadDec
	mov secondVal, EAX

;-------------------------------------------------------
;       CHECK if value is less than first value. 
;    if the secondValue is greater than the first, 
;              print error message. 
;-------------------------------------------------------

	cmp firstVal, EAX
	jle _errMessage

	; get the third value
	mov EDX, OFFSET thirdNumber
	call WriteString
	call ReadDec
	mov thirdVal, EAX

;------------------------------------------------------
;      CHECK if value is less than second value. 
;    if the thirdValue is greater than the second, 
;             print error message. 
;------------------------------------------------------

	cmp secondVal, EAX
	jle _errMessage

; 3. CALCULATE THE GIVEN VALUES

	; A + B
	mov EAX, firstVal
	ADD EAX, secondVal
	mov aPlusB, EAX

	; A - B
	mov EAX, firstVal
	SUB EAX, secondVal
	mov aMinusB, EAX

	; A + C
	mov EAX, firstVal
	ADD EAX, thirdVal
	mov aPlusC, EAX

	; A - C
	mov EAX, firstVal
	SUB EAX, thirdVal
	mov aMinusC, EAX

	; B + C
	mov EAX, secondVal
	ADD EAX, thirdVal
	mov bPlusC, EAX

	; B - C
	mov EAX, secondVal
	SUB EAX, thirdVal
	mov bMinusC, EAX

	; A + B + C
	mov EAX, firstVal
	ADD EAX, secondVal
	ADD EAX, thirdVal
	mov sumAllThree, EAX

; 4. DISPLAY THE RESULTS

	call CrLf
	mov EDX, OFFSET computationM
	call WriteString
	call CrLf

	; A + B
	mov EAX, firstVal
	call WriteDec
	mov EDX, OFFSET plusSign
	call WriteString
	mov EAX, secondVal
	call WriteDec
	mov EDX, OFFSET equalSign
	call WriteString
	mov EAX, aPlusB
	call WriteDec
	call CrLf

	; A - B
	mov EAX, firstVal
	call WriteDec
	mov EDX, OFFSET minusSign
	call WriteString
	mov EAX, secondVal
	call WriteDec
	mov EDX, OFFSET equalSign
	call WriteString
	mov EAX, aMinusB
	call WriteDec
	call CrLf

	; A + C
	mov EAX, firstVal
	call WriteDec
	mov EDX, OFFSET plusSign
	call WriteString
	mov EAX, thirdVal
	call WriteDec
	mov EDX, OFFSET equalSign
	call WriteString
	mov EAX, aPlusC
	call WriteDec
	call CrLf

	; A - C
	mov EAX, firstVal
	call WriteDec
	mov EDX, OFFSET minusSign
	call WriteString
	mov EAX, thirdVal
	call WriteDec
	mov EDX, OFFSET equalSign
	call WriteString
	mov EAX, aMinusC
	call WriteDec
	call CrLf

	; B + C
	mov EAX, secondVal
	call WriteDec
	mov EDX, OFFSET plusSign
	call WriteString
	mov EAX, thirdVal
	call WriteDec
	mov EDX, OFFSET equalSign
	call WriteString
	mov EAX, bPlusC
	call WriteDec
	call CrLf

	; B - C
	mov EAX, secondVal
	call WriteDec
	mov EDX, OFFSET minusSign
	call WriteString
	mov EAX, thirdVal
	call WriteDec
	mov EDX, OFFSET equalSign
	call WriteString
	mov EAX, bMinusC
	call WriteDec
	call CrLf

	; A + B + C
	mov EAX, firstVal
	call WriteDec
	mov EDX, OFFSET plusSign
	call WriteString
	mov EAX, secondVal
	call WriteDec
	mov EDX, OFFSET plusSign
	call WriteString
	mov EAX, thirdVal
	call WriteDec
	mov EDX, OFFSET equalSign
	call WriteString
	mov EAX, sumAllThree
	call WriteDec
	call CrLf

	; ask if user wants to repeat game.
	mov EDX, OFFSET askToRepeat
	call WriteString
	call ReadDec
	mov repeatVal, EAX
	call CrLf

	; ------------------------------------------------------
	;    check if the user's input is 0, if it is, start
	;              the main program again.
	; ------------------------------------------------------
	cmp trueVal, EAX
	je _mainProgram

	
	;--------------------------------------------------------
	;  if it gets here, it means the numbers are strictly in 
	;     descending order. So skip the errMessage by: 
	;--------------------------------------------------------
	jmp _goodByeM

_errMessage:
	mov EDX, OFFSET errDescending
	call WriteString
	call CrLf

; 5. SAY GOODBYE
_goodByeM:
	call CrLf
	mov EDX, OFFSET goodByeMessage
	CALL WriteString
	CALL CrLf

	Invoke ExitProcess, 0	; exit to operating system
main ENDP


END main
