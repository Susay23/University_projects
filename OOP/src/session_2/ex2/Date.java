package session_2.ex2;
import java.util.Scanner;

public class Date {
    public int day, month, year;

    public Date() { // Default constructor
        day = 1;
        month = 1;
        year = 2026;
    }

    public Date(int day, int month, int year) { // Constructor with 3 parameters
        this.day = day;
        this.month = month;
        this.year = year;
    }

    public void display() { // display date
        System.out.println("day: " + day + " month: " + month + " year " + year);
    }

    public boolean isleapyear(int year) {
        return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
    }

    public int maxday() {
        switch (month) {
            case 4,6,9,11:
                return 30;
            case 2:
                return isleapyear(year) ? 29 : 28;
            default:
                return 31;
        }
    }

    public boolean hople(){
        if(year<1||month<1||month > 12) return false;
        if(day<1||day>maxday()) return false;
        return true;
    }
    public void input(){ 
        Scanner sc = new Scanner(System.in);
        do{
        System.out.println("input day month year");
        this.day = sc.nextInt();
        this.month = sc.nextInt();
        this.year = sc.nextInt();
        if(!hople()) System.out.println("ERROR!!!!!");
        }while(!hople());
    }
    public Date nextDate(){
        Date res = new Date(this.day,this.month,this.year);
        res.day++;
        if(res.day >= res.maxday()){
            res.day = 1;
            res.month +=1;
            if(res.month>12){
                res.month = 1;
                res.year ++;
            }
        }
        return res;
    }
    public Date add(int n){
        Date res = new Date(this.day, this.month,this.year);
        for(int i = 0; i<n;i++){
            res = res.nextDate();
        }
        return res;
    }
}