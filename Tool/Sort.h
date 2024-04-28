#include <iostream>

template <class T>
inline int read(T &&x = 0) {
  x = 0;
  char c = std::cin.get();
  bool f = 0;
  while (c > '9' && c < '0') {
    if (c == '-') {
      f = 1;
    }
    c = std::cin.get();
  }
  while (c >= '0' && c <= '9') {
    x = (x << 1) + (x << 3) + (c ^ '0');
    c = std::cin.get();
  }
  return f ? -x : x;
}

namespace Sort {

#define MAXN 5000
using type = unsigned int;

type a[MAXN], b[MAXN];
type cnt0[1 << 8], cnt8[1 << 8], cnt16[1 << 8], cnt24[1 << 8];
type n, seed;

inline void init_date() {
  for (type *to = a + n, *now = a; now < to; ++now) {
    *now = read(seed);
    ++cnt0[seed & 255];
    ++cnt8[seed >> 8 & 255];
    ++cnt16[seed >> 16 & 255];
    ++cnt24[seed >> 24 & 255];
  }
}

inline void sort() {
  for (int i = 1; i < 256; ++i) {
    cnt0[i] += cnt0[i - 1];
    cnt8[i] += cnt8[i - 1];
    cnt16[i] += cnt16[i - 1];
    cnt24[i] += cnt24[i - 1];
  }

  int rep = n >> 3, tim = rep;
  type *now = a + n - 1;
  while (tim--) {
    b[--cnt0[now[0] & 255]] = now[0];
    b[--cnt0[now[-1] & 255]] = now[-1];
    b[--cnt0[now[-2] & 255]] = now[-2];
    b[--cnt0[now[-3] & 255]] = now[-3];
    b[--cnt0[now[-4] & 255]] = now[-4];
    b[--cnt0[now[-5] & 255]] = now[-5];
    b[--cnt0[now[-6] & 255]] = now[-6];
    b[--cnt0[now[-7] & 255]] = now[-7];
    now -= 8;
  }
  switch (n & 7) {
  case 7: {
    b[--cnt0[*now & 255]] = *now;
    --now;
  }
  case 6: {
    b[--cnt0[*now & 255]] = *now;
    --now;
  }
  case 5: {
    b[--cnt0[*now & 255]] = *now;
    --now;
  }
  case 4: {
    b[--cnt0[*now & 255]] = *now;
    --now;
  }
  case 3: {
    b[--cnt0[*now & 255]] = *now;
    --now;
  }
  case 2: {
    b[--cnt0[*now & 255]] = *now;
    --now;
  }
  case 1: {
    b[--cnt0[*now & 255]] = *now;
    --now;
  }
  }
  tim = rep;
  now = b + n - 1;
  while (tim--) {
    a[--cnt8[now[0] >> 8 & 255]] = now[0];
    a[--cnt8[now[-1] >> 8 & 255]] = now[-1];
    a[--cnt8[now[-2] >> 8 & 255]] = now[-2];
    a[--cnt8[now[-3] >> 8 & 255]] = now[-3];
    a[--cnt8[now[-4] >> 8 & 255]] = now[-4];
    a[--cnt8[now[-5] >> 8 & 255]] = now[-5];
    a[--cnt8[now[-6] >> 8 & 255]] = now[-6];
    a[--cnt8[now[-7] >> 8 & 255]] = now[-7];
    now -= 8;
  }
  switch (n & 7) {
  case 7: {
    a[--cnt8[*now >> 8 & 255]] = *now;
    --now;
  }
  case 6: {
    a[--cnt8[*now >> 8 & 255]] = *now;
    --now;
  }
  case 5: {
    a[--cnt8[*now >> 8 & 255]] = *now;
    --now;
  }
  case 4: {
    a[--cnt8[*now >> 8 & 255]] = *now;
    --now;
  }
  case 3: {
    a[--cnt8[*now >> 8 & 255]] = *now;
    --now;
  }
  case 2: {
    a[--cnt8[*now >> 8 & 255]] = *now;
    --now;
  }
  case 1: {
    a[--cnt8[*now >> 8 & 255]] = *now;
    --now;
  }
  }
  tim = rep;
  now = a + n - 1;
  while (tim--) {
    b[--cnt16[now[0] >> 16 & 255]] = now[0];
    b[--cnt16[now[-1] >> 16 & 255]] = now[-1];
    b[--cnt16[now[-2] >> 16 & 255]] = now[-2];
    b[--cnt16[now[-3] >> 16 & 255]] = now[-3];
    b[--cnt16[now[-4] >> 16 & 255]] = now[-4];
    b[--cnt16[now[-5] >> 16 & 255]] = now[-5];
    b[--cnt16[now[-6] >> 16 & 255]] = now[-6];
    b[--cnt16[now[-7] >> 16 & 255]] = now[-7];
    now -= 8;
  }
  switch (n & 7) {
  case 7: {
    b[--cnt16[*now >> 16 & 255]] = *now;
    --now;
  }
  case 6: {
    b[--cnt16[*now >> 16 & 255]] = *now;
    --now;
  }
  case 5: {
    b[--cnt16[*now >> 16 & 255]] = *now;
    --now;
  }
  case 4: {
    b[--cnt16[*now >> 16 & 255]] = *now;
    --now;
  }
  case 3: {
    b[--cnt16[*now >> 16 & 255]] = *now;
    --now;
  }
  case 2: {
    b[--cnt16[*now >> 16 & 255]] = *now;
    --now;
  }
  case 1: {
    b[--cnt16[*now >> 16 & 255]] = *now;
    --now;
  }
  }
  tim = rep;
  now = b + n - 1;
  while (tim--) {
    a[--cnt24[now[0] >> 24]] = now[0];
    a[--cnt24[now[-1] >> 24]] = now[-1];
    a[--cnt24[now[-2] >> 24]] = now[-2];
    a[--cnt24[now[-3] >> 24]] = now[-3];
    a[--cnt24[now[-4] >> 24]] = now[-4];
    a[--cnt24[now[-5] >> 24]] = now[-5];
    a[--cnt24[now[-6] >> 24]] = now[-6];
    a[--cnt24[now[-7] >> 24]] = now[-7];
    now -= 8;
  }
  switch (n & 7) {
  case 7: {
    a[--cnt24[*now >> 24]] = *now;
    --now;
  }
  case 6: {
    a[--cnt24[*now >> 24]] = *now;
    --now;
  }
  case 5: {
    a[--cnt24[*now >> 24]] = *now;
    --now;
  }
  case 4: {
    a[--cnt24[*now >> 24]] = *now;
    --now;
  }
  case 3: {
    a[--cnt24[*now >> 24]] = *now;
    --now;
  }
  case 2: {
    a[--cnt24[*now >> 24]] = *now;
    --now;
  }
  case 1: {
    a[--cnt24[*now >> 24]] = *now;
    --now;
  }
  }
}

} // namespace Sort