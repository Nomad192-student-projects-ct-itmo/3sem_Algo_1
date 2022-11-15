#include <iostream>
#include <vector>

using namespace std;

struct node_t
{
    vector<size_t> in;
    vector<size_t> out;
};

node_t nodes[100000];

vector<size_t> top_list_g;

char color_g[100000];

void top_sort(size_t v)
{
    if(color_g[v] == 'b')
        return;
    if(color_g[v] == 'g')
        throw 0;
    color_g[v] = 'g';

    for(auto next : nodes[v].out)
    {
        top_sort(next);
    }

    top_list_g.push_back(v);
    color_g[v] = 'b';
}

int main()
{
    size_t n, m;
    cin >> n >> m;

    for(size_t i = 0; i < n; i++)
        color_g[i] = 'w';

    for(size_t i = 0; i < m; i++)
    {
        size_t a, b;
        cin >> a >> b;
        a--;
        b--;

        nodes[a].out.push_back(b);
        nodes[b].in.push_back(a);
    }

    for(size_t i = 0; i < n; i++)
    {
        if(color_g[i] == 'w')
        {
            try
            {
                top_sort(i);
            }
            catch(...)
            {
                cout << -1;
                return 0;
            }
        }
    }

    for(size_t i = top_list_g.size(); i--; )
        cout << top_list_g[i] + 1 << " ";
}