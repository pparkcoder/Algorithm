// https://www.acmicpc.net/problem/1662
// Solving -> 괄호 앞의 숫자는 그대로, 나머지는 1로 push
// Tip -> to_string(숫자)만 가능 -> to_string('(') (X) -> 시간이 오래 걸렸던 이유

// to_string 함수
// string to_string (int num);
// string to_string (long num);
// string to_string (long long num);
// string to_string (unsigned num);
// string to_string (unsigned long num);
// string to_string (unsigned long long num);
// string to_string (float num);
// string to_string (double num);
// string to_string (long double num);

#include<iostream>
#include<string>
#include<stack>
using namespace std;
stack<string> st;
string s, temp, t = "";
int cnt, res = 0;
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> s;
	for (int i = 0; i < s.length(); ++i) {
		cnt = 0;
		if (s[i] == ')') {
			while (1) {
				temp = st.top(); st.pop();
				if (temp == "(") break;
				cnt += stoi(temp);
			}
			cnt *= stoi(st.top()); st.pop();
			st.push(to_string(cnt));
		}
		else if (s[i] == '(') st.push(s[i] + t);
		else {
			if (i == s.length() - 1) st.push("1");
			else {
				if ('0' <= s[i] && s[i] <= '9' && s[i + 1] == '(') st.push(s[i]+t);
				else st.push("1");
			}
		}
	}
	while (!st.empty()) {
		res += stoi(st.top());
		st.pop();
	}
	cout << res;
}
