#include "MasodikOpenMP.h"

MasodikOpenMP::MasodikOpenMP()
{
	// SectionsTest();
	// ScopeTest();
	ScheduleTest();
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

void MasodikOpenMP::ScheduleTest()
{
	int N = 16;
#pragma omp parallel num_threads(4)
#pragma omp for schedule(guided, 3)
	for (int t = 0; t < N; t++)
	{
		int id = omp_get_thread_num();
		printf("id: %d\titeration: %d\n", id, t);
	}
}
