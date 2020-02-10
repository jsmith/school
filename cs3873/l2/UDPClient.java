import java.io.*;
import java.net.*;

class UDPClient {
	public static void main(String args[]) throws Exception {

		BufferedReader inFromUser = new BufferedReader(new InputStreamReader(
				System.in));

		DatagramSocket clientSocket = new DatagramSocket();
		InetAddress IPAddress = InetAddress.getByName(args[0]);

		System.out.println("Attemping to connect to " + IPAddress
				+ " via UDP port 9876");

		byte[] sendData = new byte[1024];
		byte[] receiveData = new byte[1024];

		System.out.print("Enter message: ");
		String sentence = inFromUser.readLine();
		sendData = sentence.getBytes();
		DatagramPacket sendPacket = new DatagramPacket(sendData,
				sendData.length, IPAddress, 9876);

		System.out.println("Sending data of " + sendData.length
				+ " bytes to server.");

		clientSocket.send(sendPacket);

		System.out.println("Done. Waiting for return packet");

		DatagramPacket receivePacket = new DatagramPacket(receiveData,
				receiveData.length);

		clientSocket.receive(receivePacket);

		InetAddress returnIPAddress = receivePacket.getAddress();
		int port = receivePacket.getPort();
		System.out.println("From server at: " + returnIPAddress + ":" + port);

		String modifiedSentence = new String(receivePacket.getData());

		System.out.println("RETURNED MESSAGE FROM SERVER: " + modifiedSentence);
		clientSocket.close();
	}
}
