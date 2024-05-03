
#include <format>
#include <iostream>

#define dprint(s, ...) std::cout << std::format(s, ##__VA_ARGS__)

inline void debug(char a) {
  std::cout << a;
}
inline void debug(const char *a) {
  std::cout << a;
}

template <typename T>
void debug(const T &a) {
  std::cout << a << " ";
}

template <typename T>
  requires requires(T p) {
    p.begin();
    p.end();
    p.begin()++;
    p.begin() != p.end();
  }
void debug(const T &a) {
  for (auto &x : a) {
    debug(x);
  }
  std::cout << "\n";
}

template <typename T>
  requires requires() {
    T::first;
    T::second;
  }
void debug(const T &a) {
  std::cout << a.first << " " << a.second;
  std::cout << "\n";
}