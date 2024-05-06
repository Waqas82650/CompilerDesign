#include<iostream>
#include<vector>
#include<unordered_set>
#include<string>
#include<fstream>
using namespace std;
void mooreMachine(string file, string input)
{
    ifstream tt(file);

    // Taking Initial State
    string temp("");
    getline(tt, temp);
    int initialState = temp[0] - '0';

    int currentState = initialState;

    // Taking Transition Table
    vector< vector<int> > mat;
    for(int r=0; getline(tt, temp); r++)
    {
        mat.resize(r+1);
        for(int i=0; i<temp.size(); i++)
        {
            if(temp[i]>='0' && temp[i] <= '9') mat[r].push_back(temp[i]-'0');
            else if(temp[i] == '-')
            {
                mat[r].push_back(-1);
                i++;
            }
            else if(temp[i]>='a' && temp[i] <= 'z') 
            mat[r].push_back(temp[i]); // Taking the ASCII value of the output in the mat
        }
    }

    // Producing Output
    vector<char> rslt;
    int i=0;
    rslt.push_back(mat[currentState][mat[0].size()-1]);
    while(i<input.size())
    {
        if(input[i]-'a' < mat[0].size()-1)
        {
            currentState = mat[currentState][input[i]-'a'];
            if(currentState == -1)
            {
                cout<<"\n***Invalid Input!\n";
                return;
            }
            rslt.push_back(mat[currentState][mat[0].size()-1]);
        }
        else
        {
            cout<<"\n***Invalid Input!\n";
            return;
        }
        i++;
    }
    cout<<"Output: ";
    for(char ele: rslt) cout<<ele;
    cout<<endl;

}
int main()
{
    string input;
    cout<<"Enter Your String: ";
    cin>>input;

    mooreMachine("file.txt", input);

    return 0;
}