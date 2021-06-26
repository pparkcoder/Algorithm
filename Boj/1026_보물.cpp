// https://www.acmicpc.net/problem/1026
// 배열 vs sort 실행시간 측정

/*-------------------------------------*/
/*배열 이용시 330ms*/

#include<iostream>
#include<algorithm>
using namespace std;
int a[50], b[50];
int n;
int sum = 0;
bool cmp(int one, int two) {
	if (one > two) return true;
	else return false;
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	for (int i = 0; i < n; ++i)
		cin >> b[i];
	sort(a, a + n);
	sort(b, b + n, cmp);
	for (int i = 0; i < n; ++i) 
		sum += (a[i] * b[i]);
	cout << sum;
}

/*-------------------------------------*/
/*vector + cmp함수 이용시 15303ms*/

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
vector<int> a, b;
int n, num;
int sum = 0;
bool cmp(int one, int two) {
	if (one > two) return true;
	else return false;
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> num;
		a.push_back(num);
	}
	for (int i = 0; i < n; ++i) {
		cin >> num;
		b.push_back(num);
	}
	sort(a.begin(), a.end());
	sort(b.begin(), b.end(),cmp);
	for (int i = 0; i < n; ++i) 
		sum += (a[i] * b[i]);
	cout << sum;
}

/*-------------------------------------*/
/*vector + reverse함수 이용시 4111ms*/

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
vector<int> a, b;
int n, num;
int sum = 0;
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> num;
		a.push_back(num);
	}
	for (int i = 0; i < n; ++i) {
		cin >> num;
		b.push_back(num);
	}
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	reverse(b.begin(), b.end());
	for (int i = 0; i < n; ++i) 
		sum += (a[i] * b[i]);
	cout << sum;
}
