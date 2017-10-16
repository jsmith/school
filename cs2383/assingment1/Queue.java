public class Queue {
  private int[] queue;

  public Queue() {
    queue_init();
  }

  public void queue_init() {
    queue = new int[0];
  }

  public boolean empty() {
    return queue.length == 0;
  }

  public void enqueue(int val) {
    int[] temp = new int[queue.length+1];
    System.arraycopy(queue, 0, temp, 0, queue.length);
    queue = temp;
    queue[queue.length-1] = val;
  }

  public void dequeue() {
    int[] temp = new int[queue.length-1];
    System.arraycopy(queue, 1, temp, 0, temp.length);
    queue = temp;
  }

  public int front() {
    return queue[0];
  }
}
