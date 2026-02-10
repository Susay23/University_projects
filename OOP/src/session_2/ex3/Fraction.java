package session_2.ex3;
import java.util.Scanner;

public class Fraction { // Default construtor: Fraction();
    public int num, denom;

    public Fraction() {
        this.num = 0;
        this.denom = 1;
    }

    public Fraction(int t, int m) { // Constructor with 2 parameters: Fraction(int t , int m);
        this.num = t;
        this.denom = m;
    }

    public void input() { // The function enters the value for a fraction. If the entered fraction has a
                          // denominator = 0, then it requires re-entry.
        do {
            Scanner sc = new Scanner(System.in);
            System.out.println("num = ");
            this.num = sc.nextInt();
            System.out.println("denom = ");
            this.denom = sc.nextInt();
        } while (this.denom == 0);
    }

    public void display() { // Displays the fraction in the form num/denom or -num/denom. void display();
        if (this.num == 0) {
            System.out.println(" = 0");
        } else if (this.denom != 1) {
            System.out.println(" = " + this.num + "/" + this.denom + "\n");
        } else {
            System.out.println(" = " + this.num + "\n");
        }
    }

    public void inverse() { // Inverse fraction (changes the value of a fraction) void inverse();
        int temp = 0;
        temp = this.num;
        this.num = this.denom;
        this.denom = temp;
    }

    public Fraction inverseValue() { // Returns the inverse of a fraction (the fraction remains the same) Fraction
                                     // inverseValue();
        Fraction res = new Fraction(this.num, this.denom);
        res.num = this.denom;
        res.denom = this.num;
        return res;
    }

    public float realValues() { // Calculates the real value (1/2 has the real value 0.5) float realValue();
        return (float) this.num / this.denom;
    }

    public boolean greater(Fraction a) { // Compare a fraction is greater than fraction a boolean greater(Fraction a);
                                         // (a/b > c/d => a*d > c*b);
        return (this.num * a.denom) > (this.denom * a.num);
    }

    public int GCD(int a, int b) { 
        a = Math.abs(a);
        b = Math.abs(b);
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    public void simplify() {
        if (this.num == 0) {
            this.denom = 1;
            return;
        }
        int common = GCD(this.num, this.denom);
        this.num = this.num / common;
        this.denom = this.denom / common;
        if (this.denom < 0) {
            this.num = -this.num;
            this.denom = -this.denom;
        }
    }

    public Fraction add(Fraction a) { // add fraction
        Fraction res = new Fraction();
        if (this.denom == a.denom) {
            res.num = this.num + a.num;
            res.denom = this.denom;
        } else {
            res.num = (this.num * a.denom) + (a.num * this.denom);
            res.denom = (this.denom) * a.denom;
        }
        res.simplify();
        return res;
    }

    public Fraction add(int n) { // add integer
        Fraction res = new Fraction();
        res.num = this.num + n * this.denom;
        res.denom = this.denom;
        res.simplify();
        return res;
    }


}