#include <bits/stdc++.h>
using namespace std;

queue<long long> q[2];
stack<long long> st;

int main(){
    ifstream fp("input.txt");
    string line;
    if(fp.is_open()) {
        long long sum = 0;
        while(getline(fp, line)) {
            // empty q[0];
            while(!q[0].empty()){
                q[0].pop();
            }
            // empty q[1]
            while(!q[1].empty()) {
                q[1].pop();
            }
            // empty st
            while(!st.empty()) {
                st.pop();
            }
            // put all numbers in q[0]
            long long curval = 0;
            bool nega = false;
            for(char c : line) {
                if(c == '-') {
                    nega = true;
                }
                if(c >= '0' && c <= '9') {
                    curval *= 10;
                    curval += c - '0';
                }
                if(c == ' ') {
                    // cout << "huh " << curval << endl;
                    q[0].push(nega ? -1 * curval : curval);
                    curval = 0;
                    nega = false;
                }
            }
            q[0].push(nega ? -1 * curval : curval);
            while(!q[0].empty()){
                // cout << q[0].front() << endl;
                st.push(q[0].front());
                q[0].pop();
            }
            while(!st.empty()) {
                q[0].push(st.top());
                st.pop();
            }
            int tmp = 0;
            bool stopage = false;
            while(!stopage) {
                stopage = true;
                while(!q[tmp].empty()) {
                    curval = q[tmp].front();
                    // cout << curval << ' ';
                    q[tmp].pop();
                    if(q[tmp].empty()) {
                        st.push(curval);
                    }
                    else {
                        q[1 - tmp].push(q[tmp].front() - curval);
                        if(stopage && q[tmp].front() - curval != 0) {
                            stopage = false;
                        }
                    }
                }
                tmp = 1 - tmp;
                // cout << endl;
            }
            long long ans = 0;
            while(!st.empty()) {
                ans += st.top();
                st.pop();
            }
            cout << ans << endl;
            sum += ans;
        }
        cout << sum << endl;
        fp.close();
    }
    return 0;
}