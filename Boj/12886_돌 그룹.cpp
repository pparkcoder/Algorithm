// https://www.acmicpc.net/problem/12886
// 시간 줄이는 방법 생각해 보기
#include<iostream>
#include<queue>
#include<vector>
#include<string>
#include<algorithm>
#include<map>
using namespace std;
typedef struct {
	int a, b, c;
}info;
info I;
queue<info> q;
vector<int> v;
map<string, int> visit;
string s;
void calc(int a, int b, int c) {
	s = "";
	v.push_back(a);
	v.push_back(b);
	v.push_back(c);
	sort(v.begin(), v.end()); // sort를 안하면 : 1128 -> 1, 12, 8 과 11, 2, 8 이 같은 경우가 된다.
	for (int i = 0; i < 3; i++) s += to_string(v[i]);
	if (!visit[s]) {
		I = { a,b,c };
		q.push(I);
		visit[s] = 1;
	}
	v.clear();
}
int bfs() {
	int a, b, c;
	while (!q.empty()) {
		a = q.front().a;
		b = q.front().b;
		c = q.front().c; q.pop();
		if (a == b && b == c) return 1;
		if (a > b) calc(a - b, b + b, c);
		if (a < b) calc(a + a, b - a, c);
		if (a > c) calc(a - c, b, c + c);
		if (a < c) calc(a + a, b, c - a);
		if (b > c) calc(a, b - c, c + c);
		if (b < c) calc(a, b + b, c - b);
	}
	return 0;
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int n1, n2, n3;
	cin >> n1 >> n2 >> n3;
	calc(n1, n2, n3);
	cout << bfs();
}
