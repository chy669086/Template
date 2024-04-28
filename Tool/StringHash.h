
#include <cassert>
#include <random>
#include <vector>

using std::vector;
using ull = unsigned long long;

namespace Tool {

class StringHash {
public:
  StringHash(int n) : n(n) {
    assert(n > 0);
    std::default_random_engine e;
    m1 = MULT[e() % MULT_SIZE];
    do {
      m2 = MULT[e() % MULT_SIZE];
    } while (m1 == m2);
    init_mult();
  }

  std::pair<ull, ull> get_hash(const std::string &s) {
    ull res1 = 0, res2 = 0;
    for (auto c : s) {
      res1 = (res1 * m1 + c) % MOD[0];
      res2 = (res2 * m2 + c) % MOD[1];
    }
    return {res1, res2};
  }

  vector<std::pair<ull, ull>> get_hash_set(const std::string &s) {
    ull res1 = 0, res2 = 0;
    vector<std::pair<ull, ull>> ans;
    for (auto c : s) {
      res1 = (res1 * m1 + c) % MOD[0];
      res2 = (res2 * m2 + c) % MOD[1];
      ans.emplace_back(res1, res2);
    }
    return ans;
  }

  void add_hash_set(vector<std::pair<ull, ull>> &a, char c) {
    std::pair<ull, ull> tmp = {(a.back().first * m1 + c) % MOD[0],
                               (a.back().second * m2 + c) % MOD[1]};
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
    return {
      (a1[r1].first + MOD[0] -
       (l1 == 0 ? 0
                : a1[l1 - 1].first * pow(m1, r1 + 1 - l1, MOD[0]) % MOD[0])) %
        MOD[0],
      (a1[r1].second + MOD[1] -
       (l1 == 0 ? 0
                : a1[l1 - 1].second * pow(m2, r1 + 1 - l1, MOD[1]) % MOD[1])) %
        MOD[1]};
  }

private:
  static const int MULT_SIZE = 9;
  static constexpr ull MOD[2]{ull(1e9) + 7, ull(1e9) + 27};
  static constexpr ull MULT[9]{131,  157,   293,   1019, 1471,
                               1667, 10037, 13331, 16183};

  int n;
  ull m1, m2;
  vector<std::pair<ull, ull>> mult;

  void init_mult() {
    mult.resize(n + 1);
    mult[0] = {1, 1};
    for (int i = 1; i <= n; i++) {
      mult[i].first = mult[i - 1].first * m1 % MOD[0];
      mult[i].second = mult[i - 1].second * m2 % MOD[1];
    }
  }

  ull pow(ull x, ull y, ull mod) {
    return mod == MOD[0] ? mult[y].first : mult[y].second;
  }
};
} // namespace Tool