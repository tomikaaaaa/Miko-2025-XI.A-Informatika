#include <iostream>
#include <fstream>
#include <fstream>
#include <stack>
#include <queue>
#define N 50
using namespace std;

// KOMPONENS = 
// fokszam 
// teljesGraf
// graf komplementere
// mi az a seta
// mi az az ut
// mi az a vonal
// mi az a kor
// mi az a kormentes
// mi az az osszefuggo komponens = amikor vannak ugynevezett szigetek a grafban, tehat csak egy adott szigetet lehet bejarni onnan
// mi az a fa
// mi az az erdo
// szomszedsagi matrix
// dfs
// bfs
// moore algoritmus

int visited[N]; //hova jutott el a BFS vagy a DFS
int l[N]; //tavolsag vektor, minden csomopont tavolsaga a start csomopont
int p[N]; //szulo(parent) vektor, minden csomopont tavolsaga a start csomopont
int fokszam[N]; //csomopontok fokszama

//Beolvassa a csomopontok szamat es az elek listajat
//felepit egy adjacencia(szomszedsagi) matrixot)
//visszateriti a csomopontok szamat
int beOlvas(string fileName, int graf[][N])
{
    ifstream f(fileName);
    int n = 0;   //csomopontok szama
    f >> n;

    while(f)
    {
        int i;
        int j;
        f >> i >> j;
        graf[i][j] = 1;
        graf[j][i] = 1;
    }

    return n;
}
//Kiirja a graf adjacencia(szomszedsagi) matrixat
void kiIr(int graf[][N], int n)
{
    cout << "Szomszedsagi matrix:" << endl;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
        {
            cout << graf[i][j] << ' ';
        }
        cout << endl;
    }
}

//Depth-first search Melysegi bejaras
//n csomopontok szama
//start kezdo csucs
void dfs(int graf[][N], int n, int start)
{
    //cout << "DFS sorrend: ";
    stack<int> verem;
    verem.push(start);
    while(!verem.empty()){
        int u = verem.top();
        verem.pop();
        if(!visited[u]) //meg nem latogattuk meg
        {
            visited[u] = true;
            //cout << u << " ";
            for(int i = 0; i < n; i++)
            {
                if(!visited[i] && graf[u][i])
                {
                    verem.push(i);
                }
            }
        }
    }
    //cout << endl;
}

//rekurziv dfs
//!!!meghivasa elott a visited tombot nullazni kell
void dfs_rekurziv(int graf[][N], int n, int start)
{
    visited[start] = true;
    for(int i = 0; i < n; i++)
    {
        if(!visited[i] && graf[start][i])
        {
            dfs_rekurziv(graf, n, i);
        }
    }
}

//Breath-first search Szelessegi bejaras
//n csomopontok szama
//start kezdo csucs
void bfs(int graf[][N], int n, int start)
{
    //cout << "BFS sorrend: ";
    queue<int> sor;
    sor.push(start);
    while(!sor.empty())
    {
        int u = sor.front();
        sor.pop();
        if(!visited[u]) // meg nem latogattuk meg
        {
            visited[u] = true;
            //cout << u << " ";
            for(int i = 0; i < n; i++)
            {
                if(!visited[i] && graf[u][i])
                {
                    sor.push(i);
                }
            }
        }
    }
    //cout << endl;
}

//feltolt egy tombot egy ertekkel
void feltolt(int tomb[], int n, int ertek)
{
    for(int i = 0; i < n; i++)
    {
        tomb[i] = ertek;
    }
}

//visszateriti egy graf osszefuggo komponenseinek a szamat
int komponensekSzama(int graf[][N], int n)
{
    //szamlalo
    int k = 0;
    //meg nem jartam sehol
    feltolt(visited, n, 0);

    int start = 0;

    do
    {
        k++;
        dfs(graf, n, start);

        start = -1;
        for(int i = 0; i < n; i++)
        {
            //meg nem jartam ott
            if(visited[i] == 0)
            {
                start = i;
                //cout << "nem jutottam ide: " << i << endl;
                break;
            }
        }
    }while(start != -1);
    return k;
}

//minden csomopont tavolsaga a start csomoponttol
//BFS-en alapul
void MooreTavolsag(int graf[][N], int n, int start)
{
    feltolt(p, n, -1);  //szulo vektor
    feltolt(l, n, -1);  //tavolsag vektor
    l[start] = 0;   //kezdo csomopont tavolsaga onmagatol 0
    queue<int> sor;
    sor.push(start);
    while(!sor.empty())
    {
        int u = sor.front();
        sor.pop();
        for(int i = 0; i < n; i++)
        {
            if(l[i] == -1 && graf[u][i])    // meg nem jartunk ott es van el oda
            {
                l[i] = l[u] +1;
                p[i] = u;
                sor.push(i);
            }
        }
    }
}
//kiirja az utvonalat start es finish kozott forditott sorrendben
void kiirUtvonal(int start, int finish)
{
    if(p[finish] == -1)
    {
        cout<<"Nincs utvonal "<< start << " es " << finish << " kozott!" <<endl;
        return;
    }
    else
    {
        cout<<"Utvonal "<< start << " es " << finish << " kozott: ";
    }
    int via = finish;
    do
    {
        cout << via << "<-";
        via = p[via];
    }while(via != start);
    cout << start << endl;
}

//a fokszam tomb tartalmazza minden csomopont fokszamat
void csomopontokFokszama(int graf[][N], int n)
{
    for(int i = 0; i < n; i++)
    {
        fokszam[i] = 0;
        for(int j = 0; j < n; j++)
        {
            if(graf[i][j]) fokszam[i]++;
        }
    }
}

//eldonti hogy egy graf teljes vagy sem
bool teljesGraf(int graf[][N], int n)
{
    csomopontokFokszama(graf, n);
    for(int i = 0; i < n; i++)
        if(fokszam[i] != n - 1)
            return false;
    return true;
}
// visszateriti az izolalt csomopontok szamat
int izolaltPontokSzama(int graf[][N], int n)
{
    csomopontokFokszama(graf, n);
    int k = 0;
    for(int i = 0; i < n; i++)
        if(fokszam[i] == 0)
            k++;
    return k;
}

//a source graf komplementere a destben grafban lesz
void komplementer(int source[][N], int dest[][N], int n)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(i == j) dest[i][j] = 0;
            else dest[i][j] = !source[i][j];
        }
    }
}

// van-e benne kor
bool tartalmazKort(int graf[][N], int n, int start)
{
    feltolt(p, n, -1);
    feltolt(visited, n, false);
    stack<int> verem;
    verem.push(start);
    p[start] = -1;  //startnak nincs szuloje
    while(!verem.empty())
    {
        int u = verem.top();
        verem.pop();
        visited[u] = true;
        for(int i = 0; i < n; i++)
        {
            if (!visited[i] && graf[u][i])
            {
                if(p[i] != -1) return true;
                p[i] = u;
                verem.push(i);
            }
        }
    }
    return false;
}

bool erdo(int graf[][N], int n)
{
    queue<int> fak;
    //meg nem jartam sehol
    feltolt(visited, n, 0);
    fak.push(0);
    int start = 0;
    do
    {
        dfs(graf, n, start);
        start = -1;
        for(int i = 0; i < n; i++)
        {
            //meg nem jartam ott
            if(visited[i] == 0)
            {
                start = i;
                fak.push(i);
                //cout << "nem jutottam ide: " << i << endl;
                break;
            }
        }
    }
    while(start != -1);

    int faSzam = 0;
    while(!fak.empty())
    {
       int f = fak.front();
       fak.pop();
       if(tartalmazKort(graf, n, f))
       {
           return false;
       }
       faSzam++;
    }
    return faSzam > 1;
}

bool fa(int graf[][N], int n)
{
    return !tartalmazKort(graf, n, 0) && komponensekSzama(graf, n) == 1;
}

int main()
{
    int graf[N][N] = {0};
    int n = beOlvas("C:/Users/tamas/Desktop/XI.A/info/Miko-2025-XI.A-Informatika/graf.txt", graf);   //csomopontok szama
    kiIr(graf, n);
    int graf_komplementer[N][N];
    komplementer(graf, graf_komplementer, n);
    cout << "A graf komplementere:" << endl;
    kiIr(graf_komplementer, n);

    int start = 0;

    MooreTavolsag(graf, n, start);
    cout << "Moore tavolsag:" << endl;
    for(int i = 0; i < n; i++)
    {
        cout << start << " - " << i << " : " << l[i] << " tavolsagra van" << endl;
    }

    kiirUtvonal(start, 3);

    //dfs(graf, n, 0);

    int kSz = komponensekSzama(graf, n);
    cout << "Komponensek szama: "<< kSz << endl;

    cout << "Izolalt pontok szama: " << izolaltPontokSzama(graf, n) << endl;

    if(teljesGraf(graf, n))
        cout << "Teljes graf" << endl;
    else
        cout << "Nem teljes graf" << endl;

    if(tartalmazKort(graf, n, 0))
        cout << "Van benne kor" << endl;
    else
        cout << "Nincs benne kor" << endl;

    if(fa(graf, n))
        cout << "Ez egy fa" << endl;
    else
        cout << "Nem fa" << endl;

    if(erdo(graf, n))
        cout << "Erdo" << endl;
    else
        cout << "Nem erdo" << endl;

    return 0;
}
