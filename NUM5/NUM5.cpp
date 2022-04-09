#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;
// #######################KLASA MATRIX##################################
class Matrix{
private:
    void fillVector_b(); // wypelnia wektor b[1 ... N];
    void resizeVectors(int size); // realogkuje pamiec na wektory
    void calculateX_J(vector<long double> &x_prev, vector<long double> &x_plus); // oblicza dana iteracje X ze wzorow Jacobiego
    void calculateX_G(vector<long double> &x_prev, vector<long double> &x_plus); // oblicza dana iteracje X ze wzorow Gaussa
public:
    vector<long double> x1_j;
    vector<long double> x2_j;
    vector<long double> x1_g;
    vector<long double> x2_g;
    vector<long double> x_jFinal;
    vector<long double> x_gFinal;
    vector<long double> b;
    int size;

    Matrix(int size_);

    long double norma_euklidesowa(vector<long double> v); // wylicza norme euklidesowa

    int jacobi(long double eps); // metoda jacobiego liczaca do zadanej dokladnoœci
    int gauss(long double eps); // metoda gausa liczaca do zadanej dokladnoœci

    void jacobi_iter(int iteration); // metoda jacobiego dzialajaca iteracyjnie
    void gauss_iter(int iteration); // metoda gausa dzialajaca iteracyjnie

    void print_vector(string name, vector<long double> v); // wyswietla tekst oraz zadany wektor
    void clear_vectors(); // wypelnia wektory zerami
	void setStartingVector(vector<long double> v, long double stPoint); // ustawia wektor X na zadana wartosc
    vector<long double> odejmij_wektory(vector<long double> v1, vector<long double> v2); // odejmuje od siebie poszczegolne skladowe wektora
};

// ########################PROTOTYPY FUNKCJI############################
void welcomeText(int &m_size);

// #########################KALSA MAIN##################################
int main()
{
    cout.precision(15);
    int m_size = 100;
    long double eps_precision = 1e-16; // zadana precyzja granicy liczenia gausa i jacobiego

    welcomeText(m_size);

    Matrix mxA(m_size); // utworz macierz o zadanym rozmiarze

    int iterations_J = mxA.jacobi(eps_precision);

    if (iterations_J % 2 == 0) {
        mxA.print_vector("Wektor x obliczony metoda Jacobiego:", mxA.x2_j);
        mxA.x_jFinal = mxA.x2_j;
    } else {
        mxA.print_vector("Wektor x obliczony metoda Jacobiego:", mxA.x1_j);
        mxA.x_jFinal = mxA.x1_j;
    }

    int iterations_G = mxA.gauss(eps_precision);

    if (iterations_G % 2 == 0) {
        mxA.print_vector("Wektor x obliczony metoda Gausa:", mxA.x2_g);
        mxA.x_gFinal = mxA.x2_g;
    } else {
        mxA.print_vector("Wektor x obliczony metoda Gausa:", mxA.x1_g);
        mxA.x_gFinal = mxA.x1_g;
    }

    // funkcje liczace po obloczonych iteracjach zapisujace dane do dwoch plikow
    mxA.clear_vectors();
    mxA.jacobi_iter(iterations_J);
    mxA.gauss_iter(iterations_G);
    return 0;
}

// ############################FUNCKJE#########################################
void welcomeText(int &m_size) {

    cout << "Czy chcesz wykonac przyklad dla mniejszej macierzy (NxN)?[T/N]\n";
    char ch;
    cin >> ch;

    if(ch == 'T' || ch == 't') {
        cout << "Podaj rozmiar nowej macierzy N = ";
        cin >> m_size;
    }
}
// ############################METODY##########################################

// realogacja pamieci dla wektorow oraz wypelnienie wektora b z tresci zadania w konstruktorze.
Matrix::Matrix(int size_) {
    size = size_;
    resizeVectors(size);
    fillVector_b();
}

// Wypisuje wektor
void Matrix::print_vector(string name, vector<long double> v) {
    cout << name << endl;
    for (int i = 0; i < v.size(); i++)
        cout << v.at(i) << endl;
    cout << endl;
}
// ustawia wartosc poczatkowa wektora x
void setStartingVector(vector<long double> v, long double stPoint) {
	for (int i = 0; i < v.size(); i++) {
		v.at(i) = stPoint;
	}
}
// liczy norme euklidesowa wektora jako pierwiastek sumy kwadratow
long double Matrix::norma_euklidesowa(vector<long double> v) {
    long double suma = 0;

    for (int i = 0; i < v.size(); i++)
        suma += (v.at(i) * v.at(i));
    return sqrt(suma);
}
// odejmuje od siebie poszczegolne skladowe wektora
vector<long double> Matrix::odejmij_wektory(vector<long double> v1, vector<long double> v2) {
    for(int i=0; i<v1.size(); i++)
        v1.at(i) -= v2.at(i);

    return v1;
}
// ustawia wszystkie wektory na 0
void Matrix::clear_vectors() {
        for(int i = 0 ; i < size; i++) {
            x1_j.at(i) = 0;
            x2_j.at(i) = 0;
            x1_g.at(i) = 0;
            x2_g.at(i) = 0;
        }
    }

int Matrix::jacobi(long double eps) {
    int iterations = 0;

    // na zmiane liczymy x w k-tej iteracji i (k+1) iteracji sprawdzaj¹c za ka¿dym razem odpowiedni warunek
    while (true) {
        calculateX_J(x2_j, x1_j);
        iterations++;

        if (norma_euklidesowa(odejmij_wektory(x1_j, x2_j)) < eps)
            return iterations;

        // #########################################################################
        // liczymy nastêpn¹ iteracjê

        calculateX_J(x1_j, x2_j);
        iterations++;

        if (norma_euklidesowa(odejmij_wektory(x2_j, x1_j)) < eps) // x2 jest k+1 iteracj¹
            return iterations;
        //##########################################################################
    }
}

void Matrix::jacobi_iter(int iteration) {
    ofstream newFile;
    newFile.open("jacobi.txt");

    for (int i = 1; i <= iteration ; i++) {

        calculateX_J(x2_j, x1_j);
        newFile << i << "\t" << norma_euklidesowa(odejmij_wektory(x1_j, x_jFinal)) << endl;

        i++;
        if(i == iteration + 1) break;
        calculateX_J(x1_j, x2_j);

        newFile << i << "\t" << norma_euklidesowa(odejmij_wektory(x2_j, x_jFinal)) << endl;

    }
    newFile.close();
}

int Matrix::gauss(long double eps) {
    int iterations = 0;
    while(true) {

            calculateX_G(x2_g, x1_g);

            iterations++;

            if ( norma_euklidesowa(odejmij_wektory(x1_g, x2_g)) < eps )
                return iterations;

            calculateX_G(x1_g, x2_g);
            iterations++;

            if ( norma_euklidesowa(odejmij_wektory(x2_g, x1_g)) < eps )
                return iterations;
    }
}

void Matrix::gauss_iter(int iteration) {
    ofstream newFile;
    newFile.open("gauss.txt");

    for (int i = 1; i <= iteration ; i++) {

        calculateX_G(x2_g, x1_g);
        newFile << i << "\t" << norma_euklidesowa(odejmij_wektory(x1_g, x_gFinal)) << endl;

        i++;
        if (i == iteration + 1) break;

        calculateX_G(x1_g, x2_g);
        newFile << i << "\t" << norma_euklidesowa(odejmij_wektory(x2_g, x_gFinal)) << endl;
    }
    newFile.close();
}

// ##############################METODY PRYWATNE################################
void Matrix::resizeVectors(int size) {
    x1_j.resize(size);
    x2_j.resize(size);
    x1_g.resize(size);
    x2_g.resize(size);
    b.resize(size);
}
void Matrix::fillVector_b() {
    // wypelnij wektor b = [1...N]
    for(int i=0; i<size; i++)
        b.at(i) = i+1;
}
void Matrix::calculateX_J(vector<long double> &x_prev, vector<long double> &x_plus) {
    x_plus.at(0) = ( b.at(0) - (1 * x_prev.at(1)) - (0.2 * x_prev.at(2)) )/3;
    x_plus.at(1) = ( b.at(1) - (1 * x_prev.at(0)) - (1 * x_prev.at(2)) - (0.2 * x_prev.at(3)) )/3;

    for(int j = 2, kol = 0; j < size - 2; ++j, ++kol)
        x_plus.at(j) = ( b.at(j) - (0.2 * x_prev.at(kol)) - (1 * x_prev.at(kol+1)) - (1 * x_prev.at(kol+3)) - (0.2 * x_prev.at(kol+4)) )/3;

    x_plus.at(size - 2) = ( b.at(size - 2) - (0.2 * x_prev.at(size - 4)) - (1 * x_prev.at(size - 3)) - (1 * x_prev.at(size - 1)) )/3;
    x_plus.at(size - 1) = ( b.at(size - 1) - (0.2 * x_prev.at(size - 3)) - (1 * x_prev.at(size - 2)) )/3;
}
void Matrix::calculateX_G(vector<long double> &x_prev, vector<long double> &x_plus) {
    x_plus.at(0) = (b.at(0)  - (1 * x_prev.at(1)) - (0.2 * x_prev.at(2)) )/3;
    x_plus.at(1) = (b.at(1) - (1 * x_plus.at(0)) - (1 * x_prev.at(2)) - (0.2 * x_prev.at(3)) )/3;

    for (int j = 2, kol = 0; j < size-2; j++, kol++)
        x_plus.at(j) = (b.at(j) - (0.2 * x_plus.at(kol)) - (1 * x_plus.at(kol+1)) - (1 * x_prev.at(kol+3)) - (0.2 * x_prev.at(kol+4)) )/3;

    x_plus.at(size-2) = (b.at(size-2) - (0.2 * x_plus.at(size-4)) - (1 * x_plus.at(size-3)) - (1 * x_prev.at(size-1)) )/3;
    x_plus.at(size-1) = (b.at(size-1) - (0.2 * x_plus.at(size-3)) - (1 * x_plus.at(size-2)))/3;
}


