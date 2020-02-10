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

        String line;
        while ((line = in.readLine()) != null) {
          if (line.equals("Done")) {
            System.out.println("\nClient has finished sending the poem.");
            System.out.println("Sending \"Bye\" :)");
            out.writeBytes("Bye\n");
            break;
          }

          System.out.println(line);
        }

        out.close();
        in.close();
      }
    } catch(IOException e) {
      System.out.println("Unknown error: " + e);
    } finally {
      socket.close();
    }
  }
}