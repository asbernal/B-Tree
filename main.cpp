#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "ArgumentManager.h"
#include "BTree.h"

using namespace std;

int getDegree(string &str);
void getLevels(vector<int>& vec, ifstream& _cmd);
void getData(vector<int>& vec, ifstream& _fin);


int main(int argc, char *argv[]){
    cout << "******************* Starting Program *******************" << endl;
    ArgumentManager am(argc, argv);
    string input = am.get("input");
    string command = am.get("command"); //CHECK WHEN DONE
    string output = am.get("output");
    ifstream fin(input);
    ifstream cmd(command); //CHECK WHEN DONE
    ofstream fout(output);

    // ifstream fin("input2.txt");
    // ifstream cmd("command2.txt");
    // ofstream fout("output2.txt");

    string line;
    getline(cmd, line);
    line.erase(remove(line.begin(), line.end(), '\n'), line.end());
    line.erase(remove(line.begin(), line.end(), '\r'), line.end());

    //Read first Command File line to get Degree for BTree
    int degree = getDegree(line);
    cout << "Degree is: " << degree << endl;

    //Read Command File, insert print levels in vector
    vector<int> level_to_print;
    getLevels(level_to_print, cmd);

    //Read data from input file, and check for duplicates
    vector<int> dataKeys;
    getData(dataKeys, fin);

    //created B-Tree class and assigned what degree to use
    BTree Btree(degree);
    for(int i = 0; i < dataKeys.size(); i++){
        Btree.insertData(dataKeys.at(i));
    }

    cout << endl;
    int treeHeight = Btree.getHeight(Btree.getRoot());
    cout << "Height=" << treeHeight << endl;
    fout << "Height=" << treeHeight << endl;

    //Print Level Order
    for(int i = 0; i < level_to_print.size(); i++){
        Btree.print_level_Order(Btree.getRoot(), level_to_print.at(i), treeHeight, fout);
        cout << endl;
        fout << endl;
    }
    //Btree.print_level_Order(Btree.getRoot(), 2);
    //cout << endl;
    fin.close();
    cmd.close();
    fout.close();
    cout << "******************* Ending Program *******************" << endl;
    return 0;
}

int getDegree(string &str){
    string num;
    for(int i = str.find("=")+1; i < str.length(); i++){
        //cout << str[i];
        num += str[i];
    }
    //cout << "EXIT" << endl;
    return stoi(num);
}
void getLevels(vector<int>& vec, ifstream& _cmd){
    //Read Command File, insert print levels in vector.
    string cmd_line;
    //string level;
    while(getline(_cmd, cmd_line)){
        cmd_line.erase(remove(cmd_line.begin(), cmd_line.end(), '\n'), cmd_line.end());
        cmd_line.erase(remove(cmd_line.begin(), cmd_line.end(), '\r'), cmd_line.end());
        string level;
        
        for(int i = cmd_line.find(" ") + 1; i < cmd_line.length(); i++){
            level += cmd_line[i];
        }

        //TEST!!!
        if(!level.empty()){
            vec.push_back(stoi(level));
        }
        //vec.push_back(stoi(level));
    }
}

void getData(vector<int>& vec, ifstream& _fin){
    cout << "Numbers to be inserted:\n\t";
    //int number;
    string line;
    while(getline(_fin, line)){
    //while(!_fin.eof()){
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());

        //string num;
        for(int i = 0; i < line.size(); i++){
            string num;
            bool isDuplicates = false;
            if(isdigit(line[i])){
                for(i; isdigit(line[i]); i++){
                    num += line[i];
                }
                
                for(int j = 0; j < vec.size(); j++){
                    if(vec.at(j) == stoi(num)){
                        isDuplicates = true;
                        break;
                    }
                }
                if(!isDuplicates){
                    cout << num << " ";
                    vec.push_back(stoi(num));
                }
                
            }
            //num = "";
        }
    }
    cout << endl << endl;
}