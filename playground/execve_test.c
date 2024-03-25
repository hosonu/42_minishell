#include <stdio.h>
#include <unistd.h>

int main() {
    char *args[] = {"/bin/ls", "'-l'", NULL}; // lsコマンドとオプション
    char *envp[] = {NULL}; // 環境変数は使わないのでNULL

    if (execve("/bin/ls", args, envp) == -1) {
        perror("execve"); // execveの呼び出しに失敗した場合、エラーを表示
    }
    
    return 0; // この行はexecveが成功した場合には実行されない
}

