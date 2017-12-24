#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "locale.h"


#define SIZE 6
#define DIST_UNREACHABLE 10000

int main()
{
	int link_matrix[SIZE][SIZE]; // матрица св€зей
	int distances[SIZE]; // минимальное рассто€ние
	int visited[SIZE]; // посещенные вершины
	int temp;
	int minindex, min;
	system("chcp 1251");
	system("cls");

	// »нициализаци€ матрицы св€зей
	for (int i = 0; i < SIZE; i++)
	{
		link_matrix[i][i] = 0;
		for (int j = i + 1; j < SIZE; j++)
		{
			printf("Input distance %d - %d: ", i + 1, j + 1);
			scanf("%d", &temp);
			link_matrix[i][j] = temp;
			link_matrix[j][i] = temp;
		}
	}

	// ¬ывод матрицы св€зей
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
			printf("%5d ", link_matrix[i][j]);
		printf("\n");
	}

	//»нициализаци€ вершин и рассто€ний
	for (int i = 0; i < SIZE; i++)
	{
		distances[i] = DIST_UNREACHABLE;
		visited[i] = 1;
	}

	distances[0] = 0;

	// Ўаг алгоритма
	do 
	{
		minindex = DIST_UNREACHABLE;
		min = DIST_UNREACHABLE;
		for (int i = 0; i < SIZE; i++)
		{ // ≈сли вершину ещЄ не обошли и вес меньше min
			if ((visited[i] == 1) && (distances[i] < min))
			{ // ѕереприсваиваем значени€
				min = distances[i];
				minindex = i;
			}
		}
		// ƒобавл€ем найденный минимальный вес
		// к текущему весу вершины
		// и сравниваем с текущим минимальным весом вершины
		if (minindex != DIST_UNREACHABLE)
		{
			for (int i = 0; i<SIZE; i++)
			{
				if (link_matrix[minindex][i] > 0)
				{
					temp = min + link_matrix[minindex][i];
					if (temp < distances[i])
					{
						distances[i] = temp;
					}
				}
			}
			visited[minindex] = 0;
		}
	} while (minindex < DIST_UNREACHABLE);

	// ¬ывод кратчайших рассто€ний до вершин
	printf("\nShortest ways to nodes: \n");
	for (int i = 0; i<SIZE; i++)
		printf("%5d ", distances[i]);

	// ¬осстановление пути
	int ver[SIZE]; // массив посещенных вершин
	int end = 4; // индекс конечной вершины = 5 - 1
	ver[0] = end + 1; // начальный элемент - конечна€ вершина
	int k = 1; // индекс предыдущей вершины
	int weight = distances[end]; // вес конечной вершины

	while (end > 0) // пока не дошли до начальной вершины
	{
		for (int i = 0; i<SIZE; i++) // просматриваем все вершины
		if (link_matrix[end][i] != 0)   // если св€зь есть
		{
			int temp = weight - link_matrix[end][i]; // определ€ем вес пути из предыдущей вершины
			if (temp == distances[i]) // если вес совпал с рассчитанным
			{                 // значит из этой вершины и был переход
				weight = temp; // сохран€ем новый вес
				end = i;       // сохран€ем предыдущую вершину
				ver[k] = i + 1; // и записываем ее в массив
				k++;
			}
		}
	}
	// ¬ывод пути (начальна€ вершина оказалась в конце массива из k элементов)
	printf("\nThe shortest way:\n");
	for (int i = k - 1; i >= 0; i--)
		printf("%3d ", ver[i]);
	getchar();
	return 0;
}
