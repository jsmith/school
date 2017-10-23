/**
 * The class represents a stack object
 * @author Jacob Smith
 */
public class Stack {
  /**
   * The integer array used to mock a stack
   */
  private int[] stack;

  /**
   * The Stack constructor
   */
  public Stack() {
    stack_init();
  }

  /**
   * Initializes the stack to being empty
   */
  public void stack_init() {
    stack = new int[]{};
  }

  /**
   * Checks to see if the stack is empty
   * @return Wether or not the stack is empty
   */
  public boolean empty() {
    return stack.length == 0;
  }

  /**
   * Pushes a value onto the stack
   * @param int val the value to push onto the stack
   */
  public void push(int val) {
    int[] temp = new int[stack.length+1];
    System.arraycopy(stack, 0, temp, 0, stack.length);
    stack = temp;
    stack[stack.length-1] = val;
  }

  /**
   * Pops a value off of the stack
   */
  public void pop() {
    if(this.empty()) throw new EmptyException();
    int[] temp = new int[stack.length-1];
    System.arraycopy(stack, 0, temp, 0, temp.length);
    stack = temp;
  }

  /**
   * Returns the value of the top of the stack
   * @return the value at the top of the stack
   */
  public int top() {
    if(this.empty()) throw new EmptyException();
    return stack[stack.length-1];
  }
}
