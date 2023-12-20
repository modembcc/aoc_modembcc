#include <bits/stdc++.h>
using namespace std;

int getVal(char c) {
    if(c >= '0' && c <= '9') {
        return c - '0';
    }
    switch(c) {
        case 'T':
            return 10;
        case 'J':
            return 1; // updated for part 2
        case 'Q':
            return 12;
        case 'K':
            return 13;
        case 'A':
            return 14;
        default:
            return 0;
    }
    return 0;
}

struct hand {
    string cards;
    int type;
    long bids;

    hand(string cards, string bids) {
        this->cards = cards;
        this->type = calc_type();
        this->bids = stol(bids);
    }

    bool operator < (const hand &o) const {
        if(type != o.type) return type < o.type;
        for(int i = 0; i < 5; i++) {
            if(cards[i] != o.cards[i]) {
                return getVal(cards[i]) < getVal(o.cards[i]);
            }
        }
        return bids < o.bids;
    }

    private:
        int calc_type() {
            int copies[6] = {0, 0, 0, 0, 0, 0};
            map<char, int> m;
            int jokers = 0;
            for(char x : cards) {
                if(x == 'J') {
                    jokers++;
                    continue;
                }
                if(m[x]) {
                    copies[m[x]]--;
                    copies[m[x] + 1]++;
                }
                else {
                    copies[1]++;
                }
                m[x]++;
            }
            while(jokers) {
                jokers--;
                if(copies[4]) {
                    copies[5]++;
                    copies[4]--;
                    continue;
                }
                if(copies[3]) {
                    copies[4]++;
                    copies[3]--;
                    continue;
                }
                if(copies[2]) {
                    copies[2]--;
                    copies[3]++;
                    continue;
                }
                copies[1]--;
                copies[2]++;
            }
            if(copies[5]) {
                return 7;
            }
            if(copies[4]) {
                return 6;
            }
            if(copies[3]) {
                if(copies[2]) {
                    return 5;
                }
                return 4;
            }
            if(copies[2]) {
                return copies[2] + 1;
            }
            return 1;
        }
};

int main(){
    ifstream fp("input.txt");
    string line;
    priority_queue<hand> pq;
    if(fp.is_open()) {
        while(getline(fp, line)) {
            string cards = line.substr().erase(5);
            string bid = line.substr().erase(0, 6);
            // cout << cards << ' ' << bid << endl;
            hand curHand(cards, bid);
            pq.push(curHand);
        }
        long n = pq.size();
        long sum = 0;
        while(!pq.empty()){
            cout << pq.top().cards << ' ' << pq.top().bids << endl;
            sum += pq.top().bids * n;
            n--;
            pq.pop();
        }
        cout << sum << endl;
        fp.close();
    }
    return 0;
}