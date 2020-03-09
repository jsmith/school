import java.io.*; 
import java.net.*; 

class TestClient {
  public static void main(String argv[]) throws Exception {
    String sentence; 
    String modifiedSentence; 
    BufferedReader inFromUser = new BufferedReader (new InputStreamReader(System.in));
    Socket clientSocket = new Socket ("localhost", 6789);

    DataOutputStream outToServer = new DataOutputStream (clientSocket.getOutputStream()); 
    BufferedReader inFromServer = new BufferedReader(new InputStreamReader(clientSocket.getInputStream())); 
    sentence = inFromServer.readLine(); 
    outToServer.writeBytes (sentence + '\n'); 
    modifiedSentence = inFromServer.readLine(); 
    System.out.println("FROM SERVER: " + modifiedSentence); 
    clientSocket.close();
  }
}