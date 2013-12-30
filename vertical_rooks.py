# https://www.hackerrank.com/challenges/vertical-rooks

def get_winner(X, Y):
    xor_sum = 0
    
    for i in range(len(X)):
        dist = abs(X[i] - Y[i])
        xor_sum ^= (dist - 1)
    
    return xor_sum != 0

if __name__ == '__main__':
    import sys
    f = sys.stdin
    
    def readint():
        return int(f.readline().strip())
    
    T = readint()
    
    for _ in range(T):
        N = readint()
        X = [readint() for i in range(N)]
        Y = [readint() for i in range(N)]
    
        if get_winner(X, Y):
            print 'player-2'
        else:
            print 'player-1'