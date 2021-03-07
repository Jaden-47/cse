#include "graph.hpp"
#include <queue>
Edge::Edge()
{
    movie = "";
    actor = "";
}

Edge::Edge(string actor1, string movie1)
{
    movie = movie1;
    actor = actor1;
}

Graph::Graph()
{
    unordered_map<Vertex, vector<Edge>> actors;
}

void Graph::make_edge(string actor1, string actor2, string movie)
{
    if (actors.find(actor1) == actors.end()) // if can't find actor1
    {
        vector<Edge> edges;
        actors.insert(make_pair(actor1, edges));
    }
    if (actors.find(actor2) == actors.end()) // if can't find actor1
    {
        vector<Edge> edges;
        actors.insert(make_pair(actor2, edges));
    }
    Edge edge1 = Edge(actor2, movie);
    Edge edge2 = Edge(actor1, movie);
    actors.find(actor1)->second.push_back(edge1);
    actors.find(actor2)->second.push_back(edge2);
}

string Graph::print()
{
    unordered_map<string, vector<Edge>>::iterator iter;
    string result = "";
    for (iter = actors.begin(); iter != actors.end(); ++iter)
    {
        result = result + "(" + iter->first + ")" + print(iter->first) + "\n";
    }
    return result;
}

string Graph::print(string actor)
{
    vector<Edge> v = actors.find(actor)->second;
    vector<Edge>::iterator iter;
    string result = "";
    for (iter = v.begin(); iter != v.end(); ++iter)
    {
        result = result + "actor: " + iter->actor + " movie: " + iter->movie + " | ";
    }
    return result;
}

string Graph::path(string actor1, string actor2)
{
    queue<string> vertices;
    vertices.push(actor1);
    vector<string> visited_actor;
    visited_actor.push_back(actor1);
    while (vertices.front().empty())
    {
        string top = vertices.front();
        vertices.pop();

        vector<string>::iterator iter_string;
        for (iter_string = visited_actor.begin(); iter_string != visited_actor.end(); ++iter_string)
        {
            if (top==*iter_string){
                continue;
            }
        }

        vector<Edge> v = actors.find(top)->second;
        vector<Edge>::iterator iter;
        for (iter = v.begin(); iter != v.end(); ++iter)
        {
            iter->path=top+iter->movie+iter->actor;
            if(iter->actor==actor2){
                return;
            }
            vertices.push(iter->actor);
            visited_actor.push_back(iter->actor);
        }
    }
    return "can't find";
}