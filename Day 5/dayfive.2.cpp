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

void get_seeds(vector<pair<unsigned long long, unsigned long long>>& seeds, string line) {
    unsigned long long curval[2] = {0, 0};
    int idx = 0;
    for(char c : line) {
        if(c >= '0' && c <= '9') {
            curval[idx] *= 10;
            curval[idx] += c - '0';
        }
        else {
            if(curval[idx] > 0) {
                if(idx == 0) {
                    idx = 1;
                }
                else {
                    seeds.push_back({curval[0], curval[0] + curval[1]});
                    curval[0] = 0;
                    curval[1] = 0;
                    idx = 0;
                }
            }
        }
    }
    if(curval[idx] > 0) {
        if(idx == 0) {
            idx = 1;
        }
        else {
            seeds.push_back({curval[0], curval[0] + curval[1]});
            curval[0] = 0;
            curval[1] = 0;
            idx = 0;
        }
    }
}

int bsearch(unsigned long long seed, int idx) {
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
    if(l == r && almanac[idx][l].src <= seed) {
        return l;    
    }
    return -1;
}

int main(){
    ifstream fp("input.txt");
    string line;
    unsigned long long location = LONG_LONG_MAX - 1 * 2;
    vector<pair<unsigned long long, unsigned long long>> seeds[20];
    int step = 1;
    if(fp.is_open()) {
        while(getline(fp, line)) {
            // cout << step << endl;
            if(line.length() < 5) {
                continue;
            }
            if(step == 1) {
                get_seeds(seeds[2], line);
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
        int idx = 3;
        int n;
        while(idx <= step) {
            n = seeds[idx - 1].size();
            // printf("Pog %d\n", n);
            // for(auto x : seeds[idx - 1]) {
            //     printf("(%llu, %llu) ", x.first, x.second);
            // }
            printf("\n");
            for(int i = 0; i < n && i < 15; i++) {
                unsigned long long st = seeds[idx - 1][i].first;
                unsigned long long nd = seeds[idx - 1][i].second;
                printf("st: %llu, nd: %llu\n", st, nd);
                printf("Current Snapshot:\n");
                for(auto x : seeds[idx - 1]) {
                    printf("%llu %llu\n", x.first, x.second);
                }
                int stdx = bsearch(st, idx);
                int nddx = bsearch(nd, idx);
                if(stdx != nddx) {
                    if(stdx >= 0 && almanac[idx][stdx].src + almanac[idx][stdx].range > st) {
                        seeds[idx].push_back({
                            st + almanac[idx][stdx].dest - almanac[idx][stdx].src, 
                            almanac[idx][stdx].range + almanac[idx][stdx].dest
                        });
                        seeds[idx - 1].push_back({
                            almanac[idx][stdx].src + almanac[idx][stdx].range,
                            nd
                        });
                        printf(
                            "Case 1: Break into (%llu, %llu) and (%llu, %llu) from %d %d\n\n", 
                            st + almanac[idx][stdx].dest - almanac[idx][stdx].src, 
                            almanac[idx][stdx].src + almanac[idx][stdx].range + almanac[idx][stdx].dest - almanac[idx][stdx].src, 
                            almanac[idx][stdx].src + almanac[idx][stdx].range, 
                            nd, 
                            stdx,
                            nddx
                        );
                        n++;
                    }
                    else {
                        seeds[idx].push_back({
                            st, 
                            almanac[idx][stdx + 1].src
                        });
                        seeds[idx - 1].push_back({
                            almanac[idx][stdx + 1].src,
                            nd
                        });
                        printf(
                            "Break into (%llu, %llu) and (%llu, %llu)\n", 
                            st, 
                            almanac[idx][stdx + 1].src, 
                            almanac[idx][stdx + 1].src,
                            nd
                        );
                        n++;
                    }
                }
                else {
                    if(stdx >= 0 && almanac[idx][stdx].src + almanac[idx][stdx].range > st) {
                        if(almanac[idx][stdx].src + almanac[idx][stdx].range > nd) {
                            seeds[idx].push_back({
                                st + almanac[idx][stdx].dest - almanac[idx][stdx].src, 
                                nd + almanac[idx][stdx].dest - almanac[idx][stdx].src
                            });
                        }
                        else {
                            seeds[idx].push_back({
                                st + almanac[idx][stdx].dest - almanac[idx][stdx].src, 
                                almanac[idx][stdx].range + almanac[idx][stdx].dest
                            });
                            seeds[idx].push_back({
                                almanac[idx][stdx].src + almanac[idx][stdx].range,
                                nd
                            });
                        }
                    }
                    else {
                        seeds[idx].push_back({
                            st, 
                            nd
                        });
                    }
                }
                // printf("still working at the end %d\n", n);
            }
            idx++;
            // cout << seed << endl;
        }
        for(auto seed : seeds[idx - 1]) {
            location = min(location, seed.first);
            printf("%llu ", seed);
        }
        printf("\nThe answer is %llu\n", location);
        // cout << location << endl;
        fp.close();
    }
    return 0;
}