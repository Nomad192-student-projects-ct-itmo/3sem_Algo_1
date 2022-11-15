#include <iostream>
#include <vector>
#include <set>
#include <cassert>

using namespace std;

#define MAX(a, b) ((a) > (b) ? a : b)
#define MIN(a, b) ((a) < (b) ? a : b)

struct edge
{
    size_t v;
    size_t id;
};

struct Compare_edge_t
{
    bool operator() (const edge& a, const edge& b)
    {
        return a.v < b.v;
    }
};

struct node_t
{
    set<edge, Compare_edge_t> out;
    bool is_good_dot = false;
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
    bool flag = true;
    for(auto& next : nodes[v].out) {
        if(next.v == prev && flag)
        {
            flag = false;
            continue;
        }

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


struct full_edge_t
{
    size_t u;
    size_t v;
    size_t color = -1;
};

full_edge_t edges[200000];

bool color[20000];
size_t k;
void paint_vertex(size_t v, size_t cur_color, size_t prev = -1)
{
    color[v] = true;

    bool flag = true;
    for(auto& next : nodes[v].out) {
        if(next.v == prev && flag)
        {
            flag = false;
            continue;
        }

        if(!color[next.v])
        {
            if(min_time_path_v[next.v] >= time_v[v])
            {
                //if(prev != -1)
                size_t new_color = ++k;
                edges[next.id].color = new_color;
                paint_vertex(next.v, new_color, v);
            }
            else
            {
                edges[next.id].color = cur_color;
                paint_vertex(next.v, cur_color, v);
            }
        }
        else if (time_v[next.v] < time_v[v])
        {
            edges[next.id].color = MIN(cur_color, edges[next.id].color);
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

        auto iter = nodes[a].out.find({b, 0});
        if(iter != nodes[a].out.end())
        {
            edges[i] = {0, 0, (*iter).id};
        }
        else
        {
            nodes[a].out.insert({b, i});
            nodes[b].out.insert({a, i});
            edges[i] = {a, b};
        }
    }

    for(size_t i = 0; i < n; i++)
    {
        find_good_dots(i);
    }

//    cout << id_good_dots.size() << "\n";
//    for (const auto &item: id_good_dots) {
//        cout << item + 1 << " ";
//    }
//    cout << endl;

//    for (const auto &item: id_good_dots) {
//        nodes[item].is_good_dot = true;
//    }

    for(size_t i = 0; i < n; i++)
    {
        color[i] = false;
    }
//    for (const auto &item: id_good_dots) {
//        color[item] = 1;
//    }
    k = 1;
    for(size_t i = 0; i < n; i++)
    {
        if(!color[i])
        {
            //k++;
            paint_vertex(i, k);
        }
    }

//    for(size_t i = 0; i < n; i++)
//    {
//        if(color[i] == 1)
//        {
//            for(auto& next : nodes[i].out) {
//                if(color[next.v] == 1)
//                {
//                    paint_good_vertex(next.v);
//                    k++;
//                    break;
//                }
//            }
//            color[i] = 2;
//        }
//    }
//    for(size_t i = 0; i < n; i++)
//    {
//        cout << color[i] << " ";
//    }
//    cout << endl;

//    size_t new_k = k;
//    for(size_t i = 0; i < m; i++)
//    {
//        if(color[edges[i].v] == 1 && color[edges[i].u] == 1)
//        {
//            new_k++;
//        }
//    }

    cout << k - 1 << endl;
    for(size_t i = 0; i < m; i++)
    {
        if(edges[i].u == 0 && edges[i].v == 0)
            cout << edges[edges[i].color].color - 1 << " ";
        else
            cout << edges[i].color - 1 << " ";
    }


//    for(size_t i = 0; i < m; i++)
//    {
//        assert(color[edges[i].v] > 0 && color[edges[i].u] > 0);
//        size_t c = color[edges[i].v];
//        if(c == 1)
//        {
//            c = color[edges[i].u];
//            if(c == 1)
//                c = k++;
//        }
//
//        cout << c - 1 << " ";
//    }

}

/*
 * Test 2
7 9
1 2
1 3
2 3
1 4
1 5
4 5
1 6
1 7
6 7

---
3
1 1 1 2 2 2 3 3 3




 * Test 5
6 6
1 2
2 3
3 1
1 4
2 5
3 6

---
4
1 1 1 4 3 2



 * Test 4
7 7
1 2
2 3
3 1
1 4
2 5
3 6
6 7

---
5
1 1 1 5 4 2 3



 * Test 18
2 2
1 2
1 2

---
1
1 1


4 2
1 2
3 4
*/