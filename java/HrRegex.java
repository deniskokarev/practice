/* https://www.hackerrank.com/challenges/java-regex/problem */
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.Scanner;

class HrRegex {

    public static void main(String[] args){
        Scanner in = new Scanner(System.in);
        while(in.hasNext()){
            String IP = in.next();
            System.out.println(IP.matches(new MyRegex().pattern));
        }

    }
}

//Write your code here

class MyRegex {
	public String pattern;
	MyRegex() {
		pattern = "^([01]|[01]\\d|[01]\\d\\d|2|2\\d|2[0-4]\\d|25[0-5]|[3-9]|[3-9]\\d)\\.([01]|[01]\\d|[01]\\d\\d|2|2\\d|2[0-4]\\d|25[0-5]|[3-9]|[3-9]\\d)\\.([01]|[01]\\d|[01]\\d\\d|2|2\\d|2[0-4]\\d|25[0-5]|[3-9]|[3-9]\\d)\\.([01]|[01]\\d|[01]\\d\\d|2|2\\d|2[0-4]\\d|25[0-5]|[3-9]|[3-9]\\d)$";
	}
}
