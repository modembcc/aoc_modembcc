#include <bits/stdc++.h>
using namespace std;

void get_numbers(vector<unsigned long long>& vect, string line) {
    unsigned long long curval = 0;
    for(char c : line) {
        if(c >= '0' && c <= '9') {
            curval *= 10;
            curval += c - '0';
        }
        // change for part 2
        // else {
        //     if(curval > 0) {
        //         vect.push_back(curval);
        //         curval = 0;
        //     }
        // }
    }
    if(curval > 0) {
        vect.push_back(curval);
        curval = 0;
    }
}

int main(){
    ifstream fp("input.txt");
    string line;
    vector<unsigned long long> time;
    vector<unsigned long long> dist;
    unsigned long long total = 1;
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
            unsigned long long ways = 0;
            unsigned long long ct = time[i];
            unsigned long long cd = dist[i];
            cout << ct << ' ' << cd << endl;
            for(int x = 1; x < ct; x++) {
                unsigned long long trav = x * (ct - x);
                if(trav > cd) {
                    ways = (ct - x) - x + 1; // upper - lower + 1
                    cout << x << endl;
                    break;
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