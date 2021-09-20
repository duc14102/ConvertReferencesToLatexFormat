#include <iostream>
#include <string>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>
using namespace std;

const bool Abbreviation=true;

const bool Title=true;
const bool Author=true;
const bool Journal=true;
const bool Volume=true;
const bool Number=true;
const bool Pages=true;
const bool Year=true;
const bool Publisher=false;

typedef struct Article
{
    string cite;
    string tit;
    string aut;
    string jou;
    string vol;
    string num;
    string pag;
    string yea;
    string pub;
} article;

typedef struct Abbreviation
{
    string nameJournal;
    string AbbName;
} abbreviation;

int main()
{
    vector<Article> references;
    string line, token;
    int pos=0;
    Article ReferTemp;
    // READING FILE BibTeX.txt
    ifstream infile("BibTeX.txt");
    if (infile){
        while(getline(infile,line)){
            cout << line << endl;
            if(line[0]!='%'){
                if ((pos=line.find("{"))!=string::npos){
                    token = line.substr(0,pos);
                    if (token=="@article"){
                        references.resize(references.size()+1);
                        line.erase(0,pos+1);
                        line.erase(line.find(","),line.length());
                        references[references.size()-1].cite=line;
                        // cout << line << endl;
                    }
                    else if (token=="  title="){
                        line.erase(0,pos+1);
                        if(line[line.length()-2]==','){line.erase(line.length()-3,line.length());}
                        else{line.erase(line.length()-1,line.length());}
                        references[references.size()-1].tit=line;
                        // cout << line << endl;
                    }
                    else if (token=="  author="){
                        line.erase(0,pos+1);
                        if(line[line.length()-2]==','){line.erase(line.length()-3,line.length());}
                        else{line.erase(line.length()-1,line.length());}
                        references[references.size()-1].aut=line;
                        // cout << line << endl;
                    }
                    else if (token=="  journal="){
                        line.erase(0,pos+1);
                        if(line[line.length()-2]==','){line.erase(line.length()-3,line.length());}
                        else{line.erase(line.length()-1,line.length());}
                        references[references.size()-1].jou=line;
                        // cout << line << endl;
                    }
                    else if (token=="  volume="){
                        line.erase(0,pos+1);
                        if(line[line.length()-2]==','){line.erase(line.length()-3,line.length());}
                        else{line.erase(line.length()-1,line.length());}
                        references[references.size()-1].vol=line;
                        // cout << line << endl;
                    }
                    else if (token=="  number="){
                        line.erase(0,pos+1);
                        if(line[line.length()-2]==','){line.erase(line.length()-3,line.length());}
                        else{line.erase(line.length()-1,line.length());}
                        references[references.size()-1].num=line;
                        // cout << line << endl;
                    }
                    else if (token=="  pages="){
                        line.erase(0,pos+1);
                        if(line[line.length()-2]==','){line.erase(line.length()-3,line.length());}
                        else{line.erase(line.length()-1,line.length());}
                        references[references.size()-1].pag=line;
                        // cout << line << endl;
                    }
                    else if (token=="  year="){
                        line.erase(0,pos+1);
                        if(line[line.length()-2]==','){line.erase(line.length()-3,line.length());}
                        else{line.erase(line.length()-1,line.length());}
                        references[references.size()-1].yea=line;
                        // cout << line << endl;
                    }
                    else if (token=="  publisher="){
                        line.erase(0,pos+1);
                        if(line[line.length()-2]==','){line.erase(line.length()-3,line.length());}
                        else{line.erase(line.length()-1,line.length());}
                        references[references.size()-1].pub=line;
                        // cout << line << endl;
                    }
                }
            }
        };
        infile.close();
        cout << "Number of references: " << references.size() << endl;
    }

    if (Abbreviation){
        vector <abbreviation> AbbJournal;
        ifstream infile("Standard_Journal_Abbreviation_ISO4.csv");
        if (infile){
            while(getline(infile,line)){
                // cout << line << endl;
                if ((pos=line.find(";"))!=string::npos){
                    AbbJournal.resize(AbbJournal.size()+1);
                    AbbJournal[AbbJournal.size()-1].nameJournal = line.substr(0,pos);
                    line.erase(0,pos+2);
                    AbbJournal[AbbJournal.size()-1].AbbName = line;
                    cout << AbbJournal[AbbJournal.size()-1].nameJournal <<" --> "<< AbbJournal[AbbJournal.size()-1].AbbName << endl;
                }
            };
            infile.close();
        }
        infile.close();

        for (long unsigned int i = 0; i < references.size(); i++){
            for (long unsigned int j = 0; j < AbbJournal.size(); j++){
                if (references[i].jou==AbbJournal[j].nameJournal){
                    references[i].jou = AbbJournal[j].AbbName;
                    // break;
                }
            }
        }
    }
    

    ofstream outfile("references.bib");
    for (long unsigned int i = 0; i < references.size(); i++){
        outfile << "@article{" + references[i].cite + "," << endl;
        if(Title&&references[i].tit!=""){outfile << "\ttitle={" + references[i].tit + "}";}
        if(Author&&references[i].aut!=""){outfile << ",\n\tauthor={" + references[i].aut + "}";}
        if(Journal&&references[i].jou!=""){outfile << ",\n\tjournal={" + references[i].jou + "}";}
        if(Volume&&references[i].vol!=""){outfile << ",\n\tvolume={" + references[i].vol + "}";}
        if(Number&&references[i].num!=""){outfile << ",\n\tnumber={" + references[i].num + "}";}
        if(Pages&&references[i].pag!=""){outfile << ",\n\tpages={" + references[i].pag + "}";}
        if(Year&&references[i].yea!=""){outfile << ",\n\tyear={" + references[i].yea + "}";}
        if(Publisher&&references[i].pub!=""){outfile << ",\n\tpublisher={" + references[i].pub + "}" << endl;}
        outfile << "\n}" << endl;
    }
    outfile.close();

    return 0;
}
