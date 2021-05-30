//Optimal page replacement algorithm
#include <bits/stdc++.h>
using namespace std;
int ramSize; //no. of frames in RAM
int Time = 0;

int predict(vector<int> &pg, vector<int> &fr, int index)
{
    // Store the index of pages which are going
    // to be used recently in future
    int res = -1, farthest = index;
    for (int i = 0; i < fr.size(); i++)
    {
        int j;
        for (j = index; j < pg.size(); j++)
        {
            if (fr[i] == pg[j])
            {
                if (j > farthest)
                {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }

        // If a page is never referenced in future,
        // return it.
        if (j == pg.size())
            return i;
    }

    // If all of the frames were not in future,
    // return any of them, we return 0. Otherwise
    // we return res.
    return (res == -1) ? 0 : res;
}

void loadPage(int pageId, vector<int> &ram, vector<int> &referenceString, int idx)
{
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
        ram.push_back(pageId);
        return;
    }

    int ptr = predict(referenceString, ram, idx);

    cout << "Replacing pageId " << pageId << " with frameNo. " << ptr << "(pageId: " << ram[ptr] << ")" << endl;
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

    for (int i = 0; i < n; i++)
    {
        loadPage(referenceString[i], ram, referenceString, i); //loading pages one by one
        displayRam(ram);
    }
}