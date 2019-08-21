package skiplist

import (
    "math/rand"
    "time"
)

const maxLevel = 16

func init() {
    rand.Seed(time.Now().UnixNano())
}

type node struct {
	key  int
	id   int
	next []*node
	prev *node
}

func newNode(key, id, level int) *node {
    return &node{
        key: key,
        id: id,
        next: make([]*node, level),
    }
}

type Skiplist struct {
    head *node
    tail *node
    level int
}

func New() *Skiplist {
    return &Skiplist {
        head: newNode(0, 0, maxLevel),
        level: 1,
    }
}

func (s *Skiplist) Insert(key, id int) {
    current := s.head
    update := make([]*node, maxLevel)

    for i := s.level; i>=0; i-- {
        if current.next[i] == nil || key < current.next[i].key {
            update[i] = current
        } else {
            for current.next[i] != nil && current.next[i].key < key {
                current = current.next[i]
            }

            update[i] = current
        }
    }
    
    level := randLevel()

    if s.level < level {
        for i := s.level + 1; i <= level; i++ {
            update[i] = s.head
        }

        s.level = level
    }

    node := newNode(key, id, level)

    if prev := update[0]; prev != nil {
        node.prev = prev
    }

    for i := 0; i < level; i++ {
        node.next[i] = update[i].next[i]
        update[i].next[i] = node
    }

    if node.next[0] != nil {
        if node.next[0].prev.key != node.key {
            node.next[0].prev = node
        }
    }

    if s.tail == nil || s.tail.key < node.key {
        s.tail = node
    }
}

func (s *Skiplist) Search(key int) *node {
    current := s.head

    for s := s.level - 1; s >= 0; s-- {
        if current.next[s].key == key {
            return current.next[s]
        } else if key < current.next[s].key {
            break
        } else {
            current = current.next[s]
        }
    }

    return nil
}

func (s *Skiplist) List(n int) []int {
    var list []int

    current := s.head.next[0]
    for i := 0; current != nil && i < n; i++ {
        list = append(list, current.id)
        current = current.next[0]
    }

    return list
}

func (s *Skiplist) ReverseList(n int) []int {
    var list []int

    current := s.tail
    for i := 0; current != s.head && i < n; i++ {
        list = append(list, current.id)
        current = current.prev
    }

    return list
}

func randLevel() int {
    level := 1

    for rand.Float32() < 0.25 && level < maxLevel {
        level++
    }

    return level
}
