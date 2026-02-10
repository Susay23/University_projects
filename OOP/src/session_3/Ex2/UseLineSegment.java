package Ex2;

public class UseLineSegment {
    public static void main(String[] args) {
        // Create 2 points A(2, 5), B(20, 35). Create a line segment AB
        Point A = new Point(2, 5);
        Point B = new Point(20, 35);
        LineSegment AB = new LineSegment(A, B);
        System.out.println("AB: ");
        AB.display();
        System.out.println("Length Of AB = " + AB.length());
        // Create any line segment CD. Enter and display values for that line segment
        // CD.
        LineSegment CD = new LineSegment();
        System.out.println("Enter details for Segment CD:");
        CD.input();
        System.out.println("\n Segment CD info: ");
        CD.display();
        System.out.println("Length Of CD = " + CD.length());
    }
}