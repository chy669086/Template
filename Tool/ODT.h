
#include <set>
using i64 = long long;

template <class T = int, class P = int>
class ODT {
public:
  void insert(T l, T r, P x) {
    s.insert(node(l, r, x));
  }

  void assign(T l, T r, P x) {
    auto itr = split(r + 1);
    auto itl = split(l);
    s.erase(itl, itr);
    s.insert(node(l, r, x));
  }

  i64 query_sum(T l, T r) {
    auto itr = split(r + 1);
    auto itl = split(l);
    i64 res = 0;
    for (auto i = itl; i != itr; i++) {
      res += i->val * (i->r - i->l + 1);
    }
    return res;
  }

  void add(T l, T r, P x) {
    auto itr = split(r + 1);
    auto itl = split(l);
    for (auto i = itl; i != itr; i++) {
      i->val += x;
    }
  }

private:
  struct node {
    T l, r;
    mutable P val;
    friend bool operator<(const node &a, const node &b) {
      return a.l < b.l;
    }
    node(T l, T r = 0, P val = 0) : l(l), r(r), val(val) {}
  };

  std::set<node> s;

  std::set<node>::iterator split(T p) {
    auto it = s.lower_bound(node(p));
    if (it != s.end() && it->l == p) {
      return it;
    }
    it--;
    if (it->r < p) {
      return s.end();
    }
    T l = it->l;
    T r = it->r;
    P val = it->val;
    s.erase(it);
    s.insert(node{l, p - 1, val});
    return s.insert(node(p, r, val)).first;
  }
};