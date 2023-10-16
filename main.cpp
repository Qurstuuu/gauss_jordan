#include <iostream>

using namespace std;

char *INPUTFILE = "input.txt";

bool to_diagonal_matrix(double** MATRIX, int n_of_rows, int n_of_columns) {
	
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
    for (int i=0; i<rows; i++) {
        for (int j=0; j<columns; j++) {
            cout << Matrix[i][j] << " ";
        }
        cout << endl;
    }
    to_diagonal_matrix(Matrix, rows, columns);
    for (int i=0; i<rows; i++) {
        delete[] Matrix[i];
    }
    delete[] Matrix;
    return 0;
}
