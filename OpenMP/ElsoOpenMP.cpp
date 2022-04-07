#include "ElsoOpenMP.h"

void ElsoOpenMP::mxm(int N, int P)
{
	double* A = (double*)malloc(N * N * sizeof(double));
	double* B = (double*)malloc(N * N * sizeof(double));
	double* C = (double*)malloc(N * N * sizeof(double));

	for (int i = 0; i < N * N; ++i)
		A[i] = B[i] = 1.0f;

	double start = omp_get_wtime();
#pragma omp parallel for num_threads(P)
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			double sum = 0.0;
			for (int k = 0; k < N; ++k) {
				sum += A[i * N + k] * B[k * N + j];
			}
			C[i * N + j] = sum;
		}
	}

	double stop = omp_get_wtime();
	printf("result of mxm (N - %ld, P - %d): %.8f, %.6f s\n", N, P, C[0], (stop - start));

	free(A);
	free(B);
	free(C);
}

void ElsoOpenMP::pi(long N, int P)
{
	double sum = 0.0;
	double h = 1.0 / N;
	double start = omp_get_wtime();

#pragma omp parallel for num_threads(P) shared(P) reduction(+:sum)
	for (int i = 0; i < N; ++i)
	{
		double x = i * h + h / 2;
		double tmp = 4.0 * h / (1.0 + x * x);
		sum += tmp;
	}

	double stop = omp_get_wtime();

	printf("result of PI (N - %ld, P - %d): %.8f, %.6f s\n", N, P, sum, (stop - start));
}

ElsoOpenMP::ElsoOpenMP()
{
	mxm(1024, 12);
	mxm(1024, 8);
	mxm(1024, 6);
	mxm(1024, 4);
	mxm(1024, 2);
	mxm(1024, 1);

	pi(1000 * 1000 * 1000, 12);
	pi(1000 * 1000 * 1000, 8);
	pi(1000 * 1000 * 1000, 6);
	pi(1000 * 1000 * 1000, 4);
	pi(1000 * 1000 * 1000, 2);
	pi(1000 * 1000 * 1000, 1);
}
