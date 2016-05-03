#ifdef __3414__
#include <iostream>
#define MAX_N 110
#define MAX_Q 5000

int A, B, C;

#define FILLA 1
#define FILLB 2
#define DROPA 3
#define DROPB 4
#define POURAB 5
#define POURBA 6

bool visit[MAX_N][MAX_N];
typedef struct State{
    int a;
    int b;
    int op;
    int pid;
    State(): a(0), b(0), op(0), pid(0){}
    State(int _a, int _b, int _op, int _id): 
    a(_a), b(_b), op(_op), pid(_id){}
}State;

State q[MAX_Q];
int qhead, qtail, qsize;

int ret;
bool success;

void print(int id);
void bfs_pots(int e_s) {
    qhead = qtail = qsize = 0;
    memset(visit, 0, sizeof(visit));
    success = false;
    q[qtail].a = 0;
    q[qtail].b = 0;
    q[qtail].pid = qtail++;
    visit[0][0] = true;
    qsize = 1;
    while (qsize) {
        State c = q[qhead];
        if (c.a == e_s || c.b == e_s) {
            success = true;
            print(qhead);
            break;
        }
        int next_a, next_b;

        //FILLA
        if (c.a < A) {
            if (!visit[A][c.b]) {
                q[qtail++] = State(A, c.b, FILLA, qhead);
                visit[A][c.b] = true;
                qsize++;
            }
        }
        //FILLB
        if (c.b < B) {
            if (!visit[c.a][B]) {
                q[qtail++] = State(c.a, B, FILLB, qhead);
                visit[c.a][B] = true;
                qsize++;
            }
        }

        //DROPA
        if (c.a > 0) {
            if (!visit[0][c.b]) {
                q[qtail++] = State(0, c.b, DROPA, qhead);
                visit[0][c.b] = true;
                qsize++;
            }
        }
        //DROPB
        if (c.b > 0) {
            if (!visit[c.a][0]) {
                q[qtail++] = State(c.a, 0, DROPB, qhead);
                visit[c.a][0] = true;
                qsize++;
            }
        }

        //POURAB
        if (c.a > 0 && c.b != B) {
            next_a = B - c.b > c.a ? 0 : c.a - (B - c.b);
            next_b = B - c.b > c.a ? c.b + c.a : B;
            if (!visit[next_a][next_b]) {
                q[qtail++] = State(next_a, next_b, POURAB, qhead);
                visit[next_a][next_b] = true;
                qsize++;
            }
        }

        //POURBA
        if (c.b > 0 && c.a != A) {
            next_a = A - c.a > c.b ? c.a + c.b : A;
            next_b = A - c.a > c.b ? 0 : c.b - (A - c.a);
            if (!visit[next_a][next_b]) {
                q[qtail++] = State(next_a, next_b, POURBA, qhead);
                visit[next_a][next_b] = true;
                qsize++;
            }
        }
        qhead++;
        qsize--;
    }
    return;
}

void print(int id) {
    if (id == 0) {
        printf("%d\n", ret);
        return;
    }
    ret++;
    print(q[id].pid);
    switch(q[id].op) {
    case FILLA:
        printf("FILL(1)\n");
        break;
    case FILLB:
        printf("FILL(2)\n");
        break;
    case DROPA:
        printf("DROP(1)\n");
        break;
    case DROPB:
        printf("DROP(2)\n");
        break;
    case POURAB:
        printf("POUR(1,2)\n");
        break;
    case POURBA:
        printf("POUR(2,1)\n");
        break;
    }
}

int main(int argc, char** args) {
    scanf("%d%d%d", &A, &B, &C);
    bfs_pots(C);
    if (!success)
        printf("impossible\n");
    return 0;
}
#endif