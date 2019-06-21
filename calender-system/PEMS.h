#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <sstream>
using namespace std;

class file{
	public:
	    int numSearch = 1 ;
		void AddFile(char *filename,string content){
			ofstream outfile;
   			outfile.open(filename, ios::app);
			if(!outfile){
				cout << "CreateFile: Cannot open the file.";
			} else {
                    outfile << content << endl;
                    outfile.close();
			}
		}

		int CountLines(char *filename){
		    ifstream ReadFile;
		    int n=0;
		    string tmp;
		    ReadFile.open(filename,ios::in);
		    if(ReadFile.fail()){
		        return n;
		    } else {
		        while(getline(ReadFile,tmp,'\n')){
		            n++;
		        }
		        ReadFile.close();
		        return n;
    		}
		}
		string ReadLine(char *filename,int line){
		    int lines,i=0;
		    string temp;
		    fstream file;
		    file.open(filename,ios::in);
		    lines=CountLines(filename);

		    if(line<=0){
		        cout << "ReadLine: The line in txt is less than 0.";
		    } else if(file.fail()){
		    	cout << "ReadLine: The txt file is not exist.";
			} else if(line>lines){
				cout << "ReadLine: The line is exceed the max lenth of line in txt file.";
			} else {
				// No error
			}
		    while(getline(file,temp)&&i<line-1){
		        i++;
		    }
		    file.close();
		    return temp;
		}
		int *searchFile(char *filename, string content){
            ifstream fileInput;
            int offset;
            string line;
            string aSearch = content;
            fileInput.open(filename);
            unsigned int curLine = 0;
            int *dataArray = new int[10];

            if(fileInput.is_open()) {
                while(getline(fileInput, line)) {
                    curLine++;
                    if (line.find(aSearch, 0) != string::npos) {
                        dataArray[0] = 1;
                        //cout << "found: " << aSearch << " line: " << curLine << endl;
                        dataArray[numSearch] = curLine;
                        numSearch++;
                    }
                }
                if(numSearch==0){
                    dataArray[0] = 0;
                }else{
                    dataArray[0] = numSearch-1;
                }
                numSearch--;
                fileInput.close();
            }else if(fileInput.fail()){
                dataArray[0] = 0;
            }
            return dataArray;
	    }
	    //Modidy or Delete Data
	    int ModOrDelData(char *filename, int n, string content){
            fstream file(filename);
            string line;
            int countt = 0;
            int icount = 0;
            ofstream outfile("in2.txt",ios::out|ios::trunc);
            countt = CountLines(filename)-1;
            //cout << countt<< endl;
            while(!file.eof())
            {
                getline(file,line);
                if(icount!=n-1){
                    if(icount!=countt){
                        outfile << line << endl;
                    } else {
                        outfile << line;
                    }
                }else if(content!="||Delete||"){
                    if(icount!=countt){
                        outfile << content << endl;
                    } else {
                        outfile << content;
                    }
                }
                icount++;
            }
            outfile.close();
            file.close();
            ofstream outfile1(filename,ios::out|ios::trunc);
            fstream file1("in2.txt");
            int tcount=0;
            while(!file1.eof())
            {
                getline(file1,line);
                if(tcount!=countt){
                    outfile1 << line << endl;
                } else {
                    outfile1 << line;
                }
                tcount++;
            }
            outfile1.close();
            file1.close();
            system("del in2.txt");

	    }
};
