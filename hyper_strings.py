# https://www.hackerrank.com/challenges/hyper-strings

import sys
from functools import wraps

# memory function that stores values in recursive function 
def memo(func):
    cache = {}
    @wraps(func)
    def wrap(*args):
            if args not in cache:
                    cache[args] = func(*args)
            return cache[args]
    return wrap

# recursively add to answer list
def findStrings(currentString):
    global  H, m
    if currentString == m:
            return 0 
    count = 0
    for s in H:
            temp = currentString + len(s) 
            if temp <= m:
                    count += findStrings(temp) + 1
    return count

def removeBuiltStrings(s, first = False):
    global H
    if len(s) == 0:
            return True
    for x in H:
            if len(x) <= len(s):
                    if first and x == s:
                            continue
                    if s[:len(x)] == x:
                            if removeBuiltStrings(s[len(x):]):
                                    return True
    return False        

if __name__ == "__main__":
    findStrings = memo(findStrings)
    data = sys.stdin.readlines()
    H = []
    
    line = data[0].rstrip('\n').split()
    n = int(line[0])
    m = int(line[1])
    
    for i in range(1, len(data)):
        H.append(data[i].rstrip('\n'))
    
    H = set(H)
    remove = []
    
    for x in H:
        if removeBuiltStrings(x, True):
            remove.append(x)

    for x in remove:
        H.remove(x)
    
    print (findStrings(0)+1) % 1000000007