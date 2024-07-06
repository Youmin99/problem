#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>

using namespace std;

// Node structure for the adjacency list
template <typename T>
class Node {
public:
    T value;
    set<T> n_vertices;
    map<T, Node<T>*> neighbors;

    Node(T value) : value(value) {}
};

// Graph class
template <typename T>
class Graph {
public:
    Graph();
    Graph(const vector<T>& vertices, const vector<pair<T, T>>& edges);
    ~Graph();
    void addVertex(T vertex);
    void addEdge(T vertex1, T vertex2);
    void findPath();
    void recurrsion(string prepath, set<T> used_node, Node<T>* cur);
    void displayGraph() const;
    void displayPath() const;
    void clear();

private:
    set<T> G_vertices;
    set<string> G_path;
    map<T, Node<T>*> nodes;
};

template <typename T>
Graph<T>::Graph() {}

template <typename T>
Graph<T>::Graph(const vector<T>& vertices, const vector<pair<T, T>>& edges) {
    for (const T& vertex : vertices) {
        addVertex(vertex);
        G_vertices.insert(vertex);
    }
    for (const pair<T, T>& edge : edges) {
        addEdge(edge.first, edge.second);
    }
}

template <typename T>
Graph<T>::~Graph() {
    clear();
}

template <typename T>
void Graph<T>::addVertex(T vertex) {
    if (nodes.find(vertex) == nodes.end()) {
        nodes[vertex] = new Node<T>(vertex);
    }
}

template <typename T>
void Graph<T>::addEdge(T vertex1, T vertex2) {
    if (nodes.find(vertex1) != nodes.end() && nodes.find(vertex2) != nodes.end()) {
        nodes[vertex1]->n_vertices.insert(vertex2);
        nodes[vertex2]->n_vertices.insert(vertex1);
        nodes[vertex1]->neighbors[vertex2] = nodes[vertex2];
        nodes[vertex2]->neighbors[vertex1] = nodes[vertex1];
    }
}

template <typename T>
void Graph<T>::findPath() {
    for (T vertice : G_vertices) {
        set<T> used_node;
        string path;
        path.push_back(vertice);
        used_node.insert(vertice);
        for (const auto& neighbor : nodes[vertice]->neighbors) {
            if (used_node.find(neighbor.first) == used_node.end()) {
                // cout<<"vertice: "<< vertice<< " neighbor: " << neighbor.first<< " ";
                recurrsion(path, used_node, neighbor.second);
            }
        }
    }
}

template <typename T>
void Graph<T>::recurrsion(string prepath, set<T> used_node, Node<T>* cur) {
    set<int> check;
    check.insert(-1);
    used_node.insert(cur->value);
    prepath.push_back(cur->value);
           //cout<<endl;

    for (const auto& neighbor : cur->neighbors) {
        if (used_node.find(neighbor.first) == used_node.end()) {
            // cout<<"neighbor: " <<neighbor.first<< " ";
            recurrsion(prepath, used_node, neighbor.second);
            check.insert(1);
        } else {
            check.insert(0);
        }
    }

    for (const auto& neighbor : cur->neighbors) {
        if (check.find(1) == check.end() ) {
            G_path.insert(prepath);
        }
    }

}

template <typename T>
void Graph<T>::displayPath() const {
    for (const auto& pre : G_path) {
        cout << pre;
        cout << endl;
    }
}

template <typename T>
void Graph<T>::displayGraph() const {
    for (const auto& pair : nodes) {
        cout << pair.first << ": ";
        for (const auto& neighbor : pair.second->neighbors) {
            cout << neighbor.first << " ";
        }
        cout << endl;
    }
}

template <typename T>
void Graph<T>::clear() {
    for (auto& pair : nodes) {
        delete pair.second;
    }
    nodes.clear();
}

int main() {
    vector<char> vertices = {'a', 'b', 'c', 'd','e', 'f', 'g', 'h','i'};
    vector<pair<char, char>> edges = {{'a', 'j'}, {'a', 'e'}, {'a', 'b'}, {'b', 'd'},
                                      {'b', 'c'}, {'b', 'e'}, {'c', 'g'}, {'c', 'h'},
                                      {'d', 'e'}, {'d', 'f'}, {'d', 'j'}, {'g', 'i'} };

    Graph<char> graph(vertices, edges);
    graph.displayGraph();
    graph.findPath();
    graph.displayPath();

    return 0;
}
