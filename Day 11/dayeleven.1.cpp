#include <bits/stdc++.h>
using namespace std;
#define SIZE 150

long long qsc[SIZE];
long long qsr[SIZE];

vector<string> image;
vector<pair<int, int>> pos;

int main(){
    ifstream fp("input.txt");
    string line;
    if(fp.is_open()) {
        while(getline(fp, line)) {
            image.push_back(line);
        }
        for(int i = 0; i < image.size(); i++) {
            bool isempty = true;
            for(int j = 0; j < image[0].length(); j++) {
                if(image[i][j] == '#') {
                    isempty = false;
                    pos.push_back({i, j});
                }
            }
            if(!isempty) {
                qsr[i] = i == 0 ? 0 : qsr[i - 1];
            }
            else {
                qsr[i] = i == 0 ? 10 : qsr[i - 1] + 1000000 - 1;
            }
        }
        for(int i = 0; i < image[0].length(); i++) {
            bool isempty = true;
            for(int j = 0; j < image.size(); j++) {
                if(image[j][i] == '#') {
                    isempty = false;
                }
            }
            if(!isempty) {
                qsc[i] = i == 0 ? 0 : qsc[i - 1];
            }
            else {
                qsc[i] = i == 0 ? 10 : qsc[i - 1] + 1000000 - 1;
            }
        }
        for(auto x : qsr) {
            cout << x << ' ';
        }
        cout << endl;
        for(auto x : qsc) {
            cout << x << ' ';
        }
        cout << endl;
        
        long long ans = 0;
        for(int i = 0; i < pos.size(); i++) {
            for(int j = i + 1; j < pos.size(); j++) {
                long long oa = ans;
                ans += abs(qsr[pos[j].first] - qsr[pos[i].first]) + abs(pos[j].first - pos[i].first);
                ans += abs(qsc[pos[j].second] - qsc[pos[i].second]) + abs(pos[j].second - pos[i].second);
                // cout << i << ' ' << j << ' ' << ans - oa << endl;
                // cout << pos[j].first << ' ' << pos[j].second << ' ' << pos[i].first << ' ' << pos[i].second << " added " << ans - oa << endl;
            }
        }
        cout << ans << endl;
        fp.close();
    }
    return 0;
}