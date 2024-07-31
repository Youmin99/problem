#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>

using namespace std;



// Graph class
template <typename T>
class Factorial {
public:
    Factorial();
    Factorial(const vector<T>& values);
    ~Factorial();
    void findFactorial();
    void recurrsion(string vale, vector<T> pre);
    void displayGraph() const;
    void displayPath() const;
    void clear();

private:
    vector<char> factorial;
    set<string> ALL;
};

template <typename T>
Factorial<T>::Factorial() {}

template <typename T>
Factorial<T>::Factorial(const vector<T>& values) {
     factorial.assign(values.begin(), values.end());
}

template <typename T>
Factorial<T>::~Factorial() {
    clear();
}


template <typename T>
void Factorial<T>::findFactorial() {

    if (factorial.size() <= 1) {
       // ALL.insert(factorial[0]);
        return;
        
    }

    for ( auto& item : factorial) {
        vector<char> next;
        string path;

        path.push_back(item);
        for (const auto& it : factorial) {
            if (it != item) {
                next.push_back(it);
            }
        }
            recurrsion(path, next);
    }
}

template <typename T>
void Factorial<T>::recurrsion(string pre_vale, vector<T> pre) {

    if (pre.size() <= 1) {
        pre_vale.push_back(pre[0]);
        ALL.insert(pre_vale);
        return;
    }

    for (const auto& item : pre) {
        vector<char> next;
        string path =pre_vale;

        path.push_back(item);
        //cout<< "path: "<<path <<endl;
        //cout<< "pre_vale: "<<pre_vale <<endl;

        for (const auto& it : pre) {
            if (it != item) {
                next.push_back(it);
                 // cout<< " next: "<<it;
            }
        }
       // cout<< endl;
            recurrsion(path,next);
    }

}

template <typename T>
void Factorial<T>::displayPath() const {
    for (const auto& pre : ALL) {
        cout << pre;
        cout << endl;
    }
}

template <typename T>
void Factorial<T>::clear() {
    factorial.clear();
    ALL.clear();
}


int main() {
    vector<char> vertices = {'1','2','3','4'};

    Factorial<char> Factorial(vertices);
    Factorial.findFactorial();
    Factorial.displayPath();

    return 0;
}
