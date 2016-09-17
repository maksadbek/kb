package bfs

import "fmt"

type Graph struct {
	G    [][]int
	D    []int
	P    []int
	Used []bool
}

func New(G [][]int) *Graph {
	return &Graph{
		G:    G,
		D:    make([]int, len(G)),
		P:    make([]int, len(G)),
		Used: make([]bool, len(G)),
	}
}

// BFS - Breadth First Search
func (graph *Graph) BFS(s int) {
	queue := Queue{}
	queue.Push(s)

	graph.P[s] = -1
	graph.Used[s] = true

	for queue.Size != 0 {
		v, ok := queue.Pop()
		if !ok {
			break
		}

		for i := 0; i < len(graph.G[v]); i++ {
			to := graph.G[v][i]
			if !graph.Used[to] {
				graph.Used[to] = true
				queue.Push(to)
				graph.D[to] = graph.D[v] + 1
				graph.P[to] = v
			}
		}
	}
}

func (graph *Graph) Path(i int) []int {
	path := []int{}
	if !graph.Used[i] {
		fmt.Println("No path")
		return path
	}

	for v := i; v != -1; v = graph.P[v] {
		path = append(path, v)
	}

	for i, j := 0, len(path)-1; i < j; i, j = i+1, j-1 {
		path[i], path[j] = path[j], path[i]
	}

	return path
}
