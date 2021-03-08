#include "graph.hpp"

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
    unordered_map<string, vector<Edge>> actors;
}

void Graph::make_edge(string actor1, string actor2, string movie)
{
    if (actors.find(actor1) == actors.end()) // if can't find actor1
    {
        vector<Edge> edges;
        actors.insert(make_pair(actor1, edges));
        //cout<<"insert: "<<actor1<<endl;
    }
    if (actors.find(actor2) == actors.end()) // if can't find actor1
    {
        vector<Edge> edges;
        actors.insert(make_pair(actor2, edges));
        //cout<<"insert: "<<actor2<<endl;
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
    if ((actors.find(actor1) == actors.end()) || (actors.find(actor2) == actors.end()))
        return "Not present";
    if (actor1 == actor2)
        return actor1;
    queue<string> vertices;
    queue<string> path;
    path.push(actor1);
    vertices.push(actor1);
    unordered_set<string> visited_actor;
    visited_actor.insert(actor1);
    while (!vertices.empty())
    {
        //cout << "inwhile:" << vertices.front() << endl;
        string front = vertices.front();
        string front_path = path.front();
        vertices.pop();
        path.pop();
        //cout<<"pop:"<<back<<endl;

        vector<Edge> v = actors.find(front)->second;
        vector<Edge>::iterator iter;
        for (iter = v.begin(); iter != v.end(); ++iter)
        {
            string to_push_path;
            to_push_path = front_path + " -(" + iter->movie + ")- " + iter->actor;
            //cout << "push_path:" << to_push_path << endl;
            if (iter->actor == actor2)
            {
                return to_push_path;
            }
            if (visited_actor.find(iter->actor) == visited_actor.end())
            {
                //cout << "push:" << iter->actor << endl;
                vertices.push(iter->actor);
                path.push(to_push_path);
                visited_actor.insert(iter->actor);
            }
        }
        //cout << endl;
    }
    return "Not present";
}