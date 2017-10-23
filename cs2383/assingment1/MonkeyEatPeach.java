/**
 * This file contains the monkey eat peach recursive algorithm
 * @author Jacob Smith
 */
public class MonkeyEatPeach {
  public static void main(String[] args) {
    int peachesLeft = 1;
    int day = 6;
    int peaches = eat(day, peachesLeft);
    System.out.print("There were " + peaches + " peaches on Monday!");
  }
  /**
   * The monkey eat peach recursive function
   * @param  int day      the day that the monkey had that amount of peaches left
   * @param  int peachesLeft   the amount of peaches left
   * @return     the initial amount of peaches
   */
  public static int eat(int day, int peachesLeft) {
    if(day == 0) {
      return peachesLeft;
    }
    peachesLeft = (peachesLeft+1)*2;
    return eat(day-1, peachesLeft);
  }
}
