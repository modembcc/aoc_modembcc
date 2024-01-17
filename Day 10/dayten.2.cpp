#include <bits/stdc++.h>
using namespace std;

vector<string> tiles;

bool is_pipe(char c) {
    return c != '.';
}

void solve(int x, int y) {
    bool a = x - 1 >= 0 && (tiles[x - 1][y] == '|' || tiles[x - 1][y] == '7' || tiles[x - 1][y] == 'F');
    bool b = x + 1 < tiles.size() && (tiles[x + 1][y] == '|' || tiles[x + 1][y] == 'L' || tiles[x + 1][y] == 'J');
    bool c = y - 1 >= 0 && (tiles[x][y - 1] == '-' || tiles[x][y - 1] == 'L' || tiles[x][y - 1] == 'F');
    bool d = y + 1 < tiles[0].length() && (tiles[x][y + 1] == '-' || tiles[x][y + 1] == '7' || tiles[x][y + 1] == 'J');
    if(a && b) {
        tiles[x][y] = '|';
    }
    if(a && c) {
        tiles[x][y] = 'J';
    }
    if(a && d) {
        tiles[x][y] = 'L';
    }
    if(b && c) {
        tiles[x][y] = '7';
    }
    if(b && d) {
        tiles[x][y] = 'F';
    }
    if(c && d) {
        tiles[x][y] = '-';
    }
    cout << tiles[x][y] << endl;
    queue<pair<pair<int, int>, long>> bfs;
    bfs.push({{x, y}, 0});
    long ans = -1;
    while(!bfs.empty()) {
        long cs = bfs.front().second;
        ans = max(ans, cs);
        int dx = bfs.front().first.first;
        int dy = bfs.front().first.second;
        bfs.pop();
        if(tiles[dx][dy] == '|') {
            if(is_pipe(tiles[dx + 1][dy])) {
                bfs.push({{dx + 1, dy}, cs + 1});
            }
            if(is_pipe(tiles[dx - 1][dy])) {
                bfs.push({{dx - 1, dy}, cs + 1});
            }
        }
        if(tiles[dx][dy] == 'L') {
            if(is_pipe(tiles[dx][dy + 1])) {
                bfs.push({{dx, dy + 1}, cs + 1});
            }
            if(is_pipe(tiles[dx - 1][dy])) {
                bfs.push({{dx - 1, dy}, cs + 1});
            }
        }
        if(tiles[dx][dy] == 'J') {
            if(is_pipe(tiles[dx][dy - 1])) {
                bfs.push({{dx, dy - 1}, cs + 1});
            }
            if(is_pipe(tiles[dx - 1][dy])) {
                bfs.push({{dx - 1, dy}, cs + 1});
            }
        }
        if(tiles[dx][dy] == '-') {
            if(is_pipe(tiles[dx][dy + 1])) {
                bfs.push({{dx, dy + 1}, cs + 1});
            }
            if(is_pipe(tiles[dx][dy - 1])) {
                bfs.push({{dx, dy - 1}, cs + 1});
            }
        }
        if(tiles[dx][dy] == '7') {
            if(is_pipe(tiles[dx + 1][dy])) {
                bfs.push({{dx + 1, dy}, cs + 1});
            }
            if(is_pipe(tiles[dx][dy - 1])) {
                bfs.push({{dx, dy - 1}, cs + 1});
            }
        }
        if(tiles[dx][dy] == 'F') {
            if(is_pipe(tiles[dx + 1][dy])) {
                bfs.push({{dx + 1, dy}, cs + 1});
            }
            if(is_pipe(tiles[dx][dy + 1])) {
                bfs.push({{dx, dy + 1}, cs + 1});
            }
        }
        tiles[dx][dy] = '.';
    }
    cout << ans << endl;
}

void print_tiles() {
    for(string x : tiles) {
        cout << x << endl;
    }
}

int main(){
    ifstream fp("input.txt");
    string line;
    if(fp.is_open()) {
        while(getline(fp, line)) {
            tiles.push_back(line);
        }
        int sx, sy;
        for(int i = 0; i < tiles.size(); i++) {
            for(int j = 0; j < tiles[0].length(); j++) {
                // cout << tiles[i][j];
                if(tiles[i][j] == 'S') {
                    sx = i;
                    sy = j;
                }
            }
        }
        solve(sx, sy);
        // print_tiles();
        fp.close();
    }
    return 0;
}