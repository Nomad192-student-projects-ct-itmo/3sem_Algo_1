#include <cstdio>
#include <iostream>
#include <set>
#include <vector>
//#include <utility>

constexpr size_t MAX_N = 10000;
constexpr int shift = 1000000000;

size_t n, m;
using namespace std;

struct graph_t {
    struct direct_edge_t
    {
        size_t from, to;
        mutable unsigned int weight;
    };

    struct Compare_by_weight_direct_edge_t
    {
        bool operator()(const direct_edge_t &a, const direct_edge_t &b)
        {
            return a.weight < b.weight;
        }
    };

    struct Compare_by_from_to_direct_edge_t
    {
        bool operator()(const direct_edge_t &a, const direct_edge_t &b)
        {
            if(a.from == b.from)
                return a.to < b.to;
            return a.from < b.from;
        }
    };

    struct directed_vertex_t
    {
        multiset<direct_edge_t, Compare_by_weight_direct_edge_t> in;
        multiset<direct_edge_t, Compare_by_weight_direct_edge_t> out;
    };

    directed_vertex_t vertexes[MAX_N];
    set<direct_edge_t, Compare_by_from_to_direct_edge_t> edges;
};

void color_achievable_vertex(size_t v, graph_t &graph, bool *color)
{
    if(color[v])
        return;

    color[v] = true;
    for (const auto &next: graph.vertexes[v].out) {
        color_achievable_vertex(next.to, graph, color);
    }
}

bool are_all_vertices_achievable(graph_t &graph)
{
    bool color[MAX_N];
    for(size_t i = 0; i < n; i++)
        color[i] = false;
    color_achievable_vertex(0, graph, color);
    for(size_t i = 0; i < n; i++)
        if(!color[i])
            return false;
    return true;
}

void dfs_top_sort(size_t v, graph_t &graph, bool* visited, vector<size_t>& top_sort_list)
{
    if(visited[v])
        return;

    visited[v] = true;
    for(auto next : graph.vertexes[v].out)
    {
        dfs_top_sort(next.to, graph, visited, top_sort_list);
    }

    top_sort_list.push_back(v);
}

void dfs_Kosaraju_and_Sharir_algorithm(size_t v, graph_t &graph, bool *visited, size_t *scc, size_t current_scc)
{
    if(visited[v])
        return;

    visited[v] = true;
    scc[v] = current_scc;
    for(auto next : graph.vertexes[v].in)
    {
        dfs_Kosaraju_and_Sharir_algorithm(next.from, graph, visited, scc, current_scc);
    }
}

void Kosaraju_and_Sharir_algorithm(graph_t &graph, size_t *scc)
{
    bool visited[MAX_N];
    vector<size_t> top_sort_list;

    for (size_t i = 0; i < n; i++)
        visited[i] = false;
    for (size_t i = 0; i < n; i++)
        dfs_top_sort(i, graph, visited, top_sort_list);
    for (size_t i = 0; i < n; i++)
        visited[i] = false;
    for (size_t i = n, current_scc = 0; i--;)
    {
        if(!visited[top_sort_list[i]])
        {
            dfs_Kosaraju_and_Sharir_algorithm(top_sort_list[i], graph, visited, scc, current_scc);
            current_scc++;
        }
    }
}

set<graph_t::direct_edge_t, graph_t::Compare_by_from_to_direct_edge_t> graph_condensation(graph_t &graph)
{
    size_t strongly_connected_component[MAX_N];
    Kosaraju_and_Sharir_algorithm(graph, strongly_connected_component);
    set<graph_t::direct_edge_t, graph_t::Compare_by_from_to_direct_edge_t> new_edges;

    for(auto& edge : graph.edges) {
        size_t scc1 = strongly_connected_component[edge.from];
        size_t scc2 = strongly_connected_component[edge.to];

        if (scc1 != scc2)
        {
            auto pair = new_edges.insert({scc1, scc2, edge.weight});
            //cout << "edge " << pair.first->weight << "\n";
            if(!pair.second && pair.first->weight > edge.weight)
            {
                //cout << "swap val " << edge.weight;
                pair.first->weight = edge.weight;
                //cout << " new val " << pair.first->weight << "\n";
            }
        }
    }
    return new_edges;
}

unsigned long long Chu_Liu_Edmonds_algorithm(graph_t &graph)
{
    unsigned long long result = 0;



    return result;
}

int main()
{
    cin >> n >> m;

    graph_t start_graph;

    for(size_t i = 0; i < m; i++)
    {
        size_t from, to;
        int weight = i;
        cin >> from >> to;// >> weight;
        from--;
        to--;

        graph_t::direct_edge_t edge = {from, to, (unsigned int)(weight+shift)};

        start_graph.vertexes[from].out.insert(edge);
        start_graph.vertexes[to].in.insert(edge);
        start_graph.edges.insert(edge);
    }


//    if(!are_all_vertices_achievable(start_graph))
//    {
//        cout << "NO" << endl;
//        return 0;
//    }

//    cout << "YES" << endl;
    cout << graph_condensation(start_graph).size() << endl;

    return 0;
}
