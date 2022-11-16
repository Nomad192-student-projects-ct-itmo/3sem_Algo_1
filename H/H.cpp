#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
size_t n;

typedef unsigned int my_size;

my_size adjacency_matrix[1000][1000];

vector<size_t> top_list_g;
bool visited[1000];
void dfs_top_sort(size_t v, my_size max_w)
{
    if(visited[v])
        return;

    visited[v] = true;
    for(size_t i = 0; i < n; i++)
    {
        if(max_w >= adjacency_matrix[v][i] && v != i)
        {
            dfs_top_sort(i, max_w);
        }
    }

    top_list_g.push_back(v);
}

void dfs_Kosaraju_and_Sharir_algorithm(size_t v, my_size max_w)
{
    if(visited[v])
        return;

    visited[v] = true;
    for(size_t i = 0; i < n; i++)
    {
        if(max_w >= adjacency_matrix[i][v] && v != i)
        {
            dfs_Kosaraju_and_Sharir_algorithm(i, max_w);
        }
    }
}

bool is_enough_tank(my_size max_w)
{
    top_list_g.clear();
    for (size_t i = 0; i < n; i++)
        visited[i] = false;
    for (size_t i = 0; i < n; i++)
        dfs_top_sort(i, max_w);
    for (size_t i = 0; i < n; i++)
        visited[i] = false;
    for (size_t i = n, k = 0; i--;)
    {
        if(!visited[top_list_g[i]])
        {
            if(k > 0)
                return false;
            dfs_Kosaraju_and_Sharir_algorithm(top_list_g[i], max_w);
            k++;
        }
    }
    return true;
}

int main()
{
    cin >> n;
    my_size max = 0;
    for(size_t i = 0; i < n ; i++)
    {
        for(size_t j = 0; j < n ; j++)
        {
            cin >> adjacency_matrix[i][j];
            if(max < adjacency_matrix[i][j]) max = adjacency_matrix[i][j];
        }
    }

    long long l = -1;
    long long r = max;
    while (l < r - 1)
    {
        long long m = (l + r) / 2;
        if (is_enough_tank(m))
            r = m;
        else
            l = m;
    }
    cout << r;
    return 0;
}
