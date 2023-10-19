#include <iostream>

using namespace std;

char *INPUTFILE = "input.txt";

void fancy_print(double** Matrix, int rows, int columns) {
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

void to_diagonal_matrix(double** MATRIX, int n_of_rows, int n_of_columns) {
	double ratio;
	for(int i=0; i<n_of_rows; i++) {
		if(MATRIX[i][i] == 0.0) {
		    fix_diagonal_zeros(MATRIX, n_of_rows, n_of_columns);
			to_diagonal_matrix(MATRIX, n_of_rows, n_of_columns);
		}
		for(int j=0; j<n_of_rows; j++) {
			if(i!=j) {
				ratio = MATRIX[j][i]/MATRIX[i][i];
				for(int k=0;k<n_of_columns; k++) {
					MATRIX[j][k] -= ratio*MATRIX[i][k];
				}
			}
		}
	}
}

void unknowns_from_diagonal(double** MATRIX, int n_of_rows) {
    
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
    for (int i=0; i<rows; i++) delete[] Matrix[i]; //удаление массива
    delete[] Matrix;
    return 0;
}