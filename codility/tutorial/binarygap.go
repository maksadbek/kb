package main

import "fmt"

func solution(N int) (max int) {
	var (
		count       int
		skippedHead bool
	)

	for N > 0 {
		if N&1 == 0 {
			if skippedHead {
				count++
			}
		} else {
			if !skippedHead {
				skippedHead = true
			} else {
				if count > max {
					max = count
				}
				count = 0
			}
		}

		N = N >> 1
	}

	return max
}

func main() {
	defer func() {
		if err := recover(); err == nil {
			println("PASS")
		} else {
			println("FAIL: ", err)
		}
	}()

	testCases := []struct {
		n      int
		bingap int
	}{
		{
			n:      5,
			bingap: 1,
		}, {
			n:      6,
			bingap: 0,
		}, {
			n:      51712,
			bingap: 1,
		},
	}

	for i := range testCases {
		if max := solution(testCases[i].n); max != testCases[i].bingap {
			panic(fmt.Sprintf("want %d, got %d", testCases[i].bingap, max))
		}
	}
}
