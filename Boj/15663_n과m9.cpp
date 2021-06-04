// https://www.acmicpc.net/problem/15663
// 1번째 : 48ms , 2번째 : 16ms

//#include<iostream>
//#include<algorithm>
//#include<vector>
//#include<string>
//#include<map>
//using namespace std;
//map<string, int> visit;
//vector<int> v, v2;
//bool check[9];
//int n, m, num;
//void dfs(int cnt) {
//	if (cnt == m) {
//		string s = "";
//		for (int i = 0; i < m; ++i)
//			s += to_string(v2[i]);
//		if (!visit[s]) {
//			visit[s] = 1;
//			for (int i = 0; i < m; ++i) 
//				cout << v2[i] << " ";
//			cout << "\n";
//		}
//		return;
//	}
//	for (int i = 0; i < n; ++i) {
//		if (!check[i]) {
//			check[i] = 1;
//			v2.push_back(v[i]);
//			dfs(cnt + 1);
//			v2.pop_back();
//			check[i] = 0;
//		}
//	}
//}
//int main() {
//	ios::sync_with_stdio(0); cin.tie(0);
//	cin >> n >> m;
//	for (int i = 0; i < n; ++i) {
//		cin >> num;
//		v.push_back(num);
//	}
//	sort(v.begin(), v.end());
//	dfs(0);
//}

#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;
vector<int> v;
int arr[10];
bool check[10];
void brute(int index, int n, int m) {
	if (index == m) {
		for (int i = 0; i < m; i++)
			cout << arr[i] << ' ';
		cout << '\n';
		return;
	}
	bool used[10001] = {0,}; // 같은 자리에 같은 숫자가 올 수 없다 - 중복 방지
	for (int i = 0; i < n; i++) {
		if (check[i]) continue;
		if (used[v[i]]) continue;
		check[i] = true;
		used[v[i]] = true;
		arr[index] = v[i];
		brute(index + 1, n, m);
		check[i] = false;
	}
}
int main() {
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		int num;
		cin >> num;
		v.push_back(num);
	}
	sort(v.begin(), v.end());
	brute(0, n, m);
	return 0;
}
