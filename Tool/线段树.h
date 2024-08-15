
template <class Info>
class SegmentTree {
public:
  SegmentTree() {}
  SegmentTree(int n) {
    init(n);
  }
  template <class T>
  SegmentTree(std::vector<T> &a) {
    init(a);
  }

  void init(int n) {
    this->n = n;
    infos.assign(4 * n + 1, Info{});
    build(1, 1, n);
  }

  template <class T>
  void init(std::vector<T> &a) {
    n = a.size() - 1;
    infos.assign(4 * a.size(), Info{});
    build(1, 1, a.size() - 1, a);
  }

  void updata(int l, int r, const Info &tag) {
    update(1, 1, n, l, r, tag);
  }

  Info query(int l, int r) {
    return query(1, 1, n, l, r);
  }

  int get_first(int z, int l, int r, int k) {
    if (l == r) {
      return l;
    }
    int mid = (l + r) >> 1;
    if (infos[z << 1].x >= k) {
      return get_first(z << 1, l, mid, k);
    } else {
      return get_first(z << 1 | 1, mid + 1, r, k - infos[z << 1].x);
    }
  }

private:
  int n;
  std::vector<Info> infos;

  void pushup(int z) {
    infos[z] = infos[z << 1] + infos[z << 1 | 1];
  }

  Info query(int z, int l, int r, int s, int e) {
    if (l > e || r < s) {
      return Info{};
    }
    if (l >= s && r <= e) {
      return infos[z];
    }
    int mid = (l + r) >> 1;
    return query(z << 1, l, mid, s, e) + query(z << 1 | 1, mid + 1, r, s, e);
  }

  void update(int z, int l, int r, int s, int e, const Info &tag) {
    if (l > e || r < s) {
      return;
    }
    if (l >= s && r <= e) {
      infos[z].apply(tag);
      return;
    }
    int mid = (l + r) >> 1;
    update(z << 1, l, mid, s, e, tag);
    update(z << 1 | 1, mid + 1, r, s, e, tag);
    pushup(z);
  }

  template <class T>
  void build(int z, int l, int r, std::vector<T> &a) {
    if (l == r) {
      infos[z] = Info{a[l]};
      return;
    }
    int mid = (l + r) >> 1;
    build(z << 1, l, mid, a);
    build(z << 1 | 1, mid + 1, r, a);
    pushup(z);
  }

  void build(int z, int l, int r) {
    if (l == r) {
      infos[z] = Info{};
      return;
    }
    int mid = (l + r) >> 1;
    build(z << 1, l, mid);
    build(z << 1 | 1, mid + 1, r);
    pushup(z);
  }
};

struct Info {
  i64 x;
  void apply(const Info &tag) {
    x += tag.x;
  }
};

Info operator+(const Info &a, const Info &b) {
  return {a.x + b.x};
}
