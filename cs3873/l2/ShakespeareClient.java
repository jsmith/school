import java.net.*;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.DataOutputStream;

public class ShakespeareClient {
  private static int PORT = 6789;

  public static void main(String[] args) {
    String file = "./PoemShakespeare.txt";
    try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
      System.out.println("Connecting to " + args[0] + ":" + ShakespeareClient.PORT + " over TCP!");
      Socket socket = new Socket(args[0], ShakespeareClient.PORT);
      DataOutputStream out = new DataOutputStream(socket.getOutputStream());
      BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));

      System.out.println("Starting to send poem from " + file);
      String line;
      while ((line = reader.readLine()) != null) {
        // note that '\n' is removed during parsing
        out.writeBytes(line + "\n");
      }
      out.writeBytes("Done\n");
		  String bye = in.readLine();

      in.close();
      out.close();
      socket.close();

      if (bye.equals("Bye")) {
        System.out.println("The server said Bye :)");
      } else {
        System.out.println("The server is rude! It said: " + bye);
      }
    } catch (FileNotFoundException e) {
      System.out.println("Unable to read poem from " + file);
    } catch (IOException e) {
      System.out.println("Unknown error: " + e);
    }
  }
}