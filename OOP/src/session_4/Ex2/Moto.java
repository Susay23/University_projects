package session_4.Ex2;

import java.util.Scanner;

public class Moto extends Vehicle{
    public int cylinderCapacity; 
    public void input(){
        super.input();
        Scanner sc = new Scanner(System.in);
        System.out.print(" Cylinder capacity (cc): ");
        cylinderCapacity = sc.nextInt();
        sc.nextLine();
    }

    public void display(){
        super.display();
        System.out.println(" Capacity: " + cylinderCapacity + "cc");
    }

    public double costPerKm(){
        return 2000;
    }
}
