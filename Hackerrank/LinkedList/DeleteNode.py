from LinkedList import *

def deleteNode(head,pos):
    if pos == 0:
        return head.next
    temp = head
    prev = None
    while pos > 0:
        prev = temp
        temp = temp.next
        pos -= 1
    prev.next = temp.next
    del temp
    return head
    
def deleteNodeRec(head,pos):
    if pos == 0:
        return head.next
    head.next = deleteNodeRec(head.next,pos-1)
    return head

llist = input_linkedlist()
pos = int(input())
head = deleteNode(llist.head,pos)
print_linkedlist(head) 