// 1번
#include <string.h>
#include <vector>
#include <iostream>
using namespace std;
int visit[10],visit2[10];
string solution(string X, string Y) {
    string answer = "";
    for(int i=0;i<X.length();++i){
        if('0' <= X[i] && X[i] <= '9') {
            ++visit[X[i] - '0'];
        }
    }
    for(int i=0;i<Y.length();++i) {
        if ('0' <= Y[i] && Y[i] <= '9') {
            ++visit2[Y[i] - '0'];
        }
    }
    for(int i=9;i>=0;--i){
        if(visit[i] && visit2[i]){
            --visit[i];
            --visit2[i];
            answer += (to_string(i));
            ++i;
        }
    }
    if(answer == "") return "-1";
    else if(answer[0] == '0') return "0";
    else return answer;
}

// 2번
#include <string>
#include <vector>
#include<map>
using namespace std;
map<string,int> check,temp;
int solution(vector<string> want, vector<int> number, vector<string> discount) {
    int result = 0, stop = 1;
    for(int i=0;i<want.size();++i) check[want[i]] = number[i];
    for(int i=0;i<10;++i) ++temp[discount[i]];
    for(int i=10;i<=discount.size();++i){
        int flag = 0;
        if(!stop) ++temp[discount[i - 1]];
        for(int j=0;j<want.size();++j){
            if(check[want[j]] != temp[want[j]]){
                flag = 1;
                break;
            }
        }
        if(!flag) ++result;
        stop = 0;
        --temp[discount[i - 10]];
    }
    return result;
}

// 3번
#include <string>
#include <vector>
#include <queue>
#include<stack>
#include<iostream>
using namespace std;
stack<int> s;
queue<int> q;
int solution(vector<int> order) {
    int result = 0;
    for(int i=1;i<=order.size();++i) q.push(i);
    for(int i=0;i<order.size();++i){
        if(!q.empty()){
            if(q.front() == order[i]){
                q.pop();
                ++result;
            }
            else{
                if(s.size() && s.top() == order[i]){
                    s.pop();
                    ++result;
                }
                else{
                    int temp = q.front();
                    q.pop();
                    s.push(temp);
                    --i;
                }
            }
        }
        else{
            if(s.top() == order[i]){
                s.pop();
                ++result;
            }
            else break;
        }
    }
    return result;
}

// 4번
#include <string>
#include <vector>
#include <set>
#include <cmath>
#include <iostream>

using namespace std;
set<string> s;
int map[11][11];
string start = "", dest = "";
int result = 987654321, len;

void show() {
    cout << "\n";
    for (int i = 1; i <= len; ++i) {
        for (int j = 1; j <= len; ++j)
            cout << map[i][j] << " ";
        cout << "\n";
    }
}

void make_map(string temp) {
    int index = 0;
    for (int i = 1; i <= len; ++i)
        for (int j = 1; j <= len; ++j)
            map[i][j] = temp[index++] - '0';
}

void brute(int flag, string temp, int cnt) {
    if (cnt && temp == dest) {
        result = cnt;
        return;
    }
    for (int i = 0; i < 2; ++i) {
        for (int j = flag; j <= len; ++j) {
            make_map(temp);
            string temp2 = "";

            for (int k = 1; k <= len; ++k) {
                if (!i) map[j][k] = abs(1 - map[j][k]);
                else map[k][j] = abs(1 - map[k][j]);
            }

            for (int k = 1; k <= len; ++k)
                for (int l = 1; l <= len; ++l)
                    temp2 += to_string(map[k][l]);

            if(s.find(temp2) == s.end()) {
                s.insert(temp2);
                brute(j, temp2, cnt + 1);
                s.erase(s.find(temp2));
            }
        }
    }
}

int solution(vector<vector<int>> beginning, vector<vector<int>> target) {
    len = beginning.size();
    for (int i = 0; i < beginning.size(); ++i) {
        for (int j = 0; j < beginning[i].size(); ++j) {
            start += to_string(beginning[i][j]);
            dest += to_string(target[i][j]);
        }
    }
    if (start == dest) return 0;
    else {
        s.insert(start);
        brute(1, start, 0);
        return (result == 987654321 ? -1 : result);
    }
}
