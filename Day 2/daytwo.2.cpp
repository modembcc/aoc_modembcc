#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fp;
    fp.open("input.txt");
    string line;
    int id = 1;
    long sum = 0;
    if(fp.is_open()) {
        while(getline(fp, line)) {
            int r = 0, g = 0, b = 0;
            // cout << id << "\n";
            line.erase(0, line.find(':') + 2); // erase game
            deque<string> games;
            size_t pos;
            string tmp;
            while((pos = line.find(';')) != string::npos) {
                tmp = line.substr(0, pos);
                games.push_back(tmp);
                // std::cout << tmp << std::endl;
                line.erase(0, pos + 2);
            }
            games.push_back(line);
            for(auto game : games) {
                deque<string> rounds;
                size_t pos;
                string tmp;
                while((pos = game.find(',')) != string::npos) {
                    tmp = game.substr(0, pos);
                    rounds.push_back(tmp);
                    game.erase(0, pos + 2);
                }
                rounds.push_back(game);
                for(auto round : rounds) {
                    // cout << round << ' ';
                    pos = round.find(' ');
                    string col;
                    int num;
                    if(pos != string::npos) {
                        num = stoi(round.substr(0, pos));
                        round.erase(0, pos + 1);
                        col = round.substr();
                        if(!col.compare("red")) {
                            r = max(r, num);
                        }
                        if(!col.compare("green")) {
                            g = max(g, num);
                        }
                        if(!col.compare("blue")) {
                            b = max(b, num);
                        }
                    }
                }
                // cout << endl;
            }
            sum += r*g*b;
            id++;            
        }
        cout << sum;
        fp.close();
    }
    return 0;
}