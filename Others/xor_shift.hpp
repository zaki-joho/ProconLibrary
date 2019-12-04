#include "../bits/stdc++.h"
// XorShift 乱数生成器
// verified:
// https://atcoder.jp/contests/rco-contest-2019-qual/submissions/4237801
struct XorShift {
  using result_type = uint32_t;
  result_type w = 123456789, x = 362436069, y = 521288629, z = 88675123;
  XorShift(result_type seed = time(nullptr)) {
    w = seed;
    x = w << 13;
    y = (w >> 9) ^ (x << 6);
    z = y >> 7;
  }
  static constexpr result_type min() { return 0; }
  static constexpr result_type max() { return 0x7FFFFFFF; }
  result_type operator()() {
    result_type t = x ^ (x << 11);
    x = y;
    y = z;
    z = w;
    return w = (w ^ (w >> 19) ^ (t ^ (t >> 8)));
  }
  result_type rand() {
    result_type t = x ^ (x << 11);
    x = y;
    y = z;
    z = w;
    return w = (w ^ (w >> 19) ^ (t ^ (t >> 8)));
  }
  // [min,max] の整数値乱数
  result_type randInt(result_type min = 0, result_type max = 0x7FFFFFFF) {
    return rand() % (max - min + 1) + min;
  }
  // [min,max] の浮動小数点乱数
  double randDouble(double min = 0, double max = 1) {
    return (double)(rand() % 0xFFFF) / 0xFFFF * (max - min) + min;
  }
};
