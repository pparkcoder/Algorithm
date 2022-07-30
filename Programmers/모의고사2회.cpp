// 1번
#include <string>
#include <vector>
using namespace std;
vector<int> v;
int result = 0;
void brute(int index, int sum, int cnt){
    if(cnt == 3){
        if(!sum) ++result;
        return;
    }
    for(int i=index;i<v.size();++i){
        brute(i+1,sum+v[i],cnt+1);
    }
}
int solution(vector<int> number) {
    v = number;
    brute(0,0,0);
    return result;
}

// 2번
#include<iostream>
#include<map>
#include<vector>
using namespace std;
map<int,bool> visit1,visit2;
int cnt1[10001], cnt2[10001];
int solution(vector<int> top) {
    int answer = 0, pivot = 1;
    cnt1[top[0]] = visit1[top[0]] = 1;
    for(int i=pivot;i<top.size();++i){
        if(!visit2[top[i]]) visit2[top[i]] = 1;
        ++cnt2[top[i]];
    }
    while(1){
        if(pivot == top.size()) break;
        if(visit1.size() == visit2.size()) ++answer;
        if(!cnt1[top[pivot]]){
            cnt1[top[pivot]] = visit1[top[pivot]] = 1;
        }
        else{
            ++cnt1[top[pivot]];
        }
        if(--cnt2[top[pivot]] <= 0){
            cnt2[top[pivot]] = 0;
            visit2.erase(top[pivot]); // visit2[top[pivot]] = 0 으로 하면 해당 원소에 해당하는 데이터가 map에서 안지워짐
        }
        ++pivot;
    }
    return answer;
}

// 3번
#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;
queue<int> q;
vector<int> v[100001];
int visit[100001];
int bfs(int num,int dest){
    while(!q.empty()) q.pop();
    memset(visit,0,sizeof(visit));
    q.push(num);
    visit[num] = 1;
    while(!q.empty()){
        int now = q.front();q.pop();
        if(now == dest) return visit[dest] - 1;
        for(int i=0;i<v[now].size();++i){
            int next = v[now][i];
            if(!visit[next]){
                q.push(next);
                visit[next] = visit[now] + 1;
            }
        }
    }
    return -1;
}
vector<int> solution(int n, vector<vector<int>> roads, vector<int> sources, int destination) {
    vector<int> answer;
    for(int i=0;i<roads.size();++i){
        int a = roads[i][0];
        int b = roads[i][1];
        v[a].push_back(b);
        v[b].push_back(a);
    }
    for(int i=0;i<sources.size();++i){
        answer.push_back(bfs(sources[i],destination));
    }
    return answer;
}
