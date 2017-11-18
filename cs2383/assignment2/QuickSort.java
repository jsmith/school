public class QuickSort {
  public static void main(String[] args) {
    int[] A = {3, 6, 10, 18, 8, 7, 25, 40};
    int[] B;
    B = A;
    sort(A);
    show(A); // display the sorted result A
  }

  public static void sort(int[] A) {
    quickSort(A, 0, A.length);
  }

  public static void quickSort(int[] A, int s, int e) {
    if(e-s <= 1) {
      return;
    }

    int partition = partition(A, 0, e);
    quickSort(A, s, partition);
    quickSort(A, partition+1, e);
  }

  public static int partition(int[] A, int s, int e) {
    int pivot = A[e-1];

    int j = 0; // index to place next value
    for(int i = s; i < e-1; i++) {
      if(A[i] <= pivot) {
        swap(A, i, j);
        j++;
      }
    }
    swap(A, j, e-1);

    return j;
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
