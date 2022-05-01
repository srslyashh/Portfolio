import heapq # Hint: use Python's priority queue class, heapq.

class Node:
    def __init__(self, count, children, left = None, right = None):
        self.count    = count
        self.children = children
        self.leftChild = left
        self.rightChild = right
        #self.direction = direction

    def is_leaf(self):
        return False

    def __lt__(self, other):
        return self.count < other.count

    def __eq__(self, other):
        return self.count == other.count

class LeafNode(Node):
    def __init__(self, symbol, count):
        super().__init__(count, [])
        self.symbol = symbol

    def is_leaf(self):
        return True


# this is implemented using the algorithms
# that was discussed during class by Professor Huck.
class HuffmanCode:
    def __init__(self, F):
        # TODO: Construct the Huffman Code and set C and T properly!

        self.C = dict() #self.C is defined in bfs function.
        hfCode = ""

        nodes = []
        heapq.heapify(nodes)

        for i in F:
            #print(len(F.keys()))
            # initializing nodes according to F
            # F[i] refers to the symbols while
            # i refers to the frequencies.
            holderForLeaf = LeafNode(i,F[i])
            # push it to heap for minimum priority queue.
            heapq.heappush(nodes, holderForLeaf)

        while len(nodes) > 1:
            # popping the mininum values from
            # the heap.
            leftChild = heapq.heappop(nodes)
            rightChild = heapq.heappop(nodes)

            # Assigning the right and left child to top node.
            topNode = Node(leftChild.count + rightChild.count, [leftChild, rightChild], leftChild, rightChild)
            heapq.heappush(nodes,topNode)

        self.T = heapq.heappop(nodes)

        #construct C by running BFS on T.
        self.traverse_bfs(self.T, hfCode)

    def traverse_bfs(self, node, hfCode):
        if node.is_leaf():
            # if node is leaf, which is what we want,
            # initialize that leaf to the hfCode.
            self.C[node.symbol] = hfCode
        elif node.is_leaf() != True:
            # as long as leaf is not true, traverse 
            # the tree. Append 0/1 to the hfCode
            # according to the direction.
            self.traverse_bfs(node.leftChild, hfCode + '0')
            self.traverse_bfs(node.rightChild, hfCode + '1')

        #print(self.C)
    def encode(self, m):
        """
        Uses self.C to encode a binary message.
.
        Parameters:
            m: A plaintext message.

        Returns:
            The binary encoding of the plaintext message obtained using self.C.
        """
        codestring = ""

        for char in m:
            codestring = codestring + self.C[char]
            #print(codestring)
            #print("self.C[char]: ", self.C[char])
            #print("Char: ", char)
            #print("\t")

        return codestring


    def decode(self, c):
        """
        Uses self.T to decode a binary message c = encode(m).
.
        Parameters:
            c: A message encoded in binary using self.encode.

        Returns:
            The original plaintext message m decoded using self.T.
        """

        # TODO: Implement this method!

        decodedStr = ""

        holder = self.T

        for char in c:
            # if char in the string is 0, go left.
            if char == '0':
                holder = holder.leftChild
            # if char in the string is 1, go right.
            elif char == '1':
                holder = holder.rightChild
            # when the function hits a leaf, it will
            # look at the symbol at the current leaf
            # and append it to the string above.
            if holder.is_leaf():
                #print("Here")
                decodedStr += holder.symbol
                # initialize the holder back to self T,
                # so we can start decoding again.
                holder = self.T

        return decodedStr

def get_frequencies(s):
    """
    Computes a frequency table for the input string "s".

    Parameters:
        s: A string.

    Returns:
        A frequency table F such that F[c] = (# of occurrences of c in s).
    """

    F = dict()

    for char in s:
        if char in F:
            F[char] += 1
        else:
            F[char] = 1

    return F



#CHECKING THE VALUE.

# Enter the sentence that wants to be tested here
sentence = get_frequencies("Four score and seven years ago our fathers brought forth on this continent, a new nation, conceived in Liberty, and dedicated to the proposition that all men are created equal. \n\n Now we are engaged in a great civil war, testing whether that nation, or any nation so conceived and dedicated, can long endure.We are met on a great battle-field of that war.We have come to dedicate a portion of that field, as a final resting place for those who here gave their lives that that nation might live.It is altogether fitting and proper that we should do this. \n\n But, in a larger sense, we can not dedicate -- we can not consecrate -- we can not hallow -- this ground. The brave men, living and dead, who struggled here, have consecrated it, far above our poor power to add or detract. The world will little note, nor long remember what we say here, but it can never forget what they did here. It is for us the living, rather, to be dedicated here to the unfinished work which they who fought here have thus far so nobly advanced. It is rather for us to be here dedicated to the great task remaining before us -- that from these honored dead we take increased devotion to that cause for which they gave the last full measure of devotion -- that we here highly resolve that these dead shall not have died in vain -- that this nation, under God, shall have a new birth of freedom -- and that government of the people, by the people, for the people, shall not perish from the earth.")
#print(sentence)
program = HuffmanCode(sentence)

# This sentence shoould be encoded to 10010100011110010100111111001000111101011111001100010011110111000001110001
encodeStc = "oregon state rules"
print("The sentence you entered has been encoded to: ")
print(program.encode(encodeStc))
print('\t')

# This code should be decoded to go beavers.
hfDecode = "11001010010010101110111011101010011010010001"
print("The code you entered has been decoded to: ")
print(program.decode(hfDecode))
print('\t')

