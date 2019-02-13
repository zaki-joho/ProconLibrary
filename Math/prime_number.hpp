#include "../bits/stdc++.h"

// sieve of eratosthenes
// primes[i] != 0 if i is prime
std::vector<int> sieve_of_eratosthenes(int n)
{
    std::vector<int> primes(n);
    for (int i = 2; i < n; ++i)
        primes[i] = i;
    for (int i = 2; i * i < n; ++i)
        if (primes[i])
            for (int j = i * i; j < n; j += i)
                primes[j] = 0;
    return primes;
}

// 素因数分解, overflow に注意
// verified: http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3381567
std::map<int, int> prime_factorization(int n)
{
    std::map<int, int> ret;
    int ntmp = n;
    for (int i = 2; i * i <= n; i++)
    {
        if (ntmp % i)
            continue;
        while (ntmp % i == 0)
        {
            ret[i]++;
            ntmp /= i;
        }
    }
    if (ntmp != 1)
    {
        ret[ntmp]++;
    }
    return ret;
}
