#include <time.h>
#include <stdio.h>
#include <locale.h>

int main() {
	time_t now = time(NULL);
	struct tm *timeinfo = localtime(&now);
	char buff[100];

	// Standard format
	strftime(buff, sizeof(buff), "%d/%m/%Y", timeinfo);
	printf("Standard: %s\n", buff);

	// With O modifier (alternative numeric symbols)
	strftime(buff, sizeof(buff), "%Od/%Om/%Oy", timeinfo);
	printf("Alternative: %s\n", buff);

	return 0;
}
