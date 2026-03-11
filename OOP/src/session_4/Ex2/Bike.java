package session_4.Ex2;

import java.util.Scanner;

public class Bike extends Vehicle{
    public int numGear;
    public void input(){
        super.input();
        Scanner sc = new Scanner(System.in);
        System.out.print(" Number of gears: ");
        numGear = sc.nextInt();
        sc.nextLine();
    }
    
    public void display(){
        super.display();
        System.out.println(" Number of gears: " + numGear);
    }
    
    public double costPerKm(){
        return 0;
    }
}
