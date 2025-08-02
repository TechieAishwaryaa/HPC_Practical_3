#include<stdio.h>
#include<omp.h>
#define N 100
int main()
{
	int i;
	int a[N],b[N];
	int pro=0;
	for(i=0;i<N;i++)
	{
		a[i]=i+1;
		b[i]=N-i;
	}
	#pragma omp parallel for reduction(+:pro) ordered
	for(i=0;i<N;i++)
	{
		#pragma omp ordered
		pro+=a[i]*b[i];
	}
	printf("Minimum Scalar Product: %d\n",pro);
	return 0;
}
