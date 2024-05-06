#include<iostream>
#include<fstream>
#include<vector>
using namespace std;
void dfa(string input)
{
    ifstream file;
    file.open("dfa_2.txt");
   
    if(file.is_open())
    {
    string temp;
    vector<int>finalstate;
    vector< vector<int> >dfa;
        getline(file,temp);
        int initialstate=temp[0]-'0';
        getline(file,temp);
        for(int i=0;i<temp.size();i++)
        {
            if(temp[i]>='0'&& temp[i]<='9'){
                finalstate.push_back(temp[i]-'0');
            }
        }
        for(int i=0;getline(file,temp);i++)
        {
            vector<int>arr;
            for(int j=0;j<temp.size();j++)
            {
                if(temp[j]>='0' && temp[j]<='9')
                {
                    arr.push_back(temp[j]-'0');
                }
                else if(temp[j]=='-')
                {
                    arr.push_back(-1);
                    j++;
                }
            }
            dfa.push_back(arr);
        }
     file.close();
     int currentstate=initialstate;
     for(int i=0;i<input.size();i++)
     {
        currentstate=dfa[currentstate][input[i]-'a'];
        if(currentstate==-1)
        {
          
            break;
        }
     }
     int c=0;
     for(int i=0;i<finalstate.size();i++)
     {
        if(finalstate[i]==currentstate)
        c++;
     }
     if(c){
     cout<<"string accepted";
     }
     else{
     cout<<"string not accepted";
     }
    }
    else{
        cout<<"file not open";
    }
}
int main()
{   cout<<"Name : Suhel Khan"<<endl<<"Roll no: 21BCS025"<<endl ;
    string input;
    cout<<"Enter String : ";
    getline(cin,input);
    dfa(input);
    
} 
