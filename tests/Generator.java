import java.io.*;
import java.util.*;

public class Generator {
    private static final int n = 10000000;

    public static void generateReadingInts(String root, long sourceDate) throws IOException {
        System.out.print("Generating " + root + "... ");
        File inFile = new File(root, "input.txt");
        File ansFile = new File(root, "answer.txt");
        if (inFile.lastModified() > sourceDate && ansFile.lastModified() > sourceDate) {
            System.out.println("already exist.");
            return;
        }
        long sum = 0;
        Random random = new Random(487365843);
        try (PrintWriter inf = new PrintWriter(inFile)) {
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
        try (PrintWriter ans = new PrintWriter(ansFile)) {
            ans.println(sum);
        }
        System.out.println("done!");
    }

    public static void generateReadingLongs(String root, long sourceDate) throws IOException {
        System.out.print("Generating " + root + "... ");
        File inFile = new File(root, "input.txt");
        File ansFile = new File(root, "answer.txt");
        if (inFile.lastModified() > sourceDate && ansFile.lastModified() > sourceDate) {
            System.out.println("already exist.");
            return;
        }
        long sum = 0;
        Random random = new Random(487365843);
        try (PrintWriter inf = new PrintWriter(inFile)) {
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
        try (PrintWriter ans = new PrintWriter(ansFile)) {
            ans.println(sum);
        }
        System.out.println("done!");
    }

    public static void generateReadingDoubles(String root, long sourceDate) throws IOException {
        System.out.print("Generating " + root + "... ");
        File inFile = new File(root, "input.txt");
        File ansFile = new File(root, "answer.txt");
        if (inFile.lastModified() > sourceDate && ansFile.lastModified() > sourceDate) {
            System.out.println("already exist.");
            return;
        }
        double sum = 0;
        Random random = new Random(487365843);
        try (PrintWriter inf = new PrintWriter(inFile)) {
            inf.println(n);
            for (int i = 0; i < n; ++i) {
                double newValue = random.nextDouble() * (random.nextBoolean() ? 1000000 : 1);
                if (random.nextBoolean()) {
                    newValue *= -1;
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
        try (PrintWriter ans = new PrintWriter(ansFile)) {
            ans.println(sum);
        }
        System.out.println("done!");
    }

    public static void generateWritingInts(String root, long sourceDate) throws IOException {
        System.out.print("Generating " + root + "... ");
        File inFile = new File(root, "input.txt");
        File ansFile = new File(root, "answer.txt");
        if (inFile.lastModified() > sourceDate && ansFile.lastModified() > sourceDate) {
            System.out.println("already exist.");
            return;
        }
        int a = 7823875, b = 761246357, c = 81387543;
        int v0 = 723528643, v1 = Integer.MIN_VALUE;
        try (PrintWriter inf = new PrintWriter(inFile)) {
            inf.println(n);
            inf.println(a + " " + b + " " + c);
            inf.println(v0 + " " + v1);
        }
        try (PrintWriter ans = new PrintWriter(ansFile)) {
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

    public static void generateWritingLongs(String root, long sourceDate) throws IOException {
        System.out.print("Generating " + root + "... ");
        File inFile = new File(root, "input.txt");
        File ansFile = new File(root, "answer.txt");
        if (inFile.lastModified() > sourceDate && ansFile.lastModified() > sourceDate) {
            System.out.println("already exist.");
            return;
        }
        long a = 11357823875L, b = -3576124635755L, c = 81387543;
        long v0 = 723528643189235L, v1 = Long.MIN_VALUE;
        try (PrintWriter inf = new PrintWriter(inFile)) {
            inf.println(n);
            inf.println(a + " " + b + " " + c);
            inf.println(v0 + " " + v1);
        }
        try (PrintWriter ans = new PrintWriter(ansFile)) {
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

    public static void generateWritingDoubles(String root, long sourceDate) throws IOException {
        System.out.print("Generating " + root + "... ");
        File inFile = new File(root, "input.txt");
        File ansFile = new File(root, "answer.txt");
        if (inFile.lastModified() > sourceDate && ansFile.lastModified() > sourceDate) {
            System.out.println("already exist.");
            return;
        }
        long a = 11357823875L, b = -3576124635755L, c = 81387543;
        long v0 = 723528643189235L, v1 = -235745654346322L;
        try (PrintWriter inf = new PrintWriter(inFile)) {
            inf.println(n);
            inf.println(a + " " + b + " " + c);
            inf.println(v0 + " " + v1);
        }
        try (PrintWriter ans = new PrintWriter(ansFile)) {
            ans.print(v0 + " " + v1);
            for (int i = 2; i < n; ++i) {
                long v2 = a * v0 + b * v1 + c;
                ans.print(" " + (v2 < 0 ? -Math.sqrt(-v2) : Math.sqrt(v2)));
                v0 = v1;
                v1 = v2;
            }
            ans.println();
        }
        System.out.println("done!");
    }

    public static void main(String[] args) throws IOException {
        long sourceDate = new File("Generator.java").lastModified();
        generateReadingInts("01-reading-ints", sourceDate);
        generateReadingLongs("02-reading-longs", sourceDate);
        generateWritingInts("03-writing-ints", sourceDate);
        generateWritingLongs("04-writing-longs", sourceDate);
        generateReadingDoubles("05-reading-doubles", sourceDate);
        generateWritingDoubles("06-writing-doubles", sourceDate);
    }
}
