#include "../bits/stdc++.h"
/**
 * 集合S の部分集合を列挙する
int S;
for (int sub = (S - 1) & S; sub != S; sub = (sub - 1) & S)
{
}
 */

/**
 * {0, 1,..., n-1} に含まれるサイズk の部分集合列挙
int k;
int comb = (1 << k) - 1;
while (comb < 1 << n)
{
    int x = comb & ~comb;
    int y = comb + x;
    comb = ((comb & ~y) / x >> 1) | y;
}
 */
