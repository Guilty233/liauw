#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
class Person {
public:
    int Oday;
    vector<string> vec;
    string rank;
    Person(int Oday, const vector<string>& vec, const string& rank)
        : Oday(Oday), vec(vec), rank(rank){}
};

unordered_map<string, Person> readdef()
{
    unordered_map<string, Person>out;
    string myText, com;
    int O = 2;
    int i;
    ifstream MyReadFile("def.txt");
    while (getline (MyReadFile, myText)) {
        stringstream ss(myText);
        vector<string> v;
        while (getline(ss, com, ' ')) {
            v.push_back(com);
        }
        for(i = 1; i < 8; ++i)
        {
            if(v[i] == "O")
            {
                --O;
            }
        }
        out.emplace(v[0], Person(O,{v[1],v[2],v[3],v[4],v[5],v[6],v[7]},v[8]));
    }
    MyReadFile.close();
    return out;

}
void write(unordered_map<string, Person> input)
{
    ofstream MyFile("result.txt");
    for(auto p : input)
    {
        MyFile << p.first << " ";
        for(auto & i : p.second.vec)
        {
            MyFile << i << " ";
        }
        MyFile << endl;
    }
    MyFile.close();
}
unordered_map<string, string> readref()
{
    unordered_map<string, string>out;
    string myText, com;
    ifstream MyReadFile("read.txt");
    while (getline (MyReadFile, myText)) {
        stringstream ss(myText);
        vector<string> v;
        while (getline(ss, com, ' ')) {
            v.push_back(com);
        }
        out.emplace(pair<string, string>(v[0],v[1]));
    }
    MyReadFile.close();
    return out;
}
map<string, vector<int>> count(unordered_map<string, Person> input)
{
    map<string, vector<int>> out;
    out.emplace("A", vector<int>{2,2,2,2,2,2,2});
    out.emplace("0930", vector<int>{1,1,1,1,1,1,1});
    out.emplace("P", vector<int>{4,4,4,4,4,4,4});
    out.emplace("1530", vector<int>{2,2,2,2,2,2,2});
    out.emplace("A/N", vector<int>{3,3,3,3,3,3,3});
    out.emplace("SenA", vector<int>{2,2,2,2,2,2,2});
    out.emplace("SenP", vector<int>{2,2,2,2,2,2,2});
    for(auto p : input)
    {
        for(int i = 0; i < 7; ++i)
        {
            if(out.find(p.second.vec[i]) != out.end())
            {
                out[p.second.vec[i]][i]--;
                if(p.second.rank == "Senior")
                {
                    if(p.second.vec[i] == "P"||p.second.vec[i] == "1530")
                    {
                        out["SenP"][i]--;
                    }
                    else
                    {
                        out["SenA"][i]--;
                    }
                }
            }
            else if(p.second.vec[i] == "O/N")
            {
                out["A"][i]++;
                out["A/N"][i]--;
            }
        }
    }
    return out;
}
vector<string> senlist(unordered_map<string, Person> input, vector<string> list)
{
    vector<string> vec;
    for(auto p : list)
    {
        if(input.find(p)->second.rank == "Senior")
        {
            vec.push_back(p);
        }
    }
    return vec;
}
vector<string> validlist(unordered_map<string, Person> input, int index)
{
    vector<string> vec;
    for(auto p : input)
    {
        if(p.second.vec[index] == "E")
        {
            vec.push_back(p.first);
        }
    }
    return vec;
}
void saveref(unordered_map<string, Person> input)
{
    ofstream MyFile("ref.txt");
    for(auto p : input)
    {
        MyFile << p.first << " ";
        MyFile << p.second.vec[6] << " ";
        MyFile << endl;
    }
    MyFile.close();
}



int main() {
    unordered_map<string, Person> personMap = readdef();
    unordered_map<string, string> ref = readref();
    map<string, vector<int>> list = count(personMap);
    /*for(int i = 0; i < 7; ++i)
    {
        vector <string> vl = validlist(personMap, i);
        vector <string> sl = senlist(personMap, vl);
        if(i == 0)
        {

        }
        else
        {

        }
    }*/
    
    
   
    //saveref(personMap);
    return 0;
}