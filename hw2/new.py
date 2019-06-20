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
                #print(curr[4])
                if curr[4] == "Iris-setosa\r":
                    curr[4] = 0
                elif curr[4] == "Iris-versicolor\r":
                    curr[4] = 1
                elif curr[4] == "Iris-virginica\r":
                    curr[4] = 2
                dataSet["y"] = curr[4]
                lst.append(dataSet)
    return lst

def findNearest(k, listData, testPoint):
    final = [1000 for i in range(0, k)]
    newFinal = 0
    yValue = [0 for i in range (0, k)]
    newY = 0
    for point in listData:
        m1 = abs(testPoint["m1"] - point["m1"])
        m2 = abs(testPoint["m2"] - point["m2"])
        m3 = abs(testPoint["m3"] - point["m3"])
        m4 = abs(testPoint["m4"] - point["m4"])

        newFinal = (m1 + m2 + m3 + m4)/4
        for i in range(0, k):
            if final[i] > newFinal:
                yValue[i] = point["y"]
                final[i] = newFinal
                point["m1"] = 1000
                newFinal = 1000
    
    for i in range(0, k):
       newY = yValue[i] + newY

    newY = newY/k
    testPoint["y"] = newY
    if newY == 0:
        print("DataPoint belongs to: Iris-setosa")
    elif newY == 1:
        print("DataPoint belongs to: Iris-versicolor")
    elif newY == 2:
        print("DataPoint belongs to: Iris-virginica")

lst = readData("a1.txt")
datalst = []
dataPoint = {"m1": 4.9,"m2": 3.0,"m3": 1.4,"m4": 0.2,"y": ""}
datalst.append(dataPoint)
dataPoint = {"m1": 4.9,"m2": 2.4,"m3": 3.3,"m4": 1.0,"y": ""}
datalst.append(dataPoint)
dataPoint = {"m1": 4.9,"m2": 2.5,"m3": 4.5,"m4": 1.7,"y": ""}
datalst.append(dataPoint)

print("Round 1: 1-NN")
for point in datalst:
    findNearest(1, lst, point) 

print("Round 2: 3-NN")
for point in datalst:
    findNearest(3, lst, point)

print("Round 3: 5-NN")
for point in datalst:
    findNearest(5, lst, point) 
