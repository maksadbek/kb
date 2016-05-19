package main

import "fmt"

type Node struct {
	next *Node
	prev *Node
	val  interface{}
}

type Queue struct {
	first *Node
	last  *Node
}

func (q *Queue) enq(item interface{}) {
	if q.first == nil {
		q.last = &Node{val: item}
		q.first = q.last
	} else {
		q.last.next = &Node{val: item}
		q.last = q.last.next
	}
}

func (q *Queue) deq() interface{} {
	if q.first != nil {
		item := q.first.val
		q.first = q.first.next
		return item
	} else {
		return nil
	}
}

func main() {
	q := Queue{}
	q.enq(1)
	q.enq(2)
	q.enq(3)
	fmt.Println(q.deq())
	fmt.Println(q.deq())
	fmt.Println(q.deq())
}
