#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Maxheap
{
public:
    void insert(string cuisine, int cpoints);
    bool getMax(string &cuisine);
    string getMaxCraving() {return hvec[0].getName();};
    void print();

private:

    class MaxheapNode
    {
    public:
        MaxheapNode(string n, int p) : cuisine(n), cpoints(p) {}
        MaxheapNode(){}

        string getName()
        {
            return cuisine;
        }

        int getPoints()
        {
            return cpoints;
        }

        void setPoints(int p)
        {
            cpoints = p;
        }

        void addPoints(int p)
        {
            cpoints+=p;
        }

    private:
        string cuisine;
        int cpoints;
    };

    void percolateDown(int index);
    void percolateUp(int index);
    void swap(int index1, int index2);

    vector <MaxheapNode> hvec;
    unordered_map <string, int> hmap;
};
#endif