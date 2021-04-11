# two list -> compare each pair of ele 
# ele[i] of a>b => a plus one point -> return [point of a,point of b]
a=list(map(int, input().rstrip().split()))
b=list(map(int, input().rstrip().split()))
p_a,p_b=0,0
for pair in zip(a,b):
    if pair[0] > pair[1]:
        p_a+=1
    elif pair[0] < pair[1]:
        p_b+=1
print(p_a,p_b)