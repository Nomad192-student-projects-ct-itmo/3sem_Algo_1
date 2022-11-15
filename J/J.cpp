#include <iostream>
#include <set>

size_t parent[200000];
size_t rank[200000];
void make_set (size_t v) {
    parent[v] = v;
    rank[v] = 0;
}

size_t find_set (size_t v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set (parent[v]);
}

void union_sets (size_t a, size_t b) {
    a = find_set (a);
    b = find_set (b);
    if (a != b) {
        if (rank[a] < rank[b])
            std::swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b])
            ++rank[a];
    }
}



using namespace std;

size_t n, m;

struct weighted_edge_t
{
    size_t from, to;
    double weight;
};
struct compare_weight_t
{
    bool operator()(const weighted_edge_t& a, const weighted_edge_t& b)
    {
        return a.weight < b.weight;
    }
};
multiset<weighted_edge_t, compare_weight_t> edges_sort;


unsigned long long Kruskals_algorithm()
{
    auto iter = edges_sort.begin();

    unsigned long long sum = 0;
    size_t k = 0;

    while(iter != edges_sort.end() && k <= n - 1)
    {
        auto edge = *iter;

        if(find_set(edge.from) != find_set(edge.to))
        {
            union_sets(edge.from, edge.to);
            sum += edge.weight;
            k++;
        }

        iter++;
    }
    return sum;
}

int main()
{
    cin >> n >> m;

    for(size_t i = 0; i < n; i++)
    {
        make_set(i);
    }

    for(size_t i = 0; i < m; i++)
    {
        size_t x, y, w;
        cin >> x >> y >> w;
        x--;
        y--;
        edges_sort.insert({x, y, w});
    }

    cout << Kruskals_algorithm() << endl;
    return 0;
}
