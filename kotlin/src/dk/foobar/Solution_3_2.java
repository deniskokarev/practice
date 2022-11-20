package dk.foobar;

import java.math.BigInteger;

public class Solution_3_2 {
    static void assertMe(Boolean c, String err) throws IllegalStateException {
        if (!c)
            throw new IllegalStateException(err);
    }

    static protected class R {
        BigInteger n, d;

        private static BigInteger lcm(BigInteger a, BigInteger b) {
            BigInteger g = a.gcd(b);
            return a.divide(g).multiply(b);
        }

        public R(BigInteger n, BigInteger d) {
            this.n = n;
            this.d = d;
        }

        public R(long n, long d) {
            this.n = new BigInteger(Long.toString(n));
            this.d = new BigInteger(Long.toString(d));
        }

        public R(long n) {
            this(n, 1);
        }

        public R() {
            this(0, 1);
        }

        R simplify() {
            BigInteger g = n.gcd(d);
            n = n.divide(g);
            d = d.divide(g);
            return this;
        }

        public R plus(R o) {
            BigInteger nd = lcm(d, o.d);
            return new R(n.multiply(nd.divide(d)).add(o.n.multiply(nd.divide(o.d))), nd);
        }

        public R minus(R o) {
            BigInteger nd = lcm(d, o.d);
            return new R(n.multiply(nd.divide(d)).subtract(o.n.multiply(nd.divide(o.d))), nd);
        }

        public R mul(R o) {
            return new R(n.multiply(o.n), d.multiply(o.d)).simplify();
        }

        public R div(R o) {
            int sign = n.signum() * o.n.signum();
            BigInteger nn = n.abs();
            BigInteger on = o.n.abs();
            BigInteger m = nn.multiply(o.d);
            if (sign < 0)
                m = m.negate();
            return new R(m, d.multiply(on)).simplify();
        }

        public R abs() {
            return new R(n.abs(), d);
        }

        public boolean isZero() {
            int i = n.intValue();
            return i == 0;
        }

        public boolean isGreaterThanZero() {
            return n.signum() > 0;
        }

        public boolean equals(R o) {
            return n.equals(o.n) && d.equals(o.d);
        }

        public String toString() {
            return n + "/" + d;
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

        // naive method rules, Gauss overflows quickly in R
        public R det() {
            int sz = rows;
            if (sz == 1) {
                return mm[0][0];
            } else {
                int sign = 1;
                R det = new R(0);
                for (int c=0; c<sz; c++) {
                    Mat minor = mat_minor(0, c);
                    det = det.plus(r(sign).mul(mm[0][c].mul(minor.det())));
                    sign *= -1;
                }
                return det;
            }
        }

        public R gauss_det() {
            int sz = rows;
            R dmat[][] = cloneMat();
            R det = r(1);
            for (int i = 0; i < sz; i++) {
                int k = i;
                for (int j = i + 1; j < sz; j++) {
                    R d = dmat[j][i].abs().minus(dmat[k][i].abs());
                    if (d.isGreaterThanZero()) // abs(mm[j][i]) > abs(mm[k][i]))
                        k = j;
                }
                if (dmat[k][i].equals(0)) {
                    det = r(0);
                    break;
                }
                //swap(mm[i], mm[k]);
                R tmp[] = dmat[i];
                dmat[i] = dmat[k];
                dmat[k] = tmp;
                if (i != k)
                    det = det.mul(r(-1));
                det = det.mul(dmat[i][i]);
                for (int j = i + 1; j < sz; j++)
                    dmat[i][j] = dmat[i][j].div(dmat[i][i]);
                for (int j = 0; j < sz; ++j)
                    if (j != i && !dmat[j][i].isZero())
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
            R a[][];
            if (rows < 2) {
                a = new R[1][1];
                a[0][0] = r(1);
            } else {
                a = new R[rows][rows];
                for (int r = 0; r < rows; r++) {
                    int sign = ((r & 1) == 0) ? 1 : -1;
                    for (int c = 0; c < rows; c++) {
                        Mat mr = mat_minor(r, c);
                        a[c][r] = mr.det().mul(r(sign));
                        sign *= -1;
                    }
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
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                mm[i][j] = r(imat[i][j]);
        return new Mat(mm);
    }

    static Mat randMat(int sz) {
        R mm[][] = new R[sz][sz];
        for (int i = 0; i < sz; i++) {
            for (int j = 0; j < sz; j++) {
                int n = (int) (Math.random() * 8) - 4;
                int d = (int) (Math.random() * 7) + 1;
                mm[i][j] = new R(n, d);
            }
        }
        return new Mat(mm);
    }

    static boolean isEye(Mat mat) {
        int sz = mat.rows;
        boolean ans = true;
        for (int i = 0; i < sz; i++)
            for (int j = 0; j < sz; j++)
                ans &= (i == j && mat.mm[i][j].n.equals(mat.mm[i][j].d)) || (i != j && mat.mm[i][j].isZero());
        return ans;
    }

    static void checkInv(Mat mat) {
        Mat inv = mat.inv();
        Mat res = mat.mul(inv);
        boolean isCorrect = isEye(res);
        if (!isCorrect) {
            System.err.println("=== Mat ===");
            System.err.println(mat);
            System.err.println("=== Inv ===");
            System.err.println(inv);
            assertMe(false, "incorrect inverse!");
        }
    }

    public static void main(String args[]) {
        int mat0[][] = {{3}};
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

        checkInv(mkRMat(mat0));
        checkInv(mkRMat(mat1));
        checkInv(mkRMat(mat2));
        checkInv(mkRMat(mat3));
        checkInv(mkRMat(mat5));
        checkInv(mkRMat(mat6));
        R mat7r[][] = {
                {r(-3, 2), r(-2, 7), r(-4, 5), r(0, 3), r(-3 / 2)},
                {r(-2, 5), r(-2, 2), r(-1, 7), r(-1, 2), r(3, 2)},
                {r(-3, 6), r(1, 5), r(-2, 7), r(1, 2), r(3, 1)},
                {r(2, 7), r(3, 1), r(-1, 1), r(3, 1), r(0, 6)},
                {r(-2, 5), r(0, 3), r(-3, 3), r(3, 7), r(3, 7)},
        };
        Mat mm7 = new Mat(mat7r);
        System.out.println(mm7);
        System.out.println(mm7.det());
        System.out.println(mm7.adj());
        checkInv(mm7);
        for (int sz = 7; sz < 8; sz++) {
            for (int rep = 0; rep < 1; rep++) {
                Mat m = randMat(sz);
                R d = m.det();
                if (!d.equals(0)) // ignore det=0
                    checkInv(m);
            }
        }
    }
}