#include <iostream>
#include <math.h>
#include <fstream>
using namespace std;

//f(x) = cos(x);
// Df(x) = ( cos(x+h) - cos(x) ) / h;
inline double Dh1_d(double x, double h) {
    return ( cos(x+h) - cos(x) ) / h;
}
inline double Dh2_d(double x, double h) {
    return ( cos(x+h) - cos(x-h) ) / (2*h);
}

inline float Dh1_f(float x, float h) {
    return ( cos(x+h) - cos(x) ) / h;
}
inline float Dh2_f(float x, float h) {
    return ( cos(x+h) - cos(x-h) ) / (2*h);
}


int main()
{
    double x = 0.3, h = 0;

    cout << "Wprowadz wartosc h= ";
    cin >> h;

    double result_D, double_Err;
    float result_F, float_Err;

    cout.precision(1e6);
    cout << "a) Blad z uzyciem double:\n\n";
    result_D = Dh1_d(x, h);
    double_Err = fabs(result_D + sin(x));
    cout << "Wynik przyblizony wynosi: " << result_D << endl;
    cout << "Wartosc bledu wynosi: " << double_Err << endl;

    cout << "\nb) Blad z uzyciem double:\n\n";
    result_D = Dh2_d(x, h);
    double_Err = fabs(result_D + sin(x));
    cout << "Wynik przyblizony wynosi: " << result_D << endl;
    cout << "Wartosc bledu wynosi: " << double_Err << endl;



    cout << "\na) Blad z uzyciem float:\n\n";
    result_F = Dh1_f(x, h);
    float_Err = fabs(result_F + sin(x));
    cout << "Wynik przyblizony wynosi: " << result_F << endl;
    cout << "Wartosc bledu wynosi: " << float_Err << endl;

    cout << "\nb) Blad z uzyciem float:\n\n";
    result_F = Dh2_f(x, h);
    float_Err = fabs(result_F + sin(x));
    cout << "Wynik przyblizony wynosi: " << result_F << endl;
    cout << "Wartosc bledu wynosi: " << float_Err << endl;

    return 0;
}
