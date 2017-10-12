import java.io.*;
import java.util.*;

public class Reference {
    public static void main(String[] args) throws IOException {
        try (BufferedReader in = new BufferedReader(new FileReader("input.txt"));
             PrintWriter out = new PrintWriter("output.txt")) {
            int n = Integer.parseInt(in.readLine());
            long sum = 0;
            int badCount = 0;
            StringTokenizer st = new StringTokenizer(in.readLine());
            for (int i = 0; i < n; ++i) {
                while (!st.hasMoreTokens()) {
                    st = new StringTokenizer(in.readLine());
                }
                String token = st.nextToken();
                try {
                    sum += Integer.parseInt(token);
                } catch (NumberFormatException ex) {
                    ++badCount;
                }
            }
            out.println(sum + " " + badCount);
        }
    }
}
