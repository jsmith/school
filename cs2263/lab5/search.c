//
// Jacob Smith 47118500
// Raven-Lee Mills 47308881
//


#include "vector.h"

static int binarySearchHelp(Vector* arr, int low, int high, int key) {
    if (low > high) {
        return -1;
    }
    int ind = (low + high) / 2;
    if (arr[ind].length == key) {
        return ind;
    }
    if (arr[ind].length > key) {
        return binarySearchHelp(arr, low, ind - 1, key);
    }
    return binarySearchHelp(arr, ind + 1, high, key);
}

int binarySearch(Vector* arr, int len, int key) {
    return binarySearchHelp(arr, 0, len - 1, key);
}