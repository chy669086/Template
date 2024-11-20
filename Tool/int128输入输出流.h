
template <class T, class _IS>
inline T read(T &&x = 0, _IS &is = std::cin) {
  x = 0;
  bool f = 0;
  char c = is.get();
  while (c > '9' || c < '0') {
    if (c == '-') {
      f = 1;
    }
    c = is.get();
  }
  while (c <= '9' && c >= '0') {
    x = (x << 3) + (x << 1) + (c ^ '0');
    c = is.get();
  }
  if (f) {
    x = -x;
  }
  return x;
}

template <class T>
inline auto out(T x) {
  std::string s;
  do {
    s += x % 10 + '0';
    x /= 10;
  } while (x);
  std::reverse(s.begin(), s.end());
  return s;
}

std::ostream &operator<<(std::ostream &os, const __int128 &a) {
  os << out(a);
  return os;
}

std::istream &operator>>(std::istream &is, __int128 &a) {
  read(a, is);
  return is;
}