#include "../bits/stdc++.h"
#include "chrono"
#include "xor_shift.hpp"

using namespace std;

using ll = long long;

constexpr ll TIME_LIMIT = 114514;  // msec

constexpr double startTemp = 0;
constexpr double endTemp = 0;

XorShift rnd;

int score = 0, bestScore = 0, nextScore = 0;

void annealing_sample() {
  int kaf = 0;
  chrono::high_resolution_clock::time_point clock_begin =
      chrono::high_resolution_clock::now();
  for (;; kaf++) {
    chrono::high_resolution_clock::time_point clock_end =
        chrono::high_resolution_clock::now();
    ll elapsed =
        chrono::duration_cast<chrono::milliseconds>(clock_end - clock_begin)
            .count();
    if (elapsed >= TIME_LIMIT) break;
    // do something here.
    if (score <= nextScore) {
      score = nextScore;
      if (bestScore < score) {
        bestScore = score;
      }
      continue;
    }
    double temp = startTemp + (endTemp - startTemp) * elapsed / TIME_LIMIT;
    double prob = exp((nextScore - score) / temp);
    if (prob > rnd.randDouble(0, 1)) {
      score = nextScore;
      continue;
    }
    // recover here
  }
}
