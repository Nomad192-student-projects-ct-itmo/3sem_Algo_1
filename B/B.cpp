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
        find_bridge(i);
    }

    cout << id_bridges.size() << "\n";
    for (const auto &item: id_bridges) {
        cout << item + 1 << " ";
    }
}








//using namespace std;
//
//#define MAX(a, b) ((a) > (b) ? a : b)
//#define MIN(a, b) ((a) < (b) ? a : b)
//
//struct node_t
//{
//    //vector<size_t> in;
//    vector<size_t> out;
//};
//
//node_t nodes[20000];
//
//size_t time_v[20000];
//size_t min_time_path_v[20000];
//size_t i_g = 0;
//
//vector<>
//
//void find_bridge(size_t v, size_t prev)
//{
//    if(time_v[v])
//        return;
//    time_v[v] = ++i_g;
//
//    for(auto& next : nodes[v].out)
//    {
//        if(next == prev)
//            continue;
//
//        if(time_v[next])
//            min_time_path_v[v] = MIN(min_time_path_v[v], time_v[next]);
//
//        if(!time_v[next])
//        {
//            find_bridge(next, v);
//            if(min_time_path_v[next] > time_v[v])
//
//        }
//    }
//}
//
//int main()
//{
//    size_t n, m;
//    cin >> n >> m;
//
//    for(size_t i = 0; i < n; i++)
//        time_v[i] = 0;
//
//    for(size_t i = 0; i < m; i++)
//    {
//        size_t a, b;
//        cin >> a >> b;
//        a--;
//        b--;
//
//        nodes[a].out.push_back(b);
//        nodes[b].out.push_back(a);
//    }
//
//    for(size_t i = 0; i < n; i++)
//    {
//        if(time_v[i] == 0)
//        {
//
//        }
//    }
//}