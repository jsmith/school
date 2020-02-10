/**
 * I warrant that this is my own work.
 * Jacob Smith (3534295)
 */ 

import java.net.*;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.DataOutputStream;

public class ShakespeareClient {
  private static int PORT = 6789;

  /**
   * The goal of this method is to open up a TCP socket connection with a server and transfer a Shakespeare poem over 
   * the connection. Once finished, it prints out the total # of bytes sent and the time spent to transfer the contents
   * of the file.
   */
  public static void main(String[] args) {
    String file = "./PoemShakespeare.txt";
    try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
      System.out.println("Connecting to " + args[0] + ":" + ShakespeareClient.PORT + " over TCP!");
      Socket socket = new Socket(args[0], ShakespeareClient.PORT);
      DataOutputStream out = new DataOutputStream(socket.getOutputStream());
      BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));

      int lineSeparatorBytes = System.getProperty("line.separator").getBytes().length;

      System.out.println("Starting to send poem from " + file);
      int bytes = 0;
      String line;
      long start = System.currentTimeMillis();
      while ((line = reader.readLine()) != null) {
        // note that '\n' is removed during parsing
        out.writeBytes(line + "\n");
        bytes += line.getBytes().length + lineSeparatorBytes;
      }
      long end = System.currentTimeMillis();

      out.writeBytes("Done\n");
		  String bye = in.readLine();

      in.close();
      out.close();
      socket.close();

      if (!bye.equals("Bye")) {
        System.out.println("The didn't say Bye :( It said: " + bye);
        return;
      }

      System.out.println("The file transfer contained " + bytes + " bytes and took " + (end - start) + "ms");
    } catch (FileNotFoundException e) {
      System.out.println("Unable to read poem from " + file);
    } catch (IOException e) {
      System.out.println("Unknown error: " + e);
    }
  }
}