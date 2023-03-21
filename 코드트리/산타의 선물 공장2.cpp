// https://www.codetree.ai/training-field/frequent-problems/santa-gift-factory-2/description?page=3&pageSize=20
// 각 상자들이 몇번 벨트에 있는지는 중요하지 않음 -> f200에서 전체를 옮길 때 반복문을 돌면서 상자에 따른 벨트 번호를 옮겨주면 시간 초과
// 각 벨트의 총 개수만 중요 + 상자들끼리 연결이 잘 처리 되었다면 각 벨트의 head와 tail만으로 해당 상자의 위치를 알 수 있음
// head, tail, prev, next 설계 시 빠진 부분 없는지 잘 체크

#include<iostream>
#include<cmath>
#include<unordered_map>
using namespace std;
typedef struct {
	int prev, next, belt;
}BOX;
typedef struct {
	int head, tail, cnt;
}BELT;
unordered_map<int, BOX> box;
BELT belt[100001];
int q, n, m;
bool empty(int num) {
	if (belt[num].head == 0) return true;
	return false;
}
void push(int pos, int num) {
	if (empty(num)) {
		belt[num].head = belt[num].tail = pos;
	}
	else {
		int prev = belt[num].tail;
		box[prev].next = pos;
		box[pos].prev = prev;
		box[pos].next = 0;
		belt[num].tail = pos;
	}
	++belt[num].cnt;
}
int f600(int b_num) {
	int a = belt[b_num].head;
	int b = belt[b_num].tail;
	int c = belt[b_num].cnt;
	if (c < 1) {
		a = b = -1;
		c = 0;
	}
	return a + 2 * b + 3 * c;
}
int f500(int p_num) {
	int a = box[p_num].prev;
	int b = box[p_num].next;
	if (!a) a = -1;
	if (!b) b = -1;
	return a + 2 * b;
}
int f400(int src, int dest) {
	int cnt = belt[src].cnt;
	int new_cnt = floor(cnt / 2);
	if (new_cnt) {
		int idx = belt[src].head;
		for (int i = 1; i <= new_cnt; ++i) {
			--belt[src].cnt;
			++belt[dest].cnt;
			idx = box[idx].next;
		}
		int next = idx;
		if (!belt[dest].head) {
			belt[dest].head = belt[src].head;
			if (next) {
				belt[dest].tail = box[next].prev;
				box[box[next].prev].next = 0;
				belt[src].head = next;
				box[next].prev = 0;
			}
			else {
				belt[dest].tail = belt[src].tail;
				belt[src].head = belt[src].tail = 0;
			}
		}
		else {
			int first = belt[src].head;
			int target = belt[dest].head;
			int last;
			if (next) {
				last = box[next].prev;
				belt[src].head = next;
				box[next].prev = 0;
			}
			else {
				last = belt[src].tail;
				belt[src].head = belt[src].tail = 0;
			}
			belt[dest].head = first;
			box[last].next = target;
			box[target].prev = last;
		}
	}
	return belt[dest].cnt;
}
int f300(int src, int dest) {
	int idx_src = belt[src].head;
	int idx_dest = belt[dest].head;
	if (!idx_src && !idx_dest) return 0;
	if (!idx_src && idx_dest) {
		int target = belt[dest].head;
		int next = box[target].next;
		box[target].next = box[target].prev = 0;
		--belt[dest].cnt;
		++belt[src].cnt;
		belt[dest].head = next;
		box[next].prev = 0;
		if (!next) belt[dest].tail = 0;
		belt[src].head = belt[src].tail = target;
	}
	else if (idx_src && !idx_dest) {
		int target = belt[src].head;
		int next = box[target].next;
		box[target].next = box[target].prev = 0;
		--belt[src].cnt;
		++belt[dest].cnt;
		belt[src].head = next;
		box[next].prev = 0;
		if (!next) belt[src].tail = 0;
		belt[dest].head = belt[dest].tail = target;
	}
	else {
		int src_target = belt[src].head;
		int src_next = box[src_target].next;
		int dest_target = belt[dest].head;
		int dest_next = box[dest_target].next;
		belt[src].head = dest_target;
		box[dest_target].next = src_next;
		if(src_next) box[src_next].prev = dest_target;
		else belt[src].tail = dest_target;
		belt[dest].head = src_target;
		box[src_target].next = dest_next;
		if(dest_next) box[dest_next].prev = src_target;
		else belt[dest].tail = src_target;
	}
	return belt[dest].cnt;
}
int f200(int src, int dest) {
	int idx = belt[src].head;
	if (!idx) return belt[dest].cnt;
	belt[dest].cnt += belt[src].cnt;
	belt[src].cnt = 0;
	if (!belt[dest].head) {
		belt[dest].head = belt[src].head;
		belt[dest].tail = belt[src].tail;
		belt[src].head = belt[src].tail = 0;
	}
	else {
		int first = belt[src].head; belt[src].head = 0;
		int last = belt[src].tail; belt[src].tail = 0;
		int target = belt[dest].head;
		belt[dest].head = first;
		box[last].next = target;
		box[target].prev = last;
	}
	return belt[dest].cnt;
}
void f100() {
	cin >> n >> m;
	int num;
	for (int i = 1; i <= m; ++i) {
		cin >> num;
		push(i, num);
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> q;
	int order, result, src, dest;
	while (q--) {
		cin >> order;
		if (order == 100) f100();
		else {
			if (200 <= order && order <= 400) {
				cin >> src >> dest;
				if (order == 200) result = f200(src, dest);
				else if (order == 300) result = f300(src, dest);
				else result = f400(src, dest);
			}
			else {
				cin >> src;
				if (order == 500) result = f500(src);
				else result = f600(src);
			}
			cout << result << "\n";
		}
	}
}

/* 시간초과 코드
#include<iostream>
#include<cmath>
#include<unordered_map>
using namespace std;
typedef struct {
	int prev, next, belt;
}BOX;
typedef struct {
	int head, tail, cnt;
}BELT;
unordered_map<int, BOX> box;
BELT belt[100001];
int q, n, m;
bool empty(int num) {
	if (belt[num].head == 0) return true;
	return false;
}
void push(int pos, int num) {
	if (empty(num)) {
		belt[num].head = belt[num].tail = pos;
	}
	else {
		int prev = belt[num].tail;
		box[prev].next = pos;
		box[pos].prev = prev;
		box[pos].next = 0;
		belt[num].tail = pos;
	}
	++belt[num].cnt;
}
int f600(int b_num) {
	int a = belt[b_num].head;
	int b = belt[b_num].tail;
	int c = belt[b_num].cnt;
	if (c < 1) {
		a = b = -1;
		c = 0;
	}
	return a + 2 * b + 3 * c;
}
int f500(int p_num) {
	int a = box[p_num].prev;
	int b = box[p_num].next;
	if (!a) a = -1;
	if (!b) b = -1;
	return a + 2 * b;
}
int f400(int src, int dest) {
	int cnt = belt[src].cnt;
	int new_cnt = floor(cnt / 2);
	if (new_cnt) {
		int idx = belt[src].head;
		for (int i = 1; i <= new_cnt; ++i) {
			--belt[src].cnt;
			box[idx].belt = dest;
			++belt[dest].cnt;
			idx = box[idx].next;
		}
		int next = idx;
		if (!belt[dest].head) {
			belt[dest].head = belt[src].head;
			if (next) {
				belt[dest].tail = box[next].prev;
				box[box[next].prev].next = 0;
				belt[src].head = next;
				box[next].prev = 0;
			}
			else {
				belt[dest].tail = belt[src].tail;
				belt[src].head = belt[src].tail = 0;
			}
		}
		else {
			int first = belt[src].head;
			int target = belt[dest].head;
			int last;
			if (next) {
				last = box[next].prev;
				belt[src].head = next;
				box[next].prev = 0;
			}
			else {
				last = belt[src].tail;
				belt[src].head = belt[src].tail = 0;
			}
			belt[dest].head = first;
			box[last].next = target;
			box[target].prev = last;
		}
	}
	return belt[dest].cnt;
}
int f300(int src, int dest) {
	int idx_src = belt[src].head;
	int idx_dest = belt[dest].head;
	if (!idx_src && !idx_dest) return 0;
	if (!idx_src && idx_dest) {
		int target = belt[dest].head;
		int next = box[target].next;
		box[target].next = box[target].prev = 0;
		--belt[dest].cnt;
		box[target].belt = src;
		++belt[src].cnt;
		belt[dest].head = next;
		box[next].prev = 0;
		if (!next) belt[dest].tail = 0;
		belt[src].head = belt[src].tail = target;
	}
	else if (idx_src && !idx_dest) {
		int target = belt[src].head;
		int next = box[target].next;
		box[target].next = box[target].prev = 0;
		--belt[src].cnt;
		box[target].belt = dest;
		++belt[dest].cnt;
		belt[src].head = next;
		box[next].prev = 0;
		if (!next) belt[src].tail = 0;
		belt[dest].head = belt[dest].tail = target;
	}
	else {
		int src_target = belt[src].head;
		int src_next = box[src_target].next;
		int dest_target = belt[dest].head;
		int dest_next = box[dest_target].next;
		belt[src].head = dest_target;
		box[dest_target].belt = src;
		box[dest_target].next = src_next;
		if(src_next) box[src_next].prev = dest_target;
		else belt[src].tail = dest_target;
		belt[dest].head = src_target;
		box[src_target].belt = dest;
		box[src_target].next = dest_next;
		if(dest_next) box[dest_next].prev = src_target;
		else belt[dest].tail = src_target;
	}
	return belt[dest].cnt;
}
int f200(int src, int dest) {
	int idx = belt[src].head;
	if (!idx) return belt[dest].cnt;
	while (idx) {
		--belt[src].cnt;
		box[idx].belt = dest;
		++belt[dest].cnt;
		idx = box[idx].next;
	}
	if (!belt[dest].head) {
		belt[dest].head = belt[src].head;
		belt[dest].tail = belt[src].tail;
		belt[src].head = belt[src].tail = 0;
	}
	else {
		int first = belt[src].head; belt[src].head = 0;
		int last = belt[src].tail; belt[src].tail = 0;
		int target = belt[dest].head;
		belt[dest].head = first;
		box[last].next = target;
		box[target].prev = last;
	}
	return belt[dest].cnt;
}
void f100() {
	cin >> n >> m;
	int num;
	for (int i = 1; i <= m; ++i) {
		cin >> num;
		box[i].belt = num;
		push(i, num);
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> q;
	int order, result, src, dest;
	while (q--) {
		cin >> order;
		if (order == 100) f100();
		else {
			if (200 <= order && order <= 400) {
				cin >> src >> dest;
				if (order == 200) result = f200(src, dest);
				else if (order == 300) result = f300(src, dest);
				else result = f400(src, dest);
			}
			else {
				cin >> src;
				if (order == 500) result = f500(src);
				else result = f600(src);
			}
			cout << result << "\n";
		}
	}
}
*/
