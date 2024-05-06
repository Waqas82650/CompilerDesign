// Here . is used for epsilon
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
using namespace std;

void printFirstFollow(string fileName)
{
    ifstream file(fileName);
    string temp;

    vector< vector<int> > grammer;
    unordered_map< int, unordered_set<int> > firsts;  // To store the firsts
    unordered_map< int, unordered_set<int> > follows; // To store the follows

    // Taking grammer from the file to vector of vector 'grammer'
    int startSymbol;
    getline(file, temp);
    startSymbol = temp[0];

    while (getline(file, temp))
    {
        vector<int> line;
        line.push_back(temp[0]);
        int i = 2;
        while (i < temp.size())
        {
            line.push_back(temp[i]);
            i++;
        }
        grammer.push_back(line);
    }
    file.close();

    // Calculating First
    bool iterateAgain = true;
    while (iterateAgain)
    {
        iterateAgain = false; // To iterate over the set of given grammers again and again until there is no change in any variable's First
        for (int r = 0; r < grammer.size(); r++)
        {
            bool epsilonFound = true; // A->BCD, if there is epsilon in First(B) we will also consider First(C) and so on for first(A)
            for (int i = 1; i < grammer[r].size() && epsilonFound; i++)
            {
                epsilonFound = false;
                int initialFirstsSetSize = firsts[grammer[r][0]].size(); // If this size changes then it means there is an update in Firsts
                if (grammer[r][i] >= 'A' && grammer[r][i] <= 'Z')
                {
                    for (int ele : firsts[grammer[r][i]])
                    {
                        firsts[grammer[r][0]].insert(ele);
                        if (ele == '.')
                            epsilonFound = true;
                    }
                }
                else
                {
                    firsts[grammer[r][0]].insert(grammer[r][i]);
                }
                if (firsts[grammer[r][0]].size() != initialFirstsSetSize)
                    iterateAgain = true;
            }
        }
    }

    // Calculating Follows
    follows[startSymbol].insert('$'); // As the start symbol will always have $ as follow
    iterateAgain = true;
    while (iterateAgain)
    {
        iterateAgain = false; // To iterate over the set of given grammers again and again until there is no change in any variable's Follow
        for (int r = 0; r < grammer.size(); r++)
        {
            for (int i = 1; i < grammer[r].size(); i++)
            {
                if (grammer[r][i] >= 'A' && grammer[r][i] <= 'Z')
                {
                    bool checkNext = true;
                    for (int j = i + 1; j < grammer[r].size() && checkNext; j++)
                    {
                        checkNext = false;
                        if (grammer[r][j] >= 'A' && grammer[r][j] <= 'Z')
                        {
                            int initialSize = follows[grammer[r][i]].size(); // To know if the Follow set size has changed

                            for (int ele : firsts[grammer[r][j]])
                            {
                                if (ele != '.')
                                    follows[grammer[r][i]].insert(ele);
                                else
                                    checkNext = true;
                            }
                            if (follows[grammer[r][i]].size() != initialSize)
                                iterateAgain = true;
                        }
                        else
                        {
                            int initialSize = follows[grammer[r][i]].size(); // To know if the Follow set size has changed
                            follows[grammer[r][i]].insert(grammer[r][j]);

                            if (follows[grammer[r][i]].size() != initialSize)
                                iterateAgain = true;
                        }
                    }
                    // A->BCDF, i.)Suppose we are finding the follow(B) and first of C, D and F have epsilon also, in this case we need to put the follow(A) in Follow(B). ii.)Also, if we are finding Follow(F).
                    if (checkNext)
                    {
                        for (int ele : follows[grammer[r][0]])
                        {
                            follows[grammer[r][i]].insert(ele);
                        }
                    }
                }
            }
        }
    }

    // Printing Values of First
    for (auto [key, val] : firsts)
    {
        char variable = key;
        cout << "First(" << variable << ")= ";
        for (int ele : val)
        {
            char x = ele;
            cout << x;
        }
        cout << endl;
    }
    cout << endl;

    // Printing Values of Follow
    for (auto [key, val] : follows)
    {
        char variable = key;
        cout << "Follow(" << variable << ")= ";
        for (int ele : val)
        {
            char x = ele;
            cout << x;
        }
        cout << endl;
    }
}

int main()
{   cout<<"Name: Suhel Khan"<<endl<<"Roll no: 21BCS025"<<endl ;
    printFirstFollow("first_follow.txt");
    return 0;
}