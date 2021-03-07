#include "graph.hpp"
#define MAX_SIZE 1000000
Edge::Edge()
{
    movie = "";
    next = NULL;
}

Edge::Edge(string name1, int index, Edge *next1)
{
    movie = name1;
    next = next1;
    vertex_index = index;
}

string Edge::print()
{
    if (movie == "")
    {
        return "";
    }
    //cout<<"&"<<endl;
    if (next == NULL)
    {
        return "->" + movie;
    }
    //cout<<"&"<<endl;
    return " ->" + movie + next->print();
}

Vertex::Vertex()
{
    visited = false;
    first = NULL;
    actor = "";
}

Vertex::Vertex(string actor_name, Edge *first_edge)
{
    visited = false;
    first = first_edge;
    actor = actor_name;
}

string Vertex::print()
{
    return "actor: " + actor + first->print();
}

Graph::Graph()
{
    actors = new Vertex[MAX_SIZE];
    num_actors = 0;
}

void Graph::make_edge(string actor1, string actor2, string movie)
{
    int a = get_vertex(actor1);
    int b = get_vertex(actor2);
    if (a == -1)
    {
        actors[num_actors] = Vertex(actor1, NULL);
        a = num_actors;
        num_actors++;
        cout<<"a"<<endl;
    }
    cout<<"number of actors:"<<num_actors<<endl;
    if (b == -1)
    {
        actors[num_actors] = Vertex(actor2, NULL);
        b = num_actors;
        num_actors++;
        cout<<"b"<<endl;
    }
  //  cout<<"&"<<endl;
    Edge *original_start_a = actors[a].first;
    if(original_start_a){
        cout<<original_start_a->movie<<endl;
    }
    Edge edge1 = Edge(movie, b, original_start_a);
   // cout<<"&"<<endl;
    Edge *original_start_b = actors[b].first;
    Edge edge2 = Edge(movie, a, original_start_b);
    //    cout<<"&"<<endl;
    //cout<<edge1.movie<<" "<<edge2.movie<<endl;
    actors[a].first = &edge1;
    //cout<<actors[a].first->movie<<endl;
    actors[b].first = &edge2;
    //cout<<actors[b].first->movie<<endl;
  //          cout<<"&"<<endl;
    cout << actors[a].print() << endl;
}

int Graph::get_vertex(string actor)
{
    for (int i = 0; i < num_actors; i++)
    {
        if (actors[i].actor == actor)
        {
            return i;
        }
    }
    return -1;
}

int Graph::get_vertex(Vertex actor)
{
    for (int i = 0; i < num_actors; i++)
    {
        if (&(actors[i]) == &(actor))
        {
            return i;
        }
    }
    return -1;
}

string Graph::print()
{
    return "";
}