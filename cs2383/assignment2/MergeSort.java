public class MergeSort {
  public static void main(String[] args) {
    int[] A = {3, 6, 10, 18, 8, 7, 25, 40};
    int[] B;
    B = A;
    sort(A);
    show(A); // display the sorted result A
  }

  public static void sort(int[] A) {
    mergeSort(A);
  }

  public static void mergeSort(int[] A) {
    if(A.length == 1) return;
    int[] A1 = new int[A.length/2];
    int[] A2 = new int[A.length/2 + A.length%2];
    System.arraycopy(A, 0, A1, 0, A1.length);
    System.arraycopy(A, A.length/2, A2, 0, A2.length);
    mergeSort(A1);
    mergeSort(A2);
    merge(A, A1, A2);
  }

  public static void merge(int[] A, int[] A1, int[] A2) {
    int i = 0;
    int j = 0;
    while(i < A1.length && j < A2.length) {
      if(A1[i] < A2[j]) {
        A[i+j] = A1[i];
        i++;
      } else {
        A[i+j] = A2[j];
        j++;
      }
    }

    for(int k = i; k < A1.length; k++) {
      A[k+j] = A1[k];
    }
    for(int k = j; k < A2.length; k++) {
      A[i+k] = A2[k];
    }
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
