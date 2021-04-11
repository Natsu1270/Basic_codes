class SinglyLinkedListNode:
    def __init__(self,data):
        self.data = data
        self.next = None
class SinglyLinkedList:
    def __init__(self):
        self.head = None
        self.tail = None

    def insert_node(self,data):
        node = SinglyLinkedListNode(data)
        if not self.head:
            self.head = node
        else:
            self.tail.next = node
        self.tail = node

def print_linkedlist(head):
    if head is None:
        return
    print(head.data)
    print_linkedlist(head.next)

def input_linkedlist():
    ll_count = int(input())
    llist = SinglyLinkedList()
    for _ in range(ll_count):
        llist.insert_node(int(input()))
    return llist