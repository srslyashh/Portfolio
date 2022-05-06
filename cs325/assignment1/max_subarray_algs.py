import sys
import time

# Usage when run from the command line: python max_subarray_algs.py <filename>.
# Example usage:                        python max_subarray_algs.py num_array_500.txt

file_name = sys.argv[1]

f = open(file_name, "r")
A = [int(num) for num in f.readline().strip().split(" ")]
f.close()

def max_subarray_enumeration(A):
    """
    Computes the value of a maximum subarray of the input array by "enumeration."
    
    Parameters:
        A: A list (array) of n >= 1 integers.

    
    Returns:
        The sum of the elements in a maximum subarray of A.
    """

    # TODO: Implement this function!

    #This code is the code that was coded
    #during lecture by Professor Huck Bennett.

    max_val = 0
    n = len(A)

    for i in range (n):
        for j in range (i, n):
            cur_val = 0
            for k in range(i, j):
                cur_val += A[k]

                if cur_val > max_val:
                    max_val = cur_val

    #print (max_val)
    return max_val

    
def max_subarray_iteration(A):
    """
    Computes the value of a maximum subarray of the input array by "iteration."
    
    Parameters:
        A: A list (array) of n >= 1 integers.
    
    Returns:
        The sum of the elements in a maximum subarray of A.
    """

    # TODO: Implement this function!

    max_val = 0
    n = len(A)

    for i in range(n):
        sum = 0
        for j in range(i, n):
            sum = sum + A[j]

            if sum > max_val:
                    max_val = sum

    return max_val

def modified_subarray_enumeration(A, items, n, m):

    max_val = 0

    for i in range (items):
        for j in range (i, items):
            #print("i: ", i)
            #print("j: ", j)
            #print("n:", n)
            cur_val = 0
            if n == 0:
                for k in range(n + i, j):
                    #print("k", k)
                    #print("A[k]", A[k])
                    cur_val += A[k]

                    if cur_val > max_val:
                        max_val = cur_val
            if n != 0:
                for k in range(n + i, n + j):
                    #print("k", k)
                    #print("A[k]", A[k])
                    cur_val += A[k]

                    if cur_val > max_val:
                        max_val = cur_val
    #print (max_val)
    return max_val
  
# This code was adapted from the one in the algorithms 
# textbook chapter 4. 
def maxSumOfLowerAndUpper(A, start, midP, endP):
 
    currSum = 0
    lowerSum = -1000
    upperSum = -1000
    
    # we do -1 with start so it'll go on a loop
    # for 6 times if midP is 5 and start is 0. 
    for i in range(midP, start-1, -1):
        #print("midP: ", midP)
        #print("start: ", start)
        #print("i: ", i)
        #print("A[i]: ", A[i])
        currSum = currSum + A[i]
 
        if (currSum > lowerSum):
            lowerSum = currSum
            maxLeftSum = i
 
    currSum = 0

    # So it will start after the midpoint we add 1, 
    # which means if midP is 249, it'll start at 250 
    # because A[249] and end at 500 (because 500-1 is 499)

    for j in range(midP + 1, endP + 1):
        currSum = currSum + A[j]
        #print("j: ", j)
        #print("A[j]: ", A[j])
 
        if (currSum > upperSum):
            upperSum = currSum
            maxRightSum = j

    return(maxLeftSum, maxRightSum, lowerSum+upperSum)
    

def max_subarray_simplification_delegation(A):
    """
    Computes the value of a maximum subarray of the input array by "simplification and delegation."
    
    Parameters:
        A: A list (array) of n >= 1 integers.
    
    Returns:
        The sum of the elements in a maximum subarray of A.
    """

    # TODO: Implement this function!

    n = len(A)
    half = n/2
    secondPart = n - half - 1
    lenMinusOne = n - 1
    max_val = 0
    start = 0

    #first = modified_subarray_enumeration(A, half, start, secondPart)
    #second = modified_subarray_enumeration(A, half, half, lenMinusOne)
    sumOfBoth = maxSumOfLowerAndUpper(A, start, secondPart, lenMinusOne)
    #sumOfBoth = maxSumOfLowerAndUpper(A, 0, 5, 10)

    #if first > second: 
       #max_val = first
    
   #if sumOfBoth > max_val:
        #max_val = sumOfBoth

    return max(sumOfBoth)

def max_subarray_recursion_inversion(A):
    """
    Computes the value of a maximum subarray of the input array by "recursion inversion."
    
    Parameters:
        A: A list (array) of n >= 1 integers.
    
    Returns:
        The sum of the elements in a maximum subarray of A.
    """

    # TODO: Implement this function!

    #The idea of this algorithm is 
    maxSum = 0
    currSum = 0
    length = len(A)
      
    for i in range(0, length):
        currSum = currSum + A[i]

        #the idea is here to switch maxSum with currSum
        #when currSum is higher than maxSum (so in the case of currSum 
        # being a minus and it doesn't )
        if maxSum < currSum:
            maxSum = currSum
 
        if currSum < 0:
            currSum = 0  

    return maxSum
  
def time_alg(alg, A):
    """
    Runs an algorithm for the maximum subarray problem on a test array and times how long it takes.
    
    Parameters:
        alg: An algorithm for the maximum subarray problem.
        A: A list (array) of n >= 1 integers.
    
    Returns:
        A pair consisting of the value of alg(A) asnd the time needed to execute alg(A) in milliseconds.
    """

    start_time = time.time() # The start time in milliseconds.
    max_subarray_val = alg(A)
    end_time = time.time()
    return max_subarray_val, end_time - start_time

    #start_time = time.monotonic_ns() // (10 ** 6) # The start time in milliseconds.
    #max_subarray_val = alg(A)
    #end_time   = time.monotonic_ns() // (10 ** 6) # The end time in milliseconds.
    #return max_subarray_val, end_time - start_time

for alg in [max_subarray_enumeration, max_subarray_iteration,
           max_subarray_simplification_delegation, max_subarray_recursion_inversion]:
    print(file_name, time_alg(alg, A))
