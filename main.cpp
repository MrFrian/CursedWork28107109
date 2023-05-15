#include <iostream>
#include <clocale>
#include <cmath>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

// Структура для представления ребра в графе
struct Edge
{
    int to;
    float weight;
};

// Структура для представления графа
struct Graph
{
    int V;
    vector<vector<Edge>> adj;
    Graph(int V)
    {
        this->V = V;
        adj.resize(V);
    }
    void addEdge(int u, int v, float weight)
    {
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight});
    }
};

// Структура для хранения информации о вершинах графа
struct Node
{
    int id;
    float dist;
    bool operator<(const Node& other) const
    {
        return dist > other.dist;
    }
};

// Алгоритм Дейкстры
vector<float> dijkstra(Graph& graph, int src)
{
    priority_queue<Node> pq;
    vector<float> dist(graph.V, numeric_limits<float>::max());
    vector<bool> visited(graph.V, false);
    pq.push({src, 0});
    dist[src] = 0;
    while (!pq.empty())
    {
        int u = pq.top().id;
        pq.pop();
        if (visited[u]) continue;
        visited[u] = true;
        for (auto& edge : graph.adj[u])
        {
            int v = edge.to;
            float weight = edge.weight;
            if (!visited[v] && dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
                pq.push({v, dist[v]});
            }
        }
    }
    return dist;
}

int main() {
    setlocale(LC_ALL, "");
    float V, n;
    while (true) {
        wcout << L"Введите количество вершин: ";
        cin >> V;
        if (!cin.fail())
            if (V == round(V))
                if (V < 3)
                    wcout << L"Количество вершин не может быть меньше 3" << endl;
                else
                    break;
            else
                wcout << L"Количество вершин не может быть дробным" << endl;
        else
        {
            wcout << L"Количество вершин не может быть символом" << endl;
            exit(-1);
        }

    }
    Graph graph(V);
    system("cls");

    int maxEdgeAmount = 0;
    for (int i = 1; i < V; ++i)
        maxEdgeAmount += i;
    while (true) {
        wcout << L"Введите количество рёбер: ";
        cin >> n;
        if (!cin.fail())
            if (n == round(n))
                if (n < 1 || n > maxEdgeAmount)
                    wcout << L"Количество рёбер не может быть меньше 1 и, с учётом указанного "
                              "количества вершин, больше " << maxEdgeAmount << endl;
                else break;
            else
                wcout << L"Количество рёбер не может быть дробным" << endl;
        else
        {
            wcout << L"Количество рёбер не может быть символом" << endl;
            exit(-1);
        }
    }
    system("cls");

    float A[(int)n][3];
    for (int i = 0; i < int(n); ++i) {
        while (true) {
            bool trig = true;
            while (true) {
                wcout << L"Укажите с какой вершины начинается ребро " << i + 1 << ": ";
                cin >> A[i][0];
                A[i][0] -= 1;
                if (!cin.fail())
                    if (A[i][0] == round(A[i][0]))
                        if (A[i][0] < 0 || A[i][0] > V)
                            wcout << L"Вершина не существует" << endl;
                        else break;
                    else
                        wcout << L"Вершины имеют целочисленные имена" << endl;
                else
                {
                    wcout << L"Вершины имеют целочисленные имена" << endl;
                    exit(-1);
                }
            }
            while (true) {
                wcout << L"Укажите с какой вершиной соединено ребро " << i + 1 << ": ";
                cin >> A[i][1];
                A[i][1] -= 1;
                if (!cin.fail())
                    if (A[i][1] == round(A[i][1]))
                        if (A[i][1] != A[i][0])
                            if (A[i][1] < 0 || A[i][1] > V)
                                wcout << L"Вершина не существует" << endl;
                            else break;
                        else
                            wcout << L"Ребро не может иметь одну вершину как начало и конец" << endl;
                    else
                        wcout << L"Вершины имеют целочисленные имена" << endl;
                else
                {
                    wcout << L"Вершины имеют целочисленные имена" << endl;
                    exit(-1);
                }
            }
            if (i > 0)
                for (int j = 0; j < i; ++j) {
                    if ((A[j][0] == A[i][0] && A[j][1] == A[i][1]) || (A[j][0] == A[i][1] && A[j][1] == A[i][0]))
                    {
                        wcout << L"Данное ребро уже указано в ребре " << j + 1 << endl;
                        trig = false;
                        break;
                    }
                }
            if (trig)
                break;
        }
        while (true) {
            wcout << L"Укажите вес ребра " << i + 1 << ": ";
            cin >> A[i][2];
            if (!cin.fail())
                if (A[i][2] < 1)
                    wcout << L"Вес ребра не может быть меньше 1" << endl;
                else break;
            else
            {
                wcout << L"Вес ребра не может быть символьным" << endl;
                exit(-1);
            }

        }
        system("cls");
    }

    for (int i = 0; i < n; ++i) graph.addEdge(A[i][0], A[i][1], A[i][2]);

    vector<float> dist = dijkstra(graph, 0);
    for (int i = 1; i < V; i++)
        if (dist[i] == numeric_limits<float>::max())
            wcout << L"Кратчайшее расстояние от вершины 1 к вершине " << i + 1 << L" - Бесконечность" << endl;
        else
            wcout << L"Кратчайшее расстояние от вершины 1 к вершине " << i + 1 << " - " << dist[i] << endl;

    system("pause");
    return 0;
}
