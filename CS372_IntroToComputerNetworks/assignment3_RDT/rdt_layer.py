from segment import Segment


# #################################################################################################################### #
# RDTLayer                                                                                                             #
#                                                                                                                      #
# Description:                                                                                                         #
# The reliable data transfer (RDT) layer is used as a communication layer to resolve issues over an unreliable         #
# channel.                                                                                                             #
#                                                                                                                      #
#                                                                                                                      #
# Notes:                                                                                                               #
# This file is meant to be changed.                                                                                    #
#                                                                                                                      #
#                                                                                                                      #
# #################################################################################################################### #


class RDTLayer(object):
    # ################################################################################################################ #
    # Class Scope Variables                                                                                            #
    #                                                                                                                  #
    #                                                                                                                  #
    #                                                                                                                  #
    #                                                                                                                  #
    #                                                                                                                  #
    # ################################################################################################################ #
    DATA_LENGTH = 4 # in characters                     # The length of the string data that will be sent per packet...
    FLOW_CONTROL_WIN_SIZE = 15 # in characters          # Receive window size for flow-control
    sendChannel = None
    receiveChannel = None
    dataToSend = ''
    currentIteration = 0                                # Use this for segment 'timeouts'

    # Add items as needed

    # ################################################################################################################ #
    # __init__()                                                                                                       #
    #                                                                                                                  #
    #                                                                                                                  #
    #                                                                                                                  #
    #                                                                                                                  #
    #                                                                                                                  #
    # ################################################################################################################ #
    def __init__(self):
        self.sendChannel = None
        self.receiveChannel = None
        self.dataToSend = ''
        self.currentIteration = 0

        # added variables
        self.totalLength = 0
        self.counter = 0
        self.numSegSent = 0
        self.serverData = ''
        self.seqNum = 0
        self.seqCounter = 0
        self.timeoutCounter = 0

        # holder for timeout and list of acknowledgements received
        self.timeoutHolder = {}
        self.acksCounter = 0
        self.acksHolder = {}




        # Add items as needed

    # ################################################################################################################ #
    # setSendChannel()                                                                                                 #
    #                                                                                                                  #
    # Description:                                                                                                     #
    # Called by main to set the unreliable sending lower-layer channel                                                 #
    #                                                                                                                  #
    #                                                                                                                  #
    # ################################################################################################################ #
    def setSendChannel(self, channel):
        self.sendChannel = channel

    # ################################################################################################################ #
    # setReceiveChannel()                                                                                              #
    #                                                                                                                  #
    # Description:                                                                                                     #
    # Called by main to set the unreliable receiving lower-layer channel                                               #
    #                                                                                                                  #
    #                                                                                                                  #
    # ################################################################################################################ #
    def setReceiveChannel(self, channel):
        self.receiveChannel = channel

    # ################################################################################################################ #
    # setDataToSend()                                                                                                  #
    #                                                                                                                  #
    # Description:                                                                                                     #
    # Called by main to set the string data to send                                                                    #
    #                                                                                                                  #
    #                                                                                                                  #
    # ################################################################################################################ #
    def setDataToSend(self,data):
        self.dataToSend = data

    # ################################################################################################################ #
    # getDataReceived()                                                                                                #
    #                                                                                                                  #
    # Description:                                                                                                     #
    # Called by main to get the currently received and buffered string data, in order                                  #
    #                                                                                                                  #
    #                                                                                                                  #
    # ################################################################################################################ #
    def getDataReceived(self):
        # ############################################################################################################ #
        # Identify the data that has been received...

        #print('getDataReceived(): Complete this...')

        # ############################################################################################################ #
        return self.serverData

     # ################################################################################################################ #
    # countSegmentTimeouts()                                                                                           #
    #                                                                                                                  #
    # Description:                                                                                                     #
    # Returning the value of timeout counter for the main function.                                                     #
    #                                                                                                                  #
    #                                                                                                                  #
    # ################################################################################################################ #
    def countSegmentTimeouts(self):
        return self.timeoutCounter

    # ################################################################################################################ #
    # processData()                                                                                                    #
    #                                                                                                                  #
    # Description:                                                                                                     #
    # "timeslice". Called by main once per iteration                                                                   #
    #                                                                                                                  #
    #                                                                                                                  #
    # ################################################################################################################ #
    def processData(self):
        self.currentIteration += 1
        self.processSend()
        self.processReceiveAndSendRespond()

    def indexOfSegment(self, num):
        holder = num // 4

        if num == 0:
            return 0
        elif num > 0:
            return holder

    # get index of packet
    def getIndexOfPacket(self, num):
        return (num * 4)

    # send acknowledgement
    def sendAck(self, ack):
        segmentAck = Segment()

        segmentAck.setAck(ack)
        print("Sending ack: ", segmentAck.to_string())

        self.sendChannel.send(segmentAck)

    # send data
    def sendData(self, seq, dataToSend):
        segmentSend = Segment()

        segmentSend.setData(seq, dataToSend)
        print("Sending segment: ", segmentSend.to_string())
        self.sendChannel.send(segmentSend)


    # ################################################################################################################ #
    # processSend()                                                                                                    #
    #                                                                                                                  #
    # Description:                                                                                                     #
    # Manages Segment sending tasks                                                                                    #
    #                                                                                                                  #
    #                                                                                                                  #
    # ################################################################################################################ #
    def processSend(self):
        # ############################################################################################################ #
        #print('processSend(): Complete this...')

        # You should pipeline segments to fit the flow-control window
        # The flow-control window is the constant RDTLayer.FLOW_CONTROL_WIN_SIZE
        # The maximum data that you can send in a segment is RDTLayer.DATA_LENGTH
        # These constants are given in # characters

        # Somewhere in here you will be creating data segments to send.
        # The data is just part of the entire string that you are trying to send.
        # The seqnum is the sequence number for the segment (in character number, not bytes)

        # if, this must be the client side.
        if self.dataToSend != '':
            # Only send data to the server once the number of acknowledgments == seq Counter.
           #print("seqCounter: " + str(self.seqCounter) + "self.acksCounter " + str(self.acksCounter))
           if self.seqCounter == self.acksCounter:
            # As the window size is 15, and the length of data is 4,
            # we send 3 segments at a time.
            for counter in range(3):
                segmentSend = Segment()

                # index to stop for the dataToSend variable
                indexToStop = self.seqCounter + self.DATA_LENGTH

                # splicing the data into 4-length segments
                #------------------------------------------------------------------------------------------
                # Citation:
                # URL : https://www.pythonforbeginners.com/python-strings/string-splicing-in-python
                # This website was used to help splicing the data into 4-length data to send
                # to the server.
                #------------------------------------------------------------------------------------------
                dataToSend = self.dataToSend[self.seqCounter:indexToStop]

                # ############################################################################################################ #
                # Display sending segment
                holder = self.seqCounter

                #index of the packet to be put in the timeout array
                index = self.indexOfSegment(self.seqCounter)
                self.timeoutHolder[index] = 0

                # add the sequence counter tracker with the data length which is 4.
                self.seqCounter += self.DATA_LENGTH
                self.numSegSent += 1

                self.sendData(holder, dataToSend)

        # if server side, the dataToSend remains empty
        if self.dataToSend == '':
            # do nothing
            return

    # ################################################################################################################ #
    # processReceive()                                                                                                 #
    #                                                                                                                  #
    # Description:                                                                                                     #
    # Manages Segment receive tasks                                                                                    #
    #                                                                                                                  #
    #                                                                                                                  #
    # ################################################################################################################ #
    def processReceiveAndSendRespond(self):

        # This call returns a list of incoming segments (see Segment class)...
        listIncomingSegments = self.receiveChannel.receive()
        #

        # Q:  How will you get them back in order?
        #-------------------------------------------------------------------------------------------
        # Citation:
        # Sorting the list of segments by their sequence number since they might be out-of-order.
        # URL: https://www.kite.com/python/answers/how-to-sort-a-list-with-a-lambda-expression-in-python
        #-------------------------------------------------------------------------------------------
        sortedIncomingSegments = sorted(listIncomingSegments, key=lambda seg: seg.seqnum)
        sortByAcks = sorted(listIncomingSegments, key=lambda ack: ack.acknum)

        # ############################################################################################################ #
        # What segments have been received?
        #print('processReceive(): Complete this...')

        # working on the server-side
        if self.dataToSend == '':
            if(sortedIncomingSegments):
                for seg in sortedIncomingSegments:
                    # Segment acknowledging packet(s) received
                    segmentAck = Segment()
                    #print("seqNum: ", seg.seqnum)
                    #print("Last seqCounter " + str(self.seqCounter))

                    #Check the checksum:
                    if(seg.checkChecksum() == False):
                        continue
                    elif(seg.seqnum == self.acksCounter):
                        # if seqnum is equal to the last seq sent, then add the data length to seqCounter
                        # which will be used as the ACK number.
                        self.acksCounter += self.DATA_LENGTH
                        #segmentAck.setAck(self.acksCounter)
                        #print("Sending ack: ", segmentAck.to_string())

                        # append the payload to the server data section.
                        self.serverData += seg.payload
                        print("Received data: " ,seg.payload)
                        #print("Server data: ", self.serverData)
                        self.sendAck(self.acksCounter)

                    else:
                        self.sendAck(self.acksCounter)
            else:
                self.sendAck(self.acksCounter)


        # Working on the client-side
        elif self.dataToSend != '':
            # Have to implement time-outs and sending the packets back to the servers
            index = 0
            timeoutFlag = 0
            for seg in sortByAcks:
                #print("here\n")
                #print("Acknum: " + str(seg.acknum) + " counter: " + str(self.acksCounter))

                # CHECK IF the ack received is seqCounter + data length.
                if(seg.acknum ==  self.DATA_LENGTH + self.acksCounter):
                    # stop keeping track of the data in the timeout array by setting it to -1.
                    self.timeoutHolder[self.indexOfSegment(seg.acknum - 4)] = -1
                    # increment by 4 to move to the next package
                    self.acksCounter += self.DATA_LENGTH
                else:
                    timeoutFlag = 1
                    index = seg.acknum

            # Timeout function
            #Check if we need to send the data again to the server
            for i in self.timeoutHolder:
                #print("value: " + str(self.timeoutHolder[i]) + "i: " + str(i))
                if(self.timeoutHolder[i] != -1):
                    if(self.timeoutHolder[i] > 3):
                        segmentSend = Segment()
                        self.timeoutCounter += 1
                        index = self.getIndexOfPacket(i)
                        timeoutFlag = 1
                        break
                    self.timeoutHolder[i] = self.timeoutHolder[i] + 1

            # if timeout, send the package again.
            if (timeoutFlag == 1):
                 segmentC = 0
                 counter = 0
                 while(segmentC == 0):
                     #print("Here")
                     if(counter == 3):
                         break

                     indexToStop = index + self.DATA_LENGTH
                     dataToSend = self.dataToSend[index:indexToStop]

                     self.sendData(index, dataToSend)

                     # move index
                     index += self.DATA_LENGTH
                     counter += 1
