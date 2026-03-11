package session_4.Ex2;

import java.util.Scanner;

abstract class Vehicle {
    public String vehicleName, color;
    public int producedYear;
    public Vehicle(){
        vehicleName = "";
        color = "";
        producedYear = 0;
    }

    public void input(){
        Scanner sc = new Scanner(System.in);
        System.out.println(" Vehicle Name: ");
        vehicleName = sc.nextLine();
        System.out.println(" Vehicle Color: ");
        color = sc.nextLine();
        System.out.println(" Vehicle Produced Year: ");
        producedYear = sc.nextInt();
        sc.nextLine();
    }

    public abstract double costPerKm();
    public double costCalculate(int Km){
        return costPerKm() * Km;
    }


    public void display(){
        System.out.println(" Name: " + vehicleName);
        System.out.println(" Color: " + color);
        System.out.println(" Vehicle Produced Year: " + producedYear);
        System.out.printf(" Cost/Km: %.0f VND\n", costPerKm());
    }

    public String getVehicleName(){
        return vehicleName;
    }
}