
namespace NTT {

constexpr i64 MOD = 998244353;
constexpr i64 G = 3;

std::vector<int> tax;
i64 inv;

constexpr i64 power(i64 x, i64 y) {
  i64 res = 1;
  while (y) {
    if (y & 1) {
      res = res * x % MOD;
    }
    x = x * x % MOD;
    y >>= 1;
  }
  return res;
}

void make_rev(int n) {
  inv = power(n, MOD - 2);
  tax.resize(n << 1);
  int d = n >> 1;
  int p = 0;
  tax[p++] = 0;
  tax[p++] = d;
  for (int w = 2; w <= n; w <<= 1) {
    d >>= 1;
    for (int p0 = 0; p0 < w; ++p0) {
      tax[p++] = tax[p0] | d;
    }
  }
}

void ntt(std::vector<i64> &a) {
  int n = a.size();
  for (int i = 1; i < n; i++) {
    if (i < tax[i]) {
      std::swap(a[i], a[tax[i]]);
    }
  }
  for (int len = 2, m = 1; len <= n; m = len, len <<= 1) {
    i64 W = power(G, (MOD - 1) / len);
    for (auto l = 0, r = len - 1; r <= n; l += len, r += len) {
      i64 w0 = 1;
      for (auto p = l, lim = l + m; p < lim; ++p) {
        i64 x = a[p];
        i64 y = w0 * a[p + m] % MOD;
        a[p] = x + y;
        if (a[p] >= MOD) {
          a[p] -= MOD;
        }
        a[p + m] = x - y;
        if (a[p + m] < 0) {
          a[p + m] += MOD;
        }
        w0 = W * w0 % MOD;
      }
    }
  }
}

void intt(std::vector<i64> &a) {
  ntt(a);
  std::reverse(a.begin() + 1, a.end());
  std::ranges::for_each(a, [](i64 &x) {
    x = x * inv % MOD;
  });
}

std::vector<i64> mult(const std::vector<i64> &a, const std::vector<i64> &b) {
  assert(a.size() == b.size());

  int n = a.size();
  std::vector<i64> c(n);

  for (int i = 0; i < n; i++) {
    c[i] = a[i] * b[i] % MOD;
  }
  return c;
}

void mult_self(std::vector<i64> &a, const std::vector<i64> &b) {
  assert(a.size() == b.size());

  int n = a.size();
  for (int i = 0; i < n; i++) {
    a[i] = a[i] * b[i] % MOD;
  }
}

} // namespace NTT