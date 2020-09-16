#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <tuple>

using namespace std;

int main(int argc, char *argv[]) {
    
    ifstream infile(argv[1]);
    
    int start_state;
    vector<int> accept_state;
    vector<int> reject_state;
    
    vector<tuple<int, char, int, char, char>> transitions[1001];
    
    string line;
    
    string s1;
    string s2;
    string s3;
    string s4;
    string s5;
    string s6;
    
    tuple<int, char, int, char, char> transition;
    
    while(getline(infile, line)){
        stringstream ss(line);
        
        ss >> s1;
        
        if(s1 == "state"){
            ss >> s2 >> s3;
                if(s3 == "start"){
                    start_state = stoi(s2);
                }
                else if(s3 == "accept"){
                    accept_state.push_back(stoi(s2));
                }
                else{
                    reject_state.push_back(stoi(s2));
                }
        }
        else{
            
            ss >> s2 >> s3 >> s4 >> s5 >> s6;
            
            get<0>(transition) = stoi(s2);
            get<1>(transition) = s3[0];
            get<2>(transition) = stoi(s4);
            get<3>(transition) = s5[0];
            get<4>(transition) = s6[0];
            
            transitions[stoi(s2)].push_back(transition);
        }
    }
    
    string word = argv[2];
    int max_transitions = stoi(argv[3]);
    int word_index = 0;
    
    int num_transitions = 0;
    int current_state = start_state;
    
    vector<int> path_taken;
    
    bool accept = false;
    bool reject = false;
    bool quit = false;
    
    while(true){
        
        for(int i = 0; i < accept_state.size(); i++){
            if(current_state == accept_state[i]){
                accept = true;
                break;
            }
        }
        for(int i = 0; i < reject_state.size(); i++){
            if(current_state == reject_state[i]){
                reject = true;
                break;
            }
        }
        if(num_transitions >= max_transitions){
            quit = true;
            break;
        }
        
        if(reject || accept == true) break;
        
        for(int i = 0; i < transitions[current_state].size(); i++){
            if(get<1>(transitions[current_state][i]) == word[word_index]){
                
                word[word_index] = get<3>(transitions[current_state][i]);
                if(get<4>(transitions[current_state][i]) == 'R'){
                    word_index = word_index + 1;
                }
                else{
                    word_index = word_index - 1;
                }
                
                path_taken.push_back(current_state);
                
                current_state = get<2>(transitions[current_state][i]);
                
                break;
            }
        }
        
        num_transitions++;
    }
    
    path_taken.push_back(current_state);
    
    for(int i = 0; i < path_taken.size()-1; i++){
        cout << path_taken[i] << "->";
    }
    cout << path_taken[path_taken.size()-1] << " ";
    
    if(accept == true){
        cout << "accept" << endl;
    }
    else if(reject == true){
        cout << "reject" << endl;
    }
    else{
        cout << "quit" << endl;
    }
    
    return 0;
}