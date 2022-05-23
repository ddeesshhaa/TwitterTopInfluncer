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
map<string ,int> mp2; //for followings
vector<pair<int,string>> v; //top influnce for sorting
set<string> s; //get id from file
map<string,int> mutual; //count mutual friends of id
vector<pair<int,string>> mutuf; //sort mutual friend
map<string,vector<string>> graph; //show following state
//threshold maximum mutual friends between followers

int main() {
    ifstream data("data.csv");
    string text, temp = "";
    while (getline(data, text)) {
        s.insert(text);
    }
    for (auto it: s) {
        string temp, temp2;
        bool x = false;
        for (auto it2: it) {
            if (it2 == ',') {
                x = true;
                continue;
            }
            if (x == false) {
                temp.push_back(it2);
            } else {
                temp2.push_back(it2);
            }
        }
        mp[temp2]++;
        graph[temp].push_back(temp2);
    }
    for (auto &x: mp) { // n
        v.push_back(make_pair(x.second, x.first));
    }
    sort(v.rbegin(), v.rend());  //n log n
    for (int i = 0; i < 2; i++) {
        cout << "USER: " << v[i].second << " Has :" << v[i].first << " Followers" << endl;
    }
    string x;
    cout << "ENTER USERID : ";
    cin >> x;
    for (int a = 0; a < graph[x].size(); a++) {
        mp2[graph[x][a]] = 1;
    }
    for (int a = 0; a < graph[x].size(); a++) {
        for (int k = 0; k < graph[graph[x][a]].size(); k++) {
            if (!mp2[graph[graph[x][a]][k]] && graph[graph[x][a]][k] != x) {
                mutual[graph[graph[x][a]][k]]++;
            }
        }
    }
    for (auto &x: mutual) {
        mutuf.push_back(make_pair(x.second, x.first));
    }
    sort(mutuf.rbegin(), mutuf.rend());

    if (mutuf.size() == 0) {
        cout<<"HERE IS TOP INFLUNCERS:"<<endl;
        for (int i = 0; i < 10; i++) {
            if (v[i].second != x) {

                cout << "USER: " << v[i].second << endl;
            }
        }
    } else{
        for (int i = 0; i < mutuf.size(); i++) {
            if (mutuf[i].second != x) {
                cout << "USER: " << mutuf[i].second << " Has :" << mutuf[i].first << " Mutual Friends" << endl;
            } else {
            }
        }

    return 0;
}
