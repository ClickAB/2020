#include "stdio.h"
void main() {
	int M, N, c;
	char a[100][100];
	int i, j, k;
	printf("请输入长和宽\n");
	scanf_s("%d%d", &N, &M);
	printf("请输入矩阵\n");
	for (i = 0; i < M; i++) {
		for (j = 0; j < N + 1; j++) {
			scanf_s("%c", &a[i][j]);
		}
	}
	printf("请输入周期\n");
	scanf_s("%d", &c);
	for (k = 0; k < c; k++)
	{
		for (i = 0; i < M; i++)
		{
			for (j = 0; j < N + 1; j++)
			{
				if (a[i][j] == 'X')
				{
					if (a[i + 1][j] == 'O')
						a[i + 1][j] = 'N';
					if (a[i - 1][j] == 'O')
						a[i - 1][j] = 'N';
					if (a[i][j + 1] == 'O')
						a[i][j + 1] = 'N';
					if (a[i][j - 1] == 'O')
						a[i][j - 1] = 'N';
				}
			}
		}
		for (i = 0; i < M; i++)
		{
			for (j = 0; j < N; j++)
			{
				if (a[i][j] == 'N')
					a[i][j] = 'X';
			}
		}
	}
	for (i = 0; i < M; i++) {
		for (j = 0; j < N + 1; j++) {
			printf("%c", a[i][j]);
		}printf("\n");
	}printf("\n");
}