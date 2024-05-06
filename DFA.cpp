#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <fstream>
using namespace std;
bool isValidString(string file, string input)
{
    ifstream tt(file);

    string temp("");
    getline(tt, temp);
    int initialState = temp[0] - '0';

    getline(tt, temp);
    unordered_set<int> finalStates;
    for (int i = 0; i < temp.size(); i += 2)
    {
        finalStates.insert(temp[i] - '0');
    }

    int currentState = initialState;

    vector< vector<int> > mat;
    for (int r = 0; getline(tt, temp); r++)
    {
        mat.resize(r + 1);
        for (int i = 0; i < temp.size(); i++)
        {
            if (temp[i] >= '0' && temp[i] <= '9')
                mat[r].push_back(temp[i] - '0');
            else if (temp[i] == '-')
            {
                mat[r].push_back(-1);
                i++;
            }
        }
    }

    int i = 0;
    while (i < input.size() && input[i] - 'a' < mat[0].size())
    {
        if (mat[currentState][input[i] - 'a'] == -1)
            break;
        currentState = mat[currentState][input[i] - 'a'];
        i++;
    }
    if (finalStates.count(currentState) && i == input.size())
        return true;
    else
        return false;
}
int main()
{
    string input;
    cout << "Enter Your String: ";
    cin >> input;

    if (isValidString("transitionTable.txt", input))
        cout << "Valid String!\n";
    else
        cout << "Invalid String!\n";

    return 0;
}