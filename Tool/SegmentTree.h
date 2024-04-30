

#include <vector>

using std::vector;

namespace Tool {

template <class T, class P>
concept CHANGE = requires(P b) { T(b); };

template <class T>
class SegmentTree {
public:
  struct node {
    T x, lazy;
    int l, r;
    int len() {
      return r - l + 1;
    }
  };

  SegmentTree(int n) : n(n), tree(4 * (n + 1)) {
    build(1, 1, n);
  }

  // 0 索引要空着
  template <class P>
    requires CHANGE<T, P>
  SegmentTree(const vector<P> &a) {
    n = a.size() - 1;
    tree.resize(4 * (n + 1));
    build(1, 1, n, a);
  }

  // 0 索引要空着
  template <class P>
    requires CHANGE<T, P>
  SegmentTree(const vector<P> &a, int n) : n(n), tree(4 * (n + 1)) {
    build(1, 1, n, a);
  }

  void update(int l, int r, T k) {
    update(1, l, r, 1, n, k);
  }
  void update(int pos, T k) {
    update(1, pos, pos, 1, n, k);
  }

  T query(int l, int r) {
    return query(1, l, r, 1, n);
  }
  T query(int pos) {
    return query(1, pos, pos, 1, n);
  }

private:
  int n;
  vector<node> tree;

  void pushup(int z) {
    tree[z].x = tree[z << 1].x + tree[z << 1 | 1].x;
  }
  void pushdown(int z) {
    T lazy = tree[z].lazy;
    if (bool(lazy)) {
      tree[z << 1].lazy += lazy;
      tree[z << 1].x += lazy * T(tree[z << 1].len());
      tree[z << 1 | 1].lazy += lazy;
      tree[z << 1 | 1].x += lazy * T(tree[z << 1 | 1].len());
      tree[z].lazy = 0;
    }
  }

  template <class P>
    requires CHANGE<T, P>
  void build(int z, int l, int r, const vector<P> &a) {
    tree[z].l = l;
    tree[z].r = r;
    if (l == r) {
      tree[z].x = T(a[l]);
      return;
    }
    int mid = (l + r) >> 1;
    build(z << 1, l, mid, a);
    build(z << 1 | 1, mid + 1, r, a);
    pushup(z);
  }

  void build(int z, int l, int r) {
    tree[z].l = l;
    tree[z].r = r;
    if (l == r) {
      return;
    }
    int mid = (l + r) >> 1;
    build(z << 1, l, mid);
    build(z << 1 | 1, mid + 1, r);
    pushup(z);
  }
  void update(int z, int s, int e, int l, int r, T k) {
    if (l > e || r < s) {
      return;
    }
    if (l >= s && r <= e) {
      tree[z].lazy += k;
      tree[z].x += T(r - l + 1) * k;
      return;
    }
    pushdown(z);
    int mid = (l + r) >> 1;
    update(z << 1, s, e, l, mid, k);
    update(z << 1 | 1, s, e, mid + 1, r, k);
    pushup(z);
  }
  T query(int z, int s, int e, int l, int r) {
    if (l > e || r < s) {
      return 0;
    }
    if (l >= s && r <= e) {
      return tree[z].x;
    }
    pushdown(z);
    int mid = (l + r) >> 1;
    return query(z << 1, s, e, l, mid) + query(z << 1 | 1, s, e, mid + 1, r);
  }
};
} // namespace Tool