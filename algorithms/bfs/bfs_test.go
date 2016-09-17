package bfs

import (
	"fmt"
	"testing"
)

func TestBFS(t *testing.T) {
	G := [][]int{
		[]int{1, 2},
		[]int{0, 2, 4},
		[]int{0, 1, 3},
		[]int{2},
		[]int{1},
	}
	graph := New(G)
	graph.BFS(0)

	fmt.Println(graph.Path(4))
}
