/**
 * This file contains an algorithm to check if a String contains valid brackets
 * @author Jacob Smith
 */
public class CheckBrackets {
  public static void main(String[] args) {
    String test1 = "(()())()";
    String test2 = "(";
    String test3 = "())";
    assert(validBrackets(test1));
    assert(!validBrackets(test2));
    assert(!validBrackets(test3));
  }

  /**
   * This is an algorithm that checks if a string has valid brackets
   * @param  String brackets      the brackets string
   * @return        whether or not the string contains valid brackets
   */
  public static boolean validBrackets(String brackets) {
    int open = 0;
    for(int i = 0; i < brackets.length(); i++) {
      char c = brackets.charAt(i);
      if(c == '(') {
        open++;
      } else if(c == ')') {
        open--;
      } else {
        continue;
      }
      if(open < 0) {
        return false;
      }
    }
    if(open == 0) {
      return true;
    } else {
      return false;
    }
  }
}
