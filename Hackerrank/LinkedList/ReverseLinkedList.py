from LinkedList import *

def ReverseRec(head):
    if head is None or head.next is None:
        return head
    node = ReverseRec(head.next)
    head.next.next = head
    head.next = None
    return node

def Reverse(head):
    tempt,prev = None,None
    while head:
        tempt = head.next
        head.next = prev
        prev = head
        head = tempt
    return prev

llst = input_linkedlist()
head = Reverse(llst.head)
print_linkedlist(head)