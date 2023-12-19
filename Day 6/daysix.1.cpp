#include <bits/stdc++.h>
using namespace std;

void get_numbers(vector<long>& vect, string line) {
    long curval = 0;
    for(char c : line) {
        if(c >= '0' && c <= '9') {
            curval *= 10;
            curval += c - '0';
        }
        else {
            if(curval > 0) {
                vect.push_back(curval);
                curval = 0;
            }
        }
    }
    if(curval > 0) {
        vect.push_back(curval);
        curval = 0;
    }
}

int main(){
    ifstream fp("input.txt");
    string line;
    vector<long> time;
    vector<long> dist;
    long total = 1;
    if(fp.is_open()) {
        while(getline(fp, line)) {
            if(line.length() <= 0) {
                continue;
            }
            if(line[0] == 'T') {
                get_numbers(time, line);
            }
            if(line[0] == 'D') {
                get_numbers(dist, line);
            }
        }
        for(int i = 0; i < time.size(); i++) {
            int ways = 0;
            long ct = time[i];
            long cd = dist[i];
            for(int x = 1; x < ct; x++) {
                int trav = x * (ct - x);
                if(trav > cd) {
                    ways++;
                }
            }
            if(ways > 0) {
                total *= ways;
            }
        }
        cout << total <<endl;
        fp.close();
    }
    return 0;
}