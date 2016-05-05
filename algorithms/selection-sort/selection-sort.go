package main

import "fmt"

func selection_sort(L []int) []int {
	for i := 0; i < len(L); i++ {
		min := L[i]
		for j := i; j < len(L); j++ {
			if L[j] < min {
				tmp := min
				min = L[j]
				L[j] = tmp
			}
		}
		L[i] = min
	}
	return L
}

func main() {
	m := []int{9, 8, 7, 6, 5, 4, 3, 2, 1}
	l := selection_sort(m)
	fmt.Println(l)
}
