#ifdef __EIGHT_BFS_SET__

#include <iostream>
#include <string>
#include <queue>
#include <set>

using std::queue;
using std::set;
using std::string;

typedef struct Node {
    string data;
    char op;

    Node* prev;
}Node;

bool up(string* next) {
    int x, i, j;
    for (x = 0; x < next->size(); x++) {
        if ((*next)[x] == 'x')
            break;
    }
    j = x % 3;
    i = x / 3;
    if (i - 1 < 0)
        return false;
    else {
        (*next)[x] = (*next)[(i - 1) * 3 + j];
        (*next)[(i - 1) * 3 + j] = 'x';
        return true;
    }
}

bool down(string* next) {
    int x, i, j;
    for (x = 0; x < next->size(); x++) {
        if ((*next)[x] == 'x')
            break;
    }
    j = x % 3;
    i = x / 3;
    if (i + 1 > 2)
        return false;
    else {
        (*next)[x] = (*next)[(i + 1) * 3 + j];
        (*next)[(i + 1) * 3 + j] = 'x';
        return true;
    }
}

bool left(string* next) {
    int x, i, j;
    for (x = 0; x < next->size(); x++) {
        if ((*next)[x] == 'x')
            break;
    }
    j = x % 3;
    i = x / 3;
    if (j - 1 < 0)
        return false;
    else {
        (*next)[x] = (*next)[i * 3 + j - 1];
        (*next)[i * 3 + j - 1] = 'x';
        return true;
    }
}

bool right(string* next) {
    int x, i, j;
    for (x = 0; x < next->size(); x++) {
        if ((*next)[x] == 'x')
            break;
    }
    j = x % 3;
    i = x / 3;
    if (j + 1 > 2)
        return false;
    else {
        (*next)[x] = (*next)[i * 3 + j + 1];
        (*next)[i * 3 + j + 1] = 'x';
        return true;
    }
}

void bfs_eight(string start, string end) {
    queue<Node*> bfs_queue;
    queue<Node*> gc_queue;
    set<string> visit;

    Node* s_node = new Node();
    s_node->data = start;
    s_node->prev = NULL;

    bfs_queue.push(s_node);
    gc_queue.push(s_node);
    visit.insert(s_node->data);

    bool result = false;
    while (!bfs_queue.empty()) {
        Node* c = bfs_queue.front();
        if (c->data == end) {
            result = true;
            break;
        }
        Node* n_node;
        string next = c->data;
        //up
        if (up(&next)) {
            if (visit.find(next) == visit.end()) {
                n_node = new Node();
                n_node->data = next;
                n_node->op = 'u';
                n_node->prev = c;
                bfs_queue.push(n_node);
                gc_queue.push(n_node);
                visit.insert(next);
            }
        }

        next = c->data;
        //down
        if (down(&next)) {
            if (visit.find(next) == visit.end()) {
                n_node = new Node();
                n_node->data = next;
                n_node->op = 'd';
                n_node->prev = c;
                bfs_queue.push(n_node);
                gc_queue.push(n_node);
                visit.insert(next);
            }
        }

        next = c->data;
        //left
        if (left(&next)) {
            if (visit.find(next) == visit.end()) {
                n_node = new Node();
                n_node->data = next;
                n_node->op = 'l';
                n_node->prev = c;
                bfs_queue.push(n_node);
                gc_queue.push(n_node);
                visit.insert(next);
            }
        }

        next = c->data;
        //right
        if (right(&next)) {
            if (visit.find(next) == visit.end()) {
                n_node = new Node();
                n_node->data = next;
                n_node->op = 'r';
                n_node->prev = c;
                bfs_queue.push(n_node);
                gc_queue.push(n_node);
                visit.insert(next);
            }
        }
        bfs_queue.pop();
    }

    string p_ret;
    if (result == false)
        printf("unsolvable\n");
    else {
        Node* e_node = bfs_queue.front();
        while (e_node->prev != NULL) {
            p_ret += e_node->op;
            e_node = e_node->prev;
        }        
        for (int i = p_ret.size() - 1; i >= 0; i--)
            printf("%c", p_ret[i]);
        printf("\n");
    }
    //GC
    //gc_queue;
}

int main(int argc, char** args) {
    //freopen("f:\\Workplace\\POJ\\input.txt", "r", stdin);
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
    bfs_eight(start, end);
}

#endif