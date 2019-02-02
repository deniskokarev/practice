import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Scanner;

public class HrSHA256 {

	public static void main(String[] args) {
		try (Scanner sc = new Scanner(System.in)) {
			MessageDigest md = MessageDigest.getInstance("SHA-256");
			String s = sc.nextLine();
			byte bb[] = md.digest(s.getBytes());
			for (byte b:bb) {
				System.out.print(String.format("%02x", b));
			}
			System.out.println();
		} catch (NoSuchAlgorithmException e) {
			e.printStackTrace();
		}
	}
}
