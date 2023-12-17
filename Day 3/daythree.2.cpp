#include <bits/stdc++.h>
using namespace std;

bool isnumber(char c) {
    if(c >= '0' && c <= '9') {
        return true;
    }
    return false;
}

long getnumber(vector<string> engine, int i, int j) {
    while(j >= 0 && isnumber(engine[i][j])) {
        j--;
    }
    j++;
    long sum = 0;
    while(engine[i][j] != '\0' && isnumber(engine[i][j])) {
        sum *= 10;
        sum += engine[i][j] - '0';
        j++;
    }
    return sum;
}

long check_gear(vector<string> engine, int i, int j, int n, int m) {
    int parts = 0;
    long total = 1;
    // check i - 1 row, if center is number then add only 1 to parts, else add more than one or less than one
    if(i > 0) {
        if(isnumber(engine[i - 1][j])) {
            parts++;
            total *= getnumber(engine, i - 1, j);
        }
        else {
            if(j > 0 && isnumber(engine[i - 1][j - 1])) {
                parts++;
                total *= getnumber(engine, i - 1, j - 1);
            }
            if(j < m - 1 && isnumber(engine[i - 1][j + 1])) {
                parts++;
                total *= getnumber(engine, i - 1, j + 1);
            }
        }
    }
    // check ith row
    if(j > 0 && isnumber(engine[i][j - 1])) {
        if(parts >= 2) {
            return 0; 
        }
        parts++;
        total *= getnumber(engine, i, j - 1);
    }
    if(j < m - 1 && isnumber(engine[i][j + 1])) {
        if(parts >= 2) {
            return 0; 
        }
        parts++;
        total *= getnumber(engine, i, j + 1);
    }
    // check i + 1 row, if center is number then add only 1 to parts, else add more than one or less than one
    if(i < n - 1) {
        if(isnumber(engine[i + 1][j])) {
            if(parts >= 2) {
                return 0;
            }
            parts++;
            total *= getnumber(engine, i + 1, j);
        }
        else {
            if(j > 0 && isnumber(engine[i + 1][j - 1])) {
                if(parts >= 2) {
                    return 0;
                }
                parts++;
                total *= getnumber(engine, i + 1, j - 1);
            }
            if(j < m - 1 && isnumber(engine[i + 1][j + 1])) {
                if(parts >= 2) {
                    return 0;
                }
                parts++;
                total *= getnumber(engine, i + 1, j + 1);
            }
        }
    }
    if(parts != 2) {
        return 0;
    }
    // cout << i << ' ' << j << endl;
    return total;
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
    // cout << n << ' ' << m << endl;
    long sum = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(engine[i][j] == '*') {
                long point = check_gear(engine, i, j, n, m);
                sum += point;
            }
        }
    }
    cout << sum << endl;
    return 0;
}