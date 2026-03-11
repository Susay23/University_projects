package session_4.Ex2;

import java.util.Scanner;

public class main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter number of vehicles: ");
        int n = sc.nextInt();
        sc.nextLine();
        Vehicle[] ds = new Vehicle[n];
        for(int i = 0; i < n; i++){
            System.out.println("\n--- Vehicle " + (i + 1) + " ---");
            System.out.println("Type: 1-Car, 2-Moto, 3-Bike");
            int type = sc.nextInt();
            sc.nextLine();


            switch (type) {
                case 1: ds[i] = new Car(); break;
                case 2: ds[i] = new Moto(); break;
                case 3: ds[i] = new Bike(); break;
                default: ds[i] = new Car();
            }

            ds[i].input();
        }


        for(int i = 0; i < n; i ++){
            ds[i].display();
            System.out.println();
        }


        for (int i = 0; i < n; i++) {
            System.out.printf("%s: %.0f VND\n", ds[i].getVehicleName(),
           ds[i].costCalculate(100));
           }


           Vehicle minCost = null;
           for (int i = 0; i < n; i++) {
            if (!(ds[i] instanceof Bike)) {
            if (minCost == null || ds[i].costCalculate(100) <
           minCost.costCalculate(100)) {
            minCost = ds[i];
            }
            }
           }
           if (minCost != null) {
            System.out.println("\n--- Loswest cost per 100km ---");
            minCost.display();
            System.out.printf("Cost: %.0f VND\n", minCost.costCalculate(100));
           }


           int numOto = 0, numMoto = 0, numBike = 0;
            for (int i = 0; i < n; i++) {
            if (ds[i] instanceof Car) numOto++;
            else if (ds[i] instanceof Moto) numMoto++;
            else if (ds[i] instanceof Bike) numBike++;
            }
            System.out.println("Car : " + numOto);
            System.out.println("Moto: " + numMoto);
            System.out.println("Bike: " + numBike);
        }
}
