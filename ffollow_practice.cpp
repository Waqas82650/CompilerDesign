#include<iostream>
#include<fstream>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<bits/stdc++.h>
using namespace std ;

void nfatodfa(){
   ifstream file ;
   file.open("first_follow.txt") ;
   unordered_map<int , unordered_set<int> > firsts ;
   unordered_map<int , unordered_set<int> > follow ;

   vector < vector <int> > grammar ;
   string temp = "" ;
   getline(file , temp) ;
   int startsy = temp[0] ;

   while(getline(file , temp)){
     vector<int> arr ;
     arr.push_back(temp[0]) ;

     int i=2 ;
     while(i<temp.size()){
        arr.push_back(temp[i]) ;
        i++ ;
     }

     grammar.push_back(arr) ;
   }
   cout<<startsy ;
   file.close() ;

   // Calculating First
   bool iterate = true ;
   while(iterate){
    iterate = false ;
     for(int i=0 ; i<grammar.size() ; i++){
        bool epsilonfound = true ; // when epsilon is found
        for(int j=1 ; j<grammar[i].size() && epsilonfound ; j++){
            epsilonfound = false ;
            int initiasize=  firsts[grammar[i][0]].size() ;
            if(grammar[i][j]>='A' &&  grammar[i][j]<='Z'){
               for(int ele : firsts[grammar[i][j]]){
                   firsts[grammar[i][0]].insert(ele) ;
                   if(ele = '.'){
                    epsilonfound=true ;
                   }
               }
            }
            else{
                firsts[grammar[i][0]].insert(grammar[i][j]) ;
            }
            if(firsts[grammar[i][0]].size() != initiasize){
                iterate = true ;
            }
        }
     }
   }

   // Calculating follow
}
int main(){
    nfatodfa() ;
}
