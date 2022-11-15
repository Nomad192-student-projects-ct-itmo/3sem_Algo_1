#include <iostream>
#include <vector>
#include <set>
#include <cassert>
#include <cmath>

using namespace std;

size_t n; //, m;

struct weighted_edge_t
{
    size_t from, to;
    double weight;
    //size_t id;
};

//struct compare_from_t
//{
//    bool operator()(const weighted_edge_t& a, const weighted_edge_t& b)
//    {
//        return a.from < b.from;
//    }
//};
//struct compare_to_t
//{
//    bool operator()(const weighted_edge_t& a, const weighted_edge_t& b)
//    {
//        return a.to < b.to;
//    }
//};
struct compare_weight_t
{
    bool operator()(const weighted_edge_t& a, const weighted_edge_t& b)
    {
//        if(a.weight == b.weight)
//            return a.id < b.id;
        return a.weight < b.weight;
    }
};
//weighted_edge_t edges[10000];
//multiset<weighted_edge_t, compare_weight_t> edges_sort;
//size_t from(size_t e)
//{
//    return edges[e].from;
//}
//size_t to(size_t e)
//{
//    return edges[e].to;
//}

//struct vertex_t
//{
//    set<weighted_edge_t, compare_from_t> in;
//    set<weighted_edge_t, compare_to_t> out;
//};

//struct vertex_t
//{
//    set<weighted_edge_t, compare_weight_t> out;
//};
//vertex_t vertexes[10000];


//bool color[10000];
//bool color_all_vertexes(size_t v, size_t prev = -1)
//{
//    if(color[v])
//        return true;
//
//    color[v] = true;
//    for (const auto &next: vertexes[v].out) {
//        if(next != prev)
//        {
//            if(color_all_vertexes(next, v))
//                return true;
//        }
//    }
//    return false;
//}

//bool is_cycle()
//{
//    for(size_t i = 0; i < n; i++)
//        color[i] = false;
//    for(size_t i = 0; i < n; i++)
//    {
//        if(color[i])
//            continue;
//
//        if(color_all_vertexes(i))
//        {
//            return true;
//        }
//    }
//    return false;
//}

//bool is_cycle(size_t root)
//{
//    for(size_t i = 0; i < n; i++)
//        color[i] = false;
//    return color_all_vertexes(root);
//}

struct coord_t
{
    int x, y;
};

coord_t coords[10000];

double weight(size_t u, size_t v)
{
    coord_t a = coords[u];
    coord_t b = coords[v];

    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

double fast_weight(size_t u, size_t v)
{
    coord_t a = coords[u];
    coord_t b = coords[v];

    return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}

struct bad_vertex_t
{
    size_t number;
    mutable double weight = 0;
    mutable size_t min_prev = -1;
    mutable bool first = true;
};

struct compare_bad_vertex_t
{
    bool operator()(const bad_vertex_t& a, const bad_vertex_t& b)
    {
        return a.number < b.number;
    }
};

weighted_edge_t next_min_edge(size_t prev, set<bad_vertex_t, compare_bad_vertex_t> &bad_vertexes)
{
    for (const auto &b: bad_vertexes) {
        double w = fast_weight(prev, b.number);
        if(b.first)
        {
            b.weight = w;
            b.min_prev = prev;
            b.first = false;
        }
        else if(w < b.weight)
        {
            b.weight = w;
            b.min_prev = prev;
        }
    }

    weighted_edge_t res;
    bool first = true;
    for (const auto &b: bad_vertexes) {
        if(first)
        {
            res = {b.min_prev, b.number, b.weight};
            first = false;
        }
        else if(b.weight < res.weight)
        {
            res = {b.min_prev, b.number, b.weight};
        }
    }
    res.weight = weight(res.from, res.to);
    return res;
}

//set<weighted_edge_t, compare_weight_t> current_edges_sort;
//vector<size_t> good_vertexes;
set<bad_vertex_t, compare_bad_vertex_t> bad_vertexes;
double Prims_algorithm()
{
    double sum = 0;
    //good_vertexes.push_back(0);
    bad_vertexes.erase(bad_vertex_t{0});
    size_t prev_v = 0;
    while(!bad_vertexes.empty())
    {
        weighted_edge_t cur_edge = next_min_edge(prev_v, bad_vertexes);
        size_t next_v = cur_edge.to;
        sum += cur_edge.weight;
        bad_vertexes.erase({next_v});
        prev_v = next_v;
    }
    return sum;
}

double sum_edges(multiset<weighted_edge_t, compare_weight_t> &edges)
{
    double res = 0;
    for (const auto &item: edges) {
        res += item.weight;
    }
    return res;
}


int main()
{
    cin >> n;

    for(size_t i = 0, id = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        coords[i] = {x, y};
        bad_vertexes.insert({i});
//        for(size_t j = 0; j < i; j++)
//        {
//            size_t from = j;
//            size_t to = i;
//            double w = weight(coords[from], coords[to]);
//
//            weighted_edge_t edge = {from, to, w};
//
//
//            vertexes[from].out.insert(edge);
//            vertexes[to].out.insert(edge);
//        }
    }

//    for (const auto &edge: edges_sort) {
//        cout << edge.from << " " << edge.to << " " << edge.weight << endl;
//    }

//    if(!are_all_vertices_achievable())
//    {
//        cout << "NO" << endl;
//        return 0;
//    }

    //add_good_vertexes();

    //cout << "YES" << endl;
    cout << Prims_algorithm() << endl;

    return 0;
}