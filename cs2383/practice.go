package main

import (
	"errors"
	"fmt"
)

func main() {
	fmt.Println("Practicing Data Structures & Algorithms")
}

// Node a node in a binary tree
type Node struct {
	data  int
	left  *Node
	right *Node
}

// Stack a stack
type Stack struct {
	head *Item
}

// List a List
type List struct {
	head *Item
}

// Item an item in a stack, queue or linked-list
type Item struct {
	data int
	next *Item
}

// Push pushes the value onto the list
func (s *Stack) Push(value int) {
	item := Item{value, s.head}
	s.head = &item
}

// Pop pops the top item off the list
func (s *Stack) Pop() error {
	if s.head == nil {
		return errors.New("the stack is empty")
	}

	s.head = s.head.next
	return nil
}

// Top returns the item at the top of the list
func (s *Stack) Top() (int, error) {
	if s.head == nil {
		return 0, errors.New("the stack is empty")
	}

	return s.head.data, nil
}

// Add adds the value to the end of the list
func (l *List) Add(value int) {
	item := l.head
	if item == nil {
		l.head = &Item{value, nil}
		return
	}

	for item.next != nil {
		item = item.next
	}
	item.next = &Item{value, nil}
}

// Del deletes all instances of value in the list
func (l *List) Del(value int) {
	item := l.head
	if item == nil {
		return
	}

	if item.next == nil {
		if item.data == value {
			l.head = nil
		}

		return
	}

	for item.next != nil {
		if item.next.data == value {
			item.next = item.next.next
		} else {
			item = item.next
		}
	}
}

// Get returns the item at the given index, -1 if > length of the list
func (l *List) Get(index int) int {
	i := 0
	item := l.head
	for item != nil {
		if i == index {
			return item.data
		}

		item = item.next
		i++
	}

	return -1
}

// Length returns the length of the list
func (l *List) Length() int {
	length := 0
	item := l.head
	for item != nil {
		length++
		item = item.next
	}

	return length
}

// Front returns the front value in the list
func (l *List) Front() int {
	return l.Get(0)
}

// End returns the last value in the list
func (l *List) End() int {
	return l.Get(l.Length() - 1)
}

// Print prints the list
func (l *List) Print() {
	item := l.head
	for item != nil {
		fmt.Print(item.data, " ")
		item = item.next
	}
	fmt.Println()
}

// BinarySearch searches for k in array a and returns the index
func BinarySearch(a []int, k int) int {
	return search(a, k, 0, len(a))
}

func search(a []int, k int, start int, end int) int {
	if start >= end {
		return -1
	}

	mid := (start + end) / 2
	if a[mid] == k {
		return mid
	} else if k < a[mid] {
		return search(a, k, start, mid)
	} else {
		return search(a, k, mid+1, end)
	}
}

// Insert inserts value into the binary tree
func Insert(root *Node, value int) {

}
