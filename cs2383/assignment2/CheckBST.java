public class CheckBST {
  public static void main(String[] args) {
    Node[] nodes1 = new Node[8];
    nodes1[1] = new Node(1, 13, 0, 2, 3);
    nodes1[2] = new Node(2, 10, 1, 0, 4);
    nodes1[3] = new Node(3, 19, 1, 5, 0);
    nodes1[4] = new Node(4, 12, 2, 0, 0);
    nodes1[5] = new Node(5, 15, 3, 6, 7);
    nodes1[6] = new Node(6, 14, 5, 0, 0);
    nodes1[7] = new Node(7, 18, 5, 0, 0);

    Node[] nodes2 = new Node[8];
    nodes2[1] = new Node(1, 12, 0, 2, 3);
    nodes2[2] = new Node(2, 10, 1, 0, 4);
    nodes2[3] = new Node(3, 19, 1, 5, 0);
    nodes2[4] = new Node(4, 13, 2, 0, 0);
    nodes2[5] = new Node(5, 15, 3, 6, 7);
    nodes2[6] = new Node(6, 14, 5, 0, 0);
    nodes2[7] = new Node(7, 18, 5, 0, 0);

    System.out.println("Min value of Trees: " + minValue(nodes1, nodes1[1]));
    System.out.println("Max value of Trees: " + maxValue(nodes1, nodes1[1]));

    System.out.println("Tree one is a BST: " + isBST(nodes1, nodes1[1]));
    System.out.println("Tree two is a BST: " + isBST(nodes2, nodes2[1]));
  }

  public static boolean isBST(Node[] nodes, Node root) {
    if(root == null) return true;

    Node left = nodes[root.left];
    if(root.data < maxValue(nodes, left)) return false;
    if(!isBST(nodes, left)) return false;

    Node right = nodes[root.right];
    if(root.data > minValue(nodes, right)) return false;
    if(!isBST(nodes, right)) return false;

    return true;
  }

  public static int minValue(Node[] nodes, Node root) {
    if(root == null) return 100000000;

    int minRight = minValue(nodes, nodes[root.right]);
    int minLeft = minValue(nodes, nodes[root.left]);
    if(minLeft < minRight && minLeft < root.data) {
      return minLeft;
    } else if(minRight < root.data) {
      return minRight;
    } else {
      return root.data;
    }
  }

  public static int maxValue(Node[] nodes, Node root) {
    if(root == null) return -100000000;

    int maxRight = maxValue(nodes, nodes[root.right]);
    int maxLeft = maxValue(nodes, nodes[root.left]);
    if(maxLeft > maxRight && maxLeft > root.data) {
      return maxLeft;
    } else if(maxRight > root.data) {
      return maxRight;
    } else {
      return root.data;
    }
  }
}
