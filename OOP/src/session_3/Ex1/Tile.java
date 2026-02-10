package Ex1;

import java.util.Scanner;

public class Tile {
    public String code, color;
    public int numOfTile, length, width;
    public long price;

    // default
    public Tile() {
    }

    // with parameters
    public Tile(String code, String color, int numOfTile, int length, int width, long price) {
        this.code = code;
        this.color = color;
        this.numOfTile = numOfTile;
        this.length = length;
        this.width = width;
        this.price = price;
    }

    // copy
    public Tile(Tile others) {
        this.code = others.code;
        this.color = others.color;
        this.numOfTile = others.numOfTile;
        this.length = others.length;
        this.width = others.width;
        this.price = others.price;
    }

    // input
    public void input() {
        Scanner sc = new Scanner(System.in);
        System.out.println("code: ");
        this.code = sc.nextLine();
        System.out.println("Color: ");
        this.color = sc.nextLine();
        System.out.println("Num of Tile: ");
        this.numOfTile = sc.nextInt();
        System.out.println("Length: (cm)");
        this.length = sc.nextInt();
        System.out.println("Width: (cm)");
        this.width = sc.nextInt();
        System.out.println("Price: ");
        this.price = sc.nextLong();
    }

    // display
    public void display() {
        System.out.println("Code: " + this.code);
        System.out.println("Color: " + this.color);
        System.out.println("Num of Tile: " + this.numOfTile);
        System.out.println("Length: " + this.length);
        System.out.println("Width: " + this.width);
        System.out.println("Price: " + this.price);
    }

    // retail price method we have value if we buy 1 tile the price is more than 20%
    // this mean price is 120%(1.2)
    public float retailPrice() {
        return (float) ((float) (price / numOfTile) * 1.2);
    }

    // max area
    public float maxArea() {
        return (float) ((float) (length * width) * numOfTile);
    }

    // area with L*w value
    public int numTile(int L, int W) {
        return (int) (L * W) / (int) (length * width);
    }

    // lowest cost
    public float lowestCost() {
        return (float) price / maxArea();
    }
}
