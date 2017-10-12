import java.io.*;
import java.util.*;

public class Generator {
    public static void generateReadingInts() throws IOException {
        System.out.print("Generating 01-reading-ints... ");
        int n = 20000000;
        long sum = 0;
        Random random = new Random(487365843);
        try (PrintWriter inf = new PrintWriter("01-reading-ints/input.txt")) {
            inf.println(n);
            for (int i = 0; i < n; ++i) {
                int newValue = random.nextInt();
                if (i == 748) {
                    newValue = Integer.MAX_VALUE;
                } else if (i == 8352) {
                    newValue = Integer.MIN_VALUE;
                }
                inf.print(newValue);
                sum += newValue;
                if ((i + 1) % 1000 != 0) {
                    inf.print(" ");
                } else {
                    inf.println();
                }
            }
        }
        try (PrintWriter ans = new PrintWriter("01-reading-ints/answer.txt")) {
            ans.println(sum);
        }
        System.out.println("done!");
    }

    public static void generateReadingLongs() throws IOException {
        System.out.print("Generating 02-reading-longs... ");
        int n = 20000000;
        long sum = 0;
        Random random = new Random(487365843);
        try (PrintWriter inf = new PrintWriter("02-reading-longs/input.txt")) {
            inf.println(n);
            for (int i = 0; i < n; ++i) {
                long newValue = random.nextLong();
                if (i == 25338) {
                    newValue = Long.MAX_VALUE;
                } else if (i == 57472) {
                    newValue = Long.MIN_VALUE;
                }
                inf.print(newValue);
                sum ^= newValue;
                if ((i + 1) % 1000 != 0) {
                    inf.print(" ");
                } else {
                    inf.println();
                }
            }
        }
        try (PrintWriter ans = new PrintWriter("02-reading-longs/answer.txt")) {
            ans.println(sum);
        }
        System.out.println("done!");
    }

    public static void generateWritingInts() throws IOException {
        System.out.print("Generating 03-writing-ints... ");
        int n = 20000000;
        int a = 7823875, b = 761246357, c = 81387543;
        int v0 = 723528643, v1 = -235745654;
        try (PrintWriter inf = new PrintWriter("03-writing-ints/input.txt")) {
            inf.println(n);
            inf.println(a + " " + b + " " + c);
            inf.println(v0 + " " + v1);
        }
        try (PrintWriter ans = new PrintWriter("03-writing-ints/answer.txt")) {
            ans.print(v0 + " " + v1);
            for (int i = 2; i < n; ++i) {
                int v2 = a * v0 + b * v1 + c;
                ans.print(" " + v2);
                v0 = v1;
                v1 = v2;
            }
            ans.println();
        }
        System.out.println("done!");
    }

    public static void generateWritingLongs() throws IOException {
        System.out.print("Generating 04-writing-longs... ");
        int n = 20000000;
        long a = 11357823875L, b = -3576124635755L, c = 81387543;
        long v0 = 723528643189235L, v1 = -235745654346322L;
        try (PrintWriter inf = new PrintWriter("04-writing-longs/input.txt")) {
            inf.println(n);
            inf.println(a + " " + b + " " + c);
            inf.println(v0 + " " + v1);
        }
        try (PrintWriter ans = new PrintWriter("04-writing-longs/answer.txt")) {
            ans.print(v0 + " " + v1);
            for (int i = 2; i < n; ++i) {
                long v2 = a * v0 + b * v1 + c;
                ans.print(" " + v2);
                v0 = v1;
                v1 = v2;
            }
            ans.println();
        }
        System.out.println("done!");
    }

    public static void main(String[] args) throws IOException {
        generateReadingInts();
        generateReadingLongs();
        generateWritingInts();
        generateWritingLongs();
    }
}
