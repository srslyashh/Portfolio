TITLE Program 5   (program4_ka.asm)

; Author: Kathleen Ashley
; Last Modified: 21 November 2021
; OSU email address: ashleyk@oregonstate.edu
; Course number/section:   CS271 Section 001
; Project Number:  5            Due Date:  21 November 2021
; Description: [Generating, sorting, and computing]. Generates 200 random numbers for the user in the range 
;				of 15 and 50. Display the original list of numbers, shows the user the median, sorts the list
;				in an ascending order and display it to the screen. The program should also show instances of
;				each value.

INCLUDE Irvine32.inc

; constants
ARRAYSIZE = 200
LO = 15
HI = 50

.data
introtoProg		BYTE	"Welcome to Generating, Sorting, and Computing by Kathleen Ashley", 13, 10, 0
instruction		BYTE	"This program computes 200 random numbers within the range of 15 and 50 (for the initial values)", 13,10,0
instruction2	BYTE	"display the original list of numbers, shows you the median value of the array, ", 13,10,0
instruction3	BYTE	"sorts the list in and ascending order, then display the number", 13,10,0
instruction4	BYTE	"of instances of each value, starting from 15",13,10,0
space			BYTE	" ", 0
unsortedM		BYTE	"Your unsorted array is: ",13,10,0
medianM			BYTE	"The median value of the array is: ",0
sortedM			BYTE	"Your sorted array is: ", 13,10,0
instancesM		BYTE	"Your list of instances is: ",13,10,0

; err message and other messages
goodbyeMessage	BYTE	"Thanks for playing and goodbye!", 13,10,0


; the variables that will be used to store the computation and user's name
input			SDWORD		?
counter			DWORD		0
holder1			DWORD		?
holder2			DWORD		?
countElement	DWORD		0
trueFlag		DWORD		1						; will be used to determine whether displayList is printing countList or not.
falseFlag		DWORD		0 
countSize		DWORD		0
someArray		DWORD		ARRAYSIZE DUP(?)		; leave 200 dword in an array uninitialized.
countArray		DWORD		HI DUP(?)				; will max have as many as HI elements.

.code
main PROC
	; call randomize
		call Randomize

	; 1. introduce users to the program

		; the parameters for introduction (passed by reference)
			push OFFSET instruction4
			push OFFSET instruction3
			push OFFSET instruction2
			push OFFSET instruction
			push OFFSET introToProg

			call introduction

	; 2. Generate random numbers & print the unsorted list to screen.
		
		; Generate random  numbers
			; pass by reference
			push offset someArray
			call fillArray

		; Print the unsorted list to the screen
			push falseFlag
			push counter			
			push offset someArray	
			push offset space		
			push offset unsortedM	
			call displayList

	; 3. Output the median value of the array
		
			; sort the array before finding the median
			push offset someArray
			call sortList

			; display the median
			push offset someArray
			push offset medianM
			call displayMedian
			

	; 4. Output the sorted array (in ascending order)
			push falseFlag
			push counter			
			push offset someArray	
			push offset space		
			push offset sortedM	
			call displayList
	
	; 5. List of instances.
			push offset countSize
			push countElement
			push offset countArray
			push offset someArray
			push offset instancesM
			call countList

			; print list of instances.
			push trueFlag
			push counter			
			push offset countArray	
			push offset space		
			push offset instancesM
			call displayList
	
	; 6. Say goodbye to users.
			push offset goodbyeMessage
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
; Receives: this procedure receives 5 address parameters from main, containing
;			introToProg, instruction, instruction2, instruction3,instruction4.
;
; Returns: this procedure outputs a series of instructions & introduction
;          to the screen.
;-------------------------------------------------------------------------

introduction PROC
	push ebp
	mov ebp, esp

	mov edx, [ebp + 8]
	call WriteString

	call CrLf
	mov edx, [ebp + 12]
	call WriteString

	mov edx, [ebp + 16]
	call WriteString

	mov edx, [ebp + 20]
	call WriteString

	mov edx, [ebp + 24]
	call WriteString

	pop ebp
	RET 20
introduction ENDP

;-------------------------------------------------------------------------
; Name : fillArray
; This procedure fill someArray with randomized numbers ranging from LO 
; to high.
;
; Preconditions: the program has to compile and someArray address has to exist
;				 so that the procedure could insert values in it.
;
; Postconditions: the values in someArray are changed and someArray is filled. ECX
;				  contains 0 at the end of the loop, edi is going to point
;				  at the end of the array, eax contains the difference between
;			      HI and LO + 1. 
;
; Receives: this procedure receives someArray's address by reference, so that
;			we would be able to manipulate its values. ARRAYSIZE is used to
;			loop through the program. HI and LO are used to indicate the 
;			range of the values that need to be put inside the list of array.
;
; Returns: this procedure returns the value 4, to pop off the address of 
;			someArray from the stack. The input parameter, someArray is 
;			changed as it's filled with values once this procedure ends.
;-------------------------------------------------------------------------
fillArray PROC
	push ebp
	mov ebp, esp

	; call the randomrange & fill in the array.
		; loopsize
		mov ecx, ARRAYSIZE
		; program gonna overwrite the values in the array, so use edi.
		; [ebp + 12] is referring to someArray.
		mov edi, [ebp + 8]

		_fillingArray:
			; set the range for the randomRange.
				; set the range to HI, with the initial range would be 50.
				mov eax, HI
				; subtract 15 from that so range of randomized numbers would be from 0-35.
				sub eax, LO
				; increment by 1 so it'll be 15 to 50.
				inc eax
				call randomRange
				; add lo to the randomized number so it would start from 15-50.
				add eax, LO

				; moving the value to the variable in the array.
				mov [edi], eax
				; add 4 to the edi so it'll point to the next element in the array.
				add edi, 4
				loop _fillingArray
		pop ebp
		RET 4
fillArray ENDP

;-------------------------------------------------------------------------
; Name : displayList
; This procedure prints out the array that is passed by reference from the
; main procedure.
;
; Preconditions: the program has to have an array to print in order for this 
;				 procedure to run.
;
; Postconditions: edx contains the space character at the end of the procedure,
;				  eax contains the last value in the array, esi points to the last
;				  element in the array, ebx contains the counter of elements in 
;				  a line.
;
; Receives: this procedure receives 5 input parameters, false/trueFlag - this indicates
;			whether the program is going to print countList/someArray, counter so that
;			the program can keep a track of the elements in a line. An address of someArray/
;			countArray, address of space and address of the message that is to be printed 
;			to the screen. ARRAYSIZE is used to loop through, or in this case where 
;			the program is printing countList, it will use HI / LO global variables to indicate
;			ecx.
;
; Returns: this procedure outputs the array that is received in the input.
;-------------------------------------------------------------------------
displayList PROC
	push ebp
	mov ebp, esp

	; print the message sent from main.
	call CrLf
	mov edx, [ebp + 8]
	call WriteString

	; mov counter to ebx.
	mov ebx, [ebp + 20]
	; move the address of someArray to esi.
	mov esi, [ebp + 16]
	; once edx has been used for message, place " " in edx.
	mov edx, [ebp + 12]

	; if this is 1, then it means we're printing for countList - different size compared to someArray.
	mov eax,[ebp + 24]
	cmp eax, 0
	jg _printListMode

	; set the loop counter for printing the array
	mov ecx, ARRAYSIZE
	jmp _printingArray

	_printListMode:
		; this means that the size of countList will be  50-15+ 1 = 36 (so it'll be from [15, 50])
		mov ecx, HI
		sub ecx, LO
		inc ecx

		; print the array, has to display 20 numbers per line, with space in between all the numbers. 
		; has to set a flag for the 20 numbers. 
		_printingArray:
			cmp ebx, 20					; see if there are already 20 elements in the curr line.
			je _printNewline
			jmp _printValue

			_printNewline:
				call CrLf
				mov ebx, 0
			_printValue:
				inc ebx
				mov eax, [esi]
				call WriteDec
				call WriteString
				add esi, 4				; add 4 byte so that it'll point to the next element.
				loop _printingArray
	
	call CrLf
	pop ebp
	RET 20
displayList ENDP

;-------------------------------------------------------------------------
; Name : countList
; This procedure counts the number of instances of each value that is 
; stored in the someArray. Moreover, this procedure also puts the number
; of instances found inside the array, countArray.
;
; Preconditions: the program has to have the address of someArray and countArray.
;				The program also needs ARRAYSIZE, HI, and LO to indicate the range
;				and the values that need to be compared to.
;
; Postconditions: esi will be pointing to the last value in the array, ecx will
;				  contain 0, ebx will contain the number of the instances for the
;				  last variable esi is pointing to. edx will contain the highest
;				  number in the range (which is HI). EAX contains the difference
;			      between HI and LO.
;
; Receives: this procedure receives 5 parameters, the address of countSize, the 
;			variable countElement, two addresses of countArray and someArray,
;			and the message that is to be printed to the screen. This program 
;			also utilizes ARRAYSIZE to loop through and count the number of 
;			instances. LO and HI are used to compare the amount of value to
;			be compared to the number that ESI is pointing to.
;
; Returns: this procedure counts the number of instances for each value, 
;		   then store that number in an array, countArray. 
;-------------------------------------------------------------------------
countList PROC
	push ebp
	mov ebp, esp
		
	; print out the message
	;call CrLf
	;mov edx, [ebp + 8]
	;call WriteString
	;call CrLf

	mov eax, HI
	sub eax, LO
	; holds the pointer to someArray
	mov esi, [ebp + 12]
	; holds the pointer to countArray
	mov edi, [ebp + 16]
	; counter element
	mov ebx, [ebp + 20]
	mov ecx, ARRAYSIZE
	; start comparing the values to the lowest value in the array which is stored in LO.
	mov edx, LO
		_loopy:
			cmp [esi], edx					; if the element ESI is pointing to is the same as edx, increment counter by 1.
			je _addOne
			jg _move						; if it's not the same, store the counter value and increment edx by 1.

			_addOne: 
				inc ebx
				jmp _next
			_move:
				mov [edi], ebx				; move the count value to the element pointed by esi.
				add edi, 4
				mov ebx, 1					; set counter to 1.
				inc edx						; set edx to the next element by incrementing it.
			_next: 
				add esi, 4					; move to the next value in the array
				cmp ecx, 1
				je _moveLastVal
				jmp _nextTwo
					_moveLastVal:
						mov [edi], ebx		; if there's only one item left in the arr, move counter.
					_nextTwo:
						loop _loopy
	pop ebp
	RET 20
countList ENDP

;-------------------------------------------------------------------------
; Name : displayMedian
; This procedure calculates and displays the median of the array to the screen.
;
; Preconditions: the program has to sort through the array before this procedure
;				can find the median of the array.
;
; Postconditions: eax will contain the median of arraysize
;				  of the array, edx will contain the remainder from the division,
;				  ebx will contain 2, and esi will contain the address of the pointer
;				  that points to the first variable in the array. 
;
; Receives: this procedure receives 2 input parameters, the address of someArray
;			that is already sorted and the address of the message that is to be
;			printed. arraysize will be used to determine the middle of the array.
;
; Returns: this procedure outputs the median of the array.
;-------------------------------------------------------------------------
displayMedian PROC
	push ebp 
	mov ebp, esp

	pushad
	; print Message
	mov edx, [ebp + 8]
	call CrLf
	call WriteString

	mov esi, [ebp + 12]
	;-----------------------------------------------------------------------------------------
	; find the middle value of the element by dividing it into two and - 1.
	;-----------------------------------------------------------------------------------------
	mov eax, ARRAYSIZE
	mov ebx, 2
	mov edx, 0
	div ebx
	dec eax
	mov ecx, eax

	mov eax, [esi + ecx * 4]
	inc ecx
	add eax, [esi + ecx * 4]
	mov ebx, 2
	mov edx, 0
	div ebx

	cmp edx, 1
	je _incrementOne
	jmp _printMedian
		;-----------------------------------------------------------------------------------------
		; If the average is odd, with a remainder of 1, then increment the eax value by 1
		; to round off the values.
		;-----------------------------------------------------------------------------------------
		_incrementOne:
			inc eax
		
		_printMedian:
			call WriteDec
			call CrLf
	popad
	pop ebp
	RET 8
displayMedian ENDP

;-------------------------------------------------------------------------
; Name : exchangeElements
; This procedure exchanges the values of the element that is being passed
; from the procedure sortList.
;
; Preconditions: the program needs to receive 2 addresses from the sortList
;				 procedure in order for this procedure to switch the values 
;				 that is contained between the addresses.
;
; Postconditions: none of the registers will be changed once the program 
;				  ends as the state of the registers were saved before the 
;				  program executed, and popad was used after the switching process
;				  was done.
;
; Receives: this procedure receives 2 address of esi and esi + 4 (so the value
;			after esi that is greater than esi.
;
; Returns: this procedure will switch the values that are in the two addresses given
;		   by sortList procedure.
;-------------------------------------------------------------------------
exchangeElements PROC
	push ebp
	mov ebp, esp

	; save the state of the registers
	pushad
	mov edx, [ebp + 12]
	mov ebx, [ebp + 8]
	; move the value of the lesser one to ecx.
	mov ecx, [ebx]
	; move the greater value to edx.
	mov eax, [edx]
	; switch the values 
	mov edi, edx
	mov [edi], ecx
	; move it to the other one.
	mov edx, ebx
	mov edi, edx
	mov [edi], eax

	popad
	pop ebp
	RET 8
exchangeElements ENDP

;-------------------------------------------------------------------------
; Name : sortList
; This procedure sorts the list so that the numbers in the array will
; be displayed in an ascending order.
;
; Preconditions: the program has to have an array to sort, the arraysize
;				 should be valid or else the procedure won't loop through
;				 the whole array.
;
; Postconditions: esi will point to the last element in the array, eax will contain
;				  the value that is in [esi + 4], ebx will contain the value that is
;				  in [esi]. Ecx will be 0 once the program ends.
;
; Receives: this procedure receives the address of an array that needs to be sorted
;			(in this case it will be someArray), arraysize is used to determine the
;			size of the loop.
;
; Returns: this procedure sorts a list of array in an ascending order.
;-------------------------------------------------------------------------
sortList PROC
	push ebp 
	mov ebp, esp

	mov ecx, ARRAYSIZE
	; holds the address of someArray.
	mov esi, [ebp + 8]							
	dec ecx
		; outer loop.
		_outerLoop:
			push ecx
			mov edx, [ebp + 8]
			mov esi, [ebp + 8]
			; inner loop.
			_innerLoop:
				mov eax, [esi + 4]				; compare the values of [esi + 4] and [esi], see if the first one is greater.
				mov ebx, [esi]
				cmp eax, ebx
				jg _skipSwitch

				push esi						; push the address of esi and the variable pointed after esi.
				add esi, 4
				push esi
				call exchangeElements
				sub esi, 4						; make sure to decrement esi after adding to it.

				_skipSwitch: 
					add esi, 4					; move to the next element in the array.
					loop _innerLoop

					pop ecx
					mov esi, edx
					add esi, 4
					loop _outerLoop
	pop ebp
	ret 4
sortList ENDP

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
	push ebp
	mov ebp, esp

	call CrLf
	mov edx, [ebp + 8]
	call WriteString
	call CrLf

	pop ebp
	RET 4
farewell ENDP

END main
