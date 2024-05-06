// Total number of states including new states should not exceed 10
// At the last there is gonna be an extra space after each line in the resulting table from this code
#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<unordered_set>
#include<map>
#include<algorithm>
using namespace std;

void convertToDFA(string transitionTable)
{
    fstream tt(transitionTable, ios::in);
    string temp;
    // Taking InitialState from the tt
    getline(tt, temp);
    int initialState = temp[0]-'0';
    
    // Taking Final States from the tt
    getline(tt, temp);
    unordered_set<int> finalStates;
    for(int i=0; i<temp.size(); i+=2)
    {
        finalStates.insert(temp[i]-'0');
    }

    // Taking transitionTable from the File
    vector< vector<string> > table;
    int r=0;
    while(getline(tt, temp))
    {
        table.resize(r+1);
        int i=0;
        for(int c=0; i<temp.size(); c++)
        {
            table[r].resize(c+1);
            while(temp[i] != ' ')
            {
                if(temp[i] == '-')
                {
                    table[r][c] = "-1";
                    i=i+2;
                    if(i>=temp.size()) break;
                }
                else
                {
                    table[r][c].push_back(temp[i]);
                    i++;
                    if(i>=temp.size()) break;
                    if(temp[i] == ',') i++;
                }
            }
            i++;
        }
        r++;
    }
    tt.close();
    // Now Starting to perform conversion

    int originalStatesNo = table.size();
    int totalStatesNo = table.size();
    int totalInputs = table[0].size();
    map<int, string> newStates;
    bool loop = true; //To check there is no more non-determinism
    int rowToFill = table.size(); //To know at which row the new state is added in the tansition table
    while(loop)
    {
        loop = false;
        // We are finding where there is non-determinism and sorting the order of states and storing new states in newStates map and also replacing the combined state from a single state
        for(int r=0; r<table.size(); r++)
        {
            for(int c=0; c<table[0].size(); c++)
            {
                if(table[r][c].size() == 1) continue;
                if(table[r][c][0] == '-') continue;
                if(!table[r][c][0]) continue;

                // If we get non-determinism
                bool stateProcessed = false;
                sort(table[r][c].begin(), table[r][c].end());
                for(auto [key, val]: newStates)
                {
                    if(val == table[r][c])
                    {
                        stateProcessed = true;
                        break;
                    }
                }
                // If that state is not in the newStates
                if(!stateProcessed)
                {
                    loop = true;
                    newStates[totalStatesNo] = table[r][c];
                    table.resize(totalStatesNo+1);
                    table[totalStatesNo].resize(totalInputs);
                    totalStatesNo++;
                }
            }
        }
        if(loop)
        {
            for(int r=rowToFill; r<table.size(); r++)
            {
                string states = newStates[rowToFill];
                for(int c=0; c<totalInputs; c++)
                {
                    unordered_set<char> rslt; //This will ensure the duplicate states are not entered into the table
                    for(char state: states)
                    {
                        for(char ele:table[state-'0'][c])
                        {
                            if(ele == '-') break;
                            rslt.insert(ele);
                        }
                        if(finalStates.count(state-'0'))
                            finalStates.insert(r);
                    }
                    if(rslt.size() == 0)
                    {
                        table[r][c]="-1";
                    }
                    else
                    {
                        for(auto ele: rslt)
                        {
                            table[r][c].push_back(ele);
                        }
                    }

                }
                rowToFill++;
            }

        }
        
    }
    // Creating a file with deterministic table
    fstream newTable("deterministicTable.txt", ios::out);
    // Writing initial state
    newTable<<initialState;
    newTable<<endl;
    // Writing Final States
    for(int ele: finalStates)
    {
        if(ele>=originalStatesNo)
        {
            newTable<<newStates[ele];
        }
        else
        {
            newTable<<ele;
        }
        newTable<<" ";
    }
    newTable<<endl;
    // Writing the transition table
    for(int r=0; r<table.size(); r++)
    {
        for(int c=0; c<table[0].size(); c++)
        {
            newTable<<table[r][c];
            newTable<<" ";
        }
        if(r!=table.size()-1) newTable<<endl; // if condition given to prevent an extra line at the end of the table
    }
    newTable.close();
}

int main()
{
    convertToDFA("nfa.txt");
    return 0;
}