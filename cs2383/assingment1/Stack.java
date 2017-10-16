public class Stack {
  private int[] stack;

  public Stack() {
    stack_init();
  }

  public void stack_init() {
    stack = new int[]{};
  }

  public boolean empty() {
    return stack.length == 0;
  }

  public void push(int val) {
    int[] temp = new int[stack.length+1];
    System.arraycopy(stack, 0, temp, 0, stack.length);
    stack = temp;
    stack[stack.length-1] = val;
  }

  public void pop() {
    int[] temp = new int[stack.length-1];
    System.arraycopy(stack, 0, temp, 0, temp.length);
    stack = temp;
  }

  public int top() {
    return stack[stack.length-1];
  }
}
