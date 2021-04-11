from LinkedList import *

def removeDup(head):
    run = head
    temp = head.next
    while temp:
        while run.data == temp.data:
            temp = temp.next
            if temp is None:
                run.next = temp
                return head
        run.next = temp
        run = run.next
        temp = temp.next
    return head

def removeDup3(head):
    if head is None:
        return head
    node = head
    while node.next:
        if node.data == node.next.data:
            node.next= node.next.next
        else:
            node = node.next
    return head

def removeDupRec(head):
    if head is None:
        return None
    nextNode = head.next
    while nextNode is not None and head.data == nextNode.data:
        nextNode = nextNode.next
    head.next = removeDupRec(nextNode)
    return head

l = input_linkedlist()
print_linkedlist(removeDup3(l.head))
        