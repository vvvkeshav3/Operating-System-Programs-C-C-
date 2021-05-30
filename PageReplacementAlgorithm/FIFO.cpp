//FIFO page replacement algorithm
#include <bits/stdc++.h>
using namespace std;
int ramSize; //no. of frames in RAM
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
        if (timestamp[i] < timestamp[ptr])
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
    cout << "Enter No. of frames : ";
    cin >> ramSize;
    cout << "Enter Size of Reference String : ";
    int n;
    cin >> n;
    cout << "Enter Reference String : " << endl;
    vector<int> referenceString(n); //contains page ids
    for (int i = 0; i < n; i++)
    {
        cin >> referenceString[i];
    }
    for (auto x : referenceString)
    {
        loadPage(x, ram, timestamp); //loading pages one by one
        displayRam(ram);
    }
}