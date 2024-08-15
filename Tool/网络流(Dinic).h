
namespace Dinic {

namespace Grap {

int tot;
std::vector<int> head, nxt, ver;
vector<i64> val;

inline void add(int x, int y, i64 z) {
  ver[++tot] = y, nxt[tot] = head[x], head[x] = tot, val[tot] = z;
}

inline void init(int n, int m) {
  tot = 0;
  head.assign(n + 1, 0);
  nxt.assign(m + 1, 0);
  ver.assign(m + 1, 0);
  val.assign(m + 1, 0);
}

} // namespace Grap

const i64 INF = 0x3f3f3f3f3f3f3f3f;
vector<i64> d;
vector<int> now;
int s, t;

inline void init(int n, int m, int _s, int _t) {
  Grap::init(n, m);
  Grap::tot = 1;
  d.resize(n + 1);
  s = _s;
  t = _t;
}

inline void add_edge(int x, int y, i64 z) {
  Grap::add(x, y, z);
  Grap::add(y, x, 0);
}

bool bfs() {
  std::fill(all(d), INF);
  std::queue<int> q;
  d[s] = 0;
  q.push(s);
  while (!q.empty()) {
    int x = q.front();
    q.pop();
    for (int i = Grap::head[x]; i; i = Grap::nxt[i]) {
      int y = Grap::ver[i];
      i64 w = Grap::val[i];
      if (d[y] == INF && w > 0) {
        q.push(y);
        d[y] = d[x] + 1;
      }
    }
  }
  return d[t] != INF;
}

i64 dfs(int x, i64 sum) {
  if (x == t) {
    return sum;
  }
  i64 k;
  i64 res = 0;
  for (int &i = now[x]; i && sum; i = Grap::nxt[i]) {
    int y = Grap::ver[i];
    i64 w = Grap::val[i];
    if (w > 0 && d[y] == d[x] + 1) {
      k = dfs(y, std::min(sum, w));
      if (k == 0) {
        d[y] = INF;
      }
      Grap::val[i] -= k;
      Grap::val[i ^ 1] += k;
      res += k;
      sum -= k;
    }
  }
  return res;
}

inline i64 dinic() {
  i64 ans = 0;
  while (bfs()) {
    now = Grap::head;
    ans += dfs(s, INF);
  }
  return ans;
}

} // namespace Dinic
