public class HeapSort {
  public static void main(String[] args) {
    int[] A = {3, 6, 10, 18, 8, 7, 25, 40};
    int[] B;
    B = A;
    sort(A);
    show(A); // display the sorted result A
  }

  public static void sort(int[] A) {
    heapify(A, 0, A.length);
    for(int i = A.length-1; i >= 0; i--) {
      swap(A, 0, i);
      siftDown(A, 0, i);
    }
  }

  public static void heapify(int[] A, int i, int n) {
    int i1 = i*2+1;
    int i2 = i*2+2;

    if(i1 < n) heapify(A, i1, n);
    if(i2 < n) heapify(A, i2, n);
    siftDown(A, i, n);
  }

  public static void siftDown(int[] A, int i, int n) {
    int i1 = i*2+1;
    int i2 = i*2+2;

    int max = i;
    if(i1 < n && A[i1] > A[max]) {
      i1 = max;
    }

    if(i2 < n && A[i2] > A[max]) {
      i2 = max;
    }

    if(i != max) {
      swap(A, i, max);
      siftDown(A, max, n);
    }
  }

  public static void swap(int[] A, int i, int j) {
    int t = A[i];
    A[i] = A[j];
    A[j] = t;
  }

  public static void show(int[] A) {
    for(int i = 0; i < A.length; i++) {
      System.out.print(A[i]);
      if(i != A.length-1) {
        System.out.print(", ");
      } else {
        System.out.println();
      }
    }
  }

}
