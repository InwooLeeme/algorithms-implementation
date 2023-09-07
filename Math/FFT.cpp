#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using cpx = complex<double>;

void FFT(vector<cpx>& P, bool inv = 0) {
	const int n = P.size();
	vector<cpx> root(n / 2);
	for (int i = 1, j = 0; i < n; i++) {
		int bit = n >> 1;
		while (j >= bit) j -= bit, bit >>= 1;
		j += bit;
		if (i < j) swap(P[i], P[j]);
	}
	double ang = (inv ? -2 : 2) * acos(-1) / n;
	for (int i = 0; i < n / 2; i++) root[i] = cpx(cos(ang * i), sin(ang * i));
	for (int i = 2; i <= n; i *= 2) {
		for (int j = 0; j < n; j += i) for (int k = 0; k < i / 2; k++) {
			cpx u = P[j + k], v = P[j + k + i / 2] * root[n / i * k];
			P[j + k] = u + v;
			P[j + k + i / 2] = u - v;
		}
	}
	if (inv) for (int i = 0; i < n; i++) P[i] /= n;
}

vector<int> Mul(const vector<int>& a, const vector<int>& b) {
	int n = 1;
	while (n < a.size() + b.size() - 1) n <<= 1;
	vector<cpx> A(a.begin(), a.end()); A.resize(n);
	vector<cpx> B(b.begin(), b.end()); B.resize(n);
	FFT(A, 0), FFT(B, 0);
	for (int i = 0; i < n; i++) A[i] *= B[i];
	FFT(A, 1);
	vector<int> ret(a.size() + b.size() - 1);
	for (int i = 0; i < ret.size(); i++) ret[i] = round(A[i].real());
	return ret;
}

int main() {
	fastio;
	
}
