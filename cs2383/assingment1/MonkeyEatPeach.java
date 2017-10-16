public class MonkeyEatPeach {
  public static void main(String[] args) {
    int peachesLeft = 1;
    int daysLeft = 6;
    int peaches = eat(daysLeft, peachesLeft);
    System.out.print("There were " + peaches + " peaches on Monday!");
  }
  public static int eat(int daysLeft, int peachesLeft) {
    if(daysLeft == 0) {
      return peachesLeft;
    }
    peachesLeft = (peachesLeft+1)*2;
    return eat(daysLeft-1, peachesLeft);
  }
}
