package main

import (
	"fmt"
)

var count = 1
func gospersHack(k, n int) {
	set := (1 << k) - 1
	limit := 1 << n

	for set < limit {
		fmt.Printf("%d:\t%06b\n", count, set)

		c := set & -set
		r := set + c

		set = (((r ^ set) >> 2) / c) | r
		count++
	}
}

func main() {
	gospersHack(1, 4)
	gospersHack(2, 4)
	gospersHack(3, 4)
	gospersHack(4, 4)
}

/*
1:	000001
2:	000010
3:	000100
4:	001000
5:	000011
6:	000101
7:	000110
8:	001001
9:	001010
10:	001100
11:	000111
12:	001011
13:	001101
14:	001110
15:	001111
*/
