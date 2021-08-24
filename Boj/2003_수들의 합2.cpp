// https://www.acmicpc.net/problem/2003
// Tip -> while문 조건이 중요
// 반례
// 3 1
// 1 2 1
// output : 2

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
