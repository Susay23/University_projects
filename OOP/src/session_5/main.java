package session_5;

import java.util.Scanner;

public class main {
    public static void main(String[] args) {
        // Enter and display a list containing n invoices, where n is entered from the keyboard
        
        Scanner sc = new Scanner(System.in);
        int n;
        System.out.println("input amount of invoices");
        n = Integer.parseInt(sc.nextLine());
        
        Invoice[] invoices = new Invoice[n];
        for(int i = 0; i<n; i++){
            invoices[i] = new Invoice();
            invoices[i].input();
        }

        //List all invoices having the total amount less than 1 million VND

        for (Invoice invoice : invoices){
            if(invoice.total()<1000000){
                invoice.display();
                System.out.println();
            }
        }

        

        //List all customers’names whose invoices were issued on 20/05/2025

        System.out.println("all customers’names whose invoices were issued on 20/05/2025");
        for(Invoice invoice : invoices){
            if(invoice.billdate.isDate(20,5,2025)){
                invoice.display();
                System.out.println();
            }
        }
    }
}
