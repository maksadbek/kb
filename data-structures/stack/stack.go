package main

import "fmt"

type Node struct {
	next *Node
	prev *Node
	val  interface{}
}

type Stack struct {
	top *Node
}

func (s *Stack) pop() interface{} {
	if s.top != nil {
		v := s.top.val
		s.top = s.top.next
		return v
	}
	return nil
}

func (s *Stack) push(item interface{}) {
	t := &Node{val: item}
	t.next = s.top
	s.top = t
}

func main() {
	s := Stack{}
	s.push(1)
	s.push(2)
	s.push(3)
	fmt.Println(s.pop())
	fmt.Println(s.pop())
	fmt.Println(s.pop())
}
