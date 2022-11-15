#include <iostream>
#include <vector>
#include <set>
#include <cassert>

using namespace std;

#define MAX(a, b) ((a) > (b) ? a : b)
#define MIN(a, b) ((a) < (b) ? a : b)

struct edge_t
{
    size_t v;
    size_t id;
};

struct node_t
{
    vector<edge_t> out;
    size_t bridge = -1;
};

node_t nodes[20000];
size_t time_v[20000];
size_t min_time_path_v[20000];
size_t i_g = 0;

set<size_t> id_bridges;

void find_bridge(size_t v, size_t prev = -1)
{
    if(time_v[v] != 0)
        return;

    time_v[v] = ++i_g;
    min_time_path_v[v] = i_g;

    size_t k = 0;
    for(auto& next : nodes[v].out)
    {
        if(next.v == prev && k == 0)
        {
            k = 1;
            continue;
        }

        if(time_v[next.v])
            min_time_path_v[v] = MIN(min_time_path_v[v], min_time_path_v[next.v]);
        else
        {
            find_bridge(next.v, v);
            min_time_path_v[v] = MIN(min_time_path_v[v], min_time_path_v[next.v]);
            if(min_time_path_v[next.v] > time_v[v])
                id_bridges.insert(next.id);
        }
    }
}

size_t color[20000];
size_t cur_color_g = 0;
void paint(size_t v, size_t cur_color)
{
    //assert(color[v] == 0);
    color[v] = cur_color;

    for(auto& edge : nodes[v].out)
    {
        if(color[edge.v] == 0)
        {
            if(min_time_path_v[edge.v] > time_v[v])
            {
                cur_color_g++;
                paint(edge.v, cur_color_g);
            }
            else
            {
                paint(edge.v, cur_color);
            }
        }
    }
}

int main()
{
    size_t n, m;
    cin >> n >> m;

    for(size_t i = 0; i < n; i++)
    {
        time_v[i] = 0;
        color[i] = 0;
    }


    for(size_t i = 0; i < m; i++)
    {
        size_t a, b;
        cin >> a >> b;
        a--;
        b--;

        nodes[a].out.push_back({b, i});
        nodes[b].out.push_back({a, i});
    }

    for(size_t i = 0; i < n; i++)
    {
        find_bridge(i);
    }

    size_t k = 0;
    for(size_t i = 0; i < n; i++)
    {
        if(color[i] == 0)
        {
            cur_color_g++;
            k++;
            paint(i, cur_color_g);
        }
    }



    size_t max_color = 0;
    for(size_t i = 0; i < n; i++)
    {
        if(color[i] > max_color)
            max_color = color[i];
    }

    cout << max_color << "\n";
    for(size_t i = 0; i < n; i++)
    {
        //assert(color[i] <= (id_bridges.size() + k));
        cout << color[i] << " ";
    }

//    for (const auto &item: color) {
//        cout << item + 1 << " ";
//    }
}