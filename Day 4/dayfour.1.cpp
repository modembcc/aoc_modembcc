#include <bits/stdc++.h>
using namespace std;

int main(){
    ifstream fp("input.txt");
    string card;
    long sum = 0;
    if(fp.is_open()) {
        while(getline(fp, card)) {
            card.erase(0, card.find(':') + 2); // erase card
            int curval = 0;
            bool holding = false;
            int points = -1;
            map<int, bool> seen;
            for(auto x : card) {
                if(holding) {
                    if(x == ' ') {
                        if(curval > 0) {
                            // cout << curval << ' ';
                            if(seen[curval]) {
                                // cout << curval << ' ';
                                points++;
                            }
                            curval = 0;
                        }
                    }
                    if(x >= '0' && x <= '9') {
                        curval *= 10;
                        curval += x - '0';
                    }
                }
                else{
                    if(x == ' ') {
                        if(curval > 0) {
                            // cout << curval << ' ';
                            seen[curval] = true;
                            curval = 0;
                        }
                    }
                    if(x == '|') {
                        holding = true;
                        curval = 0;
                        // cout << endl;
                    }
                    if(x >= '0' && x <= '9') {
                        curval *= 10;
                        curval += x - '0';
                    }
                }
            }
            if(curval > 0) {
                // cout << curval << ' ';
                if(seen[curval]) {
                    // cout << curval << ' ';
                    points++;
                }
                curval = 0;
            }
            // cout << points << endl;
            if(points >= 0) sum += pow(2, points);
        }
        cout << sum << endl;
        fp.close();
    }
    return 0;
}