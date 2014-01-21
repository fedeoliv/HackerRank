import java.io.*;

public class MatrixTracing {
    private static long MODULO = 1000000007;
    private static long movement;
    
    private static long getInverse(long l) {
        if(l == 0) return 1;
        if(l == 1) return movement;
        
        long inv = getInverse(l/2);
        
        inv *= inv;
        inv %= MODULO;
        
        if((l&1) == 1) {
        	inv *= movement;
        	inv %= MODULO;
        }
        
        return inv;
    }
    
	public static void main(String[] args) {
		try {
			BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
			int T = Integer.parseInt(in.readLine());

			long movements[] = new long[2000002];
			long inv[] = new long[2000002];
			
			movements[0] = 1;
			
			for (int i = 1; i <= 2000001; i++) {
				movements[i] = movements[i - 1] * i;

				movements[i] %= MODULO;
				movement = movements[i];
				inv[i] = getInverse(MODULO - 2);
			}

			while(T-- > 0) {
				String[] strNumAry = in.readLine().split(" ");

				int n = Integer.parseInt(strNumAry[0]);
				int m = Integer.parseInt(strNumAry[1]);

				int tot = n + m - 2;

				if ((n == 1) || (m == 1))
					System.out.println(1);
				else {
					long ways = (movements[tot] * inv[n - 1]) % MODULO;
					ways = (ways * inv[m - 1]) % MODULO;
					
					System.out.println(ways);
				}
			}
			
			in.close();
		} catch (IOException i) {
			i.printStackTrace();
		}
	}
}
