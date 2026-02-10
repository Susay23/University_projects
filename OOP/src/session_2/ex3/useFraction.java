package session_2.ex3;
import java.util.Scanner;

public class useFraction {
    public static void main(String[] args) {
        Fraction x = new Fraction(); // create x,y
        Fraction y = new Fraction();
        x.input();
        y.input();
        x.inverseValue().display();
        Fraction sum = x.add(y);
        sum.display();

        int n; // input n
        Scanner sc = new Scanner(System.in);
        n = sc.nextInt();
        Fraction[] list = new Fraction[n];
        for (int i = 0; i < n; i++) {
            list[i] = new Fraction();
            list[i].input();
        }

        Fraction Totalsum = new Fraction(); // total
        for (int i = 0; i < n; i++) {
            Totalsum = Totalsum.add(list[i]);
        }
        System.out.println("Total: ");
        Totalsum.display();

        Fraction greater = new Fraction(); // max value
        Fraction maxF = list[0];
        for (int i = 0; i < n; i++) {
            if (list[i].greater(maxF)) {
                maxF = list[i];
            }
        }
        System.out.println("Max Value: ");
        maxF.display();

        for (int i = 0; i < n - 1; i++) { // insertion sort
            for (int j = i + 1; j < n; j++) {
                if (list[j].greater(list[i]) == false) {
                    Fraction temp = list[i];
                    list[i] = list[j];
                    list[j] = temp;
                }
            }
        }
        System.out.println("After sort: ");
        for (int i = 0; i < list.length; i++) {
            list[i].display();
        }
    }
}
