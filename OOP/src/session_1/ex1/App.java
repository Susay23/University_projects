package practical_session_01.ex1;
import java.util.Scanner;

public class App{
    public static void main(String[] args){
        System.out.println("Please typing, quit by pressing 'q'");

        Scanner sc = new Scanner(System.in);
        while(true){
            char nextChar = sc.next().charAt(0);

            if (nextChar == 'q'){
                sc.close();
                break;
            }
        }
    }
}