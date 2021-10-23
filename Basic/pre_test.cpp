// 1번 - branch : 1번 나무에 붙음 , merge A - A번 나뭇가지가 1번 나무에 붙고, 사라짐
//for (int i = 0; i < n; ++i) {
//	if (q[i].first == 'branch') {
//		max_num = max(max_num, cnt);
//		used[cnt] = 1;
//		if (check[cnt]) check[cnt] = 0;
//		++cnt;
//	}
//	else {
//		num = q[i].second;
//		used[num] = 0;
//		check[num] = (check[num] == 1 ? 0 : 1);
//		if (now > num) now = num;
//		else {
//			for (int j = now; j <= max_num; ++j) {
//				if (!used[j]) {
//					now = j;
//					break;
//				}
//			}
//		}
//	}
//}

// 2번 - k개를 뽑아 가장 많이 속하는 것 찾기
//void brute(int cnt, int index) {
//	if (cnt == k) {
//		for (int i = 0; i < n; ++i) {
//			for (int j = 0; j < num[i]; ++j) {
//				for (int l = 0; l < v.size(); ++l) {
//					if (map[i][j] == v[l]) {
//						++ans;
//						break;
//					}
//				}
//			}
//		}
//		result = max(result, ans);
//		return;
//	}
//	for (int i = index; i < k; ++i) {
//		v2.push_back(v[i]);
//		brute(cnt + 1, i + 1);
//		v2.pop_back();
//	}
//}

// 3번 - (8명 줄 세우기 - 이웃하는 경우)
//void brute(int cnt) {
//	if (cnt == 8) {
//		for (int i = 0; i < n; ++i) {
//			for (int j = 1; j < v.size(); ++j) {
//				if ((v[j - 1] == pairs[i].first && v[j] == pairs[i].second) || (v[j - 1] == pairs[i].second && v[j] == pairs[i].first)) {
//					++result;
//					return;
//				}
//			}
//		}
//		return;
//	}
//}
