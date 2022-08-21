// 1번
#include <string>
#include <vector>

using namespace std;

int solution(int a, int b, int n) {
    int answer = 0, total = n;
    int num1, num2;
    while (1) {
        num1 = (total / a) * b;
        num2 = total % a;
        if (total < a) break;
        answer += num1;
        total = num1 + num2;
    }
    return answer;
}

// 2번
#include <string>
#include <vector>
#include <stack>

using namespace std;
stack<int> st;

int solution(vector<int> ingredient) {
    int answer = 0;
    for (int i = 0; i < ingredient.size(); ++i) {
        if (ingredient[i] == 1) {
            st.push(i);
            if (i + 3 <= ingredient.size() && ingredient[i + 1] == 2 && ingredient[i + 2] == 3 && ingredient[i + 3] == 1) {
                st.pop();
                ++answer;
                ingredient.erase(ingredient.begin() + i, ingredient.begin() + i + 4);
                if (st.size()) {
                    i = st.top() - 1;
                    st.pop();
                }

            }
        }
    }
    return answer;
}

// 3번
#include <vector>
#include <algorithm>
#include <iostream>

#define mp make_pair
using namespace std;
vector<pair<pair<int, int>, pair<int, int> > > v;

int solution(int distance, vector<vector<int>> scope, vector<vector<int>> times) {
    int st_d, ed_d, st_t, ed_t, tum, temp, index, t, answer;
    for (int i = 0; i < scope.size(); ++i) {
        int temp1 = scope[i][0];
        int temp2 = scope[i][1];
        if (temp1 < temp2) v.push_back(mp(mp(scope[i][0], scope[i][1]), mp(times[i][0], times[i][1])));
        else v.push_back(mp(mp(scope[i][1], scope[i][0]), mp(times[i][0], times[i][1])));
    }
    sort(v.begin(), v.end());
    answer = t = index = 0;
    while (1) {
        ++t;
        ++answer;
        if (answer == distance) break;
        if (index < v.size()) {
            st_d = v[index].first.first;
            ed_d = v[index].first.second;
            if (st_d <= answer && answer <= ed_d) {
                st_t = v[index].second.first;
                ed_t = v[index].second.second;
                tum = st_t + ed_t;
                temp = t % tum;
                if (temp && temp <= st_t) break;
                if (answer == ed_d) ++index;
            }
        }
    }
    return answer;
}
