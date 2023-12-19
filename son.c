#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <limits.h>
#include <stdint.h>

int main() {
	char userInput[50]; // Kullanıcı girişi için yeterli bir karakter dizisi
	size_t convertedNumber;

	while (1)
	{
		// Kullanıcıdan giriş istenir
		printf("Bir sayi girin:	");
		fgets(userInput, sizeof(userInput), stdin);

		// Kullanıcı girişi sayıya çevrilir
		convertedNumber = strtoul(userInput, NULL, 10);

		// Eğer sayı size_t sınırlarından büyükse hata mesajı gösterilir
		if (convertedNumber > SIZE_MAX) {
			printf("Hata: Girilen sayi SIZE_MAX degerinden buyuk!\n");
		} else {
			// Sayı size_t sınırlarında ise işlemlere devam edebilirsiniz
			printf("Girilen sayi:	%zu\n", convertedNumber);
			// İşlemlerinizi buraya ekleyebilirsiniz
		}
	}
	return 0;
}
