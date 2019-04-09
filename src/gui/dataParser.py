import time

#Code to parse data from socket
#Format:

#-----------------
#<key>: <value>
#<key2>: <value2>
#<key3>: <value3>, time: <int>
#-----------------

def inferDataType(string):
    """Converts data type to best matching and returns"""
    if string.isalpha():
        return string
    elif '.' in string:
        return float(string)
    else:
        return int(string)

def parseToDict(data):
    """Convert data from socket into a dictionary object for easier manipulation"""
    dataDict = {}

    #Split into lines
    data = data.split("\n")

    #For each line in the received data
    for d in data:

        #If not a separator line
        if d[0] != '-':

            #If multiple key/value pairs on one line, split
            d = d.split(", ")
            for pair in d:

                #Separate key and value then save in dataDict
                pair = pair.split(": ")
                dataDict[pair[0]] = inferDataType(pair[1])

    #Return created dictionary object
    return dataDict
