#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
#define int int64_t

template<size_t sz = 100'000>
struct Math {
	vector<int> p;      // primes
	int fpr[sz + 1];    // smallest prime divisor, IsPrime(p) ? 0 : fpr[p]
	int expo[sz + 1];   // exponent of smallest prime divisor
	int cnt_pr[sz + 1]; // number of distinct prime divisors
	int phi[sz + 1];    // euler phi function
	int mu[sz + 1];     // mobius function
	int tau[sz + 1];    // number of divisors
	int sig[sz + 1];    // sum of divisors

	Math() { linear_sieve(); }

	int _pow(int x, int n) {
		int ret = 1;
		while (n) {
			if (n & 1) ret *= x;
			x *= x; n >>= 1;
		}
		return ret;
	}

	void linear_sieve(int n = sz) {
		phi[1] = mu[1] = tau[1] = sig[1] = 1;
		for (int i = 2; i <= n; i++) {
			if (!fpr[i]) {
				p.push_back(i);
				expo[i] = 1;
				phi[i] = i - 1;
				mu[i] = -1;
				tau[i] = 2;
				sig[i] = i + 1;
			}
			for (const auto& j : p) {
				if (i * j > n) break;
				fpr[i * j] = j;
				if (i % j == 0) {
					expo[i * j] = expo[i] + 1;
					phi[i * j] = phi[i] * j;
					mu[i * j] = 0;
					tau[i * j] = tau[i] / expo[i * j] * (expo[i * j] + 1);
					sig[i * j] = sig[i] * (j - 1) / (_pow(j, expo[i * j]) - 1) * (_pow(j, expo[i * j] + 1) - 1) / (j - 1);
					break;
				}
				expo[i * j] = 1;
				phi[i * j] = phi[i] * phi[j];
				mu[i * j] = mu[i] * mu[j];
				tau[i * j] = tau[i] * tau[j];
				sig[i * j] = sig[i] * sig[j];
			}
		}
	}

	bool IsPrime(int n) {
		if (n <= 1) return 0;
		return !fpr[n];
	}

	vector<pair<int, int>> Factorize(int n) { // must be n > 1
		vector<pair<int, int>> ret;
		for (int cur; cur = fpr[n];) {
			int t = 0;
			while (fpr[n] == cur) t++, n /= cur;
			if (cur == n) n = 1, t++;
			ret.push_back({ cur, t });
		}
		if (n != 1) ret.push_back({ n, 1 });
		return ret;
	}

	bool IsPrime_naive(int n) {
		if (n <= 1) return 0;
		for (int i = 2; i * i <= n; i++) {
			if (n % i) continue;
			return 0;
		}
		return 1;
	}

	int phi_naive(int n) {
		int ret = n;
		for (int i = 2; i * i <= n; i++) {
			if (n % i) continue;
			ret = ret / i * (i - 1);
			while (n % i == 0) n /= i;
		}
		if (n != 1) ret = ret / n * (n - 1);
		return ret;
	}

	int tau_naive(int n) {
		int ret = 0;
		for (int i = 1; i * i <= n; i++) {
			if (n % i) continue;
			ret += i * i == n ? 1 : 2;
		}
		return ret;
	}

	int sig_naive(int n) {
		int ret = 0;
		for (int i = 1; i * i <= n; i++) {
			if (n % i) continue;
			ret += i * i == n ? i : i + n / i;
		}
		return ret;
	}

	vector<pair<int, int>> Factorize_naive(int n) { // must be n > 1
		vector<pair<int, int>> ret;
		for (int i = 2; i * i <= n; i++) {
			if (n % i) continue;
			int t = 0;
			while (n % i == 0) t++, n /= i;
			ret.push_back({ i, t });
		}
		if (n != 1) ret.push_back({ n, 1 });
		return ret;
	}

	int minv(int a, int b) {
		if (a == 0 && b == 1) return 0;
		if (a == 1) return 1;
		return b - minv(b % a, a) * b / a;
	}

	pair<int, int> crt(pair<int, int> A, pair<int, int> B) {
		if (A.Y == -1 || B.Y == -1) return { -1, -1 };
		if (A.Y == 1) return B;
		if (B.Y == 1) return A;
		int g = gcd(A.Y, B.Y), l = A.Y * (B.Y / g);
		if ((B.X - A.X) % g != 0) return { -1, -1 };
		int a = A.Y / g, b = B.Y / g;
		int mul = (B.X - A.X) / g;
		mul = (mul * minv(a % b, b)) % b;
		int ret = (mul * A.Y + A.X);
		ret %= l; ret = (ret + l) % l;
		return { ret, l };
	}

}; Math math;