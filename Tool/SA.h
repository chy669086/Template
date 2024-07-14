#include <cmath>
#include <string>
#include <vector>

#define all(a) a.begin(), a.end()

struct SA {
  std::string s;
  int n, m, p;
  std::vector<int> rk, sa;

  SA(std::string &s) {
    int n = s.size();
    this->s = " " + s;
    init(n);
  }

  void init(int n) {
    this->n = n;
    m = 128;
    rk.assign(2 * n + 5, 0);
    sa.assign(2 * n + 5, 0);
    std::vector<int> cnt(std::max(n + 5, m + 1));
    for (int i = 1; i <= n; i++) {
      cnt[rk[i] = s[i]]++;
    }
    for (int i = 1; i <= m; i++) {
      cnt[i] += cnt[i - 1];
    }
    for (int i = n; i >= 1; i--) {
      sa[cnt[rk[i]]] = i;
      cnt[rk[i]]--;
    }

    std::vector<int> id(2 * n + 5);
    std::vector<int> oldrk(2 * n + 5);
    for (int w = 1;; w <<= 1, m = p) {
      int cur = 0;
      for (int i = n - w + 1; i <= n; i++) {
        id[++cur] = i;
      }
      for (int i = 1; i <= n; i++) {
        if (sa[i] > w) {
          id[++cur] = sa[i] - w;
        }
      }

      std::fill(all(cnt), 0);
      for (int i = 1; i <= n; i++) {
        cnt[rk[i]]++;
      }
      for (int i = 1; i <= m; i++) {
        cnt[i] += cnt[i - 1];
      }
      for (int i = n; i >= 1; i--) {
        sa[cnt[rk[id[i]]]] = id[i];
        cnt[rk[id[i]]]--;
      }

      p = 0;
      std::copy(all(rk), oldrk.begin());
      for (int i = 1; i <= n; i++) {
        if (oldrk[sa[i]] == oldrk[sa[i - 1]] &&
            oldrk[sa[i] + w] == oldrk[sa[i - 1] + w]) {
          rk[sa[i]] = p;
        } else {
          rk[sa[i]] = ++p;
        }
      }

      if (p == n) {
        break;
      }
    }
  }
};