#ifdef _1077_BIBFS_MAP__
#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <set>

using std::queue;
using std::map;
using std::set;
using std::string;

typedef struct Node {
    int i, prev;
    string value;
    char op;
    
    int L;
    Node(int _i, int _prev):i(_i), prev(_prev){};
} Node;

Node s_node[400000];
int node = 0;

set<string> visit1, visit2;

void bibfs_eight(string start, string end) {
    queue<int> bfs_queue1, bfs_queue2;

    s_node[node].i = node;
    s_node[node].prev = -1;
    s_node[node].value = start;
    s_node[node].L = 0;
    bfs_queue1.push(node++);
    visit1.insert(start);

    s_node[node].i = node;
    s_node[node].prev = -1;
    s_node[node].value = end;
    s_node[node].L = 0;
    bfs_queue2.push(node++);
    visit2.insert(end);

    while (!bfs_queue1.empty() && !bfs_queue2.empty()) {
        if (bfs_queue1.size() <= bfs_queue2.size()) {
            int c = bfs_queue1.front();
            
            int cL = s_node[c].L;
            while (1) {
                if (visit1.find(s_node[c].value) != visit1.end())
            }

        }
    }
}

int main(int argc, char** args) {
    freopen("f:\\Workplace\\POJ\\input.txt", "r", stdin);
    string start;
    char input;
    while (scanf("%c", &input)) {
        if (input == ' ')
            continue;
        else start += input;
        if (start.size() == 9)
            break;
    }
    string end;
    end.append("12345678x");
    bibfs_eight(start, end);
}
#endif