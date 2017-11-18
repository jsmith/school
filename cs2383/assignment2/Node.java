public class Node {
  int id;
  int data;
  int parent;
  int left;
  int right;

  public Node(int id, int data, int parent, int left, int right) {
    this.id = id;
    this.data = data;
    this.parent = parent;
    this.left = left;
    this.right = right;
  }
}
