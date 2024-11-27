#include <iostream>
#include <iomanip>
using namespace std;

void CreateMatrix(int** matrix, int rows, int cols, int i = 0, int j = 0);
void PrintMatrix(int** matrix, int rows, int cols, int i = 0, int j = 0);
int CountRowsWithZero(int** matrix, int rows, int cols, int i = 0, int j = 0);
void FindColumnWithLongestSeries(int** matrix, int rows, int cols, int& column, int& maxSeriesLength, int j = 0, int i = 1, int currentSeriesLength = 1);

int main() {
    int rows, cols;
    cout << "Enter the number of rows: ";
    cin >> rows;
    cout << "Enter the number of columns: ";
    cin >> cols;

    int** matrix = new int* [rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }

    CreateMatrix(matrix, rows, cols);
    cout << "Matrix:" << endl;
    PrintMatrix(matrix, rows, cols);

    int zeroRows = CountRowsWithZero(matrix, rows, cols);
    cout << "Number of rows with at least one zero element: " << zeroRows << endl;

    int column = 0, maxSeriesLength = 0;
    FindColumnWithLongestSeries(matrix, rows, cols, column, maxSeriesLength);
    cout << "Column with the longest series of identical elements: " << column << " (length = " << maxSeriesLength << ")" << endl;

    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}

// Рекурсивне заповнення матриці
void CreateMatrix(int** matrix, int rows, int cols, int i, int j) {
    if (i >= rows) return;
    cout << "matrix[" << i << "][" << j << "] = ";
    cin >> matrix[i][j];
    if (j + 1 < cols) {
        CreateMatrix(matrix, rows, cols, i, j + 1);
    }
    else {
        CreateMatrix(matrix, rows, cols, i + 1, 0);
    }
}

// Рекурсивне виведення матриці
void PrintMatrix(int** matrix, int rows, int cols, int i, int j) {
    if (i >= rows) return;
    cout << setw(4) << matrix[i][j];
    if (j + 1 < cols) {
        PrintMatrix(matrix, rows, cols, i, j + 1);
    }
    else {
        cout << endl;
        PrintMatrix(matrix, rows, cols, i + 1, 0);
    }
}

// Рекурсивний підрахунок рядків з нульовими елементами
int CountRowsWithZero(int** matrix, int rows, int cols, int i, int j) {
    if (i >= rows) return 0; // Умова завершення: пройдено всі рядки

    if (j < cols) {
        if (matrix[i][j] == 0) return 1 + CountRowsWithZero(matrix, rows, cols, i + 1); // Знайдено нуль
        return CountRowsWithZero(matrix, rows, cols, i, j + 1); // Перевірка наступного елемента в рядку
    }
    return CountRowsWithZero(matrix, rows, cols, i + 1); // Перевірка наступного рядка
}

// Рекурсивний пошук стовпця з найдовшою серією однакових елементів
void FindColumnWithLongestSeries(int** matrix, int rows, int cols, int& column, int& maxSeriesLength, int j, int i, int currentSeriesLength) {
    if (j >= cols) return; // Умова завершення: пройдено всі стовпці

    if (i < rows) {
        if (matrix[i][j] == matrix[i - 1][j]) {
            currentSeriesLength++;
            if (currentSeriesLength > maxSeriesLength) {
                maxSeriesLength = currentSeriesLength;
                column = j;
            }
        }
        else {
            currentSeriesLength = 1;
        }
        FindColumnWithLongestSeries(matrix, rows, cols, column, maxSeriesLength, j, i + 1, currentSeriesLength); // Рекурсія по рядках
    }
    else {
        FindColumnWithLongestSeries(matrix, rows, cols, column, maxSeriesLength, j + 1, 1, 1); // Переход до наступного стовпця
    }
}
