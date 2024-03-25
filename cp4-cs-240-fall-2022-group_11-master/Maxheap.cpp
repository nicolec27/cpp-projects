#include "Maxheap.h"

void Maxheap::insert(string cuisine, int cpoints)
{
    int index;

    if (hmap.find(cuisine) == hmap.end())
    {
        index = hvec.size();
        hvec.emplace_back(cuisine, cpoints);
        hmap[cuisine] = index;
    }
    else
    {
        index = hmap.at(cuisine);
        hvec[index].addPoints(cpoints);
        //cout << hvec[index].getName() << " " << hvec[index].getPoints() << " " << index << endl;
    }

    percolateUp(index);
}

bool Maxheap::getMax(string &cuisine)
{
    if (hvec.size() == 0)
    {
        return false;
    }

    cuisine = hvec[0].getName();
    hvec[0].setPoints(0);
    swap(0, hvec.size()-1);
    percolateDown(0);
    //cout << "new max " << hvec[0].getName() << " " << hvec[0].getPoints() << endl;
    return true;
}

void Maxheap::print()
{
    for (MaxheapNode n: hvec)
    {
        cout << n.getName() << " " << n.getPoints() << endl;
    }
}

void Maxheap::percolateDown(int index)
{
    int child_index1 = index*2 + 1;
    int child_index2 = index*2 + 2;

    while (child_index1 < hvec.size())
    {

        if ((hvec[index].getPoints() < hvec[child_index1].getPoints()) && (child_index2 < hvec.size()) && (hvec[index].getPoints() < hvec[child_index2].getPoints()))
        {
            if (hvec[child_index1].getPoints() > hvec[child_index2].getPoints())
            {
                swap(index, child_index1);
                index = child_index1;
            }
            else
            {
                swap(index, child_index2);
                index = child_index2;
            }
        }
        else if (hvec[index].getPoints() < hvec[child_index1].getPoints())
        {
            swap(index, child_index1);
            index = child_index1;
        }
        else if (hvec[index].getPoints() < hvec[child_index2].getPoints() && (child_index2 < hvec.size()))
        {
            swap(index, child_index2);
            index = child_index2;
        }
        else
        {
            break;
        }

        child_index1 = index*2 + 1;
        child_index2 = index*2 + 2;
    }
}

void Maxheap::percolateUp(int index)
{
    int parent_index;

    while (index > 0)
    {
        parent_index = (index-1)/2;

        if (hvec[index].getPoints() > hvec[parent_index].getPoints())
        {
            swap(index, parent_index);
        }
        else
        {
            break;
        }

        index = parent_index;
    }
}

void Maxheap::swap(int index1, int index2)
{
    MaxheapNode s;

    s = hvec[index1];
    hvec[index1] = hvec[index2];
    hvec[index2] = s;

    hmap[hvec[index1].getName()] = index1;
    hmap[hvec[index2].getName()] = index2;
}