#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline.h>

void sonraki(int signal) {
	// SIGINT sinyali alındığında hiçbir şey yapma
}

int main() {
	char text[];

	// SIGINT sinyalini sonraki() fonksiyonuna bağla
	signal(SIGINT, sonraki);

	// İlk girişi al
	text = readline("ilk: ");

	// İkinci girişi al
	text = readline("ikinci: ");

	return 0;
}