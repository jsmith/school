import java.util.Scanner;

public class CS4015DP1Java {
    public static char read() {
        Scanner scanner = new Scanner(System.in);
        return scanner.next().charAt(0);
    }

    public static void main(String[] args) {    
        char c;
        do {
            System.out.println("Options");
            System.out.println("'0' to select HH:MM:SS format");
            System.out.println("'1' to select MS format");
            System.out.print("> ");

            c = CS4015DP1Java.read();
            System.out.println();
        } while(c != '0' && c != '1');

        Clock clock;
        if (c == '0') {
            clock = new HourMinuteSecondClock();
        } else {
            clock = new MilliClock();
        }
        
        while (true) {
            System.out.println("Options");
            System.out.println("'t' print the elapsed time in the desired format");
            System.out.println("'r' reset the elapsed time to 0");
            System.out.println("'q' quit the program");
            System.out.print("> ");
            
            switch (CS4015DP1Java.read()) {
                case 't':
                    System.out.printf("The elapsed time is -> %s\n", clock.elapsedTime());
                    break;
                case 'r':
                    System.out.print("Are you sure you want to reset the elapsed time [y/n]? ");
                    char confirmation = CS4015DP1Java.read();

                    if (confirmation == 'y') {
                        System.out.println("Resetting...");
                        clock.reset();
                    }
                    break;
                case 'q':
                    System.out.println("Bye\n");
                    return;
                default:
                    System.out.println("Invalid option");
                    break;
            }
            System.out.println();
        }
    }
}