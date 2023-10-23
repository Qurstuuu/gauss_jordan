#include <iostream>
#include <iomanip>

using namespace std;

char *INPUTFILE = "input.txt";

void fancy_print(double** Matrix, int rows, int columns) {
    cout << setprecision(3);
	for (int i=0; i<rows; i++) {
        for (int j=0; j<columns-1; j++) {
            cout << Matrix[i][j] << " ";
        }
        cout << " | " << Matrix[i][columns-1] << endl;
    }
}

void fix_diagonal_zeros(double** MATRIX, int n_of_rows, int n_of_columns) {
    for(int zero_row=0; zero_row<n_of_rows; zero_row++) {
        if(MATRIX[zero_row][zero_row] == 0.0) {
            for(int switch_row = 0; switch_row<n_of_rows; switch_row++) {
                if((MATRIX[switch_row][zero_row] != 0.0) and (MATRIX[zero_row][switch_row] != 0.0)) {
                    double* TempPointer;
                    TempPointer = MATRIX[switch_row];
                    MATRIX[switch_row] = MATRIX[zero_row];
                    MATRIX[zero_row] = TempPointer;
                }
            }
        }
    }
}

int pivot_element(double** MATRIX, int n_of_rows, int current_row, int current_column) {
    for(int p = current_row, pivot = current_row; p < n_of_rows; p++) { // поиск ведущего элемента
	    if(abs(MATRIX[p][current_column]) > abs(MATRIX[pivot][current_column])) {
	        int pivot = p;
	    }
    }
    return pivot;
}

void to_diagonal_matrix(double** MATRIX, int n_of_rows, int n_of_columns) {
	double ratio;
	int skipped_cols = 0;
	for(int i=0; i<n_of_rows; i++) {
	    do {int pivot = pivot_element(MATRIX, n_of_rows, i + skipped_cols);
	    if(MATRIX[pivot][i + skipped_cols] == 0) skipped_cols++;
	    } while(MATRIX[pivot][i + skipped_cols == 0);
	    double* TempPointer = MATRIX[i]; // ставим строку с ведущим элементом
	    MATRIX[i] = MATRIX[pivot]; // вместо i-ой
	    MATRIX[pivot] = TempPointer;
	    }
		if(MATRIX[i][i + skipped_cols] == 0.0) {
		    fix_diagonal_zeros(MATRIX, n_of_rows, n_of_columns);
			to_diagonal_matrix(MATRIX, n_of_rows, n_of_columns);
		}
		for(int j=0; j<n_of_rows; j++) {
			if(i!=j) {
				ratio = MATRIX[j][i + skipped_cols]/MATRIX[i][i + skipped_cols];
				for(int k=i + skipped_cols; k < n_of_columns; k++) {
					MATRIX[j][k] -= ratio*MATRIX[i][k];
				}
			}
		}
	}
}

void to_identity_matrix(double** Matrix, int n_of_rows, int n_of_columns) {
    int where[n_of_columns-1];
    for(int current_row, current_column; (current_row < n_of_rows)&&(current_column < n_of_columns); current_row++) {
        where[current_column] = -1;
        int pivot = pivot_element(Matrix, n_of_rows, current_row, current_column); // выбираем ведущий элемент
        while((Matrix[current_row][pivot] == 0)&&(current_column+1 < n_of_columns)) { // ищем в следующем столбце, если не нашли
            current_column++;
            where[current_column] = -1;
            pivot = pivot_element(Matrix, n_of_rows, current_row, current_column);
        }
        double* TempPointer = Matrix[current_row]; // меняем найденную ведущую строку местами с рабочей
        Matrix[current_row] = Matrix[pivot];
        Matrix[pivot] = TempPointer;
        where[current_column] = current_row;
        for(int i = current_column+1; i < n_of_columns; i++) { // деление всех элементов строки на первый элемент строки
            Matrix[current_row][i] /= Matrix[current_row][current_column];
        }
        Matrix[current_row][current_column] = 1.0; // деление первого элемента на самого себя
        for(int i = 0; i < n_of_rows; i++) { // вычитаем из всех строк, кроме ведущей, ведущую
			if(current_row!=i) {
				double ratio = MATRIX[i][current_column];
				for(int k = current_column; k < n_of_columns; k++) {
					MATRIX[i][k] -= ratio * MATRIX[current_row][k];
				}
			}
		} //
        current_column++;
    }
}

void unknowns_from_diagonal(double** MATRIX, int n_of_rows) {
    cout << setprecision(3);
    double x;
    for(int i=0; i<n_of_rows; i++) {
        x = MATRIX[i][n_of_rows] / MATRIX[i][i];
        cout << 'x' << i+1 << " = " << x << endl;
    }
}

int main()
{
    double** Matrix;
    int rows, columns;
    FILE *IFile;
    if ((IFile = fopen(INPUTFILE, "r")) == NULL) {
        puts("Error opening input file\n");
    }
    else {
        fscanf(IFile, "%d %d", &rows, &columns);
		columns++;
        Matrix = new double*[rows]; //ввод динамического массива
        for(int i=0; i<rows; i++) {
        Matrix[i] = new double[columns];
        }
    }
    for(int i=0; i<rows; i++) {
        for(int j=0; j<columns; j++) {
            if(feof(IFile)==0) fscanf(IFile, "%lf", &Matrix[i][j]);
        }
    }
    cout << "Input successful." << endl;
    fclose(IFile);
    fancy_print(Matrix, rows, columns);
    to_diagonal_matrix(Matrix, rows, columns);
	fancy_print(Matrix, rows, columns);
	unknowns_from_diagonal(Matrix, rows);
    for (int i=0; i<rows; i++) delete[] Matrix[i]; //удаление массива
    delete[] Matrix;
    return 0;
}