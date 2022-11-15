#include <cstdio>
#include <cassert>
#include <iostream>
#include <map>
#include <set>
#include <vector>
size_t n, m;
using namespace std;

struct directed_vertex_t
{
	set<size_t> in;
	set<size_t> out;

    size_t strongly_connected_component{};
};

constexpr size_t buf_size = 11;

//directed_vertex_t graph_imp[2000];
map<string, size_t> name_to_vertex;
//map<char[buf_size], size_t> name_to_revers_vertex;
map<size_t, string> vertex_to_name;
//map<size_t, char[buf_size]> revers_vertex_to_name;

struct graph_imp_t
{
	directed_vertex_t vertexes[2000];

	void add(size_t a, size_t b)
	{
		vertexes[a].out.insert(b);
		vertexes[b].in.insert(a);
	}

	void add(char str1[buf_size], char str2[buf_size])
	{
		size_t a = name_to_vertex[str1];
		size_t b = name_to_vertex[str2];

		add(a, b);
	}

	void add(bool r1, char str1[buf_size], bool r2, char str2[buf_size])
	{
		size_t a = name_to_vertex[str1];
		size_t b = name_to_vertex[str2];
//		if(r1) a++;
//		if(r2) b++;

        if(r1 && r2)
        {
            add(a, b);
            add(b+1, a+1);
        }
        if(!r1 && r2)
        {
            add(a+1, b);
            add(b+1, a);
        }
        if(r1 && !r2)
        {
            add(a, b+1);
            add(b, a+1);
        }
        if(!r1 && !r2)
        {
            add(a+1, b+1);
            add(b, a);
        }
	}

	directed_vertex_t& operator[](size_t i)
	{
		return vertexes[i];
	}

    vector<size_t> top_list_g;
    bool visited[2000];
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
        for (size_t i = 0; i < 2*n; i++)
            visited[i] = false;
        for (size_t i = 0; i < 2*n; i++)
            dfs_top_sort(i);
        for (size_t i = 0; i < 2*n; i++)
            visited[i] = false;
        for (size_t i = 2*n, k = 0; i--;)
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

    bool is_solved()
    {
//        for(size_t i = 0; i < n; i++)
//        {
//            size_t ssc1 = vertexes[i*2].strongly_connected_component;
//            size_t ssc2 = vertexes[i*2 + 1].strongly_connected_component;
//            cout << ssc1 << " " << ssc2 << "\n";
//        }
        for(size_t i = 0; i < n; i++)
        {
            size_t ssc1 = vertexes[i*2].strongly_connected_component;
            size_t ssc2 = vertexes[i*2 + 1].strongly_connected_component;
            if(ssc1 == ssc2)
                return false;
        }
        return true;
    }
} graph_imp;


int main()
{
	cin >> n >> m;

	for(size_t i = 0; i < n; i++)
	{
		//char buffer[buf_size];
        string buffer;
		//scanf("%s", buffer);
        cin >> buffer;
		name_to_vertex[buffer] = i*2;
		//name_to_revers_vertex[buffer] = i*2 + 1;
        vertex_to_name[i*2] = buffer;
		//revers_vertex_to_name[i*2 + 1] = buffer;
	}
//    for (const auto &item: name_to_vertex) {
//        cout << item.first << " " << item.second << endl;
//    }
//    for (const auto &item: vertex_to_name) {
//        cout << item.first << " " << item.second << endl;
//    }
	for(size_t i = 0; i < m; i++)
	{
		char buf, s1, s2, buffer_1[buf_size], buffer_2[buf_size];
		scanf("%c%c%s => %c%s", &buf, &s1, buffer_1, &s2, buffer_2);
		assert(buf == '\n');
		assert(s1 == '+' || s1 == '-');
		assert(s2 == '+' || s2 == '-');
		bool r1 = (s1 == '+');
		bool r2 = (s2 == '+');
		// printf("%d|%s|%d|%s\n", r1, buffer_1, r2, buffer_2);
		graph_imp.add(r1, buffer_1, r2, buffer_2);
	}

//	for(size_t i = 0; i < 2*n; i++)
//	{
//		cout << i << " in: ";
//		for(auto& v : graph_imp[i].in)
//			cout << v << " ";
//		cout << " out: ";
//		for(auto& v : graph_imp[i].out)
//			cout << v << " ";
//		cout << "\n";
//	}

    graph_imp.Kosaraju_and_Sharir_algorithm();
    if(!graph_imp.is_solved())
    {
        cout << -1;
        return 0;
    }

    vector<size_t> answer;
    for(size_t i = 0; i < n; i++)
    {
        if(graph_imp[i*2].strongly_connected_component > graph_imp[i*2+1].strongly_connected_component)
        {
            answer.push_back(i*2);
        }
    }

    cout << answer.size() << endl;
    for (const auto &item: answer) {
        cout << vertex_to_name[item] << endl;
    }
	return 0;
}
