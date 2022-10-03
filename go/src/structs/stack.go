package main

import (
	"fmt"
	node "src/package"
)

func main() {
	var miNodo node.NodePublic
	miNodo.Data = 1
	fmt.Println(miNodo.Data)
}
