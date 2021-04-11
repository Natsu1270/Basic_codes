from LinkedList import *

def mergeLists(head1,head2):
    run1,run2 = head1,head2
    res = head1 if head1.data < head2.data else head2
    result = res
    while run1 or run2:
        while run1.data < run2.data:
            if run1.next is None:
                res.next = run2
                res = res.next
                return result
            if run1.next.data >= run2.data:
                run1 = run1.next
                res.next = run2
                res = res.next
                break
            run1 = run1.next
            res = res.next
        while run2.data <= run1.data:
            if run2.next is None:
                res.next = run1
                res = res.next
                return result
            if run2.next.data > run1.data:
                run2 = run2.next
                res.next = run1
                res = res.next
                break
            run2 = run2.next
            res = res.next
    return result

def mergeListsRec(head1, head2):
    pass


    
l1 = input_linkedlist()
l2 = input_linkedlist()
print_linkedlist(mergeLists(l1.head,l2.head))