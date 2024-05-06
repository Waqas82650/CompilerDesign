#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
using namespace std;

void mealy(string inputstr)
{
    ifstream infile;
    infile.open("mealy.txt");
    string temp = "";

    if (infile.is_open())
    {
        getline(infile, temp);
        int initialState = temp[0] - '0'; // taking initial state

        vector<int> finalState; // storing final states
        getline(infile, temp);
        for (int i = 0; i < temp.size(); i++)
        {
            finalState.push_back(temp[i] - '0');
        }

        vector< vector<int> > matrix; // loading data into 2D matrix
        for (int i = 0; getline(infile, temp); i++)
        {
            vector<int> arr;
            for (int j = 0; j < temp.size(); j++)
            {
                if (temp[j] >= '0' && temp[j] <= '9')
                    arr.push_back(temp[j] - '0');
                else if (temp[i] == '-')
                {
                    arr.push_back(-1);
                    j++;
                }
            }
            matrix.push_back(arr);
        }
        infile.close();

        int i = 0;
        int currState = initialState;
        string output = "";
        while (i < inputstr.size())
        {
            int colm = inputstr[i] - '0';
            if (colm == 0)
            {
                output += matrix[currState][colm + 1] + '0';
                currState = matrix[currState][colm];
            }
            else if (colm == 1)
            {
                output += matrix[currState][colm + 2] + '0';
                currState = matrix[currState][colm + 1];
            }
            i++;
        }

        cout << output;
    }
    else
    {
        cerr << "Error: Unable to open file" << endl;
    }
}

int main()
{
    string inputstr;
    cout<<"Name: Suhel Khan"<<endl<<"Roll No: 21BCS025"<<endl ;
    cout << "Enter input string" << endl;
    cin >> inputstr;
    cout<<"The result is :"<<endl ;
    mealy(inputstr);
    return 0;
}