#include "../bits/stdc++.h"
#include "chrono"

using namespace std;

using ll = long long;

constexpr ll TIME_LIMIT = 0; // msec

void timer_sample()
{
    int kaf = 0;
    chrono::high_resolution_clock::time_point clock_begin = chrono::high_resolution_clock::now();
    for (;; kaf++)
    {
        chrono::high_resolution_clock::time_point clock_end = chrono::high_resolution_clock::now();
        ll elapsed = chrono::duration_cast<chrono::milliseconds>(clock_end - clock_begin).count();
        if (elapsed >= TIME_LIMIT)
            break;

        // do something here.
    }
}
