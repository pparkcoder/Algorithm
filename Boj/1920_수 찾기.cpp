// https://www.acmicpc.net/problem/1920

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<int> v;
int n, m, num, low, high, mid, flag;
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> num;
		v.push_back(num);
	}
	sort(v.begin(), v.end());
	cin >> m;
	for (int i = 0; i < m; ++i) {
		cin >> num;
		flag = low = 0;
		high = n - 1;
		while (low <= high) {
			mid = (low + high) / 2;
			if (v[mid] == num) {
				flag = 1;
				break;
			}
			else if (v[mid] > num) high = mid - 1;
			else low = mid + 1;
		}
		cout << flag << "\n";
	}
}
