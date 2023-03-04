#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

unsigned int Log(unsigned int n) {
	n--;
	n |= n >> 1;
	n |= n >> 2;
	n |= n >> 4;
	n |= n >> 8;
	n |= n >> 16;
	return n + 1;
}

int main() {
	fastio;
	cout << Log(0) << '\n'; // 0
	cout << Log(1) << '\n'; // 1
	cout << Log(2) << '\n'; // 2
	cout << Log(3) << '\n'; // 4
	cout << Log(4) << '\n'; // 4
	cout << Log(5) << '\n'; // 8
	cout << Log(16) << '\n'; // 16
	cout << Log(17) << '\n'; // 32
}
