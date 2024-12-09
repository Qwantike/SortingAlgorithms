#include "SortingComparison.h"
bool debug = false;

tableau::tableau(int n)
{
    this->T = nullptr;
    if (n > 0)
    {
        this->n = n;
        T = new int[n];
        this->cpt = 0;
    }
}

tableau::~tableau()
{
    delete[] T;
    T = nullptr;
}

void tableau::affiche()
{
    for (int i = 0; i < this->n; i++)
    {
        cout << T[i] << " ";
    }
}

void tableau::triBulle()
{
    for (int i = 0; i < this->n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (this->T[j] > this->T[j + 1])
            {
                this->echanger(j, j + 1);
                this->cpt++;
            }
        }
    }
}

void tableau::triTas()
{
    int k;
    for (k = (n / 2) - 1; k >= 0; k--)
    {
        this->reorganiser(k);
    }
    for (int k = n - 1; k > 0; k--)
    {
        this->echanger(0, k);
        this->cpt++;
        this->reorganiser(0);
    }
}

void tableau::echanger(int i, int j)
{
    int temp = this->T[i];
    this->T[i] = this->T[j];
    this->T[j] = temp;
}

void tableau::reorganiser(int j)
{
    int i = j;
    int m = 0;
    while (i < (n / 2))
    {
        if (2 * i + 2 < n && T[2 * i + 1] < T[2 * i + 2])
            m = 2 * i + 1;
        else
            m = 2 * i + 2;
        if (T[i] > T[m])
        {
            this->echanger(i, m);
            this->cpt++;
            i = m;
        }
        else
            i = n;
    }
}

void tableau::triInsertion()
{
    this->cpt = 0;
    for (int i = 1; i < this->n; i++)
    {
        int x = T[i];
        int j = i - 1;
        while (j >= 0 && T[j] > x)
        {
            T[j + 1] = T[j];
            j--;
            this->cpt++;
        }
        T[j + 1] = x;
    }
}

int tableau::suppression(int k)
{
    if (k < 0 || k >= n)
    {
        throw out_of_range("Hors de portée");
    }
    else
    {
        int min = T[0];
        T[0] = T[k];
        this->reorganiser(0);
        return min;
    }
}

void tableau::triFusion(int a, int b)
{
    if (a < b)
    {
        int m = (a + b) / 2;
        this->triFusion(a, m);
        this->triFusion(m + 1, b);
        this->fusion(a, m, b);
    }
}

void tableau::fusion(int a, int m, int b)
{
    int n1 = m - a + 1;
    int n2 = b - m;
    int *G = new int[n1 + 1];
    int *D = new int[n2 + 1];
    for (int i = 0; i < n1; i++)
    {
        G[i] = this->T[a + i];
    }
    for (int j = 0; j < n2; j++)
    {
        G[j] = this->T[m + 1 + j];
    }
    G[n1] = INT8_MAX;
    D[n2] = INT8_MAX;
    int i = 0;
    int j = 0;
    for (int k = a; k <= b; k++)
    {
        if (G[i] <= D[j])
        {
            T[k] = G[i];
            i++;
            this->cpt++;
        }
        else
        {
            T[k] = D[j];
            j++;
            this->cpt++;
        }
    }
}
// élément le plus à gauche triRapide(0, n-1, 0)
// élément le plus à droite triRapide(0, n-1, n-1)
// élément du milieu triRapide(0, n-1, (n-1)/2)
// élément aléatoire triRapide(0, n-1, p)

void tableau::triRapide(int a, int b, int p)
{
    if (p != a)
    {
        this->echanger(a, p);
        this->cpt++;
    }

    if (a < b)
    {
        if (debug)
        {
            cout << "tri rapide a<b ok" << endl;
        }
        int m;
        this->partitionnement(a, b, m);
        this->triRapide(a, m - 1, a);
        this->triRapide(m + 1, b, m + 1);
    }
}

void tableau::partitionnement(int a, int b, int &m)
{
    if (debug)
    {
        cout << "entrée dans partitionnement" << endl;
    }
    int l = a + 1;
    int k = b;
    while (l <= k)
    {
        if (debug)
        {
            cout << "test T[l] <= T[a]" << endl;
        }
        while (T[l] <= T[a] && l <= b)
        {
            if (debug)
            {
                cout << "test T[l] <= T[a] ok, l++" << endl;
            }
            l++;
        }
        if (debug)
        {
            cout << "test T[k] > T[a]" << endl;
        }
        while (T[k] > T[a] && k >= a)
        {
            if (debug)
            {
                cout << "test T[k] > T[a] ok, l--" << endl;
            }
            k--;
        }
        if (l < k)
        {
            if (debug)
            {
                cout << "échange car l<K" << endl;
            }
            this->echanger(k, l);
            this->cpt++;
            l++;
            k--;
            if (debug)
            {
                cout << "échange ok" << endl;
            }
        }
        if (debug)
        {
            cout << "échange a et k" << endl;
        }
        this->echanger(a, k);
        this->cpt++;
        if (debug)
        {
            cout << "échange ok" << endl;
        }
        if (debug)
        {
            cout << "m=k" << endl;
        }
        m = k;
    }
}

void tableau::copier(int aux[], int taille)
{
    for (int i = 0; i < taille; i++)
    {
        this->T[i] = aux[i];
    }
}

void tableau::test(int n)
{
    // init temps
    clock_t debutBulle;
    clock_t finBulle;
    clock_t debutInsertion;
    clock_t finInsertion;
    clock_t debutTas;
    clock_t finTas;
    clock_t debutRapide;
    clock_t finRapide;
    clock_t debutFusion;
    clock_t finFusion;
    double tempsBulle;
    double tempsInsertion;
    double tempsTas;
    double tempsRapide;
    double tempsFusion;

    // init stats compteur
    long long minBulle, maxBulle, sommeBulle = 0;
    long long minInsertion, maxInsertion, sommeInsertion = 0;
    long long minTas, maxTas, sommeTas = 0;
    long long minRapide, maxRapide, sommeRapide = 0;
    long long minFusion, maxFusion, sommeFusion = 0;

    // init stats temps
    int tempsMinBulle, tempsMaxBulle, tempsMoyBulle, sommeTempsBulle = 0;
    int tempsMinInsertion, tempsMaxInsertion, tempsMoyInsertion, sommeTempsInsertion = 0;
    int tempsMinTas, tempsMaxTas, tempsMoyTas, sommeTempsTas = 0;
    int tempsMinRapide, tempsMaxRapide, tempsMoyRapide, sommeTempsRapide = 0;
    int tempsMinFusion, tempsMaxFusion, tempsMoyFusion, sommeTempsFusion = 0;

    // Affichage entête
    cout << "Itération | Type de tri     | Echange moyen | Echange min | Echange max | Temps moyen (μs) | Temps min (μs) | Temps max (μs)" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------" << endl;

    // start
    if (debug)
    {
        cout << "début créations tableau init valeurs" << endl;
    }
    const int taille[] = {10, 100, 1000, 10000, 100000, 1000000};
    const int nbtaille = 6;
    if (debug)
    {
        cout << "début créations tableau : boucle for" << endl;
    }
    for (int s = 0; s < nbtaille; s++)
    {
        if (debug)
        {
            cout << "création tableau de taille = " << taille[s] << endl;
        }

        int tailleActuelle = taille[s];

        for (int i = 0; i < n; i++)
        {
            this->n = tailleActuelle;
            for (int j = 0; j < tailleActuelle; j++)
            {
                this->T[j] = (rand() % 1901) + 100;
            }
            // Sauvegarde
            if (debug)
            {
                cout << "sauvegarde du tableau" << endl;
            }
            int *aux = new int[tailleActuelle];
            for (int i = 0; i < tailleActuelle; i++)
            {
                aux[i] = this->T[i];
            }
            if (debug)
            {
                cout << "sauvegarde ok" << endl;
            }
            if (debug)
            {
                cout << "lancement tri bulle" << endl;
            }
            // Bulle
            this->cpt = 0;
            debutBulle = clock();
            this->triBulle();
            finBulle = clock();
            tempsBulle = 1000000 * double(finBulle - debutBulle) / CLOCKS_PER_SEC;

            // Calculs Bulle
            // initiatisation
            if (i == 0)
            {
                // stats
                minBulle = this->cpt;
                maxBulle = this->cpt;
                sommeBulle = this->cpt;
                // temps
                tempsMinBulle = tempsBulle;
                tempsMaxBulle = tempsBulle;
                sommeTempsBulle = tempsBulle;
            }
            else
            {
                // stats
                if (this->cpt < minBulle)
                    minBulle = this->cpt;
                if (this->cpt > maxBulle)
                    maxBulle = this->cpt;
                sommeBulle += this->cpt;
                // temps
                if (tempsBulle < tempsMinBulle)
                    tempsMinBulle = tempsBulle;
                if (tempsBulle > tempsMaxBulle)
                    tempsMaxBulle = tempsBulle;
                sommeTempsBulle += tempsBulle;
            }

            // Insertion
            if (debug)
            {
                cout << "copie tableau pour insertion" << endl;
            }
            this->copier(aux, tailleActuelle);
            if (debug)
            {
                cout << "lancement tri insertion" << endl;
            }
            this->cpt = 0;
            debutInsertion = clock();
            this->triInsertion();
            finInsertion = clock();
            tempsInsertion = 1000000 * double(finInsertion - debutInsertion) / CLOCKS_PER_SEC;
            // Calculs Insertion
            // initiatisation
            if (i == 0)
            {
                // stats
                minInsertion = this->cpt;
                maxInsertion = this->cpt;
                sommeInsertion = this->cpt;
                // temps
                tempsMinInsertion = tempsInsertion;
                tempsMaxInsertion = tempsInsertion;
                sommeTempsInsertion = tempsInsertion;
            }
            else
            {
                // stats
                if (this->cpt < minInsertion)
                    minInsertion = this->cpt;
                if (this->cpt > maxInsertion)
                    maxInsertion = this->cpt;
                sommeInsertion += this->cpt;
                // temps
                if (tempsInsertion < tempsMinInsertion)
                    tempsMinInsertion = tempsInsertion;
                if (tempsInsertion > tempsMaxInsertion)
                    tempsMaxInsertion = tempsInsertion;
                sommeTempsInsertion += tempsInsertion;
            }
            // Tas
            if (debug)
            {
                cout << "copie tableau pour tas" << endl;
            }
            this->copier(aux, tailleActuelle);
            if (debug)
            {
                cout << "lancement tri tas" << endl;
            }
            this->cpt = 0;
            debutTas = clock();
            this->triTas();
            finTas = clock();
            tempsTas = 1000000 * double(finTas - debutTas) / CLOCKS_PER_SEC;

            // Calculs Tas
            // initiatisation
            if (i == 0)
            {
                // stats
                minTas = this->cpt;
                maxTas = this->cpt;
                sommeTas = this->cpt;
                // temps
                tempsMinTas = tempsTas;
                tempsMaxTas = tempsTas;
                sommeTempsTas = tempsTas;
            }
            else
            {
                // stats
                if (this->cpt < minTas)
                    minTas = this->cpt;
                if (this->cpt > maxTas)
                    maxTas = this->cpt;
                sommeTas += this->cpt;
                // temps
                if (tempsTas < tempsMinTas)
                    tempsMinTas = tempsTas;
                if (tempsTas > tempsMaxTas)
                    tempsMaxTas = tempsTas;
                sommeTempsTas += tempsTas;
            }
            // Rapide
            if (debug)
            {
                cout << "copie tableau pour rapide" << endl;
            }
            this->copier(aux, tailleActuelle);
            if (debug)
            {
                cout << "lancement tri rapide" << endl;
            }
            this->cpt = 0;
            debutRapide = clock();
            int p = rand() % tailleActuelle;
            this->triRapide(0, tailleActuelle - 1, p);
            finRapide = clock();
            tempsRapide = 1000000 * double(finRapide - debutRapide) / CLOCKS_PER_SEC;
            // Calculs Rapide
            // initiatisation
            if (i == 0)
            {
                // stats
                minRapide = this->cpt;
                maxRapide = this->cpt;
                sommeRapide = this->cpt;
                // temps
                tempsMinRapide = tempsRapide;
                tempsMaxRapide = tempsRapide;
                sommeTempsRapide = tempsRapide;
            }
            else
            {
                // stats
                if (this->cpt < minRapide)
                    minRapide = this->cpt;
                if (this->cpt > maxRapide)
                    maxRapide = this->cpt;
                sommeRapide += this->cpt;
                // temps
                if (tempsRapide < tempsMinRapide)
                    tempsMinRapide = tempsRapide;
                if (tempsRapide > tempsMaxRapide)
                    tempsMaxRapide = tempsRapide;
                sommeTempsRapide += tempsRapide;
            }

            // Fusion
            if (debug)
            {
                cout << "copie tableau pour fusion" << endl;
            }
            this->copier(aux, tailleActuelle);
            if (debug)
            {
                cout << "lancement tri fusion" << endl;
            }
            this->cpt = 0;
            debutFusion = clock();
            this->triFusion(0, tailleActuelle - 1);
            finFusion = clock();
            tempsFusion = 1000000 * double(finFusion - debutFusion) / CLOCKS_PER_SEC;
            // Calculs Fusion
            // initiatisation
            if (i == 0)
            {
                // stats
                minFusion = this->cpt;
                maxFusion = this->cpt;
                sommeFusion = this->cpt;
                // temps
                tempsMinFusion = tempsFusion;
                tempsMaxFusion = tempsFusion;
                sommeTempsFusion = tempsFusion;
            }
            else
            {
                // stats
                if (this->cpt < minFusion)
                    minFusion = this->cpt;
                if (this->cpt > maxFusion)
                    maxFusion = this->cpt;
                sommeFusion += this->cpt;
                // temps
                if (tempsFusion < tempsMinFusion)
                    tempsMinFusion = tempsFusion;
                if (tempsFusion > tempsMaxFusion)
                    tempsMaxFusion = tempsFusion;
                sommeTempsFusion += tempsFusion;
            }
        }
        // Affichage pour Tri à Bulles
        cout << tailleActuelle << "          | Tri à bulles   | " << sommeBulle / n << "           | " << minBulle << "           | " << maxBulle
             << "           | " << sommeTempsBulle / n << "            | " << tempsMinBulle << "            | " << tempsMaxBulle << endl;

        // Affichage pour Tri par Insertion
        cout << tailleActuelle << "          | Tri insertion  | " << sommeInsertion / n << "           | " << minInsertion << "           | " << maxInsertion
             << "           | " << sommeTempsInsertion / n << "            | " << tempsMinInsertion << "            | " << tempsMaxInsertion << endl;
        // Affichage pour Tri par Tas
        cout << tailleActuelle << "          | Tri par tas    | " << sommeTas / n << "           | " << minTas << "           | " << maxTas
             << "           | " << sommeTempsTas / n << "            | " << tempsMinTas << "            | " << tempsMaxTas << endl;
        // Affichage pour Tri Rapide
        cout << tailleActuelle << "          | Tri Rapide  | " << sommeRapide / n << "           | " << minRapide << "           | " << maxRapide
             << "           | " << sommeTempsRapide / n << "            | " << tempsMinRapide << "            | " << tempsMaxRapide << endl;
        // Affichage pour Tri Fusion
        cout << tailleActuelle << "          | Tri Fusion  | " << sommeFusion / n << "           | " << minFusion << "           | " << maxFusion
             << "           | " << sommeTempsFusion / n << "            | " << tempsMinFusion << "            | " << tempsMaxFusion << endl;
        cout << "****************************************************************************************************" << endl;
    }
}
