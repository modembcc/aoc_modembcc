#include <bits/stdc++.h>
using namespace std;

struct entry {
    unsigned long long dest;
    unsigned long long src;
    unsigned long long range; 

    bool operator < (entry o) {
        return src < o.src;
    }
};

vector<entry> almanac[20];

entry get_entry(string line) {
    entry res;
    int idx = 0;
    unsigned long long curval = 0;
    for(char c : line) {
        if(c >= '0' && c <= '9') {
            curval *= 10;
            curval += c - '0';
        }
        else {
            if(idx == 0) {
                res.dest = curval;
                curval = 0;
                idx++;
            }
            else if(idx == 1) {
                res.src = curval;
                curval = 0;
                idx++;
            }
        }
    }
    res.range = curval;
    // cout << res.dest << ' ' << res.src << ' ' << res.range << endl;
    return res;
}

void get_seeds(vector<unsigned long long>& seeds, string line) {
    unsigned long long curval = 0;
    for(char c : line) {
        if(c >= '0' && c <= '9') {
            curval *= 10;
            curval += c - '0';
        }
        else {
            if(curval > 0) {
                seeds.push_back(curval);
                curval = 0;
            }
        }
    }
    if(curval > 0) {
        seeds.push_back(curval);
        curval = 0;
    }
}

int main(){
    ifstream fp("input.txt");
    string line;
    unsigned long long location = LONG_LONG_MAX - 1 * 2;
    vector<unsigned long long> seeds;
    int step = 1;
    if(fp.is_open()) {
        while(getline(fp, line)) {
            // cout << step << endl;
            if(line.length() < 5) {
                continue;
            }
            if(step == 1) {
                get_seeds(seeds, line);
                step++;
                continue;
            }
            if(line[0] < '0' || line[0] > '9') {
                sort(almanac[step].begin(), almanac[step].end());
                step++;
                continue;
            }
            if(step >= 2) {
                almanac[step].push_back(get_entry(line));
            }
        }
        sort(almanac[step].begin(), almanac[step].end());
        for(unsigned long long seed : seeds) {
            int idx = 3;
            while(idx <= step) {
                // cout << seed << ' ';
                int l = 0;
                int r = almanac[idx].size() - 1;
                while(r > l) {
                    int mid = (l + r + 1) / 2;
                    // cout << almanac[idx][mid].src << ' ';
                    if(almanac[idx][mid].src > seed) {
                        r = mid - 1;
                    }
                    else {
                        l = mid;
                    }
                }
                if(l == r && almanac[idx][l].src + almanac[idx][l].range > seed && almanac[idx][l].src <= seed) {
                    // cout << "with src as " << almanac[idx][l].src << ' ';
                    // cout << "with dest as " << almanac[idx][l].dest << ' ';
                    seed = seed + almanac[idx][l].dest - almanac[idx][l].src;
                }
                idx++;
            }
            location = min(seed, location);
            // cout << seed << endl;
        }
        cout << location << endl;
        fp.close();
    }
    return 0;
}