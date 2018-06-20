#include <assert.h>
#include "list.h"

int main() {
    int a1[] = {0, 1, 2, 3, 4}, a2[] = {5, 6, 7, 8, 9}, a3[] = {4, 2, 6, 7, 3}, n = 5;
    Node *h1 = constructLinkedList(a1, n), *h2 = constructLinkedList(a2, n);
    h1 = reverse(h1);
    int e0[] = {4, 3, 2, 1, 0};
    assert(equalLinkedList(h1, e0));

    join(h1, h2);
    int e1[] = {4, 3, 2, 1, 0, 5, 6, 7, 8, 9};
    assert(equalLinkedList(h1, e1));

    for (int i = 7; i >= 0; i--) {
        h1 = delete(h1, i);
    }
    int e2[] = {8, 9};
    assert(equalLinkedList(h1, e2));

    h1 = pushNode(h1, 2);
    int e3[] = {8, 9, 2};
    assert(equalLinkedList(h1, e3));
    destructLinkedList(h1);

    List *l1 = constructList(a3, n);
    sort(l1);
    push(l1, 9); push(l1, 10); pop(l1);

    int e4[] = {2, 3, 4, 6, 7, 9};
    for (int i = 0; i < l1->length; i++) {
        assert(l1->list[i] == e4[i]);
    }

    destructList(l1);
}