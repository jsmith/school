public class HeapSort {
  public static void main(String[] args) {
    int[] A = {3, 6, 10, 18, 8, 7, 25, 40};
    int[] B;
    B = A;
    sort(A);
    show(A); // display the sorted result A
  }

  public static void sort(int[] A) {
    for(int i = A.length-1; i >= 0; i--) {
      heapify(A, 0, i+1);
      swap(A, 0, i);
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

    if(n <= i2) {
      return;
    } else if(n <= i1) {
      if(A[i] < A[i1]) {
        swap(A, i, i1);
      }
      return;
    }

    if(A[i1] > A[i2] && A[i1] > A[i]) {
      swap(A, i, i1);
      siftDown(A, i1, n);
    } else if(A[i2] > A[i]) {
      swap(A, i, i2);
      siftDown(A, i2, n);
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
