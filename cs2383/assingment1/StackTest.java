/**
 * This file tests the Stack.java file
 * @author Jacob Smith
 */
public class StackTest {
  public static void main (String[] args) {
    Stack stack = new Stack();
    stack.stack_init();
    int[] input = new int[]{0, 78, 456, -1, 0, -1, 60, 33, -1, 0, -1, 0, 0, -1, 0};
    for(int i : input) {
      if(i > 0) {
        stack.push(i);
        continue;
      }
      try {
        if (i == 0) {
           stack.pop();
        } else { // i < 0
          System.out.println(stack.top());
        }
      } catch(EmptyException e) {
        System.out.println("Error - Stack is empty");
      }
    }
  }
}
