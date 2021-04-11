# Start at ground, everytime go down below sea level it is a valey, and finish trip at ground
# Sample input:
# 8
# UDDDUDUU
# -> output: 1 (one valey)
n = int(input())
s = input()
height,res=0,0
for step in s:
    if step is 'U':
        height+=1
    else:
        height-=1
        if height == -1:
            res+=1
print(res)