# https://www.hackerrank.com/challenges/ants

TIME = 1000000006
CIRCLE_TIME = 10000
    
def get_answer_test(n, V, v):
    if n % 2 == 0:
        hit = TIME / CIRCLE_TIME * (n / 2 * 2 * n / 2 * 2)
    else:
        hit = TIME / CIRCLE_TIME * (n / 2 * 2 * (n / 2 + 1) * 2)
    
    # Counting additional hits (where sub is 1)
    additional = 0
    flag = 0
    
    for i in xrange(len(v)-1):
        if flag == 0:
            if v[i+1] - v[i] == 1:
                additional +=2
                flag = 1
            else:
                flag = 0
        else:
            flag = 0
    
    return hit + additional

if __name__ == '__main__':
    n = int(raw_input())
    V = raw_input().split()
    
    v = [int(i) for i in V]
    v = sorted(v)
    
    print get_answer_test(n, V, v)    