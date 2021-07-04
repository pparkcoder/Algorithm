// https://www.acmicpc.net/problem/2003
// Two pointer algorithm

#include<iostream>
using namespace std;
int arr[10001];
int n, m, s, e, sum;
int result = 0;
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		cin >> arr[i];
	s = 1, e = 1, sum = arr[s];
	while (s <= n && e <= n) {
		if (sum < m) sum += arr[++e];
		else {
			if (sum == m) ++result;
			sum -= arr[s++];
		}
	}
	cout << result;
}
