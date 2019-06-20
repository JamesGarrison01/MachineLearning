
def readData(file):
    count = 0
    lst = []
    with open(file, 'r') as fp:
        for line in str(fp.read()).split("\n"):
            curr = line.split(",")
            if curr and curr[-1] != "\r" and curr[-1] != "":
                dataSet = {}
                dataSet["m1"] = float(curr[0])
                dataSet["m2"] = float(curr[1])
                dataSet["m3"] = float(curr[2])
                dataSet["m4"] = float(curr[3])
                dataSet["y"] = curr[4]
                lst.append(dataSet)
    return lst

def findNearest(k, listData, testPoint):
    final = [1000 for i in range(0, k)]
    newFinal = 0
    for point in listData:
        m1 = abs(testPoint["m1"] - point["m1"])
        m2 = abs(testPoint["m2"] - point["m2"])
        m3 = abs(testPoint["m3"] - point["m3"])
        m4 = abs(testPoint["m4"] - point["m4"])

        newFinal = (m1 + m2 + m3 + m4)/4
        for i in range(0,k):
            if(final[i] > newFinal):
                for t in range(0,i):
                    if(final[t] != newFinal):
                        final[i] = newFinal
                        print(final[i])



dataPoint = {"m1": 1.0,"m2": 2.0,"m3": 0.0,"m4": 0.0,"y": ""}
lst = readData("a1.txt")
findNearest(3, lst, dataPoint) 
