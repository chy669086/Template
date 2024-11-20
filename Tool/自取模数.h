
constexpr i64 ex_gcd(i64 a, i64 b, i64 &x, i64 &y) {
  if (b == 0) {
    x = 1, y = 0;
    return a;
  }
  i64 r = ex_gcd(b, b % b, y, x);
  y -= (a / b) * x;
  return r;
}

constexpr i64 inv(i64 m, const i64 mod) {
  i64 x, y;
  ex_gcd(m, mod, x, y);
  return (x % mod + mod) % mod;
}

constexpr i64 mul(i64 a, i64 b, i64 p) {
  i64 res = a * b - (i64)(1.L * a * b / p) * p;
  res %= p;
  if (res < 0) {
    res += p;
  }
  return res;
}

template <class T>
constexpr T power(T a, i64 b) {
  T res = 1;
  for (; b; b /= 2, a *= a) {
    if (b % 2) {
      res *= a;
    }
  }
  return res;
}

template <i64 P>
struct MLong {
  i64 x;
  constexpr MLong() : x{} {}
  constexpr MLong(i64 x) : x{norm(x % getMod())} {}

  static i64 Mod;
  constexpr static i64 getMod() {
    if (P > 0) {
      return P;
    } else {
      return Mod;
    }
  }
  constexpr static void setMod(i64 Mod_) {
    Mod = Mod_;
  }
  constexpr i64 norm(i64 x) const {
    if (x < 0) {
      x += getMod();
    }
    if (x >= getMod()) {
      x -= getMod();
    }
    return x;
  }
  constexpr i64 val() const {
    return x;
  }
  explicit constexpr operator i64() const {
    return x;
  }
  constexpr MLong operator-() const {
    MLong res;
    res.x = norm(getMod() - x);
    return res;
  }
  constexpr MLong inv() const {
    assert(x != 0);
    return power(*this, getMod() - 2);
  }
  constexpr MLong &operator*=(MLong rhs) & {
    x = mul(x, rhs.x, getMod());
    return *this;
  }
  constexpr MLong &operator+=(MLong rhs) & {
    x = norm(x + rhs.x);
    return *this;
  }
  constexpr MLong &operator-=(MLong rhs) & {
    x = norm(x - rhs.x);
    return *this;
  }
  constexpr MLong &operator/=(MLong rhs) & {
    return *this *= rhs.inv();
  }
  friend constexpr MLong operator*(MLong lhs, MLong rhs) {
    MLong res = lhs;
    res *= rhs;
    return res;
  }
  friend constexpr MLong operator+(MLong lhs, MLong rhs) {
    MLong res = lhs;
    res += rhs;
    return res;
  }
  friend constexpr MLong operator-(MLong lhs, MLong rhs) {
    MLong res = lhs;
    res -= rhs;
    return res;
  }
  friend constexpr MLong operator/(MLong lhs, MLong rhs) {
    MLong res = lhs;
    res /= rhs;
    return res;
  }
  friend constexpr std::istream &operator>>(std::istream &is, MLong &a) {
    i64 v;
    is >> v;
    a = MLong(v);
    return is;
  }
  friend constexpr std::ostream &operator<<(std::ostream &os, const MLong &a) {
    return os << a.val();
  }
  friend constexpr bool operator==(MLong lhs, MLong rhs) {
    return lhs.val() == rhs.val();
  }
  friend constexpr bool operator!=(MLong lhs, MLong rhs) {
    return lhs.val() != rhs.val();
  }
  constexpr operator bool() {
    return x;
  }
};

template <int P>
struct MInt {
  int x;
  constexpr MInt() : x{} {}
  constexpr MInt(i64 x) : x{norm(x % getMod())} {}

  static int Mod;
  constexpr static int getMod() {
    if (P > 0) {
      return P;
    } else {
      return Mod;
    }
  }
  constexpr static void setMod(int Mod_) {
    Mod = Mod_;
  }
  constexpr int norm(int x) const {
    if (x < 0) {
      x += getMod();
    }
    if (x >= getMod()) {
      x -= getMod();
    }
    return x;
  }
  constexpr int val() const {
    return x;
  }
  explicit constexpr operator int() const {
    return x;
  }
  constexpr MInt operator-() const {
    MInt res;
    res.x = norm(getMod() - x);
    return res;
  }
  constexpr MInt inv() const {
    assert(x != 0);
    return power(*this, getMod() - 2);
  }
  constexpr MInt &operator*=(MInt rhs) & {
    x = 1LL * x * rhs.x % getMod();
    return *this;
  }
  constexpr MInt &operator+=(MInt rhs) & {
    x = norm(x + rhs.x);
    return *this;
  }
  constexpr MInt &operator-=(MInt rhs) & {
    x = norm(x - rhs.x);
    return *this;
  }
  constexpr MInt &operator/=(MInt rhs) & {
    return *this *= rhs.inv();
  }
  friend constexpr MInt operator*(MInt lhs, MInt rhs) {
    MInt res = lhs;
    res *= rhs;
    return res;
  }
  friend constexpr MInt operator+(MInt lhs, MInt rhs) {
    MInt res = lhs;
    res += rhs;
    return res;
  }
  friend constexpr MInt operator-(MInt lhs, MInt rhs) {
    MInt res = lhs;
    res -= rhs;
    return res;
  }
  friend constexpr MInt operator/(MInt lhs, MInt rhs) {
    MInt res = lhs;
    res /= rhs;
    return res;
  }
  friend constexpr std::istream &operator>>(std::istream &is, MInt &a) {
    i64 v;
    is >> v;
    a = MInt(v);
    return is;
  }
  friend constexpr std::ostream &operator<<(std::ostream &os, const MInt &a) {
    return os << a.val();
  }
  friend constexpr bool operator==(MInt lhs, MInt rhs) {
    return lhs.val() == rhs.val();
  }
  friend constexpr bool operator!=(MInt lhs, MInt rhs) {
    return lhs.val() != rhs.val();
  }
  constexpr operator bool() {
    return x;
  }
};

template <class Z>
struct Comb {
  int n = 0;
  std::vector<Z> _fac = {1};
  std::vector<Z> _invfac = {1};
  std::vector<Z> _inv = {0};

  Comb() = default;

  Comb(int n) {
    init(n);
  }

  void init(int m) {
    if (m <= n)
      return;
    _fac.resize(m + 1);
    _invfac.resize(m + 1);
    _inv.resize(m + 1);

    for (int i = n + 1; i <= m; i++) {
      _fac[i] = _fac[i - 1] * Z(i);
    }
    _invfac[m] = _fac[m].inv();
    for (int i = m; i > n; i--) {
      _invfac[i - 1] = _invfac[i] * Z(i);
      _inv[i] = _invfac[i] * _fac[i - 1];
    }
    n = m;
  }

  Z fac(int m) {
    if (m > n)
      init(2 * m);
    return _fac[m];
  }
  Z invfac(int m) {
    if (m > n)
      init(2 * m);
    return _invfac[m];
  }
  Z inv(int m) {
    if (m > n)
      init(2 * m);
    return _inv[m];
  }
  Z binom(int m, int k) {
    if (m < k || k < 0)
      return 0;
    return fac(m) * invfac(k) * invfac(m - k);
  }
};

using Z = MInt<>;

Comb<Z> comb;

template <>
struct std::formatter<Z, char> {
  bool quoted = false;

  template <class ParseContext>
  constexpr ParseContext::iterator parse(ParseContext &ctx) {
    auto it = ctx.begin();
    return it;
  }

  template <class FmtContext>
  FmtContext::iterator format(Z s, FmtContext &ctx) const {
    return format_to(ctx.out(), "{}", s.x);
  }
};