//https://www.acmicpc.net/problem/16235
//TLE -> vector의 초기화(clear)와 data를 옮겨주는 과정(Line 55) 때문
//Solving -> deque를 이용하여 초기화하는 과정을 없애주고, data를 옮겨주는 과정을 pop과 push를 이용하여 구현
// sort는 한번만 가능 -> 처음에 나이순 정렬 -> 다음부터 나이순으로 알아서 된다 -> 중요한건 새로 생긴 나무는 앞에서 넣어주기

//#include<iostream>
//#include<vector>
//#include<algorithm>
//#define mp make_pair
//using namespace std;
//vector<pair<int, pair<int, int> > > temp, alive, die;
//vector<pair<int, int> >five;
//int map[11][11], energy[11][11];
//int dx[8] = { -1,-1,-1,0,0,1,1,1 };
//int dy[8] = { -1,0,1,-1,1,-1,0,1 };
//int n, m, k, x, y, age, nx, ny;
//void start() {
//	sort(alive.begin(), alive.end());
//	while (k--) {
//		for (int i = 0; i < alive.size(); ++i) { // 봄
//			age = alive[i].first;
//			x = alive[i].second.first;
//			y = alive[i].second.second;
//			if (map[x][y] - age >= 0) {
//				map[x][y] -= age;
//				temp.push_back(mp(age + 1, mp(x, y)));
//				if ((age + 1) % 5 == 0)
//					five.push_back(mp(x, y));
//			}
//			else
//				die.push_back(mp(age / 2, mp(x, y)));
//		}
//		alive.clear();
//		for (int i = 0; i < die.size(); ++i) { // 여름
//			age = die[i].first;
//			x = die[i].second.first;
//			y = die[i].second.second;
//			map[x][y] += age;
//		}
//		die.clear();
//		for (int i = 0; i < five.size(); ++i) { // 가을
//			x = five[i].first;
//			y = five[i].second;
//			for (int j = 0; j < 8; ++j) {
//				nx = x + dx[j];
//				ny = y + dy[j];
//				if (1 > nx || nx > n || 1 > ny || ny > n) continue;
//				temp.insert(temp.begin(), (mp(1, mp(nx, ny))));
//			}
//		}
//		five.clear();
//		for (int i = 1; i <= n; ++i) // 겨울
//			for (int j = 1; j <= n; ++j)
//				map[i][j] += energy[i][j];
//		alive = temp;
//		temp.clear();
//	}
//	cout << alive.size();
//}
//int main() {
//	ios::sync_with_stdio(0); cin.tie(0);
//	cin >> n >> m >> k;
//	for (int i = 1; i <= n; i++) {
//		for (int j = 1; j <= n; j++) {
//			cin >> energy[i][j];
//			map[i][j] = 5;
//		}
//	}
//	while (m--) {
//		cin >> x >> y >> age;
//		alive.push_back(mp(age, mp(x, y)));
//	}
//	start();
//}

#include<iostream>
#include<vector>
#include<deque>
#include<algorithm>
#define mp make_pair
using namespace std;
vector<pair<int, pair<int, int> > > v;
deque<pair<int, pair<int, int> > > temp, alive, die;
deque<pair<int, int> > five;
int map[11][11], energy[11][11];
int dx[8] = { -1,-1,-1,0,0,1,1,1 };
int dy[8] = { -1,0,1,-1,1,-1,0,1 };
int n, m, k, x, y, age, nx, ny;
void start() {
	sort(v.begin(), v.end());
	for (int i = 0; i < v.size(); ++i)
		alive.push_back(mp(v[i].first, mp(v[i].second.first, v[i].second.second)));
	while (k--) {
		while (!alive.empty()) { // 봄
			age = alive.front().first;
			x = alive.front().second.first;
			y = alive.front().second.second; alive.pop_front();
			if (map[x][y] - age >= 0) {
				map[x][y] -= age;
				temp.push_back(mp(age + 1, mp(x, y)));
				if ((age + 1) % 5 == 0)
					five.push_back(mp(x, y));
			}
			else
				die.push_back(mp(age / 2, mp(x, y)));
		}
		while (!die.empty()) { // 여름
			age = die.front().first;
			x = die.front().second.first;
			y = die.front().second.second; die.pop_front();
			map[x][y] += age;
		}
		while (!five.empty()) { // 가을
			x = five.front().first;
			y = five.front().second; five.pop_front();
			for (int j = 0; j < 8; ++j) {
				nx = x + dx[j];
				ny = y + dy[j];
				if (1 > nx || nx > n || 1 > ny || ny > n) continue;
				temp.push_front(mp(1, mp(nx, ny)));
			}
		}
		for (int i = 1; i <= n; ++i) // 겨울
			for (int j = 1; j <= n; ++j)
				map[i][j] += energy[i][j];
		alive.swap(temp);
		while (!temp.empty())
			temp.pop_back();
	}
	cout << alive.size();
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> energy[i][j];
			map[i][j] = 5;
		}
	}
	while (m--) {
		cin >> x >> y >> age;
		v.push_back(mp(age, mp(x, y)));
	}
	start();
}
