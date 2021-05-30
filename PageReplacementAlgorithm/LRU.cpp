//LRU page replacement algorithm
#include <bits/stdc++.h>
using namespace std;
#define ramSize 4 //ram has got 3 frames
int Time = 0;
void loadPage(int pageId, vector<int> &ram, vector<int> &timestamp)
{
    Time++;
    cout << "--------\n";
    cout << "Request to load pageId " << pageId << endl;
    //check if already present
    for (int i = 0; i < ram.size(); i++)
    {
        if (ram[i] == pageId)
        {
            cout << "HIT\n";
            timestamp[i] = Time;
            return;
        }
    }
    cout << "PAGE FAULT\n";
    //check if ram is empty
    if (ram.size() < ramSize)
    {
        cout << "Loading pageId " << pageId << " in frameNo. " << ram.size() << endl;
        timestamp.push_back(Time);
        ram.push_back(pageId);
        return;
    }

    //we need to replace one frame--the one which came earliest
    int ptr = 0;
    for (int i = 0; i < ramSize; i++)
    {
        if (timestamp[i] < timestamp[ptr]) //choose the least recently used page
            ptr = i;
    }
    cout << "Replacing pageId " << pageId << " with frameNo. " << ptr << "(pageId: " << ram[ptr] << ")" << endl;
    timestamp[ptr] = Time;
    ram[ptr] = pageId;
}

void displayRam(vector<int> &ram)
{
    cout << "RAM: ";
    for (int i = 0; i < ram.size(); i++)
        cout << ram[i] << " ";
    cout << endl;
}

signed main()
{
    vector<int> ram;
    vector<int> timestamp;
    vector<int> referenceString = {7, 0, 1, 2, 0, 3, 0, 4, 2, 6, 5, 0}; //contains page ids
    for (auto x : referenceString)
    {
        loadPage(x, ram, timestamp); //loading pages one by one
        displayRam(ram);
    }
}