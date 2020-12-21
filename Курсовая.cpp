#define _CRT_NONSTDC_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>
#include <queue>
#include <iostream>
char post[100], way[100][100];
int p, err;
void Dijkstra(int**A, int*DIS, int*vis, int start, int N) {
	int i;
	start--;
	DIS[start] = 0;
	vis[start] = 1;
	int k = 1;
	p = start;
	_itoa(start + 1, way[start], 10);// для пути в каждую вершину ставим в начало стартовую 
	do {
		for (i = 0; i < N; i++) {
			if ((A[p][i] != 0) && (vis[i] == 0) && (i != p) && (DIS[i] > DIS[p] + A[p][i])) {
				_itoa(i + 1, post, 10);
				strcpy(way[i], way[p]);
				strcat(way[i], " -> ");
				strcat(way[i], post);
				DIS[i] = DIS[p] + A[p][i];
			}
		}
		int min = 8000;
		for (i = 0; i < N; i++)
			if ((DIS[i] < min) && (vis[i] == 0)) {
				min = i;
			}
		p = min;
		vis[p] = 1;
		k++;
	} while (k != N);

}
void Title() {
	printf("\nКурсовая работа \nпо дисциплине");
	printf("\nЛогика и основы алгоритмизации в инженерных задачах");
	printf("\nНа тему: \"Реализация алгоритма Дейкстры\"");
	printf("\n\nВыполнила студентка группы 19ВВ3");
	printf("\nХанбекова Е. В.");
	printf("\n\nПринял:");
	printf("\nМитрохин М.А.\n\n");
	printf("\nНажмите любую клавишу для продолжения");
	_getch();
}
char Menu() {
	int komanda = 0;
	system("cls");
	printf("1| Ручной ввод графа ");
	printf("\n2| Автоматический ввод графа");
	printf("\n3| Загрузить граф из файла");
	printf("\n0| Завершение работы\n\n");
	printf("Ведите номер команды  ");
	scanf_s("%d", &komanda);
	system("cls");
	return(komanda);

}
void Saverez(int*DIS, int start, int N) {
	char nazvanie[10];
	printf("\nВедите название файла: ");
	scanf("%s", nazvanie);
	FILE *F;
	if ((F = fopen(nazvanie, "a+")) == NULL)
	{
		fprintf(stderr, "Невозможно открыть для записи файл\n");
		return;
	}
	for (p = 0; p < N; p++) {
		if (start - 1 != p) {
			if (DIS[p] != 8000) {
				fprintf(F, "\n Путь:  %s\n", way[p]);
				fprintf(F, " Расстояние = %d \n", DIS[p]);
			}
			else
				fprintf(F, "\n Пути из %d в %d нет\n\n ", start + 1, p + 1);
		}
	}

	fclose(F);
}
void Save(int N, int **A) {
	char nazvanie[10];
	printf("Ведите название файла: ");
	scanf("%s", nazvanie);
	FILE *F;
	if ((F = fopen(nazvanie, "w+")) == NULL)
	{
		fprintf(stderr, "Невозможно открыть для записи файл\n");
		return;
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			fprintf(F, "%d ", A[i][j]);
		}
		fprintf(F, "\n");
	}
	fclose(F);
}
int** Handvvod(int N, int **A) {
	int komanda = 0, i, j;
	printf("1| Ориентированный граф");
	printf("\n2| Неориентированный граф");
	printf("\n\nВедите номер команды  ");
	scanf_s("%d", &komanda);
	while ((komanda < 1) || (komanda > 2)) {
		printf("\n\nНеверно введена команда. Попробуйте еще раз.  ");
		scanf_s("%d", &komanda);
	}
	switch (komanda) {
	case 1:
		for (i = 0; i < N; i++) {
			for (j = 0; j < N; j++) {
				if (i != j) {
					printf("Расстояние от  %d  до %d  ", i + 1, j + 1);
					scanf_s("%d", &A[i][j]);
					while (A[i][j] < 0) {
						printf("\nТолько положительные числа! Введите другое число ");
						scanf_s("%d", &A[i][j]);
					}
				}
				else
					A[i][j] = 0;
			}
		}
		break;
	case 2:
		for (i = 0; i < N; i++) {
			for (j = 0; j < N; j++) {
				if (i == j) {
					A[i][j] = 0;
				}
				if (i < j) {
					printf("Расстояние от  %d  до %d  ", i + 1, j + 1);
					scanf_s("%d", &A[i][j]);
					while (A[i][j] < 0) {
						printf("\nТолько положительные числа! Введите другое ");
						scanf_s("%d", &A[i][j]);
					}
					A[j][i] = A[i][j];
				}
			}
		}
		break;
	}
	printf("\n\n    ");
	for (i = 0; i < N; i++) {
		printf("%d  ", i + 1);
	}
	printf("\n\n");
	for (i = 0; i < N; i++) {
		printf("%d|  ", i + 1);
		for (j = 0; j < N; j++) {
			printf("%d  ", A[i][j]);
		}
		printf("\n");
	}
	printf("\nДля сохранения графа нажмите 1 ");
	char kom;
	kom = getch();
	if (kom == '1') {
		Save(N, A);
	}
	return(A);
}
int** Avtovvod(int N, int **A) {
	int komanda = 0, i, j;
	printf("1| Ориентированный граф");
	printf("\n2| Неориентированный граф");
	printf("\n\nВедите номер команды  ");
	scanf_s("%d", &komanda);
	while ((komanda > 2) || (komanda < 1)) {
		printf("\n\nНеверно введена команда. Попробуйте еще раз.  ");
		scanf_s("%d", &komanda);
	}
	switch (komanda) {
	case 1:
		for (i = 0; i < N; i++) {
			for (j = 0; j < N; j++) {
				A[i][j] = rand() % 5;
				if (i == j) {
					A[i][j] = 0;
				}
			}
		}
		break;
	case 2:
		for (i = 0; i < N; i++) {
			for (j = 0; j < N; j++) {
				A[i][j] = rand() % 6;
				A[j][i] = A[i][j];
				if (i == j) {
					A[i][j] = 0;
				}
			}
		}
		break;
	}
	printf("\n\n    ");
	for (i = 0; i < N; i++) {
		printf("%d  ", i + 1);
	}
	printf("\n\n");
	for (i = 0; i < N; i++) {
		printf("%d|  ", i + 1);
		for (j = 0; j < N; j++) {
			printf("%d  ", A[i][j]);
		}
		printf("\n");
	}
	printf("\nДля сохранения графа введите 1  ");
	char kom;
	kom = getch();
	if (kom == '1') {
		Save(N, A);
	}
	return(A);
}
int** Loadvvod(int N, int **A) {
	FILE *F;
	int i, j;
	char nazvanie[10];
	printf("\nВедите название файла: ");
	scanf("%s", nazvanie);
	if ((F = fopen(nazvanie, "r")) == NULL)
	{
		fprintf(stderr, "Невозможно открыть для чтения файл\n Нажмите любую клавишу для выхода\n");
		_getch();
		return 0;
	}
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			fscanf(F, "%d", &A[i][j]);
		}
	}
	fclose(F);
	if (A[N - 1][N - 1] < 0) {
		printf("Количество вершин было введено неверно. Для выхода нажмите любую клавишу ");
		_getch();
		err = 1;
		return 0;
	}
	printf("\n\n    ");
	for (i = 0; i < N; i++) {
		printf("%d  ", i + 1);
	}
	printf("\n\n");
	for (i = 0; i < N; i++) {
		printf("%d|  ", i + 1);
		for (j = 0; j < N; j++) {
			printf("%d  ", A[i][j]);
		}
		printf("\n");
	}
	return(A);
}
int main(void)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int Selection;
	Title();
	system("cls");
	while ((Selection = Menu()) != 0) {
		while ((Selection > 3) || (Selection < 0)) {
			printf("Неверно введен номер. Попоробуйте еще раз");
			_getch();
			Selection = Menu();
		}
		int N;
		printf("\nВведите число вершин графа:  ");
		scanf_s("%d", &N);
		int **A = (int **)malloc(N * sizeof(int *));
		for (int i = 0; i < N; i++) {
			A[i] = (int *)malloc(N * sizeof(int));
		}
		switch (Selection) {
		case 1:
			Handvvod(N, A);
			break;
		case 2:
			Avtovvod(N, A);
			break;
		case 3:
			Loadvvod(N, A);
			if (err == 1)
				return 0;
			break;
		case 0:
			return 0;
			break;
		}
		int *DIS = (int*)malloc(N * sizeof(int));
		int *vis = (int*)malloc(N * sizeof(int));
		for (int i = 0; i < N; i++) {
			DIS[i] = 8000;
			vis[i] = 0;
		}
		int start;
		printf("\n\nВедите вершину, с которой начать обход  ");
		scanf_s("%d", &start);
		while (start > N) {
			printf("\n Ошибка. Введите вершину заново  ");
			scanf("%d", &start);
		}
		Dijkstra(A, DIS, vis, start, N);
		for (p = 0; p < N; p++) {
			if (start-1!=p) {
				if (DIS[p] != 8000){
					printf("\n Путь:  %s", way[p]);
					printf("\n");
					printf(" Расстояние = %d \n\n", DIS[p]);
				}
				else
					printf("\n Пути из %d в %d нет\n\n ", start + 1, p + 1);
			}
		}
		printf("\nДля сохранения результата нажмите 1 ");
		char kom;
		kom = getch();
		if (kom == '1') {
			Saverez(DIS, start, N);
		}
		_getch();
		free(A);
		free(DIS);
		free(vis);
		for (int k = 0; k < 100; k++) {
			post[k] = 0;
			for (int l = 0; l < 100; l++) {
				way[k][l] = 0;
			}
		}
	}
}