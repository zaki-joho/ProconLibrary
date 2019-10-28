/**
{0, 1,..., n-1} に含まれるサイズk の部分集合列挙
int k;
int comb = (1 << k) - 1;
while (comb < 1 << n)
{
    int x = comb & ~comb;
    int y = comb + x;
    comb = ((comb & ~y) / x >> 1) | y;
}

集合S の部分集合を列挙する
int S;
for (int sub = (S - 1) & S; sub != S; sub = (sub - 1) & S)
{
}

高速ゼータ変換, F(S)=Σ(T⊂S)G(T)
rep (i, n) rep (b, 1 << n) if (0 == (b & (1 << i))) a[b] += a[b | (1 << i)];

高速メビウス変換 F(S)=Σ(S⊂T)G(T)
REP(i,n) REP(j, 1<<n) if(j & (1 << i)) f[j] -= f[j ^ (1 << i)];
 */
