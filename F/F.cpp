#include <cstdio>
#include <iostream>
#include <set>
#include <vector>
#include <utility>

size_t n, m;
using namespace std;

set<pair<size_t, size_t>> edges;

struct directed_vertex_t
{
	multiset<size_t> in;
	multiset<size_t> out; 

	size_t strongly_connected_component{};
};

directed_vertex_t vertexes[10000];

vector<size_t> top_list_g;
bool visited[10000];
void dfs_top_sort(size_t v)
{
	if(visited[v])
		return;

	visited[v] = true;
    for(auto next : vertexes[v].out)
    {
        dfs_top_sort(next);
    }
 
    top_list_g.push_back(v);
}

vector<size_t> strongly_connected_component_g;
void dfs_Kosaraju_and_Sharir_algorithm(size_t v)
{
	if(visited[v])
		return;

	visited[v] = true;
	strongly_connected_component_g.push_back(v);
    for(auto next : vertexes[v].in)
    {
        dfs_Kosaraju_and_Sharir_algorithm(next);
    }
}

void Kosaraju_and_Sharir_algorithm()
{
	for (size_t i = 0; i < n; i++)
		visited[i] = false;
	for (size_t i = 0; i < n; i++)
		dfs_top_sort(i);
	for (size_t i = 0; i < n; i++)
		visited[i] = false;
	for (size_t i = n, k = 0; i--;)		
	{
	    if(!visited[top_list_g[i]])
	    {
    		dfs_Kosaraju_and_Sharir_algorithm(top_list_g[i]);
    		//cout << "comp " << k << " : ";
    		for(const auto& item : strongly_connected_component_g)
    		{
    		    //cout << item << " ";
    			vertexes[item].strongly_connected_component = k;
    		}
    		//cout << endl;
    		strongly_connected_component_g.clear();	 
    		k++;
	    }
	}
}

int main()
{
	cin >> n >> m;

	for(size_t i = 0; i < m; i++)
	{
		size_t from, to;
		cin >> from >> to;
		from--;
		to--;

		vertexes[from].out.insert(to);
		vertexes[to].in.insert(from);
		edges.insert(pair<size_t, size_t>{from, to});
	}

	Kosaraju_and_Sharir_algorithm();


	std::set<std::pair<int, int>> answer;
	for(auto& edge : edges)
	{
		size_t scc1 = vertexes[edge.first].strongly_connected_component;
		size_t scc2 = vertexes[edge.second].strongly_connected_component;

        //cout << scc1 << " " << scc2 << "\n";
		if(scc1 != scc2) answer.insert({scc1, scc2});
	}

	cout << answer.size();

	return 0;
}
