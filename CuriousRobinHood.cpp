#include <vector>
#include <cstdio>
#include <cmath>

class FenwickTree {
 public:
  int N;
  std::vector<int> T;

  // Initiate tree, internal tree is 1-based indexing, but external isn't
  FenwickTree(int N) {
    this->N = N;
    T = std::vector<int>(N + 1, 0);
  }

  void add(int r, int v) {
    r++;
    while (r <= N) {
      this->T[r] += v;
      r = r + (r & -r);
    }
  }

  // Sums [0 - r] inclusive
  int sum(int r) {
    int ret = 0;
    r++;
    while (r > 0) {
      ret += this->T[r];
      r = r - (r & -r);
    }
    return ret;
  }

  // Sums [l - r] inclusive
  int sumRange(int l, int r) {
    return this->sum(r) - this->sum(l - 1);
  }
};

int main() {
  int T;
  scanf("%d", &T);
  int testCase = 1;
  while (T--) {
    printf("Case %d:\n", testCase++);
    int N, Q;
    int next;
    scanf("%d %d", &N, &Q);
    FenwickTree t = FenwickTree(N);
    for (int n=0; n<N; n++) {
      scanf("%d", &next);
      t.add(n, next);
    }
    int type, i, v, j;
    for (int q=0; q<Q; q++) {
      scanf("%d", &type);
      if (type == 1) {
        scanf("%d", &i);
        int removed = t.sumRange(i, i);
        printf("%d\n", removed);
        t.add(i, -removed);
      } else if (type == 2) {
        scanf("%d %d", &i, &v);
        t.add(i, v);
      } else {
        scanf("%d %d", &i, &j);
        printf("%d\n", t.sumRange(i, j));
      }
    }
  }
  return 0;
}
