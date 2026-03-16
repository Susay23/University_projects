package session_5;

import java.util.Scanner;

public class Details {
    int number;
    long unitprice;
    Invoice Invoice;
    product product;

    public Details() {
        number = 0;
        unitprice = 0;
    }

    public Details(int number, long unitprice, Invoice Invoice, product product){
        this.number = number;
        this.unitprice = unitprice;
        this.Invoice = Invoice;
        this.product = product;
    }

    // input

    public void input(){
        Scanner sc = new Scanner(System.in);
        System.out.println("input number");
        this.number = sc.nextInt();
        System.out.println("input unit price");
        this.unitprice = sc.nextInt();
        sc.nextLine();
    }

    // display

    public void display(){
        System.out.println("Number: " + number);
        System.out.println("Unit Price: "+ unitprice);
    }
}
