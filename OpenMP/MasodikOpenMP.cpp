#include "MasodikOpenMP.h"

MasodikOpenMP::MasodikOpenMP()
{
	// SectionsTest();
	// ScopeTest();
	// ScheduleTest();
    Mandelbrot();
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

void MasodikOpenMP::Mandelbrot()
{
    int limit = 5000;
    int width = 2200;
    int height = 2200;
    double scale = 4.0 / width;
    double c_real = 0;
    double c_imag = 0;
    double z_real = 0;
    double z_imag = 0;
    double temp_real, temp_imag, magnitude;
    int count;
    // 2.437920 

    double start = omp_get_wtime();
#pragma omp parallel for schedule(guided, 50)
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            z_real = z_imag = 0;
            c_real = col * scale - 2.0;
            c_imag = (height - row + 1) * scale - 2.0;
            count = 0;
            do {
                // Zn*Zn + c
                temp_real = z_real * z_real - z_imag * z_imag + c_real;
                temp_imag = 2 * z_real * z_imag + c_imag;
                z_real = temp_real;
                z_imag = temp_imag;
                magnitude = z_real * z_real + z_imag * z_imag;
                count++;
            } while ((count < limit) && (magnitude < 4));
            // generate colour from count and display 
        }
    }
    double stop = omp_get_wtime();
    printf("time: %.6f\n", (stop - start));
    printf("%f", magnitude); // if you delete this, the for won't run, because you are not using anything from it
}
