#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <ctime>
using namespace std;

class tableau
{
    int *T;
    int n;
    int cpt;

public:
    tableau(int n);
    ~tableau();
    void affiche();
    void triTas();
    void triBulle();
    void triInsertion();
    void triFusion(int a, int b);
    void fusion(int a, int m, int b);
    void triRapide(int a, int b, int p);
    void partitionnement(int a, int b, int &m);
    void test(int n);
    void reorganiser(int j);
    int suppression(int k);
    void copier(int T[], int size);
    void echanger(int i, int j);
};