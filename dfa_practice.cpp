#include<iostream>
#include<bits/stdc++.h>
#include<vector>
#include<fstream>

using namespace std ;

void dfa(string input){

  ifstream file ;
  file.open("dfa_2.txt") ;

  if(file.is_open()){
    vector<int>final_state ;
    vector< vector<int> > dfa ;
    string temp ;

    getline(file , temp) ;
    int initialstate =  temp[0] - '0' ;
    getline(file , temp) ;

    for(int i=0 ; i<temp.size() ; i++){
        if(temp[i]>='0' && temp[i]<='9'){
        final_state.push_back(temp[i] - '0') ;
        }
    }
    // Getting the dfa
    for(int i=0 ; getline(file , temp) ; i++){
        vector<int> arr ;
        
        for(int j=0 ; j<temp.size() ; j++){
            if(temp[j]>='0' && temp[j]<='9'){
            arr.push_back(temp[j] - '0') ;
        }
         else if(temp[j]=='-'){
            arr.push_back(-1) ;
            j++ ;
        }
        }
       
        dfa.push_back(arr) ;
    }
    file.close() ;
    int curr_state = initialstate ;
    for (int i=0 ; i<input.size() ; i++){
        curr_state = dfa[curr_state][input[i]-'a'] ;
        if(curr_state == -1){
            break ;
        }
    }
    int c = 0 ;
    for(int i =0 ; i<final_state.size() ; i++){
    if(curr_state == final_state[i]){
        c++ ;
    }
    }
    if(c){
        cout<<"String Accepted"<<endl ;
    }
    else{
        cout<<"not Accepted"<<endl ;
    }
  }
}
int main()
{
    string input;
    cout<<"enter string  "<<"  ";
    getline(cin,input);
    dfa(input);
    
} 