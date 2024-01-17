#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

int main()
{
	char str[100];  // 100 karakter uzunluğunda bir string tanımla
	long long deger;

	// Kullanıcıdan bir string al
	printf("Bir sayi girin: ");
	scanf("%s", str);

	// Stringi long long türüne çevir
	deger = atoll(str);
	printf("%lld\n", deger);
/* 	// Çevrilen değeri kontrol et
	if (deger > LONG_MAX || deger < LONG_MIN) {
		printf("Hata: Girdi, long veri tipinin sınırlarını aşıyor.\n");
	} else {
		printf("Girdi geçerli: %lld\n", deger);
	}

	return 0;*/
}
// 9223372036854775807
// 18446744073709551616