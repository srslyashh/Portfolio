TITLE Program 4   (program4_ka.asm)

; Author: Kathleen Ashley
; Last Modified: 13 November 2021
; OSU email address: ashleyk@oregonstate.edu
; Course number/section:   CS271 Section 001
; Project Number:  4            Due Date:  14 November 2021
; Description: [PRIME INTEGERS] This is a simple program that shows users prime numbers
;				depending on the input that they give. (Input should be 1 <= n <= 200).

INCLUDE Irvine32.inc

; constants
lowestLimit = 1
highestLimit = 200

.data
introtoProg		BYTE	"Welcome to Prime Integers, by Kathleen Ashley", 13, 10, 0
instruction		BYTE	"Enter the number of prime numbers you would like to see", 13,10,0
instruction2	BYTE	"The number should be between and including 1 and 200", 13,10,0
inputMessage	BYTE	"Enter the number of primes to display: ", 0
spaces			BYTE	"   ", 0

; err message and other messages
errorMessage	BYTE	"ERROR: Number is not within range! Try again", 13, 10, 0
goodbyeMessage	BYTE	"Thanks for playing and goodbye!", 13,10,0


; the variables that will be used to store the computation and user's name
input			SDWORD		?
counter			SDWORD		0
startLoop		SDWORD		1
divisionNum		SDWORD		2
oneVal			SDWORD		1
zeroVal			SDWORD		0
returnVal		SDWORD		?
currValue		SDWORD		2		; the number the program starts to evaluate.
tenElements		SDWORD		0		; used to keep a track of the elements within a line.


.code
main PROC
	; 1. introduce users to the program
	call introduction

	; 2. take input from users
	call getUserData
	call CrLf

	; 3. show the prime numbers
	call showPrimes
	call CrLf
	call CrLf

	; 4. Say goodbye to users.
	call farewell
	Invoke ExitProcess, 0	; exit to operating system
main ENDP

;-------------------------------------------------------------------------
; Name : introduction
; This procedure introduces the user to the program and gives instructions
; on what is expected by the program.
;
; Preconditions: the program has to successfully compile.
;
; Postconditions: edx will be used to print strings to the screen.
;
; Receives: this procedure receives nothing from the users.
;
; Returns: this procedure outputs a series of instructions & introduction
;          to the screen.
;-------------------------------------------------------------------------

introduction PROC
	mov edx, OFFSET introToProg
	call WriteString
	call CrLf
	mov edx, OFFSET instruction
	call WriteString
	mov edx, OFFSET instruction2
	call WriteString
	RET
introduction ENDP

;-------------------------------------------------------------------------
; Name : getUserData
; This procedure takes in a user's input and then calls the procedure
; validate to check whether or not the input is valid.
;
; Preconditions: The input has to be within range, that is between and
;                including the number 1 and 200.
;
; Postconditions: if the input is valid, the program will put the value from 
;                 eax to input.
;
; Receives: this procedure receives an input from the user (between 1 and 200)
;
; Returns: this procedure outputs an instruction to get the user to input the
;          value they want.
;-------------------------------------------------------------------------

getUserData PROC
	call CrLf
	mov edx, OFFSET inputMessage
	call WriteString
	call ReadInt
	call validate
	mov input, eax
	RET
getUserData ENDP

;-------------------------------------------------------------------------
; Name : validate
; This procedure takes in a user's input and then calls the procedure
; validate to check whether or not the input is valid.
;
; Preconditions: The input has to be within range, that is between and
;                including the number 1 and 200.
;
; Postconditions: if the input is valid, the program will put the value from 
;                 eax to input.
;
; Receives: this procedure receives an input from the user (between 1 and 200)
;
; Returns: this procedure outputs an instruction to get the user to input the
;          value they want.
;-------------------------------------------------------------------------

validate PROC
	; if input is less than 1, call error
	cmp eax, highestlimit
	jg _errorPrint

	; if input is greater than 200, call error 
	cmp eax, lowestlimit
	jl _errorPrint

	RET
validate ENDP

;-----------------------------------------------------------------------------------------
; Name : isPrime
; This procedure checks whether or not the current value being evaluated 
; by the program is prime.
;
; Preconditions: The counter of the amount of values being printed (ecx from looping function
;				 in showPrimes is not more than the amount of prime numbers the user requested.
;
; Postconditions: the returnVal will be altered depending on the value being prime/not prime.
;				  If value is prime, returnVal will be 1, otherwise 0.
;
; Receives: this procedure receives a currentValue being evaluated by showPrimes, uses divisionNum
;			to divide the value received and divisionNum will continue on being incremented if 
;			the value being evaluated doesn't result in R = 0. 
;
; Returns: this procedure returns two values - (0 for not prime numbers and 1 for prime numbers)
;		   the return value is stored in returnVal. It also calls output procedure to 
;		   print the prime numbers to the screen.
;-----------------------------------------------------------------------------------------

isPrime PROC
		_divisionPrime:
			mov eax, currValue
			mov ebx, divisionNum
			mov edx, zeroVal
			div ebx

			;--------------------------------------------------------------------
			; if remainder equals to 0, jump to the next function to see if the
			; EAX is 1. If it is, then it is a prime number.
			;--------------------------------------------------------------------
			cmp edx, 0
			je _checkPrimeTwo

			; keep on adding to divisionNum until the input number could be divided by it.
			inc divisionNum
			jmp _divisionPrime

		_checkPrimeTwo:
			;------------------------------------------------------------------------------
			; checks and see if eax is 1 while edx is 0 (ex : 2 would be Q : 1, R : 0)
			; then if it is, the said number must be prime.
			;------------------------------------------------------------------------------
			mov divisionNum, 2 ; set divisionNum to its normal state.
			cmp eax, 1
			; if it is prime, return 1.
			je _returnOne
			jmp _returnZero

		_returnOne:
			; change value in returnVal to 1 if prime
			mov returnVal, 1
			CALL outputResults
			jmp _goBack

		_returnZero:
			; change value in returnVal to 0 if not prime
			mov returnVal, 0
			CALL outputResults
		
		_goBack:
		RET
isPrime ENDP

;-----------------------------------------------------------------------------------------
; Name : outputResults
; This procedure prints the prime numbers to screen, if the number is not prime, then it will
; go directly to _goBack and returns to the previous function.
;
; Preconditions: In order for the number to be printed to screen, returnVal has to be 1. If 
;				 returnVal is 0, then return to the previous procedure.
;
; Postconditions: eax is changed to the currentValue, tenElements and counter are incremented so
;				  we could keep a track of them. Edx contains three spaces and later on gets
;			      printed to the screen.
;
; Receives: this procedure receives a returnVal from isPrime to determine whether or not the
;			procedure should print the number to screen, it also takes the current value to be printed
;			in the currValue variable. tenElements is used by the program to determine whether
;           10 elements have been printed to screen or not. 			
;
; Returns: this procedure 
;-----------------------------------------------------------------------------------------

outputResults PROC
	;--------------------------------------------------------------------------------
	; if return val is 1, then output results and increment counter (to check how many 
	; elements have been printed.
	;--------------------------------------------------------------------------------
	cmp returnVal, 1
	je _printNumber
	jmp _goBack

	_printNumber:
		;----------------------------------------------
		; see if there are already ten elements printed, 
		; if true, jmp to _addNewline function. 
		;----------------------------------------------
		cmp tenElements, 10
		je _addNewline
		jmp _printNumberTwo

		_addNewline:
			mov tenElements, 0
			call CrLf

		_printNumberTwo:
			inc tenElements
			inc counter
			mov eax, currValue
			call WriteDec
			mov edx, OFFSET spaces
			call WriteString

		_goBack:
		RET
outputResults ENDP

;-------------------------------------------------------------------------
; Name : showPrimes
; This procedure will keep on looping until the amount of prime numbers
; that the user has requested has been printed to the screen.
;
; Preconditions: for this procedure to run, the value entered by the user must be valid
;                (within range).
;
; Postconditions: the program will change the value of ecx depending whether the current value
;				  being evaluated is prime or not. If it's not prime, then loop again without 
;				  decrementing ecx. currValue also changes as the procedure goes on, so we could
;				  keep track of the number being evaluated by the program. EAX also changes as
;  				  the currValue changes (eax will be used in isPrime function)
;
; Receives: this procedure receives input from the user (determines how many prime numbers the
;			program should output to the screen, currValue is used to keep track of the number
;			being evaluated by isPrime procedure, returnVal is used to determine whether the 
;			value evaluated by isPrime is prime or not (1 for prime, 0 for not prime).
;
; Returns: this procedure only loops through the numbers until the amount of prime numbers
;		   requested by the user is printed to their screen.
;-------------------------------------------------------------------------

showPrimes PROC
	mov ecx, input
	mov ebx, 1
	mov eax, currValue
	_loopy:
		call isPrime
		inc currValue
		mov eax, currValue
		cmp returnVal, 0	; if the number is not prime (0), then jump to _loopy without decrementing ecx.
		je _loopy
		LOOP _loopy			; if returnVal is prime (1), loop the function and decrement ecx.
	RET
showPrimes ENDP

;-------------------------------------------------------------------------
; Name : farewell
; This procedure outputs a goodbye message to the screen.
;
; Preconditions: The last few steps of the program have to be finished, and
;                the program has to already output the prime numbers to the screen.
;
; Postconditions: the program puts a goodbyeMessage into edx to then print it out
;				  to the screen.
;
; Receives: this procedure receives no input from the user.
;
; Returns: this procedure outputs a goodbye message.
;-------------------------------------------------------------------------

farewell PROC
	mov edx, offset goodbyeMessage
	call WriteString
	call CrLf
	RET
farewell ENDP

;---------------------------------------------------------
; if the user's input is not within range, then print 
; this error message.
;---------------------------------------------------------
_errorPrint:
	mov edx, OFFSET errorMessage
	call WriteString
	call CrLf
	jmp getUserData

END main
