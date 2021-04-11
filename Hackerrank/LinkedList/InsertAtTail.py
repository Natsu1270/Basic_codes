def InsertTail(head,data):
    node = SinglyLinkedListNode(data)
    if head is None:
        head = node
    else:
        run = head
        while run.next:
            run = run.next
        run.next = node
    return head

# time out problem
def InsertTailRec(head,data):
    if head is Node:
        return SinglyLinkedListNode(data)
    head.next = InsertTailRec(head.next,data)
    return head