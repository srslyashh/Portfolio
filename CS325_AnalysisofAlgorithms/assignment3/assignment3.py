import sys

def file_contents_letters(file_name):
    """
    Takes a file name as input and returns a string consisting of the file's contents
    with all non-letter characters removed.
    
    Parameters:
        file_name: The name of the file.
    
    Returns:
        A string with the contents of <file_name> but with all non-letter characters removed.
    """

    f = open(file_name, "r")
    file_contents = f.read()
    f.close()
    return "".join([c for c in file_contents if c.isalpha()])
    
def edit_distance(s1, s2):
    """
    Computes the edit distance between two strings, s1 and s2.
    
    Parameters:
        s1: The first string.
        s2: The second string.
    
    Returns:
        The edit distance between s1 and s2.
    """

    # TODO: Implement this function!
    # Implemented using professor Huck's lecture notes

    str1 = len(s1)
    str2 = len(s2)

    # Make a (str1 + 1) * (str2 + 1) array
    array = [[0 for i in range(str2 + 1)] for i in range (str1 + 1)]

    #Initializing the table array
    for i in range(str1):
        for j in range(str2):
            #Initializing the table array.
            # Initialize the first column
            # if j is 0, initialize i so [1][0] would be 1.
            if j == 0:
                 array[i][j] = i
            # Initialize the first row.
            # if i is 0, initialize the value in that row to j.
            elif i == 0:
                 array[i][j] = j

    #Finding the edit distance
    for i in range(str1):
        for j in range(1, str2 + 1):
            # compare the character in string 1 and string 2,
            # if they are the same, take the value from the row -1 and column-1
            # before the current value that is being evaluated.
            if s1[i-1] == s2[j - 1]:
                array[i][j] = array[i - 1][j - 1]
            else:
                # if the characters are not the same, try to find the minimum operation from either 
                # insert (array[i][j-1]), remove (array[i-1][j], or replace[i-1][j-1])
                array[i][j] = 1 + min(array[i][j - 1], array[i - 1][j], array[i - 1][j - 1])    
    
    return array[i][j]

def reverseLCS(str):
    return str[::-1]
    
def longest_common_subsequence(s1, s2):
    """
    Computes the length of the longest common subsequence between two strings, s1 and s2.
    
    Parameters:
        s1: The first string.
        s2: The second string.
    
    Returns:
        The length of the longest common subsequence between s1 and s2.
    """

    str1 = len(s1)
    str2 = len(s2)

    # Make a (str1 + 1) * (str2 + 1) array table
    array = [[0 for i in range(str2 + 1)] for i in range (str1 + 1)]

    # Initializing the table! 
    for i in range(str1):
        for j in range(str2):
            # comparing the characters to a " ", that's why 
            # the first row and column are initialized to 0.
            if j == 0:
                array[i][j] = 0
            elif i == 0:
                array[i][j] = 0

    #Finding the longest common subsequence
    for i in range(1,str1):
        for j in range(1,str2):
            # if the characters match, go to the previous
            # row and column and add one to that.
            if s1[i-1] == s2[j - 1]:
                array[i][j] = 1 + array[i - 1][j - 1]
            # if the characters don't match, take the maximum value 
            # from [i][j -1] and [i - 1][j] and compare.
            else:
                array[i][j] = max(array[i][j - 1], array[i - 1][j])
        
    return array[i][j]


s1 = file_contents_letters(sys.argv[1])
s2 = file_contents_letters(sys.argv[2])
print("Edit distance: ", edit_distance(s1, s2), "Longest common subsequence: ", longest_common_subsequence(s1, s2))