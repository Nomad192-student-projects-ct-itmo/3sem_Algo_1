#include <iostream>
#include <vector>
#include <set>

using namespace std;

#define MAX(a, b) ((a) > (b) ? a : b)
#define MIN(a, b) ((a) < (b) ? a : b)

struct edge
{
    size_t v;
    size_t id;
};

struct node_t
{
    vector<edge> out;
};

node_t nodes[20000];
size_t time_v[20000];
size_t min_time_path_v[20000];
size_t i_g = 0;

set<size_t> id_good_dots;

void find_good_dots(size_t v, size_t prev = -1)
{
    if(time_v[v] != 0)
        return;

    time_v[v] = ++i_g;
    min_time_path_v[v] = i_g;


    size_t k = 0;
    for(auto& next : nodes[v].out)
    {
        if(next.v == prev)
            continue;

        if(time_v[next.v])
            min_time_path_v[v] = MIN(min_time_path_v[v], time_v[next.v]);
        else
        {
            find_good_dots(next.v, v);
            min_time_path_v[v] = MIN(min_time_path_v[v], min_time_path_v[next.v]);
            if(min_time_path_v[next.v] >= time_v[v] && prev != -1)
                id_good_dots.insert(v);
            k++;
        }
    }

    if(prev == -1 && k > 1)
        id_good_dots.insert(v);
}

int main()
{
    size_t n, m;
    cin >> n >> m;

    for(size_t i = 0; i < n; i++)
        time_v[i] = 0;

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
        find_good_dots(i);
    }

    cout << id_good_dots.size() << "\n";
    for (const auto &item: id_good_dots) {
        cout << item + 1 << " ";
    }
}
