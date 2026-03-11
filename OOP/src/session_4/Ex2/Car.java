package session_4.Ex2;

import java.util.Scanner;

public class Car extends Vehicle {
    public int numSeats;
    public void input(){
        super.input();
        Scanner sc = new Scanner(System.in);
        System.out.println(" number of Seats: ");
        numSeats = sc.nextInt();
        sc.nextLine();
    }

    public void display(){
        super.display();
        System.out.println(" Num Seats: " + numSeats);
    }

    public double costPerKm(){
        return 5000;
    }
}
