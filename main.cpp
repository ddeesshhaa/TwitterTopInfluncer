#include <iostream>
#include <bits/stdc++.h>
#include <cmath>
#include <string>
#include <fstream>
using namespace std;
#define ll  long long
#define ull unsigned long long
#define fl(i,k) for(int i=0 ;i<k; i++)
#define fle(i,k) for(int i=0 ;i<k; i++)
#define sz(c) (int)(c).size()
#define print( a) cout << a << '\n'

map<string,int> mp;   // count followers
vector<pair<int,string>> v; //top influnce for sorting
vector<string> s; //get id from file
map<string,int> mutual; //count mutual friends of id
vector<pair<int,string>> mutuf; //sort mutual friend
map<string,vector<string>> graph; //show following state
//threshold maximum mutual friends between followers

int main()
{
    ifstream  data("data.txt");
    string text,temp="";
    while(getline(data, text))
    {
      s.push_back(text);
    }
    for(auto it: s)
    {
        string temp,temp2;
        bool x=false;
        for(auto it2: it)
        {
            if(it2==',')
            {
                x=true;
                continue;
            }
            if(x==false){
                temp.push_back(it2);
            }else
            {
                temp2.push_back(it2);
            }
        }
        mp[temp2]++;
        graph[temp].push_back(temp2);
    }
    for(auto& x: mp) {
        v.push_back(make_pair(x.second,x.first));
    }
    sort(v.rbegin(), v.rend());
    for (int i = 0; i < 10 ; i++) {
        cout<<"USER: "<<v[i].second<<" Has :"<<v[i].first<<" Followers"<<endl;
    }
    string x;
    cout<<"ENTER USERID : ";
    cin>>x;
    for(int a=0;a<graph[x].size();a++)
    {
        for(int k=0;k<graph[graph[x][a]].size();k++)
        {
            if(find (graph[x].begin(), graph[x].end(), graph[graph[x][a]][k]) != graph[x].end())
            {
                mutual[graph[graph[x][a]][k]]++;
            }
        }
    }
    for(auto& x: mutual) {
        mutuf.push_back(make_pair(x.second,x.first));
    }
sort(mutuf.rbegin(), mutuf.rend());

    for (int i = 0; i <mutuf.size()  ; i++) {
        cout<<"USER: "<<mutuf[i].second<<" Has :"<<mutuf[i].first<<" Mutual Friends"<<endl;
    }
    return 0;
}
