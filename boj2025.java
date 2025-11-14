import java.util.*;
import java.io.*;

public class boj2025 {
    static int n;
    static boolean[][] board;
    static List<int[]> result = new ArrayList<>();
    static final int[][] moves = {
        { 2,  1}, { 1,  2}, {-1,  2}, {-2,  1},
        {-2, -1}, {-1, -2}, { 1, -2}, { 2, -1}
    };

    static int eval(int x, int y) {
        if (board[x][y]) return Integer.MAX_VALUE;
        int cnt = 0;
        for (int[] mv : moves) {
            int nx = x + mv[0], ny = y + mv[1];
            if (nx >= 0 && nx < n && ny >= 0 && ny < n && !board[nx][ny]) {
                ++cnt;
            }
        }
        return cnt;
    }

    static boolean knightTour(int sx, int sy) {
        board  = new boolean[n][n];
        result.clear();

        int x = sx, y = sy;
        for (int i = 0; i < n * n; i++) {
            board[x][y] = true;
            result.add(new int[]{ x + 1, y + 1 });

            int bestDeg = Integer.MAX_VALUE;
            int nx = -1, ny = -1;

            for (int[] mv : moves) {
                int tx = x + mv[0], ty = y + mv[1];
                if (tx >= 0 && tx < n && ty >= 0 && ty < n && !board[tx][ty]) {
                    int d = eval(tx, ty);
                    Random ran = new Random();
                    if (d < bestDeg || (d == bestDeg && ran.nextInt(100) > 50)) {
                        bestDeg = d;
                        nx = tx;
                        ny = ty;
                    }
                }
            }

            x = nx;
            y = ny;
            if (x < 0 && i != n * n - 1) {
                return false;
            }
        }
        
        return true;
    }

    public static void main(String[] args) throws IOException{
    	BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        Scanner sc = new Scanner(System.in);
        n = sc.nextInt();
        int sx = sc.nextInt(), sy = sc.nextInt();
        sc.close();
        
        for(int i = 0; i<10; i++)
        	if(knightTour(sx - 1, sy - 1)) {
        		for (int[] p : result) {
        			bw.write(p[0] + " " + p[1] + "\n");
        		}
        		bw.close();
        		return;
        	}
        bw.write("-1 -1");
        bw.flush();
    }
}
