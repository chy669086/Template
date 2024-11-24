
#include <iostream>


inline void debug(char a) {
  std::cerr << a;
}
inline void debug(const char *a) {
  std::cerr << a;
}

template <typename T>
void debug(const T &a) {
  std::cerr << a << " ";
}

template <typename T>
  requires requires() {
    T::first;
    T::second;
  }
void debug(const T &a) {
  std::cerr << a.first << " " << a.second;
  std::cerr << "\n";
}

inline void debug() {
  std::cerr << "\n";
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
  std::cerr << "\n";
}

template <typename... Args>
void debug(Args... args) {
  (debug(args), ...);
}