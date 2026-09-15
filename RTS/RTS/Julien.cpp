#include<math.h>

int lokta_Euler(int entity_rate,int P0, int n) {
	return round((1 + entity_rate * n) * P0);
}

