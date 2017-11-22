public class TreeOrder {
  public static void main(String[] args) {
    Node[] nodes = new Node[8];
    nodes[1] = new Node(1, 12, 0, 2, 3);
    nodes[2] = new Node(2, 10, 1, 0, 4);
    nodes[3] = new Node(3, 19, 1, 5, 0);
    nodes[4] = new Node(4, 13, 2, 0, 0);
    nodes[5] = new Node(5, 15, 3, 6, 7);
    nodes[6] = new Node(6, 14, 5, 0, 0);
    nodes[7] = new Node(7, 18, 5, 0, 0);

    System.out.println("--- Pre Order ---");
    preOrder(nodes[1], nodes);

    System.out.println("\n--- In Order ---");
    inOrder(nodes[1], nodes);

    System.out.println("\n--- Post Order ---");
    postOrder(nodes[1], nodes);
    //postOrder(nodes[1], nodes);
  }

  public static void preOrder(Node root, Node[] nodes) {
    if(root != null) {
      System.out.print(root.data + " ");
      preOrder(nodes[root.left], nodes);
      preOrder(nodes[root.right], nodes);
    }
  }

  public static void inOrder(Node root, Node[] nodes) {
    if(root != null) {
      inOrder(nodes[root.left], nodes);
      System.out.print(root.data + " ");
      inOrder(nodes[root.right], nodes);
    }
  }

  public static void postOrder(Node root, Node[] nodes) {
    if(root != null) {
      postOrder(nodes[root.left], nodes);
      postOrder(nodes[root.right], nodes);
      System.out.print(root.data + " ");
    }
  }
}
