#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;
const int SIZE = 100;
const int pSIZE = 4;

void fillArray(double xval[]);
void saveFile(string fileName ,const double xval[], double const result[]);

// funkcje zwracaja wektor par (xi,yi) dla odpowiednich funkcji z zadania
void setOfValuesfun1a(int size, vector<pair<double,double>> &result);
void setOfValuesfun1b(int size, vector<pair<double,double>> &result);
void setOfValuesfun2a(int size, vector<pair<double,double>> &result);
void setOfValuesfun2b(int size, vector<pair<double,double>> &result);

void interpolation(vector<pair<double,double>> &v, const double xval[], double result[]);

int main() {
    double xval[SIZE + 1]; // punkty w przedziale <-1, 1>
    double result[SIZE];
    fillArray(xval);
    
    vector<pair<double,double>> f1a;
    vector<pair<double,double>> f1b;
    vector<pair<double,double>> f2a;
    vector<pair<double,double>> f2b;
    
    setOfValuesfun1a( pSIZE, f1a );
    setOfValuesfun1b( pSIZE, f1b );
    setOfValuesfun2a( pSIZE, f2a );
    setOfValuesfun2b( pSIZE, f2b );

    interpolation(f1a, xval, result);
    saveFile("f1a_4.csv", xval, result);

    interpolation(f1b, xval, result);
    saveFile("f1b_4.csv", xval, result);

    interpolation(f2a, xval, result);
    saveFile("f2a_4.csv", xval, result);

    interpolation(f2b, xval, result);
    saveFile("f2b_4.csv", xval, result);

    return 0;
}

void fillArray(double xval[]) {
    double val = -1.0;
    int i = 0;
    while(val <= 1)
    {
        xval[i++] = val;
        val += 0.02;
    }
    xval[100] = 1;
}

void setOfValuesfun1a(int size, vector<pair<double,double>> &result) {
    result.resize(size + 1);
    for(int i = 0; i < result.size(); i++) {
        result.at(i).first = ((-1.0) + (2.0 * ((double)i/(size))));
        result.at(i).second = ((1.0)/(1.0 + (25.0 * result.at(i).first * result.at(i).first)));
    }
}

void setOfValuesfun1b(int size, vector<pair<double,double>> &result) {
    result.resize(size + 1);
    for(int i = 0; i < result.size(); i++) {
        result.at(i).first = cos(((2 * (double)i + 1) * M_PI)/(2*(size+1)));
        result.at(i).second = ((1.0)/(1.0 + (25.0 * result.at(i).first * result.at(i).first)));
    }
}

void setOfValuesfun2a(int size, vector<pair<double,double>> &result) {
    result.resize(size + 1);
    for(int i = 0; i < result.size(); i++) {
        result.at(i).first = ((-1.0) + (2.0 * ((double)i/(size))));
        result.at(i).second = ((1.0)/(1 + result.at(i).first * result.at(i).first));
    }
}

void setOfValuesfun2b(int size, vector<pair<double,double>> &result){
    result.resize(size + 1);
    for(int i = 0; i < result.size(); i++) {
        result.at(i).first = cos(((2 * (double)i + 1) * M_PI)/(2*(size+1)));
        result.at(i).second = ((1.0)/(1 + result.at(i).first * result.at(i).first));
    }
}

void interpolation(vector<pair<double,double>> &v,const double xval[], double result[]) {
    double val;
    double fi;

    for(int k = 0; k <= SIZE; k++) {
        val = 0.0;
        for(int i = 0; i < v.size(); i++) {
            fi = 1.0;
            for(int j = 0; j < v.size(); j++) {
                if(i != j)
                    fi = fi * ((xval[k] - v.at(j).first)/(v.at(i).first - v.at(j).first));
            }
            val += fi * v.at(i).second;
        }
        result[k] = val;
    }
}

void saveFile(string fileName ,const double xval[], double const result[]) {
    ofstream file;
    file.precision(10);
    file.open(fileName);

    for(int i = 1; i <= SIZE; i++) {
        file << xval[i] << "\t" << result[i] << endl;
    }
}
