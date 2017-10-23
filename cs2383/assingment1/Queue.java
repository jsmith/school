/**
 * The class represents a queue
 */
public class Queue {
  /**
   * The array used to represent a queue
   */
  private int[] queue;

  /**
   * The queue contructor
   */
  public Queue() {
    queue_init();
  }

  /**
   * Initializes the queue to it's empty state
   */
  public void queue_init() {
    queue = new int[0];
  }

  /**
   * Checks to see if the queue is empty
   * @return Whether or not the queue is empty
   */
  public boolean empty() {
    return queue.length == 0;
  }

  /**
   * Enqueues an object
   * @param int val the value to enqueue
   */
  public void enqueue(int val) {
    int[] temp = new int[queue.length+1];
    System.arraycopy(queue, 0, temp, 0, queue.length);
    queue = temp;
    queue[queue.length-1] = val;
  }

  /**
   * Removes the item from the front of the queue
   */
  public void dequeue() {
    if(this.empty()) throw new EmptyException();
    int[] temp = new int[queue.length-1];
    System.arraycopy(queue, 1, temp, 0, temp.length);
    queue = temp;
  }

  /**
   * Checks what value is at the front of the queue
   * @return the value at the front of the queue
   */
  public int front() {
    if(this.empty()) throw new EmptyException();
    return queue[0];
  }
}
