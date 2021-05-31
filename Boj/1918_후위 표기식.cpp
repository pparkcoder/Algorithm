// https://www.acmicpc.net/problem/1918
// Solving -> 연산자를 pop 하는 과정에서 우선순위를 고려하는 과정이 필요
// 현재 연산자가 stack의 top의 연산자의 우선순위보다 높은 경우 : 현재 연산자 push
// 현재 연산자가 stack의 top의 연산자의 우선순위보다 낮거나 같은 경우 : stack에서 현재 연산자보다 낮은 연산자가 나오기 '전'까지 pop 하며 출력
// '(' 를 push 후, ')' 를 만나면 '(' 까지 모든 연산자 pop , '('는 출력x

#include<string>
#include<iostream>
#include<stack>
using namespace std;
stack<char> st;
string s;
int flag;
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> s;
	for (int i = 0; i < s.length(); ++i) {
		if ('A' <= s[i] && s[i] <= 'Z') cout << s[i];
		else {
			if (s[i] == '(') st.push(s[i]);
			else if (s[i] == ')') {
				flag = 1;
				while (flag) {
					if (st.top() == '(') flag = 0;
					if (flag) cout << st.top();
					st.pop();
				}
			}
			else {
				if (!st.empty()) {
					if ((s[i] == '*' || s[i] == '/') && (st.top() == '+' || st.top() == '-')) // 현재 연산자가 stack의 top의 연산자의 우선순위보다 높은 경우
						st.push(s[i]);
					else {        // 현재 연산자가 stack의 top의 연산자의 우선순위보다 낮거나 같은 경우
						while (!st.empty()) {
							if ((s[i] == '*' || s[i] == '/') && (st.top() == '+' || st.top() == '-')) break;
							if (st.top() == '(') break;
							cout << st.top();
							st.pop();
						}
						st.push(s[i]);
					}
				}
				else  //stack이 비었으면 무조건 연산자 push
					st.push(s[i]);
			} 
		}
	}
	while (!st.empty()) {
		cout << st.top();
		st.pop();
	}
}
