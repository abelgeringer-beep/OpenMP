#include "MasodikOpenMP.h"

MasodikOpenMP::MasodikOpenMP()
{
	// SectionsTest();
	ScopeTest();
}

void MasodikOpenMP::DummyCalcA()
{
	int id = omp_get_thread_num();
	printf("One - %d\n", id);
}

void MasodikOpenMP::DummyCalcB()
{
	int id = omp_get_thread_num();
	printf("Two - %d\n", id);
}

void MasodikOpenMP::SectionsTest()
{
#pragma omp parallel
	{
#pragma omp single
		printf("Starting sections...\n");
#pragma omp sections
		{
#pragma omp section
			DummyCalcA();

#pragma omp section 
			DummyCalcB();

		}
	}
}

void MasodikOpenMP::ScopeTest()
{
	double value = 3;
#pragma omp parallel default(none) firstprivate(value)
	{
		value += (int)omp_get_thread_num();
		printf("value in thread: %.2f\n", value);
	}
	printf("value in main: %.2f\n", value);
}
