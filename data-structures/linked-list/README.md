#Linked list data structure
The linked list data structure description and implementation

## Abstract
The linked list keeps objects in a linear order. Unlike, the arrayobjects are arranged by array indices, the LL uses pointers from object to object to arrange the order of objects. 
The linked list have the following attributes:
* prev - the predecessor of object X. If _x.prev_ is nil, then X is the first elem and the HEAD of the list.
* next(head) - the successor of the object X. If _x.next_ is nil, then the _x_ is the last elem in the list or TAIL of the list. If the _L.head_ is nil then the list is empty
* key - the value of the node

The linked list can be in several forms
* Singly linked - objects have only successors, _prev_ attr does not exist
* Doubly linked - objects have both successors and predecessors
* Sorted -  

## Algorithms
### Search
Steps:
1. Get the head of the list to start the search from it.
2. Iterate over nodes while node is not nil or nodes value is not what we a searching for.

Pseudocode:
```
List-Search(L, k)
  x = L.head
  while x != NIL and x.key != k
    x = x.next
  return x
```

### Insert
Steps:
1. Link the node to list by setting next value of node to the head.
2. If head is not nil, set its prev value to node.
3. Set current head to newly inserted node.
4. Set newly inserted node's prev to NIL

Pseudocode:
```
List-Insert(L, x)
  x.next = L.head
  if L.head != NIL
    L.head.prev = x
  L.head = x
  x.prev = NIL
```

### Delete
Deletion is done unlinking given node from the list.
This is done in 2 steps in doubly linked list.
Firstly, set the _next pointer_ of node that _lays before given node_ to the _next node of given node_.
Secondly, set the 

Steps:
1.  If given node to delete is not head of the list, set the next pointer of 
this node's previous value to its next value: x.prev.next = x.next
Else, set list's head to node's next value: L.head = x.next
2. If node's next value is not nil, set its next value' prev value to node's prev value.

Pseudocode:
```
List-Delete(L, x)
  if x.prev != nil
    x.prev.next = x.next
  else 
    L.head = x.next
  
  if x.next != nil
    x.next.prev = x.prev
```