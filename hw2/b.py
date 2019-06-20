import numpy as np
from sklearn.preprocessing import StandardScaler

def readData(file):
    count = 0
    mean = 0
    lst = []
    with open(file, 'r') as fp:
        for line in str(fp.read()).split("\n"):
            curr = line.split("\t")
            scaler = StandardScaler()
            if curr and curr[0] != "? " and curr[0] != "?" and curr[-1] != "":
                count = count + 1
                curr[5] = curr[5].rstrip()
                dataSet = {}
                StandardScaler(copy=True, with_mean=True, with_std=True)
                dataSet["y"] = float(curr[0])
                dataSet["m2"] = float(curr[1])
                dataSet["m3"] = float(curr[2])
                dataSet["m4"] = float(curr[3])
                dataSet["m5"] = float(curr[4])
                dataSet["m6"] = float(curr[5])
                lst.append(dataSet)
                mean = dataSet["m2"] + dataSet["m3"] + dataSet["m4"] + dataSet["m5"] + dataSet["m6"]
                mean = mean/5
                dataSet["x"] = mean
            elif curr[0] == "? " or curr[0] == "?":
                count = count + 1
                curr[5] = curr[5].rstrip()
                curr[0] = 0.0
                curr = np.array(curr).reshape(3, 2)
                scaler.fit(curr)
                curr = scaler.transform(curr)
                print(curr)
                #curr = curr.reshape(1, 6)
                #print(curr)
                dataSet = {}
                dataSet["y"] = 0.0
                dataSet["m2"] = float(curr[0][1])
                dataSet["m3"] = float(curr[1][0])
                dataSet["m4"] = float(curr[1][1])
                dataSet["m5"] = float(curr[2][0])
                dataSet["m6"] = float(curr[2][1])
                mean = dataSet["m2"] + dataSet["m3"] + dataSet["m4"] + dataSet["m5"] + dataSet["m6"]
                print(mean)
                mean = mean/5
                print(mean)
                dataSet["x"] = mean
                #print(dataSet)
                lst.append(dataSet)
    return lst

def cost(x, y, theta):
    m = len(x)
    J = 1/(2*m) * sum((x.dot(theta).flatten() - y)**2)
    return J

def gradient2(x, y, theta):
    alpha = 0.01
    it = 398
    m = 398
    J = []

    for i in range(it):
        a = theta[0][0] - alpha*(1/m)*sum((x.dot(theta).flatten() - y)*x[:,0])
        b = theta[1][0] - alpha*(1/m)*sum((x.dot(theta).flatten() - y)*x[:,1])
        theta[0][0],theta[1][0]=a,b
        print theta[0][0]
        print theta[1][0]
        J.append(cost(x,y,theta))
        print 'Cost: ' + str(J[-1])

    return theta

def gradient(datapoints, x, y):
    alpha = 0.01
    it = 398
    while it > 0:
        x = x - (alpha * derive(datapoints, x, y))
        it = it - 1
    return x

def derive(datapoints, x, y):
    sum = 0.0
    for point in datapoints:
        sum = sum + ((x + y * float(point["y"])) - float(point["x"]))
    return float(sum/398)

def lineReg(train, test):
    i = 0
    theta = gradient(train, 0, 0)
    for point in test:
        print(point["x"])
        print(theta)
        newY = theta * point["x"]
        point["y"] = newY
        print("Test Point new Y: ", i)
        print(point["y"])
        print("\n")
        i += 1
        

lst = readData("linear_regression_data.txt")
trainX = lst[:-3]
testX = lst[-3:] 

lineReg(trainX, testX)



