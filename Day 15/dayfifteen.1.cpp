#include <bits/stdc++.h>
using namespace std;

vector<pair<string, int>> boxes[300];

int find_label(string label, int idx) {
    int i = 0;
    for(auto x : boxes[idx]) {
        if(x.first == label) {
            return i;
        }
        i++;
    }
    return -1;
}

int main(){
    ifstream fp("input.txt");
    string line;
    unsigned long long sum = 0;
    if(fp.is_open()) {
        while(getline(fp, line)) {
            // we got the line
        }
        // cout << line.substr(0, 10) << endl;
        size_t pos;
        string tmp;
        while((pos = line.find(',')) != string::npos) {
            unsigned long long cv = 0;
            tmp = line.substr(0, pos);
            bool ins = !(tmp[tmp.length() - 1] == '-');
            int fl = ins ? tmp[tmp.length() - 1] - '0' : -1;
            tmp = tmp.erase(tmp.length() - (ins ? 2 : 1));
            // cout << cv << endl;
            // cout << tmp << ' ';
            for(char c : tmp) {
                cv += c;
                cv *= 17;
                cv %= 256;
                // cout << c << ' ' << cv << endl;
            }
            // cout << cv << endl;
            if(ins) {
                int bdx = find_label(tmp, cv);
                if(bdx > -1) {
                    boxes[cv].erase(boxes[cv].begin() + bdx);
                    boxes[cv].insert(boxes[cv].begin() + bdx, {tmp, fl});
                }
                else {
                    boxes[cv].push_back({tmp, fl});
                }
            }
            else {
                int bdx = find_label(tmp, cv);
                if(bdx > -1) {
                    boxes[cv].erase(boxes[cv].begin() + bdx);
                }
            }
            // std::cout << tmp << std::endl;
            line.erase(0, pos + 1);
        }
        unsigned long long cv = 0;
        tmp = line.substr(0, pos);
        bool ins = !(tmp[tmp.length() - 1] == '-');
        int fl = ins ? tmp[tmp.length() - 1] - '0' : -1;
        tmp = tmp.erase(tmp.length() - (ins ? 2 : 1));
        // cout << tmp << ' ';
        // cout << cv << endl;
        for(char c : tmp) {
            cv += c;
            cv *= 17;
            cv %= 256;
            // cout << c << ' ' << cv << endl;
        }
        // cout << cv << endl;
        if(ins) {
            int bdx = find_label(tmp, cv);
            if(bdx > -1) {
                boxes[cv].erase(boxes[cv].begin() + bdx);
                boxes[cv].insert(boxes[cv].begin() + bdx, {tmp, fl});
            }
            else {
                boxes[cv].push_back({tmp, fl});
            }
        }
        else {
            int bdx = find_label(tmp, cv);
            if(bdx > -1) {
                boxes[cv].erase(boxes[cv].begin() + bdx);
            }
        }
        fp.close();
    }
    unsigned long long i = 0;
    for(auto x : boxes) {
        if(x.size() > 0) {
            cout << "Box " << i << ": ";
            unsigned long long j = 1;
            for(auto y : x) {
                cout << y.first << y.second << ' ';
                sum += (i + 1) * j * y.second;
                j++;
            }
            cout << endl;
        }
        i++;
    }
    cout << "sum is " << sum << endl;
    return 0;
}