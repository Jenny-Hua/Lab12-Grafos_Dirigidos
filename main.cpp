#include <bits/stdc++.h>
#include <sstream>
#include <fstream>

#define NOMBRE_ARCHIVO "Malla_Curricular.csv"
using namespace std;

template <class V, class A>
class Grafo
{
private:
    int n;
    vector<V> nombres;     // Almacena el valor de los vertices
    map<V, int> mapn;      // Almacena cada vértice con un valor de pos. o indice
    vector<vector<A>> ady; // Almacena las aristas entre dos vectores
    vector<int> ordenados; // Almacena orden topológico
    vector<int> gradoE;    // Almacena el número de aristas dirigidas a cada nodo
public:
    Grafo() : n{0}, ady{0} {};
    Grafo<V, A> &operator=(const Grafo<V, A> &other)
    {
        this->n = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                ady[i][j] = other[i][j];
            }
        }
    }

    Grafo(vector<vector<A>> x)
    {
        this->crearGrafo(x.size());
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                this->ady[i][j] = x[i][j];
            }
        }
    }
    void crearGrafo(int); // que crea un Grafo<V,A>::vacío.
    void insertarNodo(V);
    void veradyacencia();
    void insertarArista(V a, V b, A arista); // inserta una nueva arista con dirección en caso no exista
    void borrarNodo(V a);                    // que elimina un nodo en caso exista.
    void borrarArista(V a, V b);             // que elimina una arista en caso esta exista.
    bool esVacio();                          // que retorna true en caso el Grafo<V,A>::sea vacío.
    bool existeNodo(V a);                    // que comprueba y retorna true si un nodo se encuentra en el
    A caminoMinimo(V a, V b);                // que retorna el camino mínimo de existir entre un nodo origen y un nodo destino.
    void ordenTopologico();                  // que retorna el orden topológico del Grafo<V,A>::dirigido.
    // importantes
    void indices();
    void gradoEntrada();
    void printgradoEntrada();
    void adyacenciaUno(int a);
    void gradoCero(int i);

    void floyd(vector<vector<A>> &x);
    void floyd();
    void reordenarmatrix(vector<vector<A>> &x);
    void warshal(vector<vector<A>> &x);

    void graficar();
};

template <class V, class A>
void Grafo<V, A>::crearGrafo(int N)
{
    ady.resize(N);
    for (int i = 0; i < N; i++)
    {
        ady[i].resize(N);
    }
    n = N;
}

template <class V, class A>
void Grafo<V, A>::insertarNodo(V nodo)
{
    if (!existeNodo(nodo))
    {
        nombres.push_back(nodo);
        mapn[nodo] = nombres.size() - 1;
        cout << "\nValor de mapn[" << nodo << "]: " << mapn[nodo];
        n = n + 1;
        ady.resize(n);
        for (int i = 0; i < n; i++)
            ady[i].resize(n);
    }
}

template <class V, class A>
void Grafo<V, A>::veradyacencia()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << ady[i][j];
        }
        cout << endl;
    }
}

template <class V, class A>
void Grafo<V, A>::insertarArista(V a, V b, A arista)
{
    if (existeNodo(a) && existeNodo(b))
    {
        int pa = mapn[a];
        cout << "\nPosición de vértice[" << a << "]: " << pa;
        int pb = mapn[b];
        cout << "\nPosición de vértice[" << b << "]: " << pb;
        if (ady[pa][pb] == 0)
            ady[pa][pb] = arista;
        cout << "\nPeso de la arista: " << arista;
        cout << endl;
    }
}

template <class V, class A>
void Grafo<V, A>::borrarNodo(V a)
{
    if (existeNodo(a))
    {
        int pos = mapn[a];
        int i = pos + 1;
        int j = 0;

        if (pos != n - 1)
        {
            while (i != n)
            {
                j = 0;
                while (j != n)
                {
                    ady[i - 1][j] = ady[i][j];
                    ++j;
                }
                // cout << i;
                ++i;
            }

            j = pos + 1;
            while (j != n)
            {
                i = 0;
                while (i != n)
                {
                    ady[i][j - 1] = ady[i][j];
                    ++i;
                }
                // cout << j;
                ++j;
            }
        }
        n = n - 1;
        ady.resize(n);
        for (int i = 0; i < n; i++)
        {
            ady[i].resize(n);
        }

        nombres.erase(nombres.begin() + pos);
        mapn.erase(mapn.find(a));
        for (int i = 0; i < n; i++)
        {
            mapn[nombres[i]] = i;
        }
    }
}

template <class V, class A>
void Grafo<V, A>::graficar()
{
    ofstream arch;
    arch.open("./graphL10.dot");
    if (arch.is_open())
    {
        arch << "strict digraph A { \n";
        for (int i = 0; i < n; i++)
        {
            arch << nombres[i] << endl;
            for (int j = 0; j < n; j++)
            {
                if (ady[i][j] != 0)
                {
                    arch << nombres[i] << "->" << nombres[j] << "[label =" << ady[i][j] << "]" << endl;
                }
            }
        }
        arch << "}\n";
        arch.close();
        system("dot -Tpng ./graphL10.dot -o ./graphL10.png ");
        system("./graphL10.png ");
    }
    else
    {
        cout << "error al crear archivo";
    }
}

template <class V, class A>
void Grafo<V, A>::borrarArista(V a, V b)
{
    if (existeNodo(a) && existeNodo(b))
    {
        int pa = mapn[a];
        int pb = mapn[b];
        if (ady[pa][pb] != 0)
        {
            ady[pa][pb] = 0;
            cout << "Se borro la arista de (" << a << "," << b << ")";
        }
    }
}
template <class V, class A>
bool Grafo<V, A>::esVacio()
{
    if (nombres.empty())
        return true;
    return false;
}

template <class V, class A>
bool Grafo<V, A>::existeNodo(V a)
{
    if (mapn.find(a) != mapn.end())
        return true;
    else
        return false;
}

template <class A>
void print(vector<vector<A>>);

template <class V, class A>
A Grafo<V, A>::caminoMinimo(V a, V b)
{
    vector<vector<A>> x;
    warshal(x);
    print(x);
    int i = mapn[a];
    cout << "Pos. de " << a << ": " << i << endl;
    int j = mapn[b];
    cout << "Pos de " << b << ": " << j << endl;
    cout << "Peso de la ruta más corta: " << x[i][j] << endl;
    return x[i][j];
}

template <class V, class A>
void Grafo<V, A>::reordenarmatrix(vector<vector<A>> &x)
{
    float a = std::numeric_limits<float>::infinity();
    x.resize(n);
    for (int i = 0; i < n; i++)
        x[i].resize(n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (!ady[i][j])
                x[i][j] = a;
            else
                x[i][j] = ady[i][j];
        }
    }
}

template <class V, class A>
void Grafo<V, A>::warshal(vector<vector<A>> &x)
{
    vector<V> s;
    reordenarmatrix(x);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                x[j][k] = min(x[j][k], x[j][i] + x[i][k]);
            }
        }
    }
}

template <class V, class A>
void Grafo<V, A>::floyd(vector<vector<A>> &x)
{

    x.resize(n);
    for (int i = 0; i < n; i++)
        x[i].resize(n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            x[i][j] = ady[i][j];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                if (x[i][j] || (x[i][k] && x[k][j]))
                {
                    x[i][j] = 1;
                }
            }
        }
    }
}

template <class A>
void print(vector<vector<A>> x)
{
    for (int i = 0; i < x.size(); i++)
    {
        for (int j = 0; j < x.size(); j++)
        {
            cout.width(5);
            cout << x[i][j] << " ";
        }
        cout << endl;
    }
}

template <class V, class A>
void Grafo<V, A>::adyacenciaUno(int a)
{
    for (int i = 0; i < n; i++)
    {
        if (ady[a][i] != 0)
        {
            gradoE[a] = gradoE[a] - 1;
        }
        else if (gradoE[i] == 0 && (find(ordenados.begin(), ordenados.end(), nombres[i]) != ordenados.end()) == false)
        {
            ordenados.push_back(nombres[i]);
        }
    }
}
template <class V, class A>
void Grafo<V, A>::ordenTopologico()
{
    for (int i = 0; i < n; i++)
    {
        if (gradoE[i] == 0)
        {
            // ordenados.push_back(nombres[i]);
            adyacenciaUno(mapn[nombres[i]]);
        }
        if (gradoE[i] == 1)
        {
            adyacenciaUno(mapn[nombres[i]]);
        }
        if (gradoE[i] == 2)
        {
            adyacenciaUno(mapn[nombres[i]]);
        }
    }
    cout << endl;
    cout << "Lista de ordenados:  ";
    for (int i = 0; i < n; i++)
    {

        cout << ordenados[i] << "-->";
    }
    cout << endl;
}

template <class V, class A>
void Grafo<V, A>::indices()
{
    cout << "INDICES : ";
    for (int i = 0; i < n; i++)
        cout << nombres[i] << "indice: " << mapn[nombres[i]] << " , ";
    // cout<<endl;
}

template <class V, class A>
void Grafo<V, A>::gradoEntrada()
{
    cout << "INDICES : ";

    for (int a = 0; a < n; a++)
    {
        cout << nombres[a] << " tiene ";

        int cont = 0;
        for (int j = 0; j < n; j++)
        {
            if (ady[a][j] != 0)
            {
                // cout<<<<" ";
                cont = cont + 1;
            }
        }
        gradoE.push_back(cont);
        cout << cont;
        cout << endl;
    }
}

template <class V, class A>
void Grafo<V, A>::printgradoEntrada()
{
    cout << "Grado de entrada: ";
    for (int i = 0; i < n; i++)
        cout << gradoE[i] << ",";
}

int main()
{
    Grafo<std::string, float> N;
    N.insertarNodo("Arequipa");
    N.insertarNodo("trujillo");
    N.insertarNodo("lima");
    N.insertarNodo("puno");
    N.insertarNodo("tumbes");
    N.insertarNodo("cusco");
    cout << endl;

    cout << "\nINSERTANDO ARISTAS\n";
    N.insertarArista("Arequipa", "trujillo", 1);
    N.insertarArista("Arequipa", "lima", 2);
    N.insertarArista("trujillo", "puno", 4);
    N.insertarArista("lima", "trujillo", 1);
    N.insertarArista("lima", "puno", 2);
    N.insertarArista("puno", "cusco", 3);
    N.insertarArista("cusco", "tumbes", 1);
    // N.graficar();

    cout << "\nBORRANDO ARISTAS\n";
    N.borrarArista("cusco", "tumbes");
    cout << endl;

    cout << "\nBORRANDO NODOS\n";
    // N.borrarNodo("trujillo");
    cout << (N.existeNodo("trujillo") ? "Si existe el vértice trujillo" : "No existe el vértice trujillo");
    cout << endl;

    cout << "\nEXISTE NODO\n";
    cout << (N.existeNodo("tumbes") ? "El nodo existe en el grafo" : "El nodo no existe en el grafo") << endl;

    cout << "\nCAMÍNO MÍNIMO\n";
    N.caminoMinimo("Arequipa", "cusco");
    cout << endl;

    N.graficar();
    cout << endl;
    cout << endl;

    return 0;
}