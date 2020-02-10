import java.net.*;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.DataOutputStream;
import java.io.IOException;

public class ShakespeareServer {
  private static int PORT = 6789;

  public static void main(String[] args) throws Exception {
    System.out.println("Creating a server at localhost:" + ShakespeareServer.PORT);
    ServerSocket socket = new ServerSocket(ShakespeareServer.PORT);
    

		try {
      while (true) {
        System.out.println ("Waiting for connection...");
        Socket connection = socket.accept();
        System.out.println ("Connection successful!\n");

        BufferedReader in = new BufferedReader(new InputStreamReader(connection.getInputStream()));
        DataOutputStream out = new DataOutputStream(connection.getOutputStream());

        int lineSeparatorBytes = System.getProperty("line.separator").getBytes().length;

        long start = System.currentTimeMillis();
        int bytes = 0;
        String line;
        while ((line = in.readLine()) != null) {
          if (line.equals("Done")) {
            System.out.println("\nClient has finished sending the poem.");
            System.out.println("Sending \"Bye\" :)");
            out.writeBytes("Bye\n");
            break;
          }

          bytes += line.getBytes().length + lineSeparatorBytes;
          System.out.println(line);
        }
        long end = System.currentTimeMillis();

        out.close();
        in.close();
        connection.close();

        System.out.println("File transfer contained " + bytes + " bytes and took " + (end - start) + "ms");
      }
    } catch(IOException e) {
      System.out.println("Unknown error: " + e);
    } finally {
      socket.close();
    }
  }
}