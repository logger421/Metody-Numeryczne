#include <iostream>
#include <fstream>
#include <cmath>

const int COL = 4;
const int ROW = 100;

void forwardSub(double L[][COL], double b[], double x[], int size = 100);
void backwardSub(double U[][COL], double y[], double b[], int size = 100);
void LU(double A[][COL], int rows = 100);

void printMx(double Mx[][COL], int row = 100);
void printV(double v[], int size = 100);

void fillMatrix(double A[][COL], int rows = 100, int cols = 4);
void fillV(double V[], int size = 100);

double detM(double A[][COL], int rows = 100)
{
	double det = 1;
	for (int i = 0; i < rows; i++)
		det *= A[i][1];
		
	return det;
}

//*********************************MAIN********************************************************//
int main()
{
	double A[ROW][COL];
	double x[ROW];
	double y[ROW];
	double b[ROW];
	std::cout.precision(8);
	fillMatrix(A);
	fillV(x);
	std::cout << "Macierz A:" << std::endl;
	printMx(A);
	LU(A);
	std::cout << "\nMacierz po rozkładzie LU:" << std::endl;
	printMx(A);
	
	std::cout << "\nPo rozwiazaniu forward substituion wektor b wynosi:\n\n";
	forwardSub(A,b,x);
	printV(b);
	std::cout << "\nPo rozwiazaniu backward substituion wetkor y wynosi:\n\n";
	backwardSub(A,y,b);
	printV(y);
	std::cout << "Wyznacznik macierzy A wynosi: " << detM(A) << std::endl;
	return 0;
}

//**********************************FUNKCJE*****************************************************//

// Wypelnij wektor x[1,2,3...N] o zadanym rozmiarze size
void fillV(double V[], int size)
{
	for (int i = 1; i <= size; i++)
		V[i-1] = i; 
}

// Wypełnij zadaną macierz zgodnie z treścią polecenia mając jej wierze i kolumny
// zakładając że każda kolumna reprezentuje kolejno wstęgę1, diagonale, wstęgę2, wstęgę3
void fillMatrix(double A[][COL], int rows, int cols)
{
	int mianownik_wstegi2 = 1;
	int mianownik_wstegi3 = 1;
	
	for (int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			if(j == 0) { // kolumna 1 przechowuje elementy 1 wstegi
				if ( i != 0)
					A[i][j] = 0.2;
				else
					A[i][j] = 0;
			}
			else if(j == 1) { // kolumna 2 przechowuje elementy diagonalne = 1.2
				A[i][j] = 1.2; 
			}
			else if(j == 2) { //kolumna 3 przechowuje elementy 1 wstegi nad diagonala
				if( i != 99) {
					A[i][j] = (0.1)/mianownik_wstegi2;
					mianownik_wstegi2++;
				}
				else
					A[i][j] = 0;	
			}
			else if(j == 3) { // kolumna 4 przechowuje elementy 2 wstegi nad diagonala
				if( i == 98 || i == 99)
					A[i][j] = 0;
				else {
					A[i][j] = ((0.4)/(pow(mianownik_wstegi3,2)));
					mianownik_wstegi3++;
				}	
			}
		}
	}
}

// Wyświetl wektor tablicowy o zadanym rozmiarze size
void printV(double v[], int size)
{
	for (int i = 0; i < size; i++) {
        std::cout << "[ ";
        std::cout.width(10);
        std::cout << v[i];
        std::cout << " ]" << std::endl;
    }

}

// Wyswietl Tablicową macierz
void printMx(double Mx[][COL], int row)
{
	for(int i = 0; i < row; i++)
	{
	       std::cout << "| ";
	       std::cout.width(14);
	       std::cout << Mx[i][0] << "  ";
	       std::cout.width(14);
	       std::cout << Mx[i][1] << "  ";
	       std::cout.width(14);
	       std::cout << Mx[i][2] << "  ";
	       std::cout.width(14);
	       std::cout << Mx[i][3] << " |"<< std::endl;
	}
}

// rozklad LU macierzy A napisujacy elementy A
void LU(double A[][COL], int rows) 
{
	A[1][0] = A[1][0]/A[0][1];
	
	for (int i = 1 ; i < rows; i++) {
		A[i][1] = A[i][1] - (A[i][0] * A[i-1][2]);
		if( i < rows - 1 ) {
			A[i][2] = A[i][2] - (A[i][0]*A[i-1][3]);
			A[i+1][0] = (A[i+1][0]/A[i][1]);
		}
		if( i < rows -2)
			A[i][3] = A[i][3];	
	}
}

void forwardSub(double L[][COL], double b[], double x[], int size)
{
	double suma = 0;
	b[0] = x[0];
	
	for (int i = 1; i < size; i++) {
		suma = 0;
		suma += (b[i-1] * L[i][0]);
		b[i] = (x[i] - suma) / 1;
	}

}
void backwardSub(double U[][COL], double y[], double b[], int size)
{
	
	double suma = 0;
	y[size-1] = b[size -1] / U[size-1][1];
	
	for (int i = (size - 2); i >= 0; i--) { 
		suma = 0;
		suma += (y[i+1] * U[i][2]) + (y[i+2]*U[i][3]);
		y[i] = (b[i] - suma)/(U[i][1]);
	} 
}



















