#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

char eexit = 'x';

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
    cout<<endl;
    if(s[0] == '.') {
        eexit = '.';
        return;
    }
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

void delete_double(vector<pair<string,string>>& vec) {
    for(int i = 0; i < vec.size()-1; ++i) {
        string one{}, two{};
        for(auto elem : vec[i].first) if(elem != ' ' && elem != '\0' && elem != '\t') one.push_back(elem);
        for(auto elem : vec[i+1].first) if(elem != ' ' && elem != '\0' && elem != '\t') two.push_back(elem);
        if(one == two) vec.erase(vec.begin()+i+1);
    }
}

void clear_endl(vector<pair<string,string>>& vec) {
    for(int i = 0; i < vec.size(); ++i) {
        for(int j = vec[i].second.size()-1; j > 0 && vec[i].second[j] == '\n' && vec[i].second[j-1] == '\n'; --j) {
            vec[i].second.erase(vec[i].second.begin()+j);
            j = vec[i].second.size();
        }
    }
}

int main() {
    ifstream input("rubrica.txt");
    ofstream output("ordinata/rubrica_ordinata.txt");
    char sep;
    input>>sep;
    vector<pair<string, string>> rubrica;
    while(!input.eof()) {
        string s{}, s2{};
        getline(input, s);
        getline(input, s2, '-');
        rubrica.emplace_back(s,s2);
        for(int k = 1; k < rubrica[rubrica.size()-1].first.size(); ++k){
            if(rubrica[rubrica.size()-1].first[k-1] == ' ' &&
               rubrica[rubrica.size()-1].first[k] >= 'a' &&
               rubrica[rubrica.size()-1].first[k] <= 'z')
                rubrica[rubrica.size()-1].first[k] -= 32;
            else if(rubrica[rubrica.size()-1].first[k] >= 'A' && rubrica[rubrica.size()-1].first[k] <= 'Z')
                rubrica[rubrica.size()-1].first[k] += 32;
        }
        rubrica[rubrica.size()-1].first[0] >= 'a' &&
        rubrica[rubrica.size()-1].first[0] <= 'z' ? rubrica[rubrica.size()-1].first[0] -= 32 : 0;
    }
    sort(rubrica);
    delete_double(rubrica);
    input.close();
    clear_endl(rubrica);
    //funzione per formattazione qt
    for(auto i = 0; i < rubrica.size(); ++i) {
        for(auto k = 0; k < rubrica[i].first.size(); ++k) {
            if(rubrica[i].first[k] == ' ' && k > 2) {
                rubrica[i].first[k] = '\n';
                break;
            }
        }
        for(auto j = 0; j < rubrica[i].second.size(); ++j) {
            if(rubrica[i].second[j] == '\n') rubrica[i].second[j] = ' ';
        }
    }
    for(const auto& elem : rubrica)
        output<<elem.first<<endl<<endl<<endl<<endl<<endl<<elem.second<<endl;
    output.close();
    cout<<rubrica.size();
    while (eexit != '.') search(rubrica);
    return 0;
}
