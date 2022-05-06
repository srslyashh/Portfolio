# #################################################################################################################### #
# Imports                                                                                                              #
#                                                                                                                      #
#                                                                                                                      #
#                                                                                                                      #
#                                                                                                                      #
# #################################################################################################################### #
import os
from socket import *
import struct
import time
import select


# #################################################################################################################### #
# Class IcmpHelperLibrary                                                                                              #
#                                                                                                                      #
#                                                                                                                      #
#                                                                                                                      #
#                                                                                                                      #
#                                                                                                                      #
#                                                                                                                      #
#                                                                                                                      #
#                                                                                                                      #
#                                                                                                                      #
#                                                                                                                      #
#                                                                                                                      #
#                                                                                                                      #
#                                                                                                                      #
#                                                                                                                      #
# #################################################################################################################### #
class IcmpHelperLibrary:
    # ################################################################################################################ #
    # Class IcmpPacket                                                                                                 #
    #                                                                                                                  #
    # References:                                                                                                      #
    # https://www.iana.org/assignments/icmp-parameters/icmp-parameters.xhtml                                           #
    #                                                                                                                  #
    #                                                                                                                  #
    #                                                                                                                  #
    #                                                                                                                  #
    #                                                                                                                  #
    #                                                                                                                  #
    #                                                                                                                  #
    #                                                                                                                  #
    #                                                                                                                  #
    #                                                                                                                  #
    # ################################################################################################################ #
    class IcmpPacket:
        # ############################################################################################################ #
        # IcmpPacket Class Scope Variables                                                                             #
        #                                                                                                              #
        #                                                                                                              #
        #                                                                                                              #
        #                                                                                                              #
        # ############################################################################################################ #
        __icmpTarget = ""               # Remote Host
        __destinationIpAddress = ""     # Remote Host IP Address
        __header = b''                  # Header after byte packing
        __data = b''                    # Data after encoding
        __dataRaw = ""                  # Raw string data before encoding
        __icmpType = 0                  # Valid values are 0-255 (unsigned int, 8 bits)
        __icmpCode = 0                  # Valid values are 0-255 (unsigned int, 8 bits)
        __packetChecksum = 0            # Valid values are 0-65535 (unsigned short, 16 bits)
        __packetIdentifier = 0          # Valid values are 0-65535 (unsigned short, 16 bits)
        __packetSequenceNumber = 0      # Valid values are 0-65535 (unsigned short, 16 bits)
        __ipTimeout = 30
        __ttl = 225                     # Time to live
        summary = ""
        minTime = 100
        maxTime = 0
        total = 0
        packetSent = 0
        packetReceived = 0


        __DEBUG_IcmpPacket = False      # Allows for debug output

        # ############################################################################################################ #
        # IcmpPacket Class Getters                                                                                     #
        #                                                                                                              #
        #                                                                                                              #
        #                                                                                                              #
        #                                                                                                              #
        # ############################################################################################################ #
        def getIcmpTarget(self):
            return self.__icmpTarget

        def getDataRaw(self):
            return self.__dataRaw

        def getIcmpType(self):
            return self.__icmpType

        def getIcmpCode(self):
            return self.__icmpCode

        def getPacketChecksum(self):
            return self.__packetChecksum

        def getPacketIdentifier(self):
            return self.__packetIdentifier

        def getPacketSequenceNumber(self):
            return self.__packetSequenceNumber

        def getTtl(self):
            return self.__ttl

        def getSummary(self):
            return self.summary

        def getMin(self):
            return self.minTime

        def getMax(self):
            return self.maxTime

        def getTotal(self):
            return self.total

        def getPacketSent(self):
            return self.packetSent

        def getPacketReceived(self):
            return self.packetReceived


        # ############################################################################################################ #
        # IcmpPacket Class Setters                                                                                     #
        #                                                                                                              #
        #                                                                                                              #
        #                                                                                                              #
        #                                                                                                              #
        # ############################################################################################################ #
        def setSummary(self, newS):
            self.summary = newS

        def setMin(self, newM):
            self.minTime = newM

        def setMax(self, newM):
            self.maxTime = newM

        def setIcmpTarget(self, icmpTarget):
            self.__icmpTarget = icmpTarget

            # Only attempt to get destination address if it is not whitespace
            if len(self.__icmpTarget.strip()) > 0:
                self.__destinationIpAddress = gethostbyname(self.__icmpTarget.strip())

        def setIcmpType(self, icmpType):
            self.__icmpType = icmpType

        def setIcmpCode(self, icmpCode):
            self.__icmpCode = icmpCode

        def setTotal(self, newt):
            self.total = newt

        def setPacketChecksum(self, packetChecksum):
            self.__packetChecksum = packetChecksum

        def setPacketIdentifier(self, packetIdentifier):
            self.__packetIdentifier = packetIdentifier

        def setPacketSequenceNumber(self, sequenceNumber):
            self.__packetSequenceNumber = sequenceNumber

        def setTtl(self, ttl):
            self.__ttl = ttl

        def setPacketSent(self, ps):
            self.packetSent = ps

        def setPacketReceived(self,pr):
            self.packetReceived = pr

        # ############################################################################################################ #
        # IcmpPacket Class Private Functions                                                                           #
        #                                                                                                              #
        #                                                                                                              #
        #                                                                                                              #
        #                                                                                                              #
        # ############################################################################################################ #
        def __recalculateChecksum(self):
            print("calculateChecksum Started...") if self.__DEBUG_IcmpPacket else 0
            packetAsByteData = b''.join([self.__header, self.__data])
            checksum = 0

            # This checksum function will work with pairs of values with two separate 16 bit segments. Any remaining
            # 16 bit segment will be handled on the upper end of the 32 bit segment.
            countTo = (len(packetAsByteData) // 2) * 2

            # Calculate checksum for all paired segments
            print(f'{"Count":10} {"Value":10} {"Sum":10}') if self.__DEBUG_IcmpPacket else 0
            count = 0
            while count < countTo:
                thisVal = packetAsByteData[count + 1] * 256 + packetAsByteData[count]
                checksum = checksum + thisVal
                checksum = checksum & 0xffffffff        # Capture 16 bit checksum as 32 bit value
                print(f'{count:10} {hex(thisVal):10} {hex(checksum):10}') if self.__DEBUG_IcmpPacket else 0
                count = count + 2

            # Calculate checksum for remaining segment (if there are any)
            if countTo < len(packetAsByteData):
                thisVal = packetAsByteData[len(packetAsByteData) - 1]
                checksum = checksum + thisVal
                checksum = checksum & 0xffffffff        # Capture as 32 bit value
                print(count, "\t", hex(thisVal), "\t", hex(checksum)) if self.__DEBUG_IcmpPacket else 0

            # Add 1's Complement Rotation to original checksum
            checksum = (checksum >> 16) + (checksum & 0xffff)   # Rotate and add to base 16 bits
            checksum = (checksum >> 16) + checksum              # Rotate and add

            answer = ~checksum                  # Invert bits
            answer = answer & 0xffff            # Trim to 16 bit value
            answer = answer >> 8 | (answer << 8 & 0xff00)
            print("Checksum: ", hex(answer)) if self.__DEBUG_IcmpPacket else 0

            self.setPacketChecksum(answer)

        def __packHeader(self):
            # The following header is based on http://www.networksorcery.com/enp/protocol/icmp/msg8.htm
            # Type = 8 bits
            # Code = 8 bits
            # ICMP Header Checksum = 16 bits
            # Identifier = 16 bits
            # Sequence Number = 16 bits
            self.__header = struct.pack("!BBHHH",
                                   self.getIcmpType(),              #  8 bits / 1 byte  / Format code B
                                   self.getIcmpCode(),              #  8 bits / 1 byte  / Format code B
                                   self.getPacketChecksum(),        # 16 bits / 2 bytes / Format code H
                                   self.getPacketIdentifier(),      # 16 bits / 2 bytes / Format code H
                                   self.getPacketSequenceNumber()   # 16 bits / 2 bytes / Format code H
                                   )

        def __encodeData(self):
            data_time = struct.pack("d", time.time())               # Used to track overall round trip time
                                                                    # time.time() creates a 64 bit value of 8 bytes
            dataRawEncoded = self.getDataRaw().encode("utf-8")

            self.__data = data_time + dataRawEncoded

        def __packAndRecalculateChecksum(self):
            # Checksum is calculated with the following sequence to confirm data in up to date
            self.__packHeader()                 # packHeader() and encodeData() transfer data to their respective bit
                                                # locations, otherwise, the bit sequences are empty or incorrect.
            self.__encodeData()
            self.__recalculateChecksum()        # Result will set new checksum value
            self.__packHeader()                 # Header is rebuilt to include new checksum value

        def __validateIcmpReplyPacketWithOriginalPingData(self, icmpReplyPacket):
            # Hint: Work through comparing each value and identify if this is a valid response.
            #print("Sent packetIdentifier", self.getPacketIdentifier())
            #print("Received packetIdentifier", icmpReplyPacket.getIcmpIdentifier())

			# Checking if the identifier are the same & if not then set valid response to false.
            if self.getPacketIdentifier() == icmpReplyPacket.getIcmpIdentifier():
                icmpReplyPacket.setIcmpIdentifier_isValid(True)

                # Debug message for identifier
                print("ERROR: MISMATCH-- Expected Packet Identifier: ", self.getPacketIdentifier(), ", Received Icmp Identifier: "
                      , icmpReplyPacket.getIcmpIdentifier()) if self.__DEBUG_IcmpPacket else 0

            if self.getPacketSequenceNumber() == icmpReplyPacket.getIcmpSequenceNumber():
                icmpReplyPacket.setIcmpSequence_isValid(True)

                # Debug message for sequence number
                print("ERROR: MISMATCH-- Expected Packet Sequence Number: ", self.getPacketSequenceNumber(), ", Received Icmp Sequence Number: "
                          , icmpReplyPacket.getIcmpSequenceNumber()) if self.__DEBUG_IcmpPacket else 0

            if(self.getDataRaw() == icmpReplyPacket.getIcmpData()):
                icmpReplyPacket.setIcmpData_isValid(True)

                # Debug message for data
                print("ERROR: MISMATCH-- Expected Packet Data: ", self.getDataRaw(), ", Received Icmp Data: "
                      , icmpReplyPacket.getIcmpData()) if self.__DEBUG_IcmpPacket else 0

            # If all three, identifier, sequence and data are true, set validResponse to true.
                if icmpReplyPacket.getIcmpIdentifier_isValid() and icmpReplyPacket.getIcmpSequence_isValid() and icmpReplyPacket.getIcmpData_isValid():
                    icmpReplyPacket.setIsValidResponse(True)

            pass

        # ############################################################################################################ #
        # IcmpPacket Class Public Functions                                                                            #
        #                                                                                                              #
        #                                                                                                              #
        #                                                                                                              #
        #                                                                                                              #
        # ############################################################################################################ #
        def buildPacket_echoRequest(self, packetIdentifier, packetSequenceNumber):
            self.setIcmpType(8)
            self.setIcmpCode(0)
            self.setPacketIdentifier(packetIdentifier)
            self.setPacketSequenceNumber(packetSequenceNumber)
            self.__dataRaw = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
            self.__packAndRecalculateChecksum()

        def sendEchoRequest(self, count, summary, trOrP):
            if len(self.__icmpTarget.strip()) <= 0 | len(self.__destinationIpAddress.strip()) <= 0:
                self.setIcmpTarget("127.0.0.1")

            if count ==0:
                print("Pinging (" + self.__icmpTarget + ") " + self.__destinationIpAddress + " with " + str(len(self.__data)) + " bytes of data.")
                print("\n")

            mySocket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)
            mySocket.settimeout(self.__ipTimeout)
            mySocket.bind(("", 0))
            mySocket.setsockopt(IPPROTO_IP, IP_TTL, struct.pack('I', self.getTtl()))  # Unsigned int - 4 bytes
            try:
                mySocket.sendto(b''.join([self.__header, self.__data]), (self.__destinationIpAddress, 0))

                # Comment:
                # keep track of num packet being sent
                ps = self.getPacketSent()
                ps += 1
                self.setPacketSent(ps)

                timeLeft = 30
                pingStartTime = time.time()
                startedSelect = time.time()
                whatReady = select.select([mySocket], [], [], timeLeft)
                endSelect = time.time()
                howLongInSelect = (endSelect - startedSelect)
                if whatReady[0] == []:  # Timeout
                    print("  *        *        *        *        *    Request timed out.")
                recvPacket, addr = mySocket.recvfrom(1024)  # recvPacket - bytes object representing data received
                # addr  - address of socket sending data
                timeReceived = time.time()
                timeLeft = timeLeft - howLongInSelect
                if timeLeft <= 0:
                    print("  *        *        *        *        *    Request timed out (By no remaining time left).")

                else:
                    # Fetch the ICMP type and code from the received packet
                    icmpType, icmpCode = recvPacket[20:22]
                    # Comment:
                    # keep track of num packet being sent
                    packetR = self.getPacketReceived()
                    packetR += 1
                    self.setPacketReceived(packetR)

                    if icmpType == 11:                          # Time Exceeded
                        self.setIcmpType(icmpType)
                        print("  TTL=%d    RTT=%.0f ms    Type=%d    Code=%d    %s" %
                                (
                                    self.getTtl(),
                                    (timeReceived - pingStartTime) * 1000,
                                    icmpType,
                                    icmpCode,
                                    addr[0]
                                )
                              )

                    elif icmpType == 3:                         # Destination Unreachable
                        self.setIcmpType(icmpType)
                        print("  TTL=%d    RTT=%.0f ms    Type=%d    Code=%d    %s" %
                                  (
                                      self.getTtl(),
                                      (timeReceived - pingStartTime) * 1000,
                                      icmpType,
                                      icmpCode,
                                      addr[0]
                                  )
                              )

                    elif icmpType == 0:                         # Echo Reply
                        self.setIcmpType(icmpType)
                        icmpReplyPacket = IcmpHelperLibrary.IcmpPacket_EchoReply(recvPacket)
                        self.__validateIcmpReplyPacketWithOriginalPingData(icmpReplyPacket)
                        icmpReplyPacket.printResultToConsole(self.getTtl(), timeReceived, addr, IcmpHelperLibrary.IcmpPacket())

                        if trOrP == 0:
                            packetSize = len(self.__header) + len(self.__data)
                            min = self.getMin()
                            max = self.getMax()
                            t = self.getTotal()
                            s,min,max, t = icmpReplyPacket.printSummaryToConsole(self.getTtl(), timeReceived,pingStartTime, packetSize, addr, self.getSummary(), count, min, max, t)
                            self.setSummary(s)
                            # setting min time
                            self.setMin(min)
                            # setting max time
                            self.setMax(max)
                            # setting total time that later on will be used for counting average
                            self.setTotal(t)

                        return      # Echo reply is the end and therefore should return

                    else:
                        print("error")
            except timeout:
                print("  *        *        *        *        *    Request timed out (By Exception).")
            finally:
                mySocket.close()


        def printIcmpPacketHeader_hex(self):
            print("Header Size: ", len(self.__header))
            for i in range(len(self.__header)):
                print("i=", i, " --> ", self.__header[i:i+1].hex())

        def printIcmpPacketData_hex(self):
            print("Data Size: ", len(self.__data))
            for i in range(len(self.__data)):
                print("i=", i, " --> ", self.__data[i:i + 1].hex())

        def printIcmpPacket_hex(self):
            print("Printing packet in hex...")
            self.printIcmpPacketHeader_hex()
            self.printIcmpPacketData_hex()

    # ################################################################################################################ #
    # Class IcmpPacket_EchoReply                                                                                       #
    #                                                                                                                  #
    # References:                                                                                                      #
    # http://www.networksorcery.com/enp/protocol/icmp/msg0.htm                                                         #
    #                                                                                                                  #
    #                                                                                                                  #
    #                                                                                                                  #
    #                                                                                                                  #
    #                                                                                                                  #
    #                                                                                                                  #
    #                                                                                                                  #
    #                                                                                                                  #
    #                                                                                                                  #
    #                                                                                                                  #
    # ################################################################################################################ #
    class IcmpPacket_EchoReply:
        # ############################################################################################################ #
        # IcmpPacket_EchoReply Class Scope Variables                                                                   #
        #                                                                                                              #
        #                                                                                                              #
        #                                                                                                              #
        #                                                                                                              #
        # ############################################################################################################ #
        __recvPacket = b''
        __isValidResponse = False

        # New variables as instructed
        IcmpSequence_isValid = False
        IcmpIdentifier_isValid = False
        IcmpData_isValid = False

        summary = ""

        # ############################################################################################################ #
        # IcmpPacket_EchoReply Constructors                                                                            #
        #                                                                                                              #
        #                                                                                                              #
        #                                                                                                              #
        #                                                                                                              #
        # ############################################################################################################ #
        def __init__(self, recvPacket):
            self.__recvPacket = recvPacket

        # ############################################################################################################ #
        # IcmpPacket_EchoReply Getters                                                                                 #
        #                                                                                                              #
        #                                                                                                              #
        #                                                                                                              #
        #                                                                                                              #
        # ############################################################################################################ #
        def getIcmpType(self):
            # Method 1
            # bytes = struct.calcsize("B")        # Format code B is 1 byte
            # return struct.unpack("!B", self.__recvPacket[20:20 + bytes])[0]

            # Method 2
            return self.__unpackByFormatAndPosition("B", 20)

        def getIcmpCode(self):
            # Method 1
            # bytes = struct.calcsize("B")        # Format code B is 1 byte
            # return struct.unpack("!B", self.__recvPacket[21:21 + bytes])[0]

            # Method 2
            return self.__unpackByFormatAndPosition("B", 21)

        def getIcmpHeaderChecksum(self):
            # Method 1
            # bytes = struct.calcsize("H")        # Format code H is 2 bytes
            # return struct.unpack("!H", self.__recvPacket[22:22 + bytes])[0]

            # Method 2
            return self.__unpackByFormatAndPosition("H", 22)

        def getIcmpIdentifier(self):
            # Method 1
            # bytes = struct.calcsize("H")        # Format code H is 2 bytes
            # return struct.unpack("!H", self.__recvPacket[24:24 + bytes])[0]

            # Method 2
            return self.__unpackByFormatAndPosition("H", 24)

        def getIcmpSequenceNumber(self):
            # Method 1
            # bytes = struct.calcsize("H")        # Format code H is 2 bytes
            # return struct.unpack("!H", self.__recvPacket[26:26 + bytes])[0]

            # Method 2
            return self.__unpackByFormatAndPosition("H", 26)

        def getDateTimeSent(self):
            # This accounts for bytes 28 through 35 = 64 bits
            return self.__unpackByFormatAndPosition("d", 28)   # Used to track overall round trip time
                                                               # time.time() creates a 64 bit value of 8 bytes

        def getIcmpData(self):
            # This accounts for bytes 36 to the end of the packet.
            return self.__recvPacket[36:].decode('utf-8')

        def isValidResponse(self):
            return self.__isValidResponse

        # Getters to confirm whether the values of the data are valid

        def getIcmpSequence_isValid(self):
            return self.IcmpSequence_isValid

        def getIcmpIdentifier_isValid(self):
            return self.IcmpIdentifier_isValid

        def getIcmpData_isValid(self):
            return self.IcmpData_isValid


        # ############################################################################################################ #
        # IcmpPacket_EchoReply Setters                                                                                 #
        #                                                                                                              #
        #                                                                                                              #
        #                                                                                                              #
        #                                                                                                              #
        # ############################################################################################################ #
        def setIsValidResponse(self, booleanValue):
            self.__isValidResponse = booleanValue

        # New setters for Icmp sequence, identifier and data

        def setIcmpSequence_isValid(self, booleanValue):
            self.IcmpSequence_isValid = booleanValue

        def setIcmpIdentifier_isValid(self, booleanValue):
            self.IcmpIdentifier_isValid = booleanValue

        def setIcmpData_isValid(self, booleanValue):
            self.IcmpData_isValid = booleanValue

        # ############################################################################################################ #
        # IcmpPacket_EchoReply Private Functions                                                                       #
        #                                                                                                              #
        #                                                                                                              #
        #                                                                                                              #
        #                                                                                                              #
        # ############################################################################################################ #
        def __unpackByFormatAndPosition(self, formatCode, basePosition):
            numberOfbytes = struct.calcsize(formatCode)
            return struct.unpack("!" + formatCode, self.__recvPacket[basePosition:basePosition + numberOfbytes])[0]

        # ############################################################################################################ #
        # IcmpPacket_EchoReply Public Functions                                                                        #
        #                                                                                                              #
        #                                                                                                              #
        #                                                                                                              #
        #                                                                                                              #
        # ############################################################################################################ #
        def printResultToConsole(self, ttl, timeReceived, addr, IcmpPacket):
            bytes = struct.calcsize("d")
            timeSent = struct.unpack("d", self.__recvPacket[28:28 + bytes])[0]

            # See if the echo response is valid
            if self.isValidResponse() == False:
                print("Response frome echo is not valid. Here are the error information details: ")

                # If not valid, check if sequence is not valid
                if self.getIcmpSequence_isValid() == False:
                    print("ERROR: MISMATCH-- Expected sequence: ", IcmpPacket.getPacketSequenceNumber(), " , Actual value: ", self.getIcmpSequenceNumber())

                # If not valid, check if data is not valid
                if self.getIcmpData_isValid() == False:
                    print("ERROR: MISMATCH-- Expected data: ", IcmpPacket.getDataRaw(), " , Actual data: ", self.getIcmpData())

                # If not valid, check if identifier is not valid
                if self.getIcmpIdentifier_isValid() == False:
                    print("ERROR: MISMATCH-- Expected data: ", IcmpPacket.getPacketIdentifier(), " , Actual data: ", self.getIcmpIdentifier())

            print("  TTL=%d    RTT=%.0f ms    Type=%d    Code=%d        Identifier=%d    Sequence Number=%d    %s" %
                  (
                      ttl,
                      (timeReceived - timeSent) * 1000,
                      self.getIcmpType(),
                      self.getIcmpCode(),
                      self.getIcmpIdentifier(),
                      self.getIcmpSequenceNumber(),
                      addr[0]
                  )
                 )

        # In the printSummaryToConsole() function,
        # we do not print anything to screen but store the string of information (Summary)
        # so that it could be printed later once the program stops running.
        def printSummaryToConsole(self, ttl, timeReceived, pingStartTime, packetSize, addr, s, count, min, max, total):
            bytes = struct.calcsize("d")
            timeSent = struct.unpack("d", self.__recvPacket[28:28 + bytes])[0]

            t = ((timeReceived-pingStartTime) *1000)

            # Appending the information together into one sentence.
            info = ""
            info += str(packetSize)
            info += " bytes from "
            info += addr[0]
            info += ":       icmp_seq ="
            info += str(self.getIcmpSequenceNumber())
            info += "        ttl = "
            info += str(ttl)
            info += "        time = "
            info += "%.3f" % ((timeReceived-pingStartTime) *1000)
            info += " ms"

            # s = summary which will be stored by .setSummary() later on.
            s += info

            if count == 0:
                min = t
                max = t
            if count > 0:
                if t < min:
                    min = t
                if t > max:
                    max = t

            # total holds the total value of the time.
            total += t

            return s, min, max, total


    # ################################################################################################################ #
    # Class IcmpHelperLibrary                                                                                          #
    #                                                                                                                  #
    #                                                                                                                  #
    #                                                                                                                  #
    #                                                                                                                  #
    # ################################################################################################################ #

    # ################################################################################################################ #
    # IcmpHelperLibrary Class Scope Variables                                                                          #
    #                                                                                                                  #
    #                                                                                                                  #
    #                                                                                                                  #
    #                                                                                                                  #
    # ################################################################################################################ #
    __DEBUG_IcmpHelperLibrary = False                  # Allows for debug output
    packetSent = 0
    packetReceived = 0


    # ################################################################################################################ #
    # IcmpHelperLibrary Private Functions                                                                              #
    #                                                                                                                  #
    #                                                                                                                  #
    #                                                                                                                  #
    #                                                                                                                  #
    # ################################################################################################################ #
    def __sendIcmpEchoRequest(self, host):
        min = 1200
        max = 0
        total = 0
        packetRecv = 0
        packetSent = 0
        summary = "\n-----Ping summary----------\n"

        print("sendIcmpEchoRequest Started...") if self.__DEBUG_IcmpHelperLibrary else 0

        for i in range(4):
            # Build packet
            icmpPacket = IcmpHelperLibrary.IcmpPacket()

            randomIdentifier = (os.getpid() & 0xffff)      # Get as 16 bit number - Limit based on ICMP header standards
                                                           # Some PIDs are larger than 16 bit

            packetIdentifier = randomIdentifier
            packetSequenceNumber = i

            icmpPacket.buildPacket_echoRequest(packetIdentifier, packetSequenceNumber)  # Build ICMP for IP payload
            icmpPacket.setIcmpTarget(host)
            icmpPacket.sendEchoRequest(i, summary, 0)

            if i >= 0:
                summary += "\n"
                # Summary will contain ping summary
                summary += icmpPacket.getSummary()
                # get the minimum rtt time.
                if icmpPacket.getMin() < min :
                    min = icmpPacket.getMin()
                # get the maximum rtt time.
                if icmpPacket.getMax() > max:
                    max = icmpPacket.getMax()
                # total of rtt times that will be used for average later on.
                total += icmpPacket.getTotal()
                # total of packets received and sent
                packetRecv += icmpPacket.getPacketReceived()
                packetSent += icmpPacket.getPacketSent()

            # Code citation:
            # The error handler was inspired by a post on Ed discussion #142 made by
            # Richard Frank. It helped me set up my error code handler.
            # Link: ttps://edstem.org/us/courses/16852/discussion/1082247
            icmpErrorType3= {
                0: "Net Unreachable",
                1: "Host Unreachable",
                2: "Protocol Unreachable",
                3: "Port Unreachable",
                4: "Fragmentation Needed and Don't Fragment was Set",
                5: "Source Route Failed",
                6: "Destination Network Unknown",
                7: "Destination Host Unknown",
                8: "Source Host Isolated",
                9: "Communication with Destination Network is Administratively Prohibited",
                10: "Communication with Destination Host is Administratively Prohibited",
                11: "Destination Network Unreachable for Type of Service",
                12: "Destination Host Unreachable for Type of Service",
                13: "Communication Administratively Prohibited",
                14: "Host Precedence Violation",
                15: "Precedence cutoff in effect"
            }

            icmpErrorType11= {
                0: "Time to live exceeded in Transit",
                1: "Fragment Reassembly Time Exceeded"
            }
                                                          # Build IP
            icmpPacket.printIcmpPacketHeader_hex() if self.__DEBUG_IcmpHelperLibrary else 0
            icmpPacket.printIcmpPacket_hex() if self.__DEBUG_IcmpHelperLibrary else 0
            # we should be confirming values are correct, such as identifier and sequence number and data

            # ICMP response error codes
            if icmpPacket.getIcmpType() != 0:
                if icmpPacket.getIcmpType() == 3:
                    if icmpPacket.getIcmpCode() in icmpErrorType3:
                        print("ERROR -- ICMP type 3 , ICMP Code " + icmpPacket.getIcmpCode() + " :" + icmpErrorType3[icmpPacket.getIcmpCode()])
                elif icmpPacket.getIcmpType() == 11:
                     if icmpPacket.getIcmpCode() in icmpErrorType11:
                         print("ERROR -- ICMP type 11 , ICMP Code " + icmpPacket.getIcmpCode() + " :" + icmpErrorType3[icmpPacket.getIcmpCode()])
        # Code citation:
        # The ping statistics and summary were inspired from the comment by professor Samina
        # on ed dicussion on post #133. Her note on how the expected output for the ping procedure
        #  helped me structure the ping function response.
        # Link: https://edstem.org/us/courses/16852/discussion/1076770
        packetL = (1 - (packetRecv / packetSent)) * 100
        print(summary)
        print("\n")
        print("------------ " + host +" ping statistics --------------")
        print(str(packetSent) + " packets transmitted, " + str(packetRecv) + " received, " + str(packetL) + "% packet loss")
        print("rtt min/avg/max = %.3f /%.3f /%.3f ms\n" % (min, (total/packetRecv), max))


# Citation:
# The post #100 made by Anonymous on Ed discussion, talking about page 448-449
# from the Computer Networking - Kurose and Ross helped my understanding on the
# traceroute program.
# Link: https://edstem.org/us/courses/16852/discussion/1050583
    def __sendIcmpTraceRoute(self, host):
        print("Traceroute to " + host)
        print("sendIcmpTraceRoute Started...") if self.__DEBUG_IcmpHelperLibrary else 0
        # Build code for trace route here

        notType0 = True
        counter = 1
        summary = ""

        # Code citation:
        # This code was inspired from the Ed discussion by Christopher Smith
        # on post number 99.
        # Link: https://edstem.org/us/courses/16852/discussion/1050454
        while notType0 == True:
             # Build packet
            trPacket = IcmpHelperLibrary.IcmpPacket()

            randomIdentifier = (os.getpid() & 0xffff)
            packetIdentifier = randomIdentifier
            packetSequenceNumber = counter
            trPacket.setTtl(counter)

            trPacket.buildPacket_echoRequest(packetIdentifier, packetSequenceNumber)  # Build ICMP for IP payload
            trPacket.setIcmpTarget(host)
            # send echo request on the packet
            trPacket.sendEchoRequest(counter, summary, 1)

            # As long as we don't get the type 0 reply message,
            # keep on looping.
            if trPacket.getIcmpType() == 0 :
                notType0 = False

            # increment ttl!
            counter = counter + 1



    # ################################################################################################################ #
    # IcmpHelperLibrary Public Functions                                                                               #
    #                                                                                                                  #
    #                                                                                                                  #
    #                                                                                                                  #
    #                                                                                                                  #
    # ################################################################################################################ #
    def sendPing(self, targetHost):
        print("ping Started...") if self.__DEBUG_IcmpHelperLibrary else 0
        self.__sendIcmpEchoRequest(targetHost)

    def traceRoute(self, targetHost):
        print("traceRoute Started...") if self.__DEBUG_IcmpHelperLibrary else 0
        self.__sendIcmpTraceRoute(targetHost)


# #################################################################################################################### #
# main()                                                                                                               #
#                                                                                                                      #
#                                                                                                                      #
#                                                                                                                      #
#                                                                                                                      #
# #################################################################################################################### #
def main():
    icmpHelperPing = IcmpHelperLibrary()


    # Choose one of the following by uncommenting out the line
    #icmpHelperPing.sendPing("209.233.126.254")
    #icmpHelperPing.sendPing("www.google.com")
    #icmpHelperPing.sendPing("oregonstate.edu")
    #icmpHelperPing.sendPing("gaia.cs.umass.edu")
    #icmpHelperPing.traceRoute("oregonstate.edu")


    # The IP addresses down below are retrieved from
    # .dotcom-monitor.com/blog/technical-tools/network-location-ip-addresses/
    # per professor Samina's suggestion on Ed discussion post #101
    # Link: https://edstem.org/us/courses/16852/discussion/1051775

    # Traceroute to an IP address in Frankfurt, Germany
    #icmpHelperPing.traceRoute("195.201.213.247")

    # Traceroute to an IP address in Tokyo, Japan
    #icmpHelperPing.traceRoute("110.50.243.6")

    # Traceroute to an IP address in Sydney, Australia
    #icmpHelperPing.traceRoute("101.0.86.43")

    # Traceroute to an IP address in Tel Aviv, Israel
    icmpHelperPing.traceRoute("185.229.226.83")

if __name__ == "__main__":
    main()
