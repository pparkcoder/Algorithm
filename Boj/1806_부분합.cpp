// https://www.acmicpc.net/problem/1806

#include<iostream>
#include<algorithm>
#include<climits>
using namespace std;
int arr[100001];
int len = INT_MAX;
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int n, m, s, e, sum;
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		cin >> arr[i];
	s = e = 1;
	sum = arr[s];
	while (s <= e) {
		if (sum >= m) {
			len = min(len, e - s + 1);
			sum -= arr[s++];
		}
		else {
			if (++e > n) break;
			sum += arr[e];
			
		}
	}
	cout << (len == INT_MAX ? 0 : len);
}
