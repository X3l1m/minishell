#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

int main()
{
	char *input;

	while (1)
	{
		input = readline("Girişinizi girin: "); // Kullanıcıdan girdi al
		if (!strcmp(input, "sil"))
		{
			rl_clear_history(); // Komut geçmişini temizle
			printf("Komut geçmişi temizlendi.\n");
		}
		else if (input)
		{
			printf("Girdiniz: %s\n", input);
			add_history(input); // Girdiyi komut geçmişine ekle
			free(input); // Belleği serbest bırak
		}
	}
	return 0;
}
