 #include <iostream>

const int SIZE = 50;
const int COL = 2;
//************************NAGŁÓWKIFUNKCJI**************************//
void backwardSub(double Mx[][COL], double z[], double val, int size = SIZE);
void shermanX(double z[], double z_prim[], double x[], int size = SIZE);

void printMx(double Mx[][COL], int row = SIZE);
void printV(std::string s, double v[], int size = SIZE);

void fillMatrix(double A[][COL], int rows = SIZE, int cols = COL);

//********MAIN**********//
int main()
{
	double A[SIZE][COL];
	double z[SIZE], z_prim[SIZE], y[SIZE];
	std::cout.precision(8);
	fillMatrix(A);
	printMx(A);
	backwardSub(A,z,5); // rozwiąż Az = b
	printV("z", z);
	backwardSub(A,z_prim,1); // rozwiąż Az' = u
	printV("z'",z_prim);
	shermanX(z,z_prim,y); // rozwiąż koncowe rownanie na z
	printV("y",y);
    return 0;
}
//********FUNKCJE**********//

void fillMatrix(double Mx[][COL], int rows , int cols ) {
	for (int i = 0; i < rows; i++) {
		if (i == rows - 1) {
			Mx[i][1] = 0;
			Mx[i][0] = 9;
		}
		else {
			Mx[i][0] = 9;
			Mx[i][1] = 7;
		}
	}
}

void printV(std::string s, double v[], int size) {
	std::cout << "\nWyswietlam wektor " << s << std::endl;
	for (int i = 0; i < size; i++) {
        std::cout << "[ ";
        std::cout.width(10);
        std::cout << v[i];
        std::cout << " ]" << std::endl;
    }
	std::cout << "GOTOWE\n";
}

void printMx(double Mx[][COL], int row) {
	std::cout << "PRINTING MATRIX:\n";
	for(int i = 0; i < row; i++)
	{
	       std::cout << "| ";
	       std::cout.width(12);
	       std::cout << Mx[i][0] << "  ";
	       std::cout.width(10);
	       std::cout << Mx[i][1] << " |"<< std::endl;
	}
	std::cout << "\nMatrix Printed!\n";
}

// dzieki temu ze nasze wektory b,u i v przechowuja takie same elementy nie musimy
// rezerwowac dodatkowej pamieci na ich przechowywanie a jedynie przekazac ich element jako parametr funkcji
void backwardSub(double Mx[][COL], double z[], double val, int size) {
	double suma = 0;
	z[size-1] = val / Mx[size-1][0];

	for (int i = (size - 2); i >= 0; i--) {
		suma = 0;
		suma += (z[i+1] * Mx[i][1]);
		z[i] = (val - suma)/(Mx[i][0]);
	}
}

void shermanX(double z[], double z_prim[], double x[], int size) {
	double suma_licznik = 0; // v transponowane * z
	double suma_mianownik = 0; // v transponowane * z'

	for (int i = 0; i < size; i++) {
		suma_licznik += 1.0*z[i];
		suma_mianownik += 1.0*z_prim[i];
	}
	suma_mianownik++; // 1 + (v transponowane * z') 
	
	for (int i = 0; i < size; i++) {
		x[i] = z[i] - ((z_prim[i] * suma_licznik) / suma_mianownik);
	}
}




