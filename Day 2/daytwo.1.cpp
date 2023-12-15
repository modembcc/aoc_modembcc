#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fp;
    fp.open("input.txt");
    string line;
    int id = 1;
    int sum = 0;
    if(fp.is_open()) {
        while(getline(fp, line)) {
            bool invalid = false;
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
                            if(num > 12) {
                                invalid = true;
                                break;
                            }
                        }
                        if(!col.compare("green")) {
                            if(num > 13) {
                                invalid = true;
                                break;
                            }
                        }
                        if(!col.compare("blue")) {
                            if(num > 14) {
                                invalid = true;
                                break;
                            }
                        }
                    }
                }
                // cout << endl;
            }
            if(!invalid) {
                sum += id;
            }
            id++;            
        }
        cout << sum;
        fp.close();
    }
    return 0;
}