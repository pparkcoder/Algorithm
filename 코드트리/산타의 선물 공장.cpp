// https://www.codetree.ai/training-field/frequent-problems/santa-gift-factory/description?page=3&pageSize=20
// 각 함수에서 벨트의 상황에 따라 head, tail에 따른 예외처리 필요 -> head, tail을 신경 안쓰려면 포인터 필요
// **map에 값을 넣을때는 세분화 하여 넣기 -> BOX target.w = 10 (x) box[pos].w = 10 (o)

#include<iostream>
#include<unordered_map>
#include<vector>
using namespace std;
typedef struct {
	int id, w, next, prev, belt_num;
}BOX;
typedef struct {
	int head, tail, broken;
}BELT;
unordered_map<int, BOX> box; // pos, box정보
unordered_map<int, int> info; // id, pos
BELT belt[11];
int m;
bool empty(int belt_num) {
	if (belt[belt_num].head == 0) return true;
	return false;
}
void push(int pos, int belt_num) {
	if (empty(belt_num)) {
		belt[belt_num].head = belt[belt_num].tail = pos;
	}
	else {
		int prev = belt[belt_num].tail;
		box[prev].next = pos;
		box[pos].prev = prev;
		box[pos].next = 0;
		belt[belt_num].tail = pos;
	}
}
void remove(int pos, int belt_num) {
	int prev, next;
	if (belt[belt_num].head == belt[belt_num].tail) {
		belt[belt_num].head = belt[belt_num].tail = 0;
	}
	else if (belt[belt_num].head == pos) {
		next = box[pos].next;
		box[next].prev = 0;
		belt[belt_num].head = next;
	}
	else if (belt[belt_num].tail == pos) {
		prev = box[pos].prev;
		box[prev].next = 0;
		belt[belt_num].tail = prev;
	}
	else {
		prev = box[pos].prev;
		next = box[pos].next;
		box[prev].next = next;
		box[next].prev = prev;
	}
	info.erase(box[pos].id);
	box.erase(pos);
}
int f_500(int b_num) {
	if (belt[b_num].broken) return -1;
	belt[b_num].broken = 1;
	if (empty(b_num)) return b_num;
	int belt_num = b_num;
	int target = belt[b_num].head; 
	int flag = 0;
	while (1) {
		if (++belt_num > m) belt_num = 1;
		if (belt[belt_num].broken) continue;
		int prev = belt[belt_num].tail;
		if (!prev) flag = 1;
		else box[prev].next = target;
		box[target].prev = prev;
		while (1) {
			box[target].belt_num = belt_num;
			if (target == belt[b_num].tail) break;
			target = box[target].next;
		}
		belt[belt_num].tail = target;
		belt[b_num].head = belt[b_num].tail = 0;
		if(flag) belt[belt_num].head = belt[belt_num].tail = target;
		return b_num;
	}
}
int f_400(int f_id) {
	if (!info[f_id]) return -1;
	int pos = info[f_id];
	BOX target = box[pos];
	int belt_num = target.belt_num;
	if (belt[belt_num].head == pos) return belt_num;
	if (belt[belt_num].tail == pos) {
		int first = belt[belt_num].head;
		int prev = target.prev;

		belt[belt_num].head = pos;
		box[pos].prev = 0;
		box[prev].next = 0;
		box[pos].next = first;
		box[first].prev = pos;
		belt[belt_num].tail = prev;
	}
	else {
		int first = belt[belt_num].head;
		int prev = target.prev;
		int last = belt[belt_num].tail;

		belt[belt_num].head = pos;
		box[pos].prev = 0;
		box[prev].next = 0;
		box[last].next = first;
		box[first].prev = last;
		belt[belt_num].tail = prev;
	}
	return belt_num;
}
int f_300(int r_id) {
	if (!info[r_id]) return -1;
	int pos = info[r_id];
	BOX target = box[pos];
	remove(pos, target.belt_num);
	return r_id;
}
int f_200(int w_max) {
	int result = 0;
	for (int i = 1; i <= m; ++i) {
		if (empty(i) || belt[i].broken) continue;
		int pos = belt[i].head;
		BOX target = box[pos];
		if (target.w <= w_max) {
			result += target.w;
			remove(pos, i);
		}
		else {
			int next = box[pos].next;
			if (next) {
				box[next].prev = 0;
				belt[i].head = next;
			}
			push(pos, i);
		}
	}
	return result;
}
void f_100() {
	vector<int> id, w;
	int n, num, pos;
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		cin >> num;
		id.push_back(num);
	}
	for (int i = 1; i <= n; ++i) {
		cin >> num;
		w.push_back(num);
	}
	pos = 1;
	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= n / m; ++j) {
			box[pos].id = id[pos - 1];
			box[pos].w = w[pos - 1];
			box[pos].belt_num = i;
			push(pos, i);
			belt[i].broken = 0;
			info[id[pos - 1]] = pos;
			pos++;
		}
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int q, order, order2, result;
	cin >> q;
	while (q--) {
		cin >> order;
		if (order == 100) f_100();
		else {
			cin >> order2;
			if (order == 200) result = f_200(order2);
			else if (order == 300) result = f_300(order2);
			else if (order == 400) result = f_400(order2);
			else result = f_500(order2);
			cout << result << "\n";
		}
	}
}
