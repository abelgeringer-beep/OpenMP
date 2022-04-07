#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <iostream>
#include "ElsoOpenMP.h"
#include "MasodikOpenMP.h"
#include "HarmadikOpenMP.h"

int main() {
	// ElsoOpenMP EOMP = ElsoOpenMP();

	// MasodikOpenMP MOMP = MasodikOpenMP();

	HarmadikOpenMP HOMP = HarmadikOpenMP();

	printf("\n\n\n\n");
	return 0;
}
