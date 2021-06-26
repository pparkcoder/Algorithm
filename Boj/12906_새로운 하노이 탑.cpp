// https://www.acmicpc.net/problem/12906
// 구조체 안에 cnt 넣은 경우 - 42924KB / 1128ms 
// visit으로 최소횟수 구한 경우 - 45288KB / 1328ms
// Tip -> 구조체 안에 cnt를 넣는 경우를 우선적으로 고려할 것

#include<iostream>
#include<queue>
#include<vector>
#include<string>
#include<map>
#define mt make_tuple
using namespace std;
typedef struct {
	string a, b, c;
	int cnt;
}info;
info I;
queue<info> q;
vector<string >v;
map<tuple<string, string, string>, bool> visit;

bool check(string a, string b, string c) {
	for (int i = 0; i < a.length(); ++i)
		if (a[i] != 'A') return false;
	for (int i = 0; i < b.length(); ++i)
		if (b[i] != 'B') return false;
	for (int i = 0; i < c.length(); ++i)
		if (c[i] != 'C') return false;
	return true;
}

int bfs() {
	string a, b, c, temp1, temp2;
	int cnt;
	I = { v[0],v[1],v[2],0 };
	q.push(I);
	visit[mt(v[0], v[1], v[2])] = 1;
	while (!q.empty()) {
		a = q.front().a;
		b = q.front().b;
		c = q.front().c;
		cnt = q.front().cnt; q.pop();
		if (check(a, b, c)) return cnt;
		temp1 = "", temp2 = "";
    
		if (a.length()) {
			for (int i = 0; i < a.length() - 1; ++i)
				temp1 += a[i];
			temp2 = a[a.length() - 1];
			if (!visit[mt(temp1, b + temp2, c)]) {
				I = { temp1,b + temp2,c,cnt + 1 };
				q.push(I);
				visit[mt(temp1, b + temp2, c)] = 1;
			}
			if (!visit[mt(temp1, b , c + temp2)]) {
				I = { temp1,b ,c + temp2,cnt + 1 };
				q.push(I);
				visit[mt(temp1, b, c + temp2)] = 1;
			}
		}
    
		if (b.length()) {
			temp1 = "", temp2 = "";
			for (int i = 0; i < b.length() - 1; ++i)
				temp1 += b[i];
			temp2 = b[b.length() - 1];
			if (!visit[mt(a + temp2, temp1, c)]) {
				I = { a + temp2, temp1, c,cnt+1 };
				q.push(I);
				visit[mt(a + temp2, temp1, c)] = 1;
			}
			if (!visit[mt(a, temp1, c + temp2)]) {
				I = { a , temp1, c + temp2,cnt + 1 };
				q.push(I);
				visit[mt(a , temp1, c + temp2)] = 1;
			}
		}
    
		if (c.length()) {
			temp1 = "", temp2 = "";
			for (int i = 0; i < c.length() - 1; ++i)
				temp1 += c[i];
			temp2 = c[c.length() - 1];
			if (!visit[mt(a + temp2, b, temp1)]) {
				I = { a + temp2, b, temp1,cnt + 1 };
				q.push(I);
				visit[mt(a + temp2, b, temp1)] = 1;
			}
			if (!visit[mt(a, b + temp2, temp1)]) {
				I = { a, b + temp2, temp1,cnt + 1 };
				q.push(I);
				visit[mt(a, b + temp2, temp1)] = 1;
			}
		}
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int num;
	string s;
	for (int i = 0; i < 3; ++i) {
		cin >> num;
		if (num) {
			cin >> s;
			v.push_back(s);
		}
		else
			v.push_back("");
	}
	cout << bfs();
}
