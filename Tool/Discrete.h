#include <algorithm>
#include <vector>

template <typename T>
  requires requires(T a) {
    a.begin() - a.end();
    a.resize(1);
    std::distance(a.begin(), a.end());
  }
inline void unique(T &a) {
  a.resize(std::distance(a.begin(), std::unique(all(a))));
}

template <class T, class cmp = std::less<T>>
class Discrete {
public:
  Discrete(std::vector<T> &_a, cmp _cp = cmp()) : a(_a), cp(_cp) {
    std::sort(a.begin(), a.end(), cp);
    unique(a);
  }

  // value to id
  int find(T c) {
    return std::lower_bound(a.begin(), a.end(), c, cp) - a.begin();
  }

  // id to value
  int get(int c) {
    return a[c];
  }

  auto size() {
    return a.size();
  }

private:
  cmp cp;
  std::vector<T> a;
};