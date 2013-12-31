# https://www.hackerrank.com/challenges/stockprediction

import numpy as np
import math

def sell(owned, prices):
    last = prices[-1]
    prices = np.array(prices[:-1])

    if last >= prices.mean():
        return owned

    return 0

def buy(m, prices):
    last = prices[-1]
    prices = np.array(prices[:-1])

    if last <= prices.mean():
        return int(m / int(math.ceil(last)))

    return 0

# Head ends here
def printTransactions(m, k, d, name, owned, prices):

    output = []

    prices = np.array(prices)

    deviations = prices.std(1)

    sold = np.zeros(k)
    for i in reversed(np.argsort(deviations)):
        num = 0
        if owned[i]:
            num = sell(owned[i], prices[i])
            if num:
                output.append("%s %s %s" % (
                    name[i], 'SELL', num))
                sold[i] = 1
        if num == 0:
            num = buy(m, prices[i])
            if num:
                output.append("%s %s %s" % (
                    name[i], 'BUY', num))
                m -= (num * int(math.ceil(prices[i][-1])))

    return output

def parse_step():
    m, k, d = [float(i) for i in raw_input().strip().split()]

    k = int(k)
    d = int(d)
    names = []
    owned = []
    prices = []
    
    for _ in range(k):
        temp = raw_input().strip().split()
        names.append(temp[0])
        owned.append(int(temp[1]))
        prices.append([float(i) for i in temp[2:7]])

    return m, k, d, names, owned, prices

# Tail starts here
if __name__ == '__main__':
    output = printTransactions(*parse_step())
    print len(output)
    
    for line in output:
        print line