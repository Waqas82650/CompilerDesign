#include<iostream>
#include<bits/stdc++.h>
#include<vector>
#include<fstream>

using namespace std ;

void mealy(string input){

    ifstream file ;
    file.open("mealy.txt") ;

    string temp ;
    vector<int > final_state ;
    vector< vector<int> > table ;
    getline(file , temp ) ;
    int initialstate =  temp[0] - '0' ;
    getline(file , temp ) ;

    for(int i=0 ; i<temp.size() ; i++){
        if(temp[i]>='0' && temp[i]<='9'){
            final_state.push_back(temp[i] - '0') ;
        }
    }

    for(int i=0 ; getline(file , temp) ; i++){
        vector<int> arr ;
        for(int j =0 ; j<temp.size() ; j++){
            if(temp[j]>='0' && temp[j]<='9'){
                arr.push_back(temp[j] - '0') ;
            }
            else if(temp[j] == '-'){
                arr.push_back(-1) ;
                j++ ;
            }
        }
        table.push_back(arr) ;
    }
  file.close() ;

  int curr_state = initialstate ;
  string res = "" ;
  for(int i=0 ; i<input.size() ; i++){
  int col = input[i] - '0' ;

  if(col == 0){
     res += table[curr_state][col + 1] + '0' ;
     curr_state = table[curr_state][col] ;
  }
  if(col == 1){
     res += table[curr_state][col + 2] + '0' ;
     curr_state = table[curr_state][col + 1] ;
  }
  }
  cout<<" The result is "<< res << endl ;
}
int main(){

    cout<<"Enter the string for which you want to get output"<<endl ;
    string input ;
    getline(cin , input) ;
    mealy(input) ;
}