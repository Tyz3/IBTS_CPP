#include <stdio.h>
#include <Windows.h>
#include <vector>

using namespace std;

void test1(int iters) {
	for (int i = 0; i < iters; i++) {
		int *a = new int[10000];
		delete[] a;
	}
}

void test2(int iters) {
	for (int i = 0; i < iters; i++) {
		vector<int> a(10000);
	}
}

void main() {
	int iters = 1000000; // 1 млн

	unsigned long long s1, s2, e1, e2;

	// Test 1 -> new int[]
	printf("Test 1 -> new int[] ...\n");
	GetSystemTimeAsFileTime((LPFILETIME)&s1);
	test1(iters);
	GetSystemTimeAsFileTime((LPFILETIME)&e1);

	double diff1 = (double) (e1 - s1) / 10000.0;
	printf(
		"Elapsed time: %.3f ms. Speed: %.2f i/ms\n",
		diff1,
		iters/diff1
	);

	// Test 2 -> vector<int>
	printf("Test 2 -> vector<int> ...\n");
	GetSystemTimeAsFileTime((LPFILETIME)&s2);
	test2(iters);
	GetSystemTimeAsFileTime((LPFILETIME)&e2);

	double diff2 = (double) (e2 - s2) / 10000.0;
	printf(
		"Elapsed time: %.3f ms. Speed: %.2f i/ms\n",
		diff2,
		iters/diff2
	);

	system("PAUSE");
}
