#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<unordered_map>
#include<unordered_set>

using namespace std ;

vector<string> split(string prod , string del){
    vector<string> parts ;
    string str ;
    size_t pos = 0 ;
    while(pos = prod.find(del) != string::npos){
        parts.push_back(prod.substr(0 , pos)) ;
        cout<<pos<<" "<<del.size()<<endl ;
        str = prod.erase(0 , pos + del.length()) ;
    }
    parts.push_back(str) ;
    return parts ;
}
int main(){
    fstream file ;
    file.open("input2.txt") ;
    string temp ;
    while(getline(file , temp)){
        cout<<temp<<endl ;
    }
    file.close() ;
    cout<<endl ;
    file.open("input2.txt") ;
    while(getline(file , temp)){
        vector<string> nter = split(temp ," -> ") ;
        cout<<nter[1]<<endl; 
        vector<string> prod = split(nter[1] , " | ") ;
        cout<<prod[0]<<endl ;
    }
}