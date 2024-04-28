
#include <vector>

namespace Grap {

int tot;
std::vector<int> head, nxt, ver;

inline void add(int x, int y) {
  ver[++tot] = y, nxt[tot] = head[x], head[x] = tot;
}

inline void init(int n, int m) {
  tot = 0;
  head.resize(n + 1);
  nxt.resize(m + 1);
  ver.resize(m + 1);
}

} // namespace Grap

using namespace Grap;