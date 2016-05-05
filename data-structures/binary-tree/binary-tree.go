package main

type Tree struct {
	val   interface{}
	right *Tree
	left  *Tree
}

func insert(tree *Tree, val interface{}) *Tree {
	if tree == nil {
		return &Tree{val, nil, nil}
	}
	if val < tree.Val {
		tree.left = insert(tree.left, val)
		return tree
	}
	tree.right = insert(tree.right, val)
	return t

}

func show(t *Tree) {

}
func main() {
	t := Tree{1}
	t2 := insert(t, 65)
	t3 := insert(t2, 100)
	t4 := insert(t2, 44)

}
