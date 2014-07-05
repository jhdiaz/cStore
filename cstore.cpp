#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <queue>
using namespace std;

string parse(int, string);
int nextIndex(int, string);
void slowintersect(string fname, string outFile);
void slowunion(string fname, string outFile);
void fastintersect(string fname, string outFile);
void fastunion(string fname, string outFile);
bool binary_search(const vector<int>& sorted_vec, int key);

int main(){

	string go = "";
	string cmd = "";
	string fname = "";
	string outFile = "";
	ifstream ifs;
	bool fileOpen = false;
	cout<<"Enter a command (loaddb/slowintersect/fastintersect/slowunion/fastunion) or type 'exit' to quit the program."<<endl;
	while(getline(cin, go)){
		cmd = parse(0, go);

		if(cmd == "loaddb"){
			fname = parse(nextIndex(0, go), go);
			ifs.clear();
			ifs.close();
			if(fname == ""){
				cout<<"Please input a file name."<<endl;
			}
			else{
				ifs.open(fname.c_str());
				if(!ifs.fail()){
					cout<<"Successfully opened file."<<endl;
					fileOpen = true;
					ifs.close();
				}
				else{
					cerr<<"Could not open file."<<endl;
					ifs.clear();
					ifs.close();
					fileOpen = false;
				}
			}
		}
		else if(cmd == "slowintersect"){
			outFile = parse(nextIndex(0, go), go);	//Name of file we are outputting into.

			if(fileOpen){
				slowintersect(fname, outFile);
			}
			else{
				cerr<<"No file was found."<<endl;
			}
		}
		else if(cmd == "fastintersect"){
			outFile = parse(nextIndex(0, go), go);

			if(fileOpen){
				fastintersect(fname, outFile);
			}
			else{
				cerr<<"No file was found."<<endl;
			}
		}
		else if(cmd == "slowunion"){
			outFile = parse(nextIndex(0, go), go);

			if(fileOpen){
				slowunion(fname, outFile);
			}
			else{
				cerr<<"No file was found."<<endl;
			}
		}
		else if(cmd == "fastunion"){
			outFile = parse(nextIndex(0, go), go);

			if(fileOpen){
				fastunion(fname, outFile);
			}
			else{
				cerr<<"No file was found."<<endl;
			}
		}
		else if(cmd == "exit"){
			cout<<"You have chose to exit the program"<<endl;
			break;
		}
		else{
			cout<<"You have entered an invalid input."<<endl;
		}

	}	

}

string parse(int start, string a){
	string ret = "";
	for(int i=start;i<a.length();i++){
		if(ret.length() == 0){
			if(a[i] != ' ' && a[i] != '\t' && a[i] != '\n' && a[i] != '\v' && a[i] != '\f' && a[i] != '\0'
			&& a[i] != '\r'){
				ret += a[i];
			}
		}
		else{
			if(a[i] == ' ' || a[i] == '\t' || a[i] == '\n' || a[i] == '\v' || a[i] == '\f' || a[i] == '\0'
			|| a[i] == '\r'){
				break;
			}
			else{
				ret += a[i];
			}
		}
	}
	return ret;
}

int nextIndex(int start, string a){
	string ret = "";
	int index = start;
	for(int i=start;i<a.length();i++){
                if(ret.length() == 0){
                        if(a[i] != ' ' && a[i] != '\t' && a[i] != '\n' && a[i] != '\v' && a[i] != '\f' && a[i] != '\0'
			&& a[i] != '\r'){
				ret += a[i];
				index = i;
                        }
                }
                else{
                        if(a[i] == ' ' || a[i] == '\t' || a[i] == '\n' || a[i] == '\v' || a[i] == '\f' || a[i] == '\0'
			|| a[i] == '\r'){
                                return i;
                        }
                        else{
                                ret += a[i];
				index = i;
                        }
                }
        }
	return index +1;
}

void slowintersect(string fname, string outFile){

	ifstream ifs(fname.c_str());
	ofstream ofs(outFile.c_str());
	string line;
	vector< vector<int> > vec;
	string curString = "";
	int curInt;
	int next = 0;
	int count = 0;
	int spaces = 0;
	char* intPtr;
	int temp = 0;

	while(getline(ifs, line)){
		vec.push_back(vector<int>());

		next = 0;
		while(next < line.length()){

			curString = parse(next, line);
			next = nextIndex(next, line)+1;
			intPtr = &curString[0];
			curInt = atoi(intPtr);
			vec.back().push_back(curInt);
		}
	}

	for(int i = 0;i<vec.size();i++){
		for(int j = 0;j<vec[i].size();j++){
			for(int k = 0;k<vec[i].size()-1;k++){
				if(vec[i][k] > vec[i][k+1]){
					temp = vec[i][k];
					vec[i][k] = vec[i][k+1];
					vec[i][k+1] = temp;
				}
			}
		}
	}
	int key = 0;
	bool inSets = false;
	if(outFile == ""){
			for(int j = 0;j<vec[0].size();j++){
				key = vec[0][j];
				for(int k = 1;k<vec.size();k++){
					if(binary_search(vec[k], vec[0][j])){
						inSets = true;
					}
					else{
						inSets = false;
						break;
					}
				}
				if(inSets){
					cout<<key<<" ";
				}
			}
	}
	else{
	         for(int j = 0;j<vec[0].size();j++){
                                key = vec[0][j];
                                for(int k = 1;k<vec.size();k++){
                                        if(binary_search(vec[k], vec[0][j])){
                                                inSets = true;
                                        }
                                        else{
                                                inSets = false;
                                                break;
                                        }
                                }
                                if(inSets){
                                        ofs<<key<<" ";
                                }
                        }
		cout<<"File '"<<outFile<<"' has been created."<<endl;
		ofs.close();
	}
}

void slowunion(string fname, string outFile){

	ifstream ifs(fname.c_str());
	ofstream sOutFile;
        string line;
        vector< vector<int> > vec;
        string curString = "";
        int curInt;
        int next = 0;
        int count = 0;
        int spaces = 0;
        char* intPtr;
        int temp = 0;
	set<int> mySet;
	set<int>::iterator it;

        while(getline(ifs, line)){
                vec.push_back(vector<int>());

                next = 0;
                while(next < line.length()){

                        curString = parse(next, line);
                        next = nextIndex(next, line)+1;
                        intPtr = &curString[0];
                        curInt = atoi(intPtr);
                        vec.back().push_back(curInt);
                }
        }

        for(int i = 0;i<vec.size();i++){
                for(int j = 0;j<vec[i].size();j++){
                        for(int k = 0;k<vec[i].size()-1;k++){
                                if(vec[i][k] > vec[i][k+1]){
                                        temp = vec[i][k];
                                        vec[i][k] = vec[i][k+1];
                                        vec[i][k+1] = temp;
                                }
                        }
                }
	}

	for(int l = 0;l<vec.size();l++){
                for(int m = 0;m<vec[l].size();m++){
                        mySet.insert(vec[l][m]);
                }
        }




	if(outFile == ""){
		cout<<"Output to screen."<<endl;
		for(it = mySet.begin();it != mySet.end();it++){
			cout<<*it<<endl;
		}
	}
	else{
		sOutFile.open(outFile.c_str());
		for(it = mySet.begin();it != mySet.end();it++){
                        sOutFile<<*it<<" ";
                }
		sOutFile.close();
		cout<<"File '"<<outFile<<"' has been created."<<endl;
	}
}

void fastintersect(string fname, string outFile){

        ifstream ifs(fname.c_str());
        string line;
        vector< vector<int> > vec;
        string curString = "";
        int curInt;
        int next = 0;
        int count = 0;
        int spaces = 0;
        char* intPtr;
        int temp = 0;

        while(getline(ifs, line)){
                vec.push_back(vector<int>());

                next = 0;
                while(next < line.length()){

                        curString = parse(next, line);
                        next = nextIndex(next, line)+1;
                        intPtr = &curString[0];
                        curInt = atoi(intPtr);
                        vec.back().push_back(curInt);
                }
        }

      
       for(int i = 0;i<vec.size();i++){
                for(int j = 0;j<vec[i].size();j++){
                        for(int k = 0;k<vec[i].size()-1;k++){
                                if(vec[i][k] > vec[i][k+1]){
                                        temp = vec[i][k];
                                        vec[i][k] = vec[i][k+1];
                                        vec[i][k+1] = temp;
                                }
                        }
                }
      
        }


	if(outFile == ""){
		cout<<"Output to screen."<<endl;
	}
	else{
		cout<<"Output to file."<<endl;
	}

}

void fastunion(string fname, string outFile){

        ifstream ifs(fname.c_str());
	ofstream ofs(outFile.c_str());
        string line;
        vector< vector<int> > vec;
        string curString = "";
        int curInt;
        int next = 0;
        int count = 0;
        int spaces = 0;
        char* intPtr;
        int temp = 0;
	priority_queue<int, vector<int>, greater<int> > min_pq;

        while(getline(ifs, line)){
                vec.push_back(vector<int>());

                next = 0;
                while(next < line.length()){

                        curString = parse(next, line);
                        next = nextIndex(next, line)+1;
                        intPtr = &curString[0];
                        curInt = atoi(intPtr);
                        vec.back().push_back(curInt);
                }
        }
	for(int i = 0;i<vec.size();i++){
		for(int j = 0;j<vec[i].size();j++){
			for(int k = 0;k<vec[i].size()-1;k++){
				if(vec[i][k] > vec[i][k+1]){
					temp = vec[i][k];
					vec[i][k] = vec[i][k+1];
					vec[i][k+1] = temp;
				}
			}
		}
	}

	if(outFile == ""){
		int curMin = vec[0][0];
		int index = 0;
		cout<<"Output to screen."<<endl;
		for(int i = 0;i<vec.size();i++){
			min_pq.push(vec[i][0]);
			cout<<min_pq.top()<<" ";
			min_pq.pop();
			for(int j = 0;j<vec.size();j++){
				if(curMin > vec[i][j]){
					curMin = vec[i][j];
				}
			}
			
			
			
		}
	}
	else{
		cout<<"Output to file."<<endl;
	}
}

bool binary_search(const vector<int>& sorted_vec, int key){
        size_t mid, left = 0;
        size_t right = sorted_vec.size();
        while(left<right){
                mid = left + (right - left)/2;
                if(key>sorted_vec[mid]){
                        left = mid+1;
                }
                else if(key<sorted_vec[mid]){
                        right = mid;
                }
                else{
                        return true;
                }
        }
        return false;
}
