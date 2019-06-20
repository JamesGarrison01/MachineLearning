from __future__ import division
import numpy as np
import math

def readData(file):
    count = 0
    lst = []
    with open(file, 'r') as fp:
        for line in str(fp.read()).split("\n"):
            curr = line.split("\t")
            if curr and curr[0] != "? " and curr[0] != "?" and curr[-1] != "":
                count = count + 1
                curr[5] = curr[5].rstrip()
                #print(curr)
                dataSet = {}
                dataSet["mean"] = 0.0
                dataSet["y"] = float(curr[0])
                dataSet["m2"] = float(curr[1])
                dataSet["m3"] = float(curr[2])
                dataSet["m4"] = float(curr[3])
                dataSet["m5"] = float(curr[4])
                dataSet["m6"] = float(curr[5])
                factor=1.0/sum(dataSet.itervalues())
                for j in dataSet:
                    dataSet[j] = dataSet[j]*factor
                lst.append(dataSet)
                #print(dataSet)
            elif curr[0] == "? " or curr[0] == "?":
                count = count + 1
                curr[5] = curr[5].rstrip()
                dataSet = {}
                dataSet["mean"] = 0.0
                dataSet["y"] = 0.0
                dataSet["m2"] = float(curr[1])
                dataSet["m3"] = float(curr[2])
                dataSet["m4"] = float(curr[3])
                dataSet["m5"] = float(curr[4])
                dataSet["m6"] = float(curr[5])
                factor=1.0/sum(dataSet.itervalues())
                for j in dataSet:
                    dataSet[j] = dataSet[j]*factor
                #print(dataSet)
                lst.append(dataSet)
    return lst

def mean(listData):
    trainlst = []
    
    mean = 0
    for point in listData:
        mean = point["m2"] + point["m3"] + point["m4"] + point["m5"] + point["m6"]
        mean = mean/6
        point["mean"] = mean
        trainlst.append(point)

    return trainlst

def mean2(values):
    return sum(values) / float(len(values))

def covariance(x, meanX, y, meanY):
    var = 0.0
    for i in range(len(x)):
        var += (x[i] - meanX) * (y[i] - meany)
    return var

def variance(values, mean):
    return sum([(mean)**2 for x in values])

def coefficents(listData):
    y = [row[0] for row in listData]
    x = [row[1] for row in listData]

    xmean = mean(x)
    ymean = mean(y)
    
    first = covariance(x, xmean, y, ymean) / variance(x, xmean)
    second = ymean - first * xmean
    return [first, second]

def linearReg(train_X, test_X):
    pred = list()
    first, second = coefficents(train_X)
    for row in test_X:
        yhat = first + second * row[0]
        pred.append(yhat)
    return pred
    
theta = np.zeros((2,1))
lst2 = readData("linear_regression_data.txt")
lst = mean(lst2)
train_X = lst[:-3]
test_X = lst[-3:] 
