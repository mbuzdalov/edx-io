import mooc.*;

public class Test {
    public static void main(String[] args) {
        try (EdxIO io = EdxIO.create()) {
            int n = io.nextInt();
            long sum = 0;
            int badCount = 0;
            for (int i = 0; i < n; ++i) {
                int value = io.nextIntOr(-1);
                if (value == -1) {
                    value = io.nextIntOr(0);
                    if (value == 0) {
                        io.skipNonWhiteSpace();
                        ++badCount;
                    } else {
                        sum += value;
                    }
                } else {
                    sum += value;
                }
            }
            io.println(sum + " " + badCount);
        }
    }
}
