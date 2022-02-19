// You can edit this code!
// Click here and start typing.
package main

import "fmt"

func removewhitespace(s []byte) string {
	i := 1

	for i < len(s) {
		if s[i] == ' ' && s[i-1] == ' ' {
			j := i + 1

			for j < len(s) && s[j] == ' ' {
				j++
			}

			if j >= len(s) {
				break
			}

			start := j
			end := start

			for end < len(s) && s[end] != ' ' {
				end++
			}

			// fmt.Println(i, start, end)
			for k := start; k < end; k++ {
				s[i], s[k] = s[k], s[i]
				i++
			}

			// fmt.Printf("%q\n", string(s))
		} else {
			i++
		}
	}

	w := 0

	for ; w < len(s); w++ {
		if s[w] == ' ' {
		}
	}

	return string(s[:i-1])
}

func main() {
	fmt.Printf("%q\n", removewhitespace([]byte("a     bbbbbb   c")))
	fmt.Printf("%q\n", removewhitespace([]byte(" ")))
	fmt.Printf("%q\n", removewhitespace([]byte("")))

}
