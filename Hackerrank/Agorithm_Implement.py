#Beautiful day

def reverseNum(i):
    return(int(str(i)[::-1]))
def beautifulDay():
    res = 0
    ijk = input().split()
    i,j,k=int(ijk[0]), int(ijk[1]), int(ijk[2])
    for n in range(i,j+1):
        res +=1 if (n-reverseNum(n))%k == 0 else 0
    print(res)


# Viral Advertising
def countViral(days,value):
    return 0 if days == 0 else value//2 + countViral(days-1,3*(value//2)) 
def viralAdvertsing():
    days = int(input())
    value = int(input())
    print(countViral(days,value))


viralAdvertsing()
# beautifulDay()
