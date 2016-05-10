#include "DisjSets.h"
#include <iostream>
using namespace std;

//Construct the disjoint sets object
Disjsets::Disjsets(int numElements):s(numElements)
{
    for(int i=0;i<s.size();i++)
        s[i] = -1;
}


void Disjsets::unionSets(int root1,int root2)
{

    if( s[root2] < s[root1] )//root2 is deeper
        s[root1] = root2; //make root2 new root
    else
    {
        if( s[root1] == s[root2] )
            s[root1]--; //update height to the same
        s[root2] = root1; //make root1 the new root
    }
}

int Disjsets::find(int x) const
{
    if( s[x] < 0)
        return x; // if x is a root,return x
    else
        return find( s[x] );// find the x's root, return it
}
