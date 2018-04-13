#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <set>
#include <map>
#include <sstream>
#include <iostream>


using namespace std;


using line_no = vector<string>::size_type;

string make_plural(size_t ctr, const string &word,const string &ending)
{
	return (ctr > 1) ? word + ending : word;
}



class QueryResult
{
friend ostream& print(ostream& ,const QueryResult&);
public:

	QueryResult(string s,shared_ptr<set<line_no>> p,shared_ptr<vector<string>> f) : 
		sought(s),lines(p),file(f){}
private:
	string sought;
	shared_ptr<set<line_no>> lines;
	shared_ptr<vector<string>> file;

};


class TextQuery
{
public:
	
	TextQuery(ifstream& in);
	~TextQuery(){};
	
	QueryResult query(const string src) const;

private:
	shared_ptr<vector<string>> file;

	map<string,shared_ptr<set<line_no>>> wm; 

};



TextQuery::TextQuery ( ifstream& in) : file (new vector<string>){
	string text;
	while(getline(in,text)){
		file->push_back(text);
		int n = file->size() - 1;
		istringstream line(text);
		string word;
		while(line >> word){
			auto &lines = wm[word];
			if(!lines){
				lines.reset(new set<line_no>);
			}

			lines->insert(n);
		}
	}
}



QueryResult TextQuery::query (const string src) const {
	static shared_ptr<set<line_no>> nodata(new set<line_no>);
	auto loc = wm.find(src);
	if(loc == wm.end())
		return QueryResult(src,nodata,file);
	else
		return QueryResult(src,loc->second,file);
}





ostream& print(ostream& os,const QueryResult& qr){

	os << qr.sought << " occurs " << qr.lines->size() << " " << make_plural(qr.lines->size(), "time", "s") << endl;
	for (auto num : *qr.lines)
	{
		os << "\t(line " << num + 1 << ") "
				<< *(qr.file->begin() + num) << endl;
	}
	return os;
}




void runQueries(ifstream &inFile){
	TextQuery tq(inFile);

	while(true){
		cout << "enter word to look for, or 'q' to quit:" ;
		string s;
		if(!(cin >> s) || s == "q")
			break;

		print(cout,tq.query(s)) << endl;

	}

}




int main(int argc,char* argv[]){
	ifstream infile((char*)argv[1]);
	if(!infile.is_open()){
		cout << "open file " << argv[1] << " failed." << endl;
		return 1;
	}
	runQueries(infile);

	cout << "quit from query ok" << endl;
	return 0;
}
