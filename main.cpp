#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <set>

using namespace std;

bool is_win(const string& s, char c) {
    // rows
    for (int i = 0; i < 3; ++i) {
        if (s[i*3] == c && s[i*3+1] == c && s[i*3+2] == c) return true;
    }
    // cols
    for (int i = 0; i < 3; ++i) {
        if (s[i] == c && s[i+3] == c && s[i+6] == c) return true;
    }
    // diags
    if (s[0] == c && s[4] == c && s[8] == c) return true;
    if (s[2] == c && s[4] == c && s[6] == c) return true;
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string start = "---------";
    set<string> reachable;
    queue<pair<string, char>> q;
    
    q.push({start, 'x'});
    reachable.insert(start);
    
    while (!q.empty()) {
        auto [curr, turn] = q.front();
        q.pop();
        
        if (is_win(curr, 'x') || is_win(curr, 'o')) {
            continue; // game over, cannot make more moves
        }
        
        for (int i = 0; i < 9; ++i) {
            if (curr[i] == '-') {
                string next_state = curr;
                next_state[i] = turn;
                if (reachable.find(next_state) == reachable.end()) {
                    reachable.insert(next_state);
                    q.push({next_state, turn == 'x' ? 'o' : 'x'});
                }
            }
        }
    }
    
    string row1, row2, row3;
    while (cin >> row1 >> row2 >> row3) {
        string input_state = row1 + row2 + row3;
        
        if (reachable.find(input_state) == reachable.end()) {
            cout << "invalid\n";
        } else {
            if (is_win(input_state, 'x')) {
                cout << "win\n";
            } else if (is_win(input_state, 'o')) {
                cout << "lose\n";
            } else {
                bool full = true;
                for (char c : input_state) {
                    if (c == '-') full = false;
                }
                if (full) cout << "tie\n";
                else cout << "ongoing\n";
            }
        }
    }
    
    return 0;
}
