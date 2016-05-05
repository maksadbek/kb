#Linked list data structure
The linked list data structure description and implementation

## Abstract
The linked list keeps objects in a linear order. Unlike, the arrayobjects are arranged by array indices, the LL uses pointers from object to object to arrange the order of objects. 
The linked list have the following attributes:
* prev - the predecessor of object X. If ```x.prev``` is nil, then X is the first elem and the HEAD of the list.
* next(head) - the successor of the object X. If ```x.next``` is nil, then the ```x``` is the last elem in the list or TAIL of the list. If the ```L.head``` is nil then the list is empty
* key - the value of the node

The linked list can be in several forms
* Singly linked - objects have only successors, ```prev``` attr does not exist
* Doubly linked - objects have both successors and predecessors
* Sorted -  
