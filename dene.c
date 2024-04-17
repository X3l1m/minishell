#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>
#include <wait.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(int argc, char const *argv[])
{
	pid_t
	return 0;
}








/* sigjmp_buf jump_buffer;

void sigintHandler(int sig) {
    printf("\nCtrl+C algılandı, readline işlemi durduruldu.\n");
    siglongjmp(jump_buffer, 1);
}

int main() {
    char *input;

    // SIGINT (Ctrl+C) sinyal işleyicisini tanımla
    signal(SIGINT, sigintHandler);

        // SIGINT sinyali alındığında longjmp kullanarak geri dön
        if (sigsetjmp(jump_buffer, 1) == 0) {
            // Readline çağrısı
            input = readline("Giriş: ");
        } else {
            // SIGINT sinyali alındı, readline çağrısını iptal et
            // ve sonraki readline çağrısına geç
            printf("kaka\n");
        }
    return 0;
}
 */