package Ex1;

import java.util.Scanner;

public class useTile {
    public static void main(String[] args) {
        // Enter and display a list of n types of floor tiles
        int n;
        Scanner sc = new Scanner(System.in);
        System.out.println(" types of floor tiles = ");
        n = sc.nextInt();
        Tile[] List = new Tile[n];
        for (int i = 0; i < n; i++) {
            List[i] = new Tile();
            List[i].input();
        }
        for (int i = 0; i < n; i++) {
            System.out.println("type: " + (i + 1));
            List[i].display();
        }
        // Display the tile with the lowest cost (price/max area).
        Tile temp = List[0];
        for (int i = 0; i < n; i++) {
            if (List[i].lowestCost() < temp.lowestCost()) {
                temp = List[i];
            }
        }
        System.out.println("the Title have Lowest price is ");
        temp.display();
        // Calculate the cost of buying tiles when we cover an area with a width of
        // 500cm and a length of 1500cm
        // when we use each type of tile in the above list
        System.out.println(
                "The cost of buying tiles when we cover an area with a width of 500cm and a length of 1500cm is ");
        for (int i = 0; i < n; i++) {
            System.out.println("Type: " + (i + 1));
            int numTile = List[i].numTile(1500, 500);
            float PricePack = ((float) numTile / (float) List[i].numOfTile) * (float) List[i].price;
            System.out.println(numTile);
            System.out.println("the Price of type " + (i + 1) + " is: " + PricePack);
        }
    }
}