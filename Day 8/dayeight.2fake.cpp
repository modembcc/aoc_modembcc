#include <bits/stdc++.h>
using namespace std;

map<string, pair<string, string>> maps;
vector<string> pos;

bool all_z() {
    for(string x : pos) {
        if(x[2] != 'Z') {
            return false;
        }
    }
    return true;
}

void all_left() {
    for(int i = 0; i < pos.size(); i++) {
        pos[i] = maps[pos[i]].first;
    }
}

void all_right() {
    for(int i = 0; i < pos.size(); i++) {
        pos[i] = maps[pos[i]].second;
    }
}

void print_pos() {
    for(string x : pos) {
        cout << x << ' ';
    }
    cout << endl;
}

int main(){
    ifstream fp("input.txt");
    string line;
    string instructions;
    int step = 1;
    if(fp.is_open()) {
        while(getline(fp, line)) {
            if(line.length() < 1) continue;
            if(step == 1) {
                // read the instructions
                instructions = line.substr();
                step++;
                continue;
            }
            // format map
            string source = line.substr().erase(3);
            line.erase(0, line.find('(') + 1);
            string lhs = line.substr().erase(3);
            line.erase(0, line.find(',') + 2);
            string rhs = line.substr().erase(3);
            maps[source] = {lhs, rhs};
            if(source[2] == 'A') {
                pos.push_back(source);
            }
        }
        for(string cp : pos) {
            long ans = 0;
            // cout << instructions << endl;
            while(cp[2] != 'Z') {
                char ci = instructions[ans % instructions.length()];
                // cout << cp << ' ' << ci << endl;
                if(ci == 'L') {
                    cp = maps[cp].first;
                }
                if(ci == 'R') {
                    cp = maps[cp].second;
                }
                ans++;
            }
            cout << ans << endl;
        }
        fp.close();
    }
    return 0;
}