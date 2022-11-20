package dk.foobar;

public class Solution_3_2 {
    static void assertMe(Boolean c, String err) throws IllegalStateException {
        if (!c)
            throw new IllegalStateException(err);
    }
    static protected class R {
        long n, d;

        // b must be pos
        private static long gcd(long a, long b) {
            a = Math.abs(a); // make a pos
            while (b != 0) {
                long temp = b;
                b = a % b;
                a = temp;
            }
            return a;
        }

        // b must be pos
        private static long lcm(long a, long b) {
            long g = gcd(a, b);
            return a / g * b;
        }

        public R(long n, long d) {
            this.n = n;
            this.d = d;
        }

        public R(long n) {
            this(n, 1);
        }

        public R() {
            this(0, 1);
        }

        R simplify() {
            long g = gcd(n, d);
            n /= g;
            d /= g;
            return this;
        }

        public R plus(R o) {
            long nd = lcm(d, o.d);
            return new R(n * (nd / d) + o.n * (nd / o.d), nd);
        }

        public R minus(R o) {
            long nd = lcm(d, o.d);
            return new R(n * (nd / d) - o.n * (nd / o.d), nd);
        }

        public R mul(R o) {
            return new R(n * o.n, d * o.d).simplify();
        }

        public R div(R o) {
            int sign = Long.signum(n) * Long.signum(o.n);
            long nn = Math.abs(n);
            long on = Math.abs(o.n);
            return new R(nn * o.d * sign, d * on).simplify();
        }

        public R abs() {
            return new R(Math.abs(n), d);
        }

        public Boolean equals(int i) {
            return n == i && d == 1 || (n == 0 && i == 0);
        }

        public Boolean equals(R o) {
            return n == o.n && d == o.d;
        }

        public String toString() {
            return Long.toString(n) + "/" + Long.toString(d);
            //return Double.toString(((double) n) / d);
        }
    }

    static R r(int i) {
        return new R(i);
    }

    static R r(int n, int d) {
        return new R(n, d);
    }

    static class Mat {
        R mm[][];
        int rows, cols;

        public Mat(R[][] mm) {
            this.mm = mm;
            rows = mm.length;
            cols = mm[0].length;
        }

        R[][] cloneMat() {
            R clMat[][] = new R[rows][cols];
            for (int i = 0; i < rows; i++)
                System.arraycopy(mm[i], 0, clMat[i], 0, cols);
            return clMat;
        }

        public R det() {
            int sz = rows;
            R dmat[][] = cloneMat();
            R tmp[] = new R[sz];
            R det = r(1);
            for (int i = 0; i < sz; i++) {
                int k = i;
                for (int j = i + 1; j < sz; j++) {
                    R d = dmat[j][i].abs().minus(dmat[k][i].abs());
                    if (d.n > 0) // abs(mm[j][i]) > abs(mm[k][i]))
                        k = j;
                }
                if (dmat[k][i].equals(0)) {
                    det = r(0);
                    break;
                }
                //swap(mm[i], mm[k]);
                System.arraycopy(dmat[i], 0, tmp, 0, sz);
                System.arraycopy(dmat[k], 0, dmat[i], 0, sz);
                System.arraycopy(tmp, 0, dmat[k], 0, sz);
                if (i != k)
                    det = det.mul(r(-1));
                det = det.mul(dmat[i][i]);
                for (int j = i + 1; j < sz; j++)
                    dmat[i][j] = dmat[i][j].div(dmat[i][i]);
                for (int j = 0; j < sz; ++j)
                    if (j != i && !dmat[j][i].equals(0))
                        for (int k2 = i + 1; k2 < sz; k2++)
                            dmat[j][k2] = dmat[j][k2].minus(dmat[i][k2].mul(dmat[j][i]));
            }
            return det;
        }

        Mat mat_minor(int r, int c) {
            R[][] res = new R[rows - 1][cols - 1];
            for (int di = 0, si = 0; si < rows; si++) {
                if (si == r)
                    continue;
                for (int dj = 0, sj = 0; sj < cols; sj++) {
                    if (sj == c)
                        continue;
                    res[di][dj] = mm[si][sj];
                    dj++;
                }
                di++;
            }
            return new Mat(res);
        }

        Mat adj() {
            R a[][] = new R[rows][rows];
            for (int r = 0; r < rows; r++) {
                int sign = ((r & 1) == 0) ? 1 : -1;
                for (int c = 0; c < rows; c++) {
                    Mat mr = mat_minor(r, c);
                    if (false && c == 0 && r == 2) {
                        System.out.println("Mat minor [2][0]");
                        for (int i=0; i<3; i++) {
                            for (int j=0; j<3; j++)
                                System.out.print(mr.mm[i][j] + " ");
                            System.out.println("\n");
                        }
                        System.out.println("sign=" + sign);
                        System.out.println("det=" + mr.det());
                        System.out.println("out=" + mr.det().mul(r(sign)));
                    }
                    a[c][r] = mr.det().mul(r(sign));
                    sign *= -1;
                }
            }
            return new Mat(a);
        }

        Mat div(R o) {
            R clMat[][] = new R[rows][cols];
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                    clMat[i][j] = mm[i][j].div(o);
            return new Mat(clMat);
        }

        Mat mul(Mat o) {
            R res[][] = new R[rows][o.cols];
            for (int r = 0; r < rows; r++) {
                for (int c = 0; c < o.cols; c++) {
                    R s = new R(0);
                    for (int j = 0; j < cols; j++)
                        s = s.plus(mm[r][j].mul(o.mm[j][c]));
                    res[r][c] = s;
                }
            }
            return new Mat(res);
        }

        Mat inv() {
            R d = det();
            Mat res = adj();
            return res.div(d);
        }

        public String toString() {
            String o = "";
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++)
                    o += mm[i][j] + " ";
                o += "\n";
            }
            return o;
        }
    }
//    public static int[] solution(int[][] m) {
//    }

    static Mat mkRMat(int[][] imat) {
        int rows = imat.length;
        int cols = imat[0].length;
        R mm[][] = new R[rows][cols];
        for (int i=0; i<rows; i++)
            for (int j=0; j<cols; j++)
                mm[i][j] = r(imat[i][j]);
        return new Mat(mm);
    }

    public static void main(String args[]) {
        int mat0[][] = {{1}};
        int mat1[][] = {
                {2, -2},
                {3, 5},
        };
        int mat2[][] = {
                {1, 0, 2, -3},
                {3, 0, 0, 5},
                {2, 1, 4, -3},
                {1, 0, 5, 0}
        };
        int mat3[][] = {
                {0, 0, 1},
                {0, 1, 0},
                {1, 0, 0}
        };
        int mat5[][] = {
                {5, -2, 2, 7},
                {1, 0, 0, 3},
                {-3, 1, 5, 0},
                {3, -1, -9, 4}
        };
        int mat6[][] = {
                {0, 2, -3},
                {0, 0, 5},
                {1, 4, -3},
        };
        Mat mm0 = mkRMat(mat0);
        System.out.println("d0=" + mm0.det());
        Mat mm1 = mkRMat(mat1);
        System.out.println("d1=" + mm1.det());

        Mat mm2 = mkRMat(mat2);
        R d2 = mm2.det();
        R expD2 = r(60);
        System.out.println("d2=" + d2);
        assertMe(d2.equals(expD2), "wrong det for matrix 2");

        Mat mm3 = mkRMat(mat3);
        R d3 = mm3.det();
        R expD3 = r(-1);
        System.out.println("d3=" + d3);
        assertMe(d3.equals(expD3), "wrong det for matrix 3");

        Mat mm6 = mkRMat(mat6);
        System.out.println(mm6);
        R d6 = mm6.det();
        R expD6 = r(10);
        System.out.println("d6=" + d6);
        assertMe(d6.equals(expD6), "wrong det for matrix 6");

        System.out.println(mm2);
        System.out.println(mm2.inv());
        System.out.println(mm2.mul(mm2.inv()));
        //System.out.println(mm2.adj());

        Mat mm5 = mkRMat(mat5);
        System.out.println(mm5);
        //System.out.println(mm5.adj());
        //System.out.println(mm5.inv());
        System.out.println(mm5.mul(mm5.inv()));
    }
}