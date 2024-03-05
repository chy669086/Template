#include <vector>

using std::vector;

namespace Tool {

template <class T>
class BinaryIndexedTrees {
public:
  BinaryIndexedTrees(int n) : c(n + 1), n(n) {}
  BinaryIndexedTrees(const vector<T> &a) {
    n = a.size() - 1;
    c.resize(4 * (n + 1));
    build(a);
  }
  static int lowbit(int x) {
    return x & -x;
  }
  void update(int i, T k) {
    while (i <= n) {
      c[i] += k;
      i += lowbit(i);
    }
  }
  T get_sum(int i) {
    T res = 0;
    while (i) {
      res += c[i];
      i -= lowbit(i);
    }
    return res;
  }

private:
  int n;
  vector<T> c;

  void build(const vector<T> &a) {
    for (int i = 1; i <= n; i++) {
      c[i] += a[i];
      if (i + lowbit(i) <= n) {
        c[i + lowbit(i)] += c[i];
      }
    }
  }
};

} // namespace Tool
