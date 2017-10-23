/**
 * This file contains the insertion sort algorithm
 * @author Jacob Smith
 */
public class InsertionSort {
  public static void main(String[] args) {
    int[] A = {7, 4, 8, 2, 5, 3, 9};
    sort(A);
    show(A); // display the sorted result A
  }

  /**
   * The insertion sort algorithm
   * @param int[] A The array to sort
   */
  public static void sort(int[] A) {
    for(int i = 1; i < A.length; i++) {
      int num = A[i]; // the current number
      int j = i-1; // the starting index
      while(j >= 0 && num < A[j]) {
        A[j+1] = A[j]; // move the number up one if it's bigger than the current number
        j--; // move to the next number
      }
      A[j+1] = num; // place the current number when end of the list is reached or a smaller number is found
    }
  }

  /**
   * Prints an integer array
   * @param int[] A The array to print
   */
  public static void show(int[] A) {
    System.out.print("Sorted array using insertion sort: ");
    for(int i = 0; i < A.length-1; i++) {
      System.out.print(A[i] + ", ");
    }
    System.out.println(A[A.length-1]);
  }
}
