package main

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

var a []int

func initArray() {
	a = []int{1, 2, 3, 4, 5}
}

func TestStack(t *testing.T) {
	s := Stack{}
	s.Push(1)
	s.Push(2)
	err := s.Pop()
	assert.Nil(t, err)

	value, err := s.Top()
	assert.Equal(t, 1, value)
	assert.Nil(t, err)

	err = s.Pop()
	assert.Nil(t, err)
	err = s.Pop()
	assert.NotNil(t, err)
}

func TestList(t *testing.T) {
	l := List{}
	l.Add(1)
	l.Add(2)
	l.Add(2)
	l.Add(3)
	assert.Equal(t, 4, l.Length())

	l.Del(2)
	assert.Equal(t, 2, l.Length())
	assert.Equal(t, 1, l.Front())
	assert.Equal(t, 3, l.End())
	assert.Equal(t, 1, l.Get(0))
	assert.Equal(t, 3, l.Get(1))
}

func TestBinarySearchFound(t *testing.T) {
	initArray()
	k := 4
	index := BinarySearch(a, k)
	assert.Equal(t, 3, index)
}

func TestBinarySearchNotFound(t *testing.T) {
	initArray()
	k := 10
	index := BinarySearch(a, k)
	assert.Equal(t, -1, index, "BinarySearch should return -1 for not found")
}
