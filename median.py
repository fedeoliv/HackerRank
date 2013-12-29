# https://www.hackerrank.com/challenges/median

from bisect import bisect_left

def median(n):
    x = []
    
    for _ in range(0, n):
        cmd,num = raw_input().split()
        num = int(num)
        pos = bisect_left(x, num)
        
        if cmd == 'r':
            if pos >= len(x) or x[pos] != num:
                return 'Wrong!'
                continue
            else:
                del(x[pos])
        else:
            x.insert(pos,num)
        
        l = len(x)
        
        if l == 0:
            return 'Wrong!'
        elif l & 1:
            return x[l/2]
        else:
            result = x[l / 2] + x[l / 2 - 1]
            
            if result == 0:
                return result
            elif sum & 1:
                return float(result) / 2.0
            else:
                return result / 2
    
if __name__ == "__main__":
    print median(int(raw_input()))