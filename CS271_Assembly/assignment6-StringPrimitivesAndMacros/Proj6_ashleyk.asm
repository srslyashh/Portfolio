TITLE Program 6  (program6_ka.asm)

; Author: Kathleen Ashley
; Last Modified: 5 December 2021
; OSU email address: ashleyk@oregonstate.edu
; Course number/section:   CS271 Section 001
; Project Number:  6            Due Date:  5 December 2021
; Description: Takes in 10 a signed integer that does not exceed a 32-bit register, 
;			   displays the valid integers, output the sum and truncated average.


INCLUDE Irvine32.inc

; Constants
HI = 2147483647				; LIMIT FOR A SIGNED 32-BIT REGISTER
LO = 2147483648				; the lowest limit in positive value (since it'll be compared to a positive value)
INPUT_SIZE = 12				; so the program will only read up to 11 characters from input.
ARRAYSIZE = 10
NEGSIGN = 45
SPACE = 32

.data
introToProg		BYTE	"[Programming assignment 6] : Designing Low-level I/O Procedures by Kathleen Ashley", 13,10,0
instruction1	BYTE	"Please enter 10 signed decimal integers.", 13, 10, 0
instruction2	BYTE	"Each number needs to fit inside a 32-bit register.", 13, 10,0
instruction3	BYTE	"After you have entered 10 numbers, the program will display the list of integers you entered, their sum, and average value", 13, 10, 0
enterMessage	BYTE	"Please enter a signed number: ", 0
tryMessage		BYTE	"Please enter another number: ", 0
numbersMessage	BYTE	"The numbers you entered are as follows: ", 13, 10, 0
sumMessage		BYTE	"The sum of these numbers is: ", 0
avgMessage		BYTE	"The average of these numbers is: ", 0
commaMessage	BYTE	",", 0

; error messages and goodbye
errorMessage	BYTE	"ERROR: Your input wasn't valid. Either it wasn't a signed number or the value was too big", 13,10, 0
goodbyeMessage	BYTE	"Goodbye and thanks for playing!", 13,10,0

; variables
countInput		 DWORD	 10
inputArr		 DWORD	 10 DUP(?)			; array to store the numbers.
usrInput		 SDWORD	 11 DUP (?)			; 11 elements are allowed considering the +/- signs.
counter			 SDWORD	 0
inputLength		 SDWORD	 ?
charToPrint		 BYTE	 ?
emptyString		 BYTE	 ?
validInput		 SDWORD	 ?
negativeSign	 SDWORD	 0
firstFlag		 SDWORD	 0
conversionHolder SDWORD	 0
sum				 SDWORD	 0
average			 SDWORD	 0
zeroVal			 SDWORD	 0
numToPrint		 SDWORD  0


;-----------------------------------------------------------------------
; Name: mDisplayString
;
; Prints to screen the message that is passed on to the macro.
;
; preconditions: this macro needs a parameter to be passed onto it.
; 
; Receives:
;    - msgToPrint: the address of the message to be printed.
; 
; Returns: message is printed to the screen.
;-----------------------------------------------------------------------
mDisplayString MACRO msgToPrint
	pushad

	; here the message gets printed
	mov edx, msgToPrint
	call WriteString

	popad
ENDM

;-----------------------------------------------------------------------
; Name: mGetString
;
; Prints to screen the message that is passed on to the macro. The macro
; also takes in user's input and put in inside a holder, usrInput. It also
; puts in the length of the input inside inputLength.
;
; preconditions: this macro needs 4 parameters to be passed onto it 
; 
; Receives:
;    - msgToPrint: the address of the message to be printed.
;	 - userInput: the address of usrInput holder.
;	 - inputLimit: the limit on the input's length (value)
;	 - iptLength : the address of inputLength holder.
; 
; Returns: userInput holds the string of input that is entered by user,
;		  iptLength is changed and holds the value of current's input
;		  length. 
;-----------------------------------------------------------------------
mGetString MACRO msgToPrint, userInput, inputLimit, iptLength
	; saving the registers
	pushad

	;mov edx, msgToPrint
	;call WriteString

	mDisplayString msgToPrint

	mov edx, userInput

	; putting a limit on the amount of characters the program reads from input.
	mov ecx, inputLimit
	call ReadString
	mov iptLength, eax

	; restoring the registers
	popad
ENDM


.code
main PROC
	; 1. PRINTING INTRODUCTION TO PROGRAM
		push offset instruction3
		push offset instruction2
		push offset instruction1
		push offset introToProg

		call introduction

	; 2. GETTING INPUT FROM USER
		mov ecx, ARRAYSIZE
		_loopInput: 
			push offset counter
			push offset conversionHolder
			push offset firstFlag
			push offset negativeSign
			push offset errorMessage
			push offset enterMessage
			push offset inputArr
			push offset usrInput
			push offset inputLength

			call ReadVal

			; moves the value to the array edi is pointing to.
			mov eax, conversionHolder
			mov edi, offset inputArr
			add edi, counter
			mov [edi], eax
			; moves to the next element of the array.
			add counter, 4

			; clear conversionHolder.
			mov eax, 0
			mov edi, offset conversionHolder
			mov [edi], eax

			LOOP _loopInput

	; 3. PRINT OUT THE ARRAY
		call CrLf
		mDisplayString offset numbersMessage

		mov ecx, ARRAYSIZE
		mov counter, 0

		_loopPrint:
			mov esi, offset inputArr
			add esi, counter
			push offset commaMessage
			push ecx			
			push offset numToPrint
			push offset charToPrint
			mov eax, [esi]
			push eax
			call WriteVal

			cmp ecx, 1
			je _next

		_next:
			add counter, 4
			LOOP _loopPrint
			mov counter, 0
		
	; 4. CALCULATING SUM
		push offset zeroVal
		push offset sum
		push offset inputArr
		call calculateSum

		mDisplayString offset sumMessage

		; calling writeVal
		mov ecx, 1
		push offset commaMessage
		push ecx
		push offset numToPrint
		push offset charToPrint
		mov eax, sum
		push eax
		call WriteVal

		
	; 5. CALCULATING AVERAGE
		push sum
		push offset average
		call calculateAverage

		mDisplayString offset avgMessage

		; calling writeVal
		mov ecx, 1
		push offset commaMessage
		push ecx
		push offset numToPrint
		push offset charToPrint
		mov eax, average
		push eax
		call WriteVal
	
	; 6. PRINTING GOODBYE MESSAGE
		push OFFSET goodbyeMessage
		call goodbye
	
	; exit to operating system
	Invoke ExitProcess, 0
main ENDP


;--------------------------------------------------------------------------------------
; Name : calculateAverage
;
; This procedure calculates the average of user's input to the screen.
; the average will be truncated.
;
; Preconditions: the array needs to be filled and have valid values. Sum also needs
;				 to be calculated beforehand.
;
; Postconditions: the average holder [ebp + 8] will contain the value of the average
;				  that is computed by this procedure.
;
; Receives: 
;		[ebp + 12] = the value of sum.
;		[ebp + 8] = the address of average variable holder.
;		ARRAYSIZE = 10 -> this is the length of the array.
;
; Returns: none.
;---------------------------------------------------------------------------------------
calculateAverage PROC
	push ebp 
	mov ebp, esp
	pushad

	mov eax, [ebp + 12]
	mov ebx, ARRAYSIZE
	mov edx, 0
	div ebx

	mov edi, [ebp + 8]
	mov [edi], eax

	popad
	pop ebp
	ret 8
calculateAverage ENDP

;--------------------------------------------------------------------------------------
; Name : calculateSum
;
; This procedure calculates the sum of user's input to the screen.
;
; Preconditions: array needs to be filled and the value of sum must not exceed the
;				 limit of 32-bit register.
;
; Postconditions: the sum holder [ebp + 12] will contain the value of sum
;				  that is computed by this procedure.
;
; Receives: 
;		[ebp + 16] = the address of zeroVal
;		[ebp + 12] = the address of sum holder.
;		[ebp + 8] = the address of inputArr.
;		ARRAYSIZE = 10 -> this is the length of the array.
;
; Returns: none.
;---------------------------------------------------------------------------------------
calculateSum PROC
	push ebp
	mov ebp, esp
	pushad 

	mov ecx, ARRAYSIZE

	; moving the value zero to eax.
	mov esi, [ebp + 12]
	mov eax, [esi]
	
	; moving the beginning of the pointer to esi.
	mov esi, [ebp + 8]

	; goes through the array and increment eax (sum holder)
	_sumLoop:
		add eax, [esi]
		add esi, 4
		loop _sumLoop

	; moving the value of sum to the sum variable.
	mov edi, [ebp + 12]
	mov [edi], eax

	popad
	pop ebp
	ret 12
calculateSum ENDP

;--------------------------------------------------------------------------------------------------
; Name : WriteVal
;
; This procedure converts an integer value to its string value and passes it on to 
; mDisplayString to be printed out to screen
;
; Preconditions: the ecx that is pushed to the program needs to be above 0 in order
;				 for the print functions to work (comma and CrLf).  The value that is to be
;				 evaluated must also be an integer. The counter numToPrint is also set to 0.
;
; Postconditions: charToPrint will contain the value that has been converted from int to ASCII.
;				  numToPrint's value (the counter) will also be reset to 0 before the program ends.
;
; Receives: 
;		[ebp + 24] =  the address of commaMessage
;		[ebp + 20] =  the value of ecx (to see if we're evaluating the last element in the arr)
;		[ebp + 16] =  the address of numToPrint
;		[ebp + 12] =  the address of charToPrint
;		[ebp + 8]  =  the value that is to be evaluated
;		
;		; GLOBAL CONSTANTS
;		ARRAYSIZE  =  10 -> this is the length of the array.
;		SPACE	   =  ASCII character for space.
;		NEGSIGN	   =  ASCII character for '-'
;
; Returns: the integer that is stored in [ebp + 8] will be converted to a string and put inside
;		   the address of charToPrint.
;---------------------------------------------------------------------------------------------------
WriteVal PROC
	push ebp
	mov ebp, esp
	pushad

	; our counter variable
	mov esi, [ebp + 16]
	mov ecx, [esi]

	; moving the value to be evaluated to eax
	mov eax, [ebp + 8]

	; mov edi to point to the string to be modified.
	mov edi, [ebp + 12]

	; check if the value stored in eax is less than 0, if it is, we have to negate it.
	cmp eax, 0
	jl _negateVal
	jmp _conversion

	_negateVal:
		; saving the value in eax.
		push eax
		; putting '-' in the string that will be stored.
		mov al, NEGSIGN
		stosb 

		; print what is stored in the string now.
		mDisplayString [EBP + 12]
		dec edi

		pop eax
		neg eax

	_conversion:
		; Increment the counter variable held by ecx.
		inc ecx
		; Here, we divide the value stored in eax by 10. Until the value inside is 0.
		mov ebx, 10
		mov edx, 0
		div ebx
		; convert the remainder to an ASCII value by adding 48 to it. 
		add edx, 48
		; pushing the value so we can pop them later. 
		push edx
			
		; check if the value is 0, if not, keep on looping.
		cmp eax, 0
		jg _conversion
		; move counter to edx.
		mov edx, ecx
		jmp _moveValue

	_moveValue:
		pop eax 
		stosb 

		; print the character one by one.
		mDisplayString [EBP + 12]
		dec edi

		dec ecx
		cmp ecx, 0
		jg _moveValue
		je _printTheString

	_printTheString:
		mov al, SPACE
		stosb 
		inc edx
 
		; print the value one by one.
		mDisplayString [EBP + 12]
		dec edi

		; see if this is the last element in the array or not by checking the ecx.
		mov ecx, [ebp + 20]
		cmp ecx, 1
		je _printNewline
		jg _printComma
		jmp _bye

	_printComma:
		mDisplayString [EBP + 24]
		jmp _bye

	_printNewline:
		call CrLf

	_bye:
		; setting the counter to 0. 
		mov eax, 0
		mov edi, [ebp + 16]
		mov [edi], eax

	popad
	pop ebp
	ret 20
WriteVal ENDP

;--------------------------------------------------------------------------------------------------
; Name : ReadVal
;
; This procedure takes in usrInput (a string) and converts it to an equivalent value in integer.
; this program also checks whether the input is too big/ not suitable for the assignment.
;
; Preconditions: the ecx counter in main is not 0 (meaning we have yet to convert all the elements 
;				 in the inputArr to its equivalent value in integer. negativeSign will be 0, firstFlag
;				 will be 0, conversionHolder will be 0 (this variable contains the value that has been
;				 computed in this procedure)
;
; Postconditions: conversionHolder, counter, firstFlag, negativeSign will be reset to 0 before the
;				  procedure ends. Only inputLength and conversionHolder will still hold the values
;			      that were assigned from this procedure.
;
; Receives: 
;		[ebp + 40] =  the address of counter
;		[ebp + 36] =  the address of conversionHolder
;		[ebp + 32] =  the address of firstFlag
;		[ebp + 28] =  the address of negativeSign
;		[ebp + 24] =  the address of errorMessage
;		[ebp + 20] =  the address of enterMessage
;		[ebp + 16] =  the address of inputArr
;		[ebp + 12] =  the address of usrInput
;		[ebp + 8]  =  the address of inputLength
;
		; GLOBAL CONSTANTS
;		ARRAYSIZE  =  10 -> this is the length of the array.
;		SPACE	   =  ASCII character for space.
;		NEGSIGN	   =  ASCII character for '-'
;		LO		   =  Lowest limit for 32-bit register in positive value.
;
; Returns: this procedure changes the value inside conversionHolder (it will contain the int value
;		   of the string that is converted.
;---------------------------------------------------------------------------------------------------
ReadVal PROC
	push ebp
	mov ebp, esp

	pushad

	_promptInput: 
		mGetString [EBP + 20], [EBP + 12], INPUT_SIZE, [EBP + 8]

		;--------------------------------------------------------
		;   ecx is set to the length of the input string 
		; so we could check whether the whole string is valid.
		;--------------------------------------------------------

		mov esi, [ebp + 12]
		mov ecx, [ebp + 8]
		mov ebx, [ebp + 8]
		cld

	; 1. Check the first character and see if it's + / -.
	_positiveOrNegativeSigns:
		lodsb

		;--------------------------------------------------------
		; this is a counter to see if this is the first element
		; of the array or not.
		;--------------------------------------------------------
		mov ebx, [ebp + 8]
		cmp ecx, ebx
		jl _checkOtherElements

		; checks if it's a minus sign.
		cmp al, 45
		je _negativeFlag

		; checks if it's a positive sign
		cmp al, 43
		je _positiveFlag
		jmp _checkOtherElements

	_negativeFlag:
		mov eax, 1
		mov edi, [ebp + 28]
		mov [edi], eax
		jmp _loopThrough

	_positiveFlag:
		jmp _loopThrough

	_checkOtherElements:
		;-----------------------------------------------
		;   checking if the rest of the values have
		;     the ASCII values between 48 and 57.
		;-----------------------------------------------
		cmp al, 48
		jl _reprompt
		cmp al, 57
		jg _reprompt
		jmp _convertToInt

	_reprompt:
		; printing the error message
		mDisplayString [EBP + 24]

		; setting the negativeFlag to 0.
		mov eax, 0
		mov edi, [ebp + 28]
		mov [edi], eax

		; setting the firstFlag to 0.
		mov edi, [ebp + 32]
		mov [edi], eax

		; setting conversion holder to 0.
		mov edi, [ebp +36]
		mov [edi], eax

		jmp _promptInput

	_convertToInt:
		; convert the character by subtracting 48.
		movsx eax, al
		sub eax, 48

		; push eax so we can save the value.
		push eax

		;--------------------------------------------------------
		; the result of the multiplication is saved here.
		; holder for the conversion holder is pointed to by edi
		;--------------------------------------------------------
		mov edi, [ebp + 36]
		mov eax, [edi]

		; add it to ten times the current total.
		mov ebx, 10
		mul ebx 

		; pop the result from the subtraction
		pop ebx

		; edi takes the conversion holder and put the value in.
		mov edi, [ebp + 36]
		JO _reprompt
		mov [edi], eax

		; increment it with the value that was decremented by 48.
		add [edi], ebx
		JO _overflowCheck
		jmp _loopThrough

	_overflowCheck:
		; check if negativeFlag is 1.
		mov eax, 1 
		mov esi, [ebp + 28]
		cmp [esi], eax

		; if it is 0, then the limit is right. reprompt user!
		jl _reprompt

		;--------------------------------------------------------------------------
		; since it is negative, the limit is bigger than the positive limit by 1.
		; so instead of 2147483647, we should check if it is 2147483648 or more.
		;--------------------------------------------------------------------------
		mov eax, [edi]
		cmp eax, LO

		; if it is bigger than 2147483648, reprompt user.
		jg _reprompt 

		; if it is 2147483648, go to the next step.
		je _loopThrough
	
	_loopThrough:
		dec ecx
		cmp ecx, 0
		jg _positiveOrNegativeSigns

		; see if we need to negate the value
		mov eax, 1
		mov esi, [ebp + 28]
		cmp [esi], eax
		je _negate
		jmp _checkFlagValue

	_negate:
		mov eax, [edi]
		neg eax
		mov [edi], eax
				
	_checkFlagValue:
		; set the first element flag to 0.
		mov ebx, [ebp + 32]
		cmp ebx, 1
		je _changeFlagValue
		jmp _bye

	_changeFlagValue:
		mov eax, 0
		mov edi, [ebp + 32]
		mov [edi], eax

	_bye:
		; change the negative sign.
		mov eax, 0
		mov edi, [ebp + 28]
		mov [edi], eax

	popad
	pop ebp
	RET 40
ReadVal ENDP

;--------------------------------------------------------------------------------------------------
; Name : introduction
;
; This procedure prints to the display some set of instructions and introduction to the program.
;
; Preconditions: there needs to be 4 parameters to be printed.
;
; Postconditions: instructions and introToProg will print to screen.
;
; Receives: 
;		[ebp + 20] =  the address of instruction3
;		[ebp + 16] =  the address of instruction2
;		[ebp + 12] =  the address of instruction1
;		[ebp + 8]  =  the address of introToProg
;
; Returns: None. This program only prints to screen some instructions.
;---------------------------------------------------------------------------------------------------
introduction PROC
	push ebp 
	mov ebp, esp

	; displaying the introduction
	mDisplayString	[EBP + 8]
	call CrLf

	; displaying the instructions
	mDisplayString	[EBP + 12]
	mDisplayString	[EBP + 16]
	mDisplayString	[EBP + 20]
	call CrLf

	pop ebp
	RET 16
introduction ENDP

;--------------------------------------------------------------------------------------------------
; Name : goodbye
;
; This procedure prints to the display a goodbye message.
;
; Preconditions: needs an address to pass to the mDisplayString MACRO.
;
; Postconditions: a goodbye message will be displayed on the screen.
;
; Receives: 
;		[ebp + 8]  =  the address of goodbyeMessage
;
; Returns: None. This program only prints to screen a goodbye message.
;---------------------------------------------------------------------------------------------------
goodbye PROC
	push ebp 
	mov ebp, esp

	call CrLf
	mDisplayString [EBP + 8]

	pop ebp
	RET 4
goodbye ENDP

END main