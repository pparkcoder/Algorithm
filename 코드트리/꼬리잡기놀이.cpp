// https://www.codetree.ai/frequent-problems/tail-catch-play/description
// 팀의 정보를 넣을 때, 1에서 시작하여 2까지 넣고 마지막 2에서 3을 찾아서 push
// 무조건 1은 3 or 4를 찾고, 3은 1 or 4를 찾음
// 방향에 따라 움직일 때, 좌표가 앞에서부터 바뀌는지 뒤에서부터 바뀌는지 check
// 공을 던질 때, 방향은 틀지만 꼭지점의 점들은 한번씩 더 등장

#include<iostream>
#include<vector>
#include<cmath>
#include<cstring>
#define mp make_pair
using namespace std;
typedef struct {
    int x, y, num;
}info;
info I;
vector<info> team[6];
queue<pair<int, int> > q;
pair<int, int> map[21][21]; // 순서번호, 팀번호 - 공에 맞았을 때 어떤 팀의 누구인지를 찾기 위해
bool visit[21][21], flag[6]; // 0 : 머리방향으로 진행, 1 : 꼬리방향으로 진행
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };
int n, m, k;
int result = 0, sx = 1, sy = 1, dir1 = 0, dir2 = 1, check = 0;
void ball() {
    int tx, ty, nx, ny, team_num, cnt;
    int stop = 0;
    for (int i = 0;; ++i) {
        nx = sx + dx[dir2] * i;
        ny = sy + dy[dir2] * i;
        if (1 > nx || nx > n || 1 > ny || ny > n) break;
        if (1 <= map[nx][ny].first && map[nx][ny].first <= 3) {
            team_num = map[nx][ny].second;
            cnt = 1;
            if (!flag[team_num]) {
                for (int j = 0; j < team[team_num].size(); ++j) {
                    if (team[team_num][j].x == nx && team[team_num][j].y == ny) {
                        flag[team_num] = !flag[team_num];
                        result += pow(cnt, 2);
                        stop = 1;
                        break;
                    }
                    ++cnt;
                }
            }
            else {
                for (int j = team[team_num].size() - 1; j >= 0; --j) {
                    if (team[team_num][j].x == nx && team[team_num][j].y == ny) {
                        flag[team_num] = !flag[team_num];
                        result += pow(cnt, 2);
                        stop = 1;
                        break;
                    }
                    ++cnt;
                }
            }
        }
        if (stop) break;
    }
    tx = sx;
    ty = sy;
    nx = tx + dx[dir1];
    ny = ty + dy[dir1];
    if (1 > nx || nx > n || 1 > ny || ny > n) {
        if (++dir1 > 3) dir1 = 0;
        if (++dir2 > 3) dir2 = 0;
        nx = tx + dx[dir1];
        ny = ty + dy[dir1];
        check = 1; // 처음 범위를 벗어난 경우
    }
    sx = nx;
    sy = ny;
    if (check) { // 좌표는 그대로, 공이 나오는 방향만 바꿈
        sx -= dx[dir1];
        sy -= dy[dir1];
        check = 0;
    }
}
pair<int, int> find_first(int x, int y, int team_num) {
   int nx, ny, num1;
   int num2 = 4;
   if(!flag[team_num]) num1 = 3;
   else num1 = 1;
   for(int i=0;i<4;++i){
       nx = x + dx[i];
       ny = y + dy[i];
       if(0 < nx && nx <= n && 0 < ny && ny <= n){
           if(map[nx][ny].first == num1 || map[nx][ny].first== num2) return mp(nx,ny);
       }
   }
}
void move() {
    int x, y, tx,ty, nx, ny, num,temp;
    pair<int, int> next;
    for (int i = 1; i <= m; ++i) {
        if (!flag[i]) { // 머리부터 방향 찾기
            next = find_first(team[i][0].x,team[i][0].y,i);
            tx = next.first;
            ty = next.second;
            temp = map[tx][ty].first;
            for(int j=team[i].size() - 1;j > 0;--j){
                x = team[i][j].x;
                y = team[i][j].y;
                num = team[i][j].num;
                nx = team[i][j - 1].x;
                ny = team[i][j - 1].y;
                map[nx][ny] = mp(num,i);
                team[i][j].x = nx;
                team[i][j].y = ny;
                if(j == team[i].size() - 1 && temp == 4) map[x][y] = mp(4,0);
            }
            map[tx][ty] = mp(1,i);
            team[i][0].x = tx;
            team[i][0].y = ty;
        }
        else { // 꼬리부터 방향 찾기
            next = find_first(team[i][team[i].size() - 1].x,team[i][team[i].size() - 1].y,i);
            tx = next.first;
            ty = next.second;
            temp = map[tx][ty].first;
            for(int j=0;j<team[i].size() - 1;++j){
                x = team[i][j].x;
                y = team[i][j].y;
                num = team[i][j].num;
                nx = team[i][j + 1].x;
                ny = team[i][j + 1].y;
                map[nx][ny] = mp(num,i);
                team[i][j].x = nx;
                team[i][j].y = ny;
                if(j == 0 && temp == 4) map[x][y] = mp(4,0);
            }
            map[tx][ty] = mp(3,i);
            team[i][team[i].size() - 1].x = tx;
            team[i][team[i].size() - 1].y = ty;
        }
    }
}
void find_team(int tx,int ty,int team_num) {
    int x = tx, y = ty;
    int nx, ny, stop;
    visit[x][y] = 1;
    while(1){
        stop = 0;
        for(int i=0;i<4;++i) {
            nx = x + dx[i];
            ny = y + dy[i];
            if (0 < nx && nx <= n && 0 < ny && ny <= n && !visit[nx][ny] && map[nx][ny].first == 2) {
                I = {nx, ny, 2};
                team[team_num].push_back(I);
                visit[nx][ny] = 1;
                map[nx][ny].second = team_num;
                stop = 1;
                break;
            }
        }
        if(!stop) break;
        x = nx;
        y = ny;
    }
    for(int i=0;i<4;++i){
        nx = x + dx[i];
        ny = y + dy[i];
        if(0 < nx && nx <= n && 0 < ny && ny <=n && map[nx][ny].first == 3){
            I = {nx,ny,3};
            team[team_num].push_back(I);
            break;
        }
    }
    memset(visit,0,sizeof(visit));
}
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m >> k;
    int num = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> map[i][j].first;
            if (map[i][j].first == 1) {
                I = { i,j,1 };
                team[num].push_back(I);
                map[i][j].second = num++;
            }
        }
    }
   for(int i=1;i<=m;++i)
       find_team(team[i][0].x,team[i][0].y,i);
    for (int i = 1; i <= k; ++i) {
        move();
        ball();
    }
    cout << result;
}
