package session_5;

import java.util.ArrayList;
import java.util.Scanner;

public class Invoice {
    Customer customer;
    Date billdate;
    ArrayList<Details> items = new ArrayList<>();
    product product;
    String inNo, billTo;

    public Invoice() {
        customer = new Customer();
        product = new product();
        inNo = "";
        billTo = "";
        billdate = new Date();        
    }

    public Invoice(Customer customer, product product, String inNo, String billTo, Date billdate, Details[] dsChiTiet, int soLuongMonHang){
        this.customer = customer;
        this.product = product;
        this.inNo = inNo;
        this.billTo = billTo;
        this.billdate = billdate;
    }

    // input invoice information
    public void input(){
        Scanner sc = new Scanner(System.in);
        System.out.println("input Customer");
        this.customer.input();
        System.out.println("input product");
        this.product.input();
        System.out.println("input bill date");
        this.billdate.input();

        sc.nextLine();

        System.out.println("input inNo");
        this.inNo = sc.nextLine();
        System.out.println("input billTo");
        this.billTo = sc.nextLine();

        int n;
        System.out.println("input amount of items");
        n = sc.nextInt();
        sc.nextLine();
        for(int i =0; i<n; i++){
            product I = new product();
            I.input();
            int number;
            number = sc.nextInt();
            Long prices;
            prices = sc.nextLong();
            Details details = new Details(number,prices,this,I);
            items.add(details);
        }

    }

    // display invoice information
    public void display(){
        System.out.println("inNo:" + inNo);
        System.out.println("billTo:" + billTo);
        System.out.println("Customer:");
        this.customer.display();
        System.out.println("product:");
        this.product.display();
        for(Details item : items){
            item.display();
        }
    }
}
