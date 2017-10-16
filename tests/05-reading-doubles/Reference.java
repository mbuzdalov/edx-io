import java.io.*;
import java.util.*;

public class Reference {
    public static void main(String[] args) throws IOException {
        try (BufferedReader in = new BufferedReader(new FileReader("input.txt"));
             PrintWriter out = new PrintWriter("output.txt")) {
            int n = Integer.parseInt(in.readLine());
            double sum = 0;
            StringTokenizer st = new StringTokenizer(in.readLine());

            for (int i = 0; i < n; ++i) {
                while (!st.hasMoreTokens()) {
                    st = new StringTokenizer(in.readLine());
                }
                sum += Double.parseDouble(st.nextToken());
            }
            out.println(sum);
        }
    }
}
