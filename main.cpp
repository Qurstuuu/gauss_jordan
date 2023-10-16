#include <iostream>

using namespace std;

char *INPUTFILE = "input.txt";

bool to_diagonal_matrix() {

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
        Matrix = new double*[rows]; //ввод динамического массива
        for(int i=0; i<rows; i++) {
        Matrix[i] = new double[columns+1];
        }
    }
    for(int i=0; i<rows; i++) {
        for(int j=0; j<columns+1; j++) {
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
