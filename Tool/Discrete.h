#include <algorithm>
#include <vector>

template <class T, class cmp = std::less<T>>
class Discrete {
public:
  Discrete(std::vector<T> &_a, cmp _cp = cmp()) : a(_a), cp(_cp) {
    std::sort(a.begin(), a.end(), cp);
    a.resize(std::distance(a.begin(), std::unique(a.begin(), a.end())));
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