# https://www.hackerrank.com/contests/codesprint5/challenges/special-multiple

from itertools import product

for _ in range(int(raw_input())):
    N = long(raw_input())
    
    if(N == 1): 
        print 9
    else:
        for x in product("09", repeat = int(round(N/2)) + len(str(N))):
            comb = long(''.join(map(str,x)))
             
            if(comb != 0 and comb % N == 0):
                print comb
                break
