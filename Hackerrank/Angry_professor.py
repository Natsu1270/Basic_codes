# yes if number of element in list that <=0 is less than threshold k else no
def angryProfessor(k, a):
    res=list(filter(lambda x: x<=0,a))
    return "YES" if len(res) < k else "NO"