from LinkedList import *

def getNode(head,pos):
    index, run ,res = 0, head, head    
    while run.next:
        run = run.next
        index +=1
        if index > pos:
            res = res.next
    return res.data

def getNode2(head,pos):
    run,res = head,head
    while pos>0:
        run = run.next
    while run.next:
        run = run.next
        res = res.next
    return res.data

llist = input_linkedlist()
print(getNode2(llist.head,0))