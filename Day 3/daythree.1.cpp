#include <bits/stdc++.h>
using namespace std;

bool checksym(vector<string> engine, int row, int st, int nd, int n, int m) {
    // start from [i-1][st-1] and end at [i+1][nd + 1]
    // i - 1 row
    char tmp;
    if(row > 0) {
        for(int j = max(0, st - 1); j <= min(m - 1, nd + 1); j++) {
            tmp = engine[row - 1][j];
            if((tmp < '0' || tmp > '9') && tmp != '.') {
                return true;
            }
        }
    }
    // ith row
    tmp = engine[row][max(0, st - 1)];
    if((tmp < '0' || tmp > '9') && tmp != '.') {
        return true;
    }
    tmp = engine[row][min(m - 1, nd + 1)];
    if((tmp < '0' || tmp > '9') && tmp != '.') {
        return true;
    }
    // i + 1th row
    if(row < n - 1) {
        for(int j = max(0, st - 1); j <= min(m - 1, nd + 1); j++) {
            tmp = engine[row + 1][j];
            if((tmp < '0' || tmp > '9') && tmp != '.') {
                return true;
            }
        }
    }
    return false;
}

int main() {
    ifstream fp;
    fp.open("input.txt");
    vector<string> engine;
    string line;
    if(fp.is_open()) {
        while(getline(fp, line)) {
            engine.push_back(line);    
        }
        fp.close();
    }
    int n = engine.size();
    int m = engine[0].length();
    cout << n << ' ' << m << endl;
    int sum = 0;
    for(int i = 0; i < n; i++) {
        int curnum = 0;
        int st = 0;
        int nd = 0;
        for(int j = 0; j < m; j++) {
            // if number, add to cur num, if curnum == 0 then set start, else set end
            if(engine[i][j] >= '0' && engine[i][j] <= '9') {
                if(curnum == 0) 
                    st = j;
                nd = j;
                curnum *= 10;
                curnum += engine[i][j] - '0';
            }
            // if . and curnum not 0, check for surrounding not .
            else {
                if(curnum > 0) {
                    cout << i << ' ' << curnum << ' ';
                    bool valid = checksym(engine, i, st, nd, n, m);
                    cout << valid << endl;
                    if(valid) {
                        sum += curnum;
                    }
                    curnum = 0;
                }
            }
        }
        if(curnum > 0) {
            bool valid = checksym(engine, i, st, nd, n, m);
            cout << curnum << ' ' << valid << endl;
            if(valid) {
                sum += curnum;
            }
            curnum = 0;
        }
    }
    cout << sum << endl;
    return 0;
}