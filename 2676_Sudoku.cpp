#ifdef __2676_SUDOKU__

#include <stdio.h>
#include <string.h>

int sudo[10][10];//1-9
bool row_flag[10][10];
bool col_flag[10][10];
bool block_flag[10][10];

bool is_set_flags(int i, int j, int num) {
    return row_flag[i][num] || 
        col_flag[j][num] || 
        block_flag[(i - 1) / 3 * 3 + (j - 1) / 3 + 1][num];
}

void set_flags(int i, int j, int num) {
    row_flag[i][num] = true;
    col_flag[j][num] = true;
    block_flag[(i - 1) / 3 * 3 + (j - 1) / 3 + 1][num] = true;
}

void unset_flags(int i, int j, int num) {
    row_flag[i][num] = false;
    col_flag[j][num] = false;
    block_flag[(i - 1) / 3 * 3 + (j - 1) / 3 + 1][num] = false;
}

bool dfs_sudo(int i, int j){
    //i,j start position.
    if (i > 9) {
        return true;
    }
    if (j > 9) {
        i++;
        j = 1;
        return dfs_sudo(i, j);
    }
    while (sudo[i][j]) {
        if (j == 9) {
            i++;
            if (i > 9)
                return true;
            j = 1;
        } else {
            j++;
        }
    }
    for (int num = 1; num <= 9; num++) {
        if (is_set_flags(i, j, num))
            continue;
        sudo[i][j] = num;
        set_flags(i, j, num);
        bool ret = dfs_sudo(i, j + 1);
        if (ret)
            return true;
        else {
            sudo[i][j] = 0;
            unset_flags(i, j, num);
        }
    }
    return false;
}

int main_2676(int argc, char** args) {
    int count;
    freopen("f:\\Workplace\\POJ\\input.txt", "r", stdin);
    scanf("%d", &count);
    while(count--) {
        memset(sudo, 0, sizeof(sudo));
        memset(row_flag, 0, sizeof(row_flag));
        memset(col_flag, 0, sizeof(col_flag));
        memset(block_flag, 0, sizeof(block_flag));

        char str[10];
        for (int i = 1; i <= 9; i++) {
            scanf("%s", str);
            for (int j = 1; j <= 9; j++) {
                sudo[i][j] = str[j - 1] - '0';
                if (sudo[i][j])
                    set_flags(i, j, sudo[i][j]);
            }
        }
        dfs_sudo(1, 1);
        for (int i = 1; i <= 9; i++) {
            for (int j = 1; j <= 9; j++)
                printf("%d", sudo[i][j]);
            printf("\n");
        }
    }
    return 0;
}

#endif