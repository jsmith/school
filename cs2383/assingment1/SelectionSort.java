/**
 * This file contains the selection sort algorithm
 * @author Jacob Smith
 */
public class SelectionSort {
  public static void main(String[] args) {
    int[] A = {7, 4, 8, 2, 5, 3, 9};
    sort(A);
    show(A); // display the sorted result A
  }

  /**
   * The selection sort algorithm
   * @param int[] A The array to sort
   */
  public static void sort(int[] A) {
    for(int i = 0; i < A.length; i++) {
      int min = i; // index of the minimum value
      for(int j = i+1; j < A.length; j++) {
        if(A[j] < A[min]) {
          min = j; // if smaller change the min index
        }
      }
      // swap the min the and the current i index
      int temp = A[i];
      A[i] = A[min];
      A[min] = temp;
    }
  }

  /**
   * Prints an integer array
   * @param int[] A The array to print
   */
  public static void show(int[] A) {
    System.out.print("Sorted array using selection sort: ");
    for(int i = 0; i < A.length-1; i++) {
      System.out.print(A[i] + ", ");
    }
    System.out.println(A[A.length-1]);
  }
}
