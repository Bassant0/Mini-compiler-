#include <iostream>
using namespace std;
const int MAXIMUM = 5000000;
class Node {
	string id, scope, type;
	int LineNumber;
	Node* nextNode;
public:
	Node(string key, string value, string type, int LineNumber)
	{
		this->id = key;
		this->scope = value;
		this->type = type;
		this->LineNumber = LineNumber;
		nextNode = NULL;
	}
	~Node()
	{
	}
	void print()
	{
		cout << "Identifier's Name:" << id
			<< "\nType:" << type
			<< "\nScope: " << scope
			<< "\nLine Number: " << LineNumber << endl;
	}
	friend class SymbolTable;
};
class SymbolTable {//creating symbol table 
	Node* header[MAXIMUM];// creating array of pointer class node type 
public:
	SymbolTable()
	{
		for (int i = 0; i < MAXIMUM; i++)
			header[i] = NULL;// intializing the value of the adrress/key is null 
	}
	int hashf(string id);
	bool insertion(string id, string scope, string Type, int LineNumber);
	string lookup(string id);
	bool modify(string id, string scope, string Type, int LineNumber);
};
bool SymbolTable::modify(string id, string s, string t, int l)
{
	int index = hashf(id);
	Node* start = header[index];
	if (start == NULL)
		return "-1";
	while (start != NULL) {
		if (start->id == id) {
			start->scope = s;
			start->type = t;
			start->LineNumber = l;
			return true;
		}
		start = start->nextNode;//sequatinal checking like array checking 
	}
	return false;
}
string SymbolTable::lookup(string id)
{
	int index = hashf(id);
	Node* start = header[index];
	if (start == NULL)
		return "-1";
	while (start != NULL) {
		if (start->id == id) {
			start->print();
			return start->scope;
		}
		start = start->nextNode;
	}
	return "-1";
}

bool SymbolTable::insertion(string id, string scope,
	string Type, int LineNumber)
{
	int index = hashf(id);
	Node* insert = new Node(id, scope, Type, LineNumber);//dynamic alloaction as  im getting info from user
	if (header[index] == NULL) {//if it is empty 
		header[index] = insert;//then insert 
		cout << "\n"
			<< id << " insertion";
		return true;
	}
	else {
		Node* start = header[index];
		while (start->nextNode != NULL)//loop till you find space 
			start = start->nextNode;
		start->nextNode = insert;// once you find then hit 
		cout << "\n";
	}
}
int SymbolTable::hashf(string id)
{
	int asci = 0;
	for (int i = 0; i < id.length(); i++) {
		asci = asci + id[i];// loop and sum all the ascii and then mod it to hit its spicific palce in the table
	}
	return (asci % MAXIMUM);
}
int main()
{
	SymbolTable st;
	string check;
	cout << "* SYMBOL_TABLE *\n";
	if (st.insertion("if", "local", "keyword", 4))
		cout << " Done successfully";
	else
		cout << "\nFailed to insert\n";
	if (st.insertion("number", "global", "variable", 2))
		cout << " done successfully\n\n";
	else
		cout << "\nFailed to insert\n";
	check = st.lookup("if");
	if (check != "-1")
		cout << "Identifier Is present\n";
	else
		cout << "\nIdentifier Not Present\n";

	if (st.modify("number", "global", "variable", 3))
		cout << "\nNumber Identifier updated\n";
	check = st.lookup("number");
	if (check != "-1")
		cout << "Identifier Is present\n";
	else
		cout << "\nIdentifier Not Present";
	return 0;
}

