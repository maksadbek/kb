package main

import "fmt"

func insSort(data []int) {
	for i := 1; i < len(data); i++ {
		key := data[i]
		j := i - 1
		for j >= 0 && data[j] > key {
			data[j+1] = data[j]
			j = j - 1
		}
		data[j+1] = key
		fmt.Printf("%+v\n", data)
	}
}

func main() {
	d := []int{9, 8, 7, 6, 5, 4, 3, 2, 1}
	insSort(d)
	fmt.Println(d)
}
