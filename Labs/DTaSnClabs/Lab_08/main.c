#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "locale.h"


#define SIZE 6
#define DIST_UNREACHABLE 10000

int main()
{
	int link_matrix[SIZE][SIZE]; // ������� ������
	int distances[SIZE]; // ����������� ����������
	int visited[SIZE]; // ���������� �������
	int temp;
	int minindex, min;
	system("chcp 1251");
	system("cls");

	// ������������� ������� ������
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

	// ����� ������� ������
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
			printf("%5d ", link_matrix[i][j]);
		printf("\n");
	}

	//������������� ������ � ����������
	for (int i = 0; i < SIZE; i++)
	{
		distances[i] = DIST_UNREACHABLE;
		visited[i] = 1;
	}

	distances[0] = 0;

	// ��� ���������
	do 
	{
		minindex = DIST_UNREACHABLE;
		min = DIST_UNREACHABLE;
		for (int i = 0; i < SIZE; i++)
		{ // ���� ������� ��� �� ������ � ��� ������ min
			if ((visited[i] == 1) && (distances[i] < min))
			{ // ��������������� ��������
				min = distances[i];
				minindex = i;
			}
		}
		// ��������� ��������� ����������� ���
		// � �������� ���� �������
		// � ���������� � ������� ����������� ����� �������
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

	// ����� ���������� ���������� �� ������
	printf("\nShortest ways to nodes: \n");
	for (int i = 0; i<SIZE; i++)
		printf("%5d ", distances[i]);

	// �������������� ����
	int ver[SIZE]; // ������ ���������� ������
	int end = 4; // ������ �������� ������� = 5 - 1
	ver[0] = end + 1; // ��������� ������� - �������� �������
	int k = 1; // ������ ���������� �������
	int weight = distances[end]; // ��� �������� �������

	while (end > 0) // ���� �� ����� �� ��������� �������
	{
		for (int i = 0; i<SIZE; i++) // ������������� ��� �������
		if (link_matrix[end][i] != 0)   // ���� ����� ����
		{
			int temp = weight - link_matrix[end][i]; // ���������� ��� ���� �� ���������� �������
			if (temp == distances[i]) // ���� ��� ������ � ������������
			{                 // ������ �� ���� ������� � ��� �������
				weight = temp; // ��������� ����� ���
				end = i;       // ��������� ���������� �������
				ver[k] = i + 1; // � ���������� �� � ������
				k++;
			}
		}
	}
	// ����� ���� (��������� ������� ��������� � ����� ������� �� k ���������)
	printf("\nThe shortest way:\n");
	for (int i = k - 1; i >= 0; i--)
		printf("%3d ", ver[i]);
	getchar();
	return 0;
}
