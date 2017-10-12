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

    public static void generateReadingIntsOr() throws IOException {
        System.out.print("Generating 02-reading-ints-or... ");
        int n = 20000000;
        long sum = 0;
        int badCount = 0;
        Random random = new Random(236642346);
        try (PrintWriter inf = new PrintWriter("02-reading-ints-or/input.txt")) {
            inf.println(n);
            for (int i = 0; i < n; ++i) {
                if (random.nextInt(10) == 0) {
                    switch (random.nextInt(8)) {
                        case 0: inf.print(Integer.MAX_VALUE); sum += Integer.MAX_VALUE; break;
                        case 1: inf.print(Integer.MIN_VALUE); sum += Integer.MIN_VALUE; break;
                        case 2: inf.print(Integer.MAX_VALUE + 1L); ++badCount; break;
                        case 3: inf.print(Integer.MIN_VALUE - 1L); ++badCount; break;
                        case 4: inf.print("Badstring"); ++badCount; break;
                        default: inf.print(random.nextLong()); ++badCount; break;
                    }
                } else {
                    int newValue = random.nextInt();
                    inf.print(newValue);
                    sum += newValue;
                }
                if ((i + 1) % 1000 != 0) {
                    inf.print(" ");
                } else {
                    inf.println();
                }
            }
        }
        try (PrintWriter ans = new PrintWriter("02-reading-ints-or/answer.txt")) {
            ans.println(sum + " " + badCount);
        }
        System.out.println("done!");
    }

    public static void main(String[] args) throws IOException {
        generateReadingInts();
        generateReadingIntsOr();
    }
}
