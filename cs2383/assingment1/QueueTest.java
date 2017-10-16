public class QueueTest {
  public static void main (String[] args) {
    Queue queue = new Queue();
    queue.queue_init();
    int[] input = new int[]{0, 78, 456, -1, 0, -1, 60, 33, 0, -1, 0, -1, 0, -1, 0};
    for(int i : input) {
      if(i > 0) {
        queue.enqueue(i);
        continue;
      }
      if(queue.empty()) {
        System.out.println("Error - Queue is empty"); //error checking is implemented here
        continue;
      }
      if (i == 0) {
         queue.dequeue();
      } else { // i < 0
        System.out.println(queue.front());
      }
    }
  }
}
