#include <iostream>
#include <bits/stdc++.h>
#include <cmath>
#include <chrono>
#include <string>
using namespace std;
using namespace std::chrono;

unordered_map<string,int> mp;   // count followers
unordered_map<string ,int> mp2; //for followings
vector<pair<int,string>> v; //top influncer for sorting
set<string> s; //get id from file
unordered_map<string,int> mutual; //count mutual friends of id
vector<pair<int,string>> mutuf; //sort mutual friend
unordered_map<string,vector<string>> graph; //show following state
//threshold maximum mutual friends between followers
auto start(){
    auto start = high_resolution_clock::now();
        return(start);
}
auto stop(auto y){
        auto start = y;
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<seconds>(stop-start);
        return (duration.count());
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    auto l=start();
    ifstream data("twitter.csv");
    string text;
    while (getline(data, text)) {//o(nlog(n)) where n total lines
        s.insert(text);
    }
    for (auto it: s) { //o(e) where e total edges
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
    for (auto &x: mp) { // e
        v.push_back(make_pair(x.second, x.first));
    }
    sort(v.rbegin(), v.rend());  //e log e
    cout<<"1st question "<<stop(l)<<endl;

    for (int i = 0; i < 2; i++) {
        cout << "USER: " << v[i].second << " Has :" << v[i].first << " Followers" << endl;
    }

    cout << "ENTER USERID : "<<endl;
    string x;

    cin >> x;
    auto m=start();
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

        cout<<"2st question after sorting only "<<stop(m)<<endl;
    if (mutuf.size() == 0) {

        cout<<"HERE IS TOP INFLUNCERS:"<<endl;
        for (int i = 0; i < 10; i++) {
            if (v[i].second != x) {

                cout << "USER: " << v[i].second << endl;
            }
        }

    } else {



        int l;
        cout<<"ENTER NUMBER OF USERS"<<endl;
        cin>>l;
        if(l>mutuf.size())l=mutuf.size();
        for (int i = 0; i < l; i++) {
            if (mutuf[i].second != x) {
                cout << "USER: " << mutuf[i].second << " Has :" << mutuf[i].first << " Mutual Friends" << endl;
            }
        }
    }
        cout<<"2st question after printing "<<stop(m)<<endl;
        cout<<"total time "<<stop(l)<<endl;

    //cout << "for bonus "<<(a-st)/CLOCKS_PER_SEC<<endl;
    return 0;
}
