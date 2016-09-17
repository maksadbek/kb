package bfs

type Node struct {
	Item int
	Next *Node
}

type Queue struct {
	Size int
	Head *Node
	Tail *Node
}

func (q *Queue) Push(n int) {
	node := &Node{n, nil}

	if q.Head == nil {
		q.Head = node
	}

	if q.Tail != nil {
		q.Tail.Next = node
	}

	q.Tail = node
	q.Size++
}

func (q *Queue) Pop() (int, bool) {
	if q.Size == 0 {
		return 0, false
	}

	n := q.Head
	q.Head = q.Head.Next
	q.Size--

	if q.Size == 0 {
		q.Head = nil
		q.Tail = nil
	}
	return n.Item, true
}
