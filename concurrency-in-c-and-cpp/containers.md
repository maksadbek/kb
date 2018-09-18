### Containers in C++

#### Vector
Vector allocates more memory that it is given. For example, we allocate a vector with size 16.
But we get a vector with size `>=16`.

```C++
std::vector<int> v(16);

v.size(); // returns the size
v.resize(32); // resize the vector

v.capacity() // get the actual size, capacity
v.reserve(128) // change capacity

v.insert(...);
v.erase(...);

v.push_back(...);
v.pop_back(...);
```

#### List

The list is a double linked list.
```C++
std::list<int> l;

l.push_front(...);
l.pop_front(...);

l.insert(...);
l.erase(...);

l.push_back(...);
l.pop_back(...);
```

The C++ has another type of list, singly linked list - `std::forward_list`

#### Deque - `std::deque`
Another type of container, double ended queue, it is a hybrid of array and list.
We can access by an index and append to the beginning of the deque.

#### Set - `std::set`

This set is implemented with binary search trees and it is balanced with red-black trees.

#### Unordered set and hashes - `std::unordered_set`
The unordered set is 
Hashing approaches:
- Open addressing - using multiple hashing algorithms. For example: `h[m] = h[m-1] + 1`, this is called linear probing.
- Circular hashing - using a linked list to keep collided values.

#### Circular buffer
