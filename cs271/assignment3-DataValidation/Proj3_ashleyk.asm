TITLE Program 3   (program1_ka.asm)

; Author: Kathleen Ashley
; Last Modified: October 31 2021
; OSU email address: ashleyk@oregonstate.edu
; Course number/section:   CS271 Section 001
; Project Number:  1             Due Date:  31 October 2021
; Description: This is a simple arithmetic program that should compute
;				the sum, rounded average, minimum and maximum values from the input 
;				that is given by the user.

INCLUDE Irvine32.inc

lowestLimit = -200
secLowestLimit = -100
secHighestLimit = -50
highestLimit = -1

.data
introtoProg		BYTE	"Welcome to Integer Accumulation, by Kathleen Ashley", 13, 10, 0
introName		BYTE	"What is your name? ", 0
sayHi			BYTE	"Hello there, ", 0
instruction		BYTE	"Please enter numbers in [-200,-100] or [-50, 1]", 13,10,0
instruction2	BYTE	"Enter a non-negative number once you are done to see the results!", 13,10,0
inputMessage	BYTE	"Enter number: ", 0
goodByeMessage	BYTE	"Thank you for playing the game and goodbye ", 0

; result messages
resultsM		BYTE	"Here are the results!",13,10,0
validNumM		BYTE	"Total of valid input: ",0
sumM			BYTE	"The sum of valid input: ",0
maximumM		BYTE	"The maximum value is: ", 0
minimumM		BYTE	"The minimum value is: ",0
averageM		BYTE	"The rounded average of the input is: ",0


; the variables that will be used to store the computation and user's name
username		BYTE	30 DUP(0)	; input will be received from user.
countNumbers	DWORD	0			; this value will increase as depending on the number of valid input.
maximumVal		SDWORD	-200		; make maximum val to be really far from 0 at the start for comparing with input later.
minimumVal		SDWORD	-1			; make minimum val to be really close to 0 at the start for comparing with input later.
holder			SDWORD	0
zeroVal			SDWORD	0
sumVal			SDWORD	0
validFlag		SDWORD	0
trueVal			SDWORD	1
averageVal		SDWORD  1
mulValue		SDWORD	100
fifty			SDWORD	50

; err message and other messages
errorMessage	BYTE	"ERROR: Invalid number! ", 13, 10, 0
specialMessage	BYTE	"ERROR: Cannot display results since you haven't entered any valid numbers yet!",13,10,0

.code
main PROC
; 1. INTRO TO PROGRAM

	mov edx, OFFSET introtoProg
	call WriteString

; 2. ASK FOR USER'S NAME AND STORE IT

	mov edx, OFFSET introName
	call WriteString
	mov edx, OFFSET username
	mov ecx, 30
	call ReadString
	call CrLf

	; saying hello

	mov edx, OFFSET sayHi
	call WriteString
	mov edx, OFFSET username
	call WriteString
	call CrLf

; 3. DISPLAY INSTRUCTIONS

	mov edx, OFFSET instruction
	call WriteString
	mov edx, OFFSET instruction2
	call WriteString
	call CrLf

; 4. REPEATEDLY PROMPT THE USER TO ENTER A NUMBER
	
	_inputNumber:
		mov edx, OFFSET inputMessage
		call WriteString
		call ReadInt
		 ; jump to print results if sign flag is clear
		JNS _goToResults

		mov holder, eax
		jmp _validCheck
	
		_goToResults:
			jmp _results
		
		; check if valid flag is 1, if it is, set it back to 0.
		; valid flag means that an input is valid and will be processed.
		_validCheck:
			mov eax, validFlag
			cmp eax, trueVal
			je _restartFlag


;-------------------------------------------------------
;      in this first check, we wanna make sure that 
;        input is <= -1 && >= -50. If that's the
;		case, set the valid flag to 1, and go to
;					the next process.
;--------------------------------------------------------
		; check if -1 is greater or equal to val
		_firstCheck:
			mov eax, highestLimit
			cmp eax, holder
			jge _firstCheckPartTwo

		; check if -50 is less than or equal to
		_firstCheckPartTwo:

			mov eax, secHighestLimit
			cmp eax, holder
			jle _validNumFlag

;-------------------------------------------------------
;      in this second check, we wanna make sure that 
;        input is <= -100 && >= -200. If that's the
;		case, set the valid flag to 1, and go to
;					the next process.
;--------------------------------------------------------
	; check if -100 is greater than or equal to value
	_secondCheck:
			mov eax, secLowestLimit
			cmp eax, holder
			jge _secondCheckPartTwo

;---------------------------------------------------------
;		if the input falls under this category,
;		it means that it's an invalid number.
;---------------------------------------------------------
			mov eax, validFlag
			cmp eax, zeroVal
			je _invalidNumberPrint
	
	; check if -200 is less than or equal to value
	_secondCheckPartTwo:
			mov eax, lowestLimit
			cmp eax, holder
			jle _validNumFlag

;---------------------------------------------------------
;		if the input falls under this category,
;		it means that it's an invalid number.
;---------------------------------------------------------
			mov eax, validFlag
			cmp eax, zeroVal
			je _invalidNumberPrint

;---------------------------------------------------------
; if number is valid, increment the valid flag and 
;				go to _validValue.
;---------------------------------------------------------
	_validNumFlag:
		inc validFlag
		jmp _validValue

	; this function sets the valid flag to 0.
	_restartFlag:
		dec validFlag
		jmp _firstCheck

	; prints the error message.
	_invalidNumberPrint:
		mov edx, OFFSET errorMessage
		call WriteString
		call CrLf
		jmp _inputNumber

;----------------------------------------------------------------------
;	if value is valid, check if it could be the new minimum
;	or maximum value, and update the sum and average value.
;----------------------------------------------------------------------
	_validValue:
		; if value is valid, increment the sum of valid number.
		mov eax, countNumbers
		add eax, 1
		mov countNumbers, eax

		; see if the input is of maximum value.
		mov eax, maximumVal
		cmp eax, holder
		; if the new value is greater than maximumVal,change maximum value to the new value.
		jl _newMaximum				
		; else, jump to the next process.
		jmp _minimum				

	_minimum:
		mov eax, minimumVal
		cmp eax, holder
		; if the new value is lesser than minimumVal, change mininum value to the new value.
		jg _newMinimum				
		; else, jump to the next process.
		jmp _sumValues				

	_sumValues:
		mov eax, sumVal
		add eax, holder
		mov sumVal, eax
		mov eax, sumVal
		jmp _average

	; 5. CALCULATE THE (ROUNDED INTEGER) AVERAGE OF THE VALID NUMBER AND STORE IN A VARIABLE.
	_average:
		; multiply sum by 100.
		mov eax, sumVal
		neg eax
		mul mulValue

		; divide by amount of numbers
		mov ebx, countNumbers
		mov edx, 0
		div ebx

		; divide by 100.
		mov ebx, mulValue
		mov edx, 0
		div ebx

;--------------------------------------------------------------
;       check if remainder is less than or more than 50.
;   if it is greater than 50, increment 1 to quotient. Else, 
;				move the value to the holder.
;--------------------------------------------------------------
		cmp edx, fifty
		jg _incrementQuotient
	
	; move value in eax to averageVal.
	_moveValToHolder:
		; turn eax value negative again.
		neg eax
		mov averageVal, eax
		jmp _inputNumber

	_incrementQuotient:
		inc eax
		jmp _moveValToHolder
	
	; replace the value in maximumVal with the new input.
	_newMaximum: 
		mov eax, holder
		mov maximumVal, eax
		jmp _minimum

	; replace the value in minimumVal with the new input.
	_newMinimum:
		mov eax, holder
		mov minimumVal, eax
		jmp _sumValues

; 6. DISPLAY THE RESULTS
	_results:
		; if numbers = 0, jump to goodbye right away
		mov eax, countNumbers
		cmp eax, zeroVal
		je _specialMessageF

		call CrLf
		mov edx, OFFSET resultsM
		call WriteString

		; A. THE COUNT OF VALIDATED NUMBERS

		mov edx, OFFSET validNumM
		call WriteString
		mov eax, countNumbers
		call WriteDec
		call CrLf

		; B. THE SUM OF VALIDATED NUMBERS

		mov edx, OFFSET sumM
		call WriteString
		mov eax, sumVal
		call WriteInt
		call CrLf

		; C. THE MAXIMUM (CLOSEST TO 0) VALID USER VALUE ENTERED

		mov edx, OFFSET maximumM
		call WriteString
		mov eax, maximumVal
		call WriteInt
		call CrLf

		; D.THE MINIMUM (FARTHEST FROM 0) VALID USER VALUE ENTERED

		mov edx, OFFSET minimumM
		call WriteString
		mov eax, minimumVal
		call WriteInt
		call CrLf

		; E. THE AVERAGE, ROUNDED TO THE NEAREST INTEGER.

		mov edx, OFFSET averageM
		call WriteString
		mov eax, averageVal
		call WriteInt
		call CrLf
		jmp _goodbye

	; if user has not entered any valid numbers, print the special message and jump to goodbye.
	_specialMessageF:
		mov edx, OFFSET specialMessage
		call WriteString

; 7. A PARTING MESSAGE WITH USER'S NAME

_goodbye:
	call CrLf
	mov edx, OFFSET goodbyeMessage
	call WriteString
	mov edx, OFFSET username
	call WriteString
	call CrLf

	Invoke ExitProcess, 0	; exit to operating system
main ENDP


END main
