#include "../bits/stdc++.h"

// 以下のような形をした論理式f が true となるような割り当てが存在するか.
// f = (x_1 or x_2) and (x_3 or x_4) ... and (x_n-1 or x_n)
// (x or y) は (not x -> y) と書ける
// not x -> y, not y -> x に辺を張り SCC して
// x, not x が同一グループに入らなければ割り当て可能
