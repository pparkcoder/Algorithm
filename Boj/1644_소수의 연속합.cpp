// https://www.acmicpc.net/problem/1644

#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
bool prime[4000001];
int n;
int result = 0;
vector<int> v;
void make_prime() {
	for (int i = 2; i <= sqrt(4000000); ++i) {
		if (prime[i]) continue;
		for (int j = i * i; j <= 4000000; j += i)
			prime[j] = 1;
	}
	for (int i = 2; i <= 4000000; ++i)
		if (!prime[i]) v.push_back(i);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	make_prime();
	int s = 0, e = 0, len = v.size(), sum = v[e];
	while (s <= e) {
		if (sum > n) {
			sum -= v[s++];
			if (s > e) {
				e = s;
				sum = v[e];
			}
		}
		else {
			if (sum == n) ++result;
			if (++e >= len) break;
			sum += v[e];
		}
	}
	cout << result;
}
