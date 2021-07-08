#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>

using namespace std;


void sort(vector<pair<string, string>>& vec) {
    vector<pair<string, string>> aux(1);
    int index;
    for(int i = 0; i < vec.size() - 1; ++i) {
        aux[0] = vec[i];
        index = i;
        for(int j = i + 1; j < vec.size(); ++j) {
            if(vec[j].first <= aux[0].first) {
                aux[0] = vec[j];
                index = j;
            }
        }
        vec[index] = vec[i];
        vec[i] = aux[0];
    }
}

void search(vector<pair<string,string>>& vec) {
    cout<<"inserisci cognome o iniziali di esso: "<<endl;
    string s;
    cin>>s;
    stringstream ss(s);
    ss>>s;
    for(char& elem : s)
        if(elem >= 'A' && elem <= 'Z') elem += 32;
    s[0] -= 32;
    for(int i = 0; i < vec.size() && vec[i].first[0] <= s[0]; ++i) {
        if(s[0] == vec[i].first[0]) {
            int j = 1;
            bool gg = true;
            while(gg && j < vec[i].first.size() && j < s.size()) {
                s[j] != vec[i].first[j] ? gg = false : 0;
                ++j;
            }
            if(gg) cout<<vec[i].first<<endl<<vec[i].second<<endl<<endl;
        }
    }
}

int main() {
    setbuf(stdout, NULL);
    ifstream input("rubrica.txt");
    ofstream output("ordinata/rubrica_ordinata.txt");
    char sep;
    char exit = 'x';
    input>>sep;
    vector<pair<string, string>> rubrica;
    while(!input.eof()) {
        string s{}, s2{};
        getline(input, s);
        getline(input, s2, '-');
        rubrica.emplace_back(s,s2);
        for(auto& elem : rubrica[rubrica.size()-1].first)
            elem >= 'A' && elem <= 'Z' ? elem += 32 : 0;
        rubrica[rubrica.size()-1].first[0] -= 32;
    }
    sort(rubrica);
    input.close();
    for(const auto& elem : rubrica)
        output<<'-'<<elem.first<<endl<<elem.second<<endl;
    output.close();
    while (1) search(rubrica);
    return 0;
}
