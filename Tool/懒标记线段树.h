

#include <vector>

using std::vector;

template <class Info, class Tag>
class SegmentTree {
public:
  SegmentTree() {}
  SegmentTree(int n) {
    init(n);
  }
  template <class T>
  SegmentTree(vector<T> &a) {
    init(a);
  }

  void init(int n) {
    this->n = n;
    infos.assign(4 * n + 1, Info{});
    tags.assign(4 * n + 1, Tag{});
    build(1, 1, n);
  }

  template <class T>
  void init(vector<T> &a) {
    n = a.size() - 1;
    infos.assign(4 * a.size(), Info{});
    tags.assign(4 * a.size(), Tag{});
    build(1, 1, a.size() - 1, a);
  }

  void updata(int l, int r, const Tag &tag) {
    update(1, 1, n, l, r, tag);
  }

  Info query(int l, int r) {
    return query(1, 1, n, l, r);
  }

private:
  int n;
  vector<Info> infos;
  vector<Tag> tags;

  void pushup(int z) {
    infos[z] = infos[z << 1] + infos[z << 1 | 1];
  }

  void pushdown(int z) {
    Tag &tag = tags[z];
    infos[z << 1].apply(tag);
    infos[z << 1 | 1].apply(tag);
    tags[z << 1].apply(tag);
    tags[z << 1 | 1].apply(tag);
    tag = Tag{};
  }

  Info query(int z, int l, int r, int s, int e) {
    if (l > e || r < s) {
      return Info{};
    }
    if (l >= s && r <= e) {
      return infos[z];
    }
    pushdown(z);
    int mid = (l + r) >> 1;
    return query(z << 1, l, mid, s, e) + query(z << 1 | 1, mid + 1, r, s, e);
  }

  void update(int z, int l, int r, int s, int e, const Tag &tag) {
    if (l > e || r < s) {
      return;
    }
    if (l >= s && r <= e) {
      infos[z].apply(tag);
      tags[z].apply(tag);
      return;
    }
    pushdown(z);
    int mid = (l + r) >> 1;
    update(z << 1, l, mid, s, e, tag);
    update(z << 1 | 1, mid + 1, r, s, e, tag);
    pushup(z);
  }

  template <class T>
  void build(int z, int l, int r, vector<T> &a) {
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

struct Tag {
  i64 x;
  void apply(const Tag &tag) {
    x += tag.x;
  }
};

struct Info {
  i64 x;
  i64 len = 1;
  void apply(const Tag &tag) {
    x += tag.x * len;
  }
};

Info operator+(const Info &a, const Info &b) {
  return {a.x + b.x, a.len + b.len};
}