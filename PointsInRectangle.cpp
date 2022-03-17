#include <vector>
#include <cstdio>
#include <cmath>
#define vi_t  std::vector<int>
#define vvi_t std::vector<vi_t>
// https://lightoj.com/problem/points-in-rectangle
class FenwickTree2D {
 public:
  int M, N;
  vvi_t A, T;

  FenwickTree2D(int M, int N) { 
      this->M = M;
      this->N = N;
      vvi_t T = vvi_t(M+1, vi_t(N + 1, 0));
      vvi_t A = vvi_t(M+1, vi_t(N + 1, 0));
  }

  void addPoint(int x, int y) {
    if (A[x][y] != 0)
        return;
    A[x][y] = 1;
    for (int i = x; i <= this->M; i = i | (i + 1)) {
        for (int j = y; j <= this->N; j = j | (j + 1))
            T[i][j] += 1;
    }
  }

  // Sums [0 - r] inclusive
  int query(int x, int y) {
    int ret = 0;
    for (int xp = x; xp >= 0; xp = (xp & (xp + 1)) - 1)
        for (int yp = y; yp >= 0; yp = (yp & (yp + 1)) - 1)
            ret += T[xp][yp];
    return ret;
  }

  // Sums [l - r] inclusive
  int countPoints(int x0, int y0, int x1, int y1) {
    return query(x1, y1) - query(x0 - 1, y1) - query(x1, y0 - 1) + query(x0 - 1, y0 - 1);
  }

  void clear(void) {
      T = vvi_t(M + 1, vi_t(N + 1, 0));
      A = vvi_t(M + 1, vi_t(N + 1, 0));
  }
};

int main() {
    int T, Q, type, x0, y0, x1, y1;
    scanf("%d", &T);
    FenwickTree2D f = FenwickTree2D(1001, 1001);
    for (int t = 1; t <= T; t++) {
        f.clear();
        printf("Case %d:\n", t);
        scanf("%d", &Q);
        while (Q--) {
            scanf("%d", &type);
            if (type == 0) {
                scanf("%d %d", &x0, &y0);
                f.addPoint(x0, y0);
            } else {
                scanf("%d %d %d %d", &x0, &y0, &x1, &y1);
                printf("%d\n", f.countPoints(x0, y0, x1, y1));
            }
        }
    }
}
