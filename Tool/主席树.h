
// 主席树
template <class T>
class EXTree {
public:
  EXTree(int n) : tree(n << 5), n(n) {
    root.push_back(build(1, n));
  }

  void update(int loc) {
    root.push_back(update(root.back(), 1, n, loc));
  }

  int query(int l, int r, int k) {
    return query(root[l - 1], root[r], 1, n, k);
  }

private:
  struct node {
    int x, l, r;
  };
  int n;
  int cnt = 0;
  std::vector<int> root;
  std::vector<node> tree;

  int build(int l, int r) {
    int cur = ++cnt;
    if (l == r) {
      return cur;
    }
    int mid = (l + r) >> 1;
    tree[cur].l = build(l, mid);
    tree[cur].r = build(mid + 1, r);
    return cur;
  }

  int clone(int pre) {
    ++cnt;
    tree[cnt].l = tree[pre].l;
    tree[cnt].r = tree[pre].r;
    tree[cnt].x = tree[pre].x + 1;
    return cnt;
  }

  // 更新
  int update(int pre, int pl, int pr, int loc) {
    int cur = clone(pre); // 新建一个节点，同时返回这个新的节点编号
    if (pl == pr) {
      return cur; // 返回当前节点编号
    }
    int mid = (pl + pr) >> 1;
    if (loc <= mid) {
      // 完成当前节点的l的update
      tree[cur].l = update(tree[cur].l, pl, mid, loc);
    } else {
      // 完成当前节点r的update
      tree[cur].r = update(tree[cur].r, mid + 1, pr, loc);
    }
    return cur; // 返回当前节点编号，实现对子根节点的lr赋值
  }

  // 查询
  int query(int pre, int cur, int pl, int pr, int k) {
    int ans = 0;
    // sum[lc[cur]]-sum[lc[pre]]
    int L1 = tree[cur].l; // 当前节点的l位置
    int L2 = tree[pre].l; // 当前节点的pre时刻的l位置
    // 通过两个时刻同一位置的val的相减，得到这个节点所包含的元素个数
    // 即表示了在[pl,pr]查询区间内，有多少个元素位于这个节点的子区间内
    int num = tree[L1].x - tree[L2].x;
    if (pl == pr) {
      return pl; // 到达叶子节点，叶子节点是我们查询的节点，直接返回pl或者pr都行
    }
    int mid = (pl + pr) >> 1;
    if (num >= k) {
      // 递归查询左子树
      return query(tree[pre].l, tree[cur].l, pl, mid, k);
    } else {
      // 递归查询右子树
      return query(tree[pre].r, tree[cur].r, mid + 1, pr, k - num);
    }
  }
};