
#include <random>
#include <vector>

using std::vector;
using ull = unsigned long long;

namespace Tool {

class StringHash {
public:
  StringHash(int n = -1) : n(n) {
    std::default_random_engine e;
    m1 = e() % MULT_SIZE;
    m2 = e() % MULT_SIZE;
    if (n > 0) {
      // 决定 O(1) 查询还是 O(logn) 查询
      init_mult();
    }
  }

  std::pair<ull, ull> get_hash(const std::string &s) {
    ull res1 = 0, res2 = 0;
    for (auto c : s) {
      res1 = (res1 * MULT[m1] + c) % MOD[0];
      res2 = (res2 * MULT[m2] + c) % MOD[1];
    }
    return {res1, res2};
  }

  vector<std::pair<ull, ull>> get_hash_set(const std::string &s) {
    ull res1 = 0, res2 = 0;
    vector<std::pair<ull, ull>> ans;
    for (auto c : s) {
      res1 = (res1 * MULT[m1] + c) % MOD[0];
      res2 = (res2 * MULT[m2] + c) % MOD[1];
      ans.emplace_back(res1, res2);
    }
    return ans;
  }

  void add_hash_set(vector<std::pair<ull, ull>> &a, char c) {
    std::pair<ull, ull> tmp = {(a.back().first * MULT[m1] + c) % MOD[0],
                               (a.back().second * MULT[m2] + c) % MOD[1]};
    a.emplace_back(std::move(tmp));
  }

  bool equal(const vector<std::pair<ull, ull>> &a1, int l1, int r1,
             const vector<std::pair<ull, ull>> &a2, int l2, int r2) {

    std::pair<ull, ull> p1 = get_pair(a1, l1, r1), p2 = get_pair(a2, l2, r2);

    return p1 == p2;
  }

  std::pair<ull, ull> get_pair(const vector<std::pair<ull, ull>> &a1, int l1,
                               int r1) {
    // 很乱，我也不知道我在写什么
    return {(a1[r1].first + MOD[0] -
             (l1 == 0 ? 0
                      : a1[l1 - 1].first * pow(MULT[m1], r1 + 1 - l1, MOD[0]) %
                          MOD[0])) %
              MOD[0],
            (a1[r1].second + MOD[1] -
             (l1 == 0 ? 0
                      : a1[l1 - 1].second * pow(MULT[m2], r1 + 1 - l1, MOD[1]) %
                          MOD[1])) %
              MOD[1]};
  }

private:
  const int MULT_SIZE = 9;
  const ull MOD[2]{ull(1e9 + 7), 998244353};
  const ull MULT[9] = {131, 157, 293, 1019, 1471, 1667, 10037, 13331, 16183};

  int n;
  int m1, m2;
  vector<std::pair<ull, ull>> mult;

  void init_mult() {
    mult.resize(n + 1);
    mult[0] = {1, 1};
    for (int i = 1; i <= n; i++) {
      auto &[x, y] = mult[i];
      auto &[px, py] = mult[i - 1];
      x = px * MULT[m1] % MOD[0];
      y = py * MULT[m2] % MOD[1];
    }
  }

  ull pow(ull x, ull y, ull mod) {
    if (this->n > 0) {
      if (mod == MOD[0]) {
        return mult[y].first;
      } else {
        return mult[y].second;
      }
    } else {
      ull res = 1;
      while (y) {
        if (y & 1) {
          (res *= x) %= mod;
        }
        x = x * x % mod;
        y >>= 1;
      }
      return res;
    }
  }
};
} // namespace Tool