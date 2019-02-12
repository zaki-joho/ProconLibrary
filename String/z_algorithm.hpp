#include "../bits/stdc++.h"
// 文字列S の各i に対し, S と S[i:|S|-1] の最長共通接頭辞を求める
// https://snuke.hatenablog.com/entry/2014/12/03/214243
// verified: https://atcoder.jp/contests/arc055/submissions/2711907
/*
 * ex.  s = "aaabaaaab"
 * -> z[i]= "*21034210"
 */
std::vector<int> z_algorithm(const std::string &s)
{
    int sz = s.length();
    std::vector<int> z(sz, 0);
    int i = 1, j = 0;
    while (i < sz)
    {
        while (i + j < sz && s[j] == s[i + j])
            j++;
        z[i] = j;
        if (j == 0)
        {
            i++;
            continue;
        }
        int k = 1;
        while (i + k < sz && k + z[k] < j)
        {
            z[i + k] = z[k];
            k++;
        }
        i += k;
        j -= k;
    }
    return z;
}
