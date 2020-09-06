#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cstring>
using namespace std;
class Person
{
public:	
	Person(); // default constructor
	Person(string n); 
	Person(string n, string pn); 
	friend bool operator< (Person, Person);
	friend bool operator> (Person, Person);
	friend bool operator==(Person, Person);
	Person operator=(Person);
	string fname;
	string lname;
	string phone;
};

// PhoneBook class 
class PhoneBook
{
private:
	struct tree_node
	{
		tree_node* left_pointer;
		tree_node* right_pointer;
		Person data;
		void printnode();
		void storenode();
	};
	tree_node* root;
public:
	PhoneBook()
	{
		root = NULL;
	}
	bool isEmpty() const { return root==NULL; }
	void load(const string& fname);
	void store(const string& fname);
	void find(Person d);
	void print_inorder();
	void store_inorder();
	void clear();
	void inorder(tree_node*);
	void store_inorder2(tree_node*);
	void insert(Person);
	void remove(Person);
	void edit(Person d);
};
Person::Person(string n, string ph)
{
	char* cstr = new char[n.size()+1];
	strcpy(cstr,n.c_str());
	fname.assign(strtok(cstr," "));
	lname.assign(strtok(NULL," "));
	phone = ph;
}
Person::Person(string n)
{
	char* cstr = new char[n.size()+1];
	strcpy(cstr,n.c_str());
	fname.assign(strtok(cstr," "));
	lname.assign(strtok(NULL," "));
}
Person::Person()
{
	// Nothing happens when no parameters are entered into the Person constructor
}
bool operator< (Person p1, Person p2)
{
	if(p1.lname == p2.lname)
		return p1.fname < p2.fname;
	else
		return p1.lname < p2.lname;
} 
bool operator> (Person p1,Person p2)
{
	if(p1.lname == p2.lname)
		return p1.fname > p2.fname;
	else
	return p1.lname > p2.lname;
} 
bool operator==(Person p1,Person p2)
{
	if( p1.fname == p2.fname && p1.lname == p2.lname && p1.phone == p2.phone )
		return true;
	else
		return false;
}  
Person Person::operator=(Person p1)
{
	fname = p1.fname;
	lname = p1.lname;
	phone = p1.phone;
	return *this;
} 

// PhoneBook Functions
void PhoneBook::insert(Person d)
{
	tree_node* t = new tree_node;
	tree_node* parent;
	t->data = d;
	t->left_pointer = NULL;
	t->right_pointer = NULL;
	parent = NULL;
	if(isEmpty()) root = t;
	else	
	{
		tree_node* current_node;
		current_node = root;
		while(current_node)
		{
			parent = current_node;
			if(t->data > current_node->data) 
				current_node = current_node->right_pointer; 
			else 
				current_node = current_node->left_pointer; 
		}
		if(t->data < parent->data) 
			parent->left_pointer = t;
		else
			parent->right_pointer = t;
	}
} 
void PhoneBook::remove(Person d)
{
	bool found = false;
	if(isEmpty())	
	{
		cout<<" Tree has no nodes, empty tree. "<<endl;
		return;
	}
	tree_node* current_node;
	tree_node* parent;
	current_node = root;
	while(current_node != NULL)	
	{
		if(current_node->data.fname == d.fname && current_node->data.lname == d.lname )	
		{
			found = true;
			break;
		}
		else	
		{
			parent = current_node;
			if(d > current_node->data) 
				current_node = current_node->right_pointer;
			else current_node = current_node->left_pointer;
		}
	}
	if(!found)
	{
		cout<<" Cannot find any data! "<<endl;
		return;
	}
	if((current_node->left_pointer == NULL && current_node->right_pointer != NULL)|| (current_node->left_pointer != NULL&& current_node->right_pointer == NULL)){
		if(current_node->left_pointer == NULL && current_node->right_pointer != NULL) 
		{ 
			if(current_node == root)
			{ 
				root = current_node->right_pointer;
				delete current_node;
				return;
			}
			if(parent->left_pointer == current_node)	
			{
				parent->left_pointer = current_node->right_pointer;
				delete current_node;
			}
			else 
			{
				parent->right_pointer = current_node->right_pointer;
				delete current_node;
			}
		}
		else 
		{
			if(current_node == root)
			{ 
				root = current_node->left_pointer;
				delete current_node;
				return;
			}
			if(parent->left_pointer == current_node)
			{
				parent->left_pointer = current_node->left_pointer;
				delete current_node;
			}
			else
			{
				parent->right_pointer = current_node->left_pointer;
				delete current_node;
			}
		}
		return;
	}
	if( current_node->left_pointer == NULL && current_node->right_pointer == NULL)
	{
		if(current_node == root)
		{
			root = NULL;
			return;
		} 
		if(parent->left_pointer == current_node) 
			parent->left_pointer = NULL;
		else 
			parent->right_pointer = NULL;
		delete current_node;
		return;
	}
	if (current_node->left_pointer != NULL && current_node->right_pointer != NULL)
	{
		tree_node* chkr;
		chkr = current_node->right_pointer;
		if((chkr->left_pointer == NULL) && (chkr->right_pointer == NULL))	
		{
			current_node = chkr;
			delete chkr;
			current_node->right_pointer = NULL;
		}
		else 
		{
			if((current_node->right_pointer)->left_pointer != NULL)
			{
				tree_node* lcurrent_node;
				tree_node* lcurrent_nodep;
				lcurrent_nodep = current_node->right_pointer;
				lcurrent_node = (current_node->right_pointer)->left_pointer;
				while(lcurrent_node->left_pointer != NULL)
				{
					lcurrent_nodep = lcurrent_node;
					lcurrent_node = lcurrent_node->left_pointer;
				} 			
				current_node->data = lcurrent_node->data;
				delete lcurrent_node;
				lcurrent_nodep->left_pointer = NULL;
			} 
			else	
			{
				tree_node* tmp;
				tmp = current_node->right_pointer;
				current_node->data = tmp->data;
				current_node->right_pointer = tmp->right_pointer;
				delete tmp;
			} 
		} 
		return;
	} 
} 
void PhoneBook::print_inorder()
{
	inorder(root);  
}
void PhoneBook::inorder(tree_node* p)
{ 
	if(p != NULL)
	{
		if(p->left_pointer) inorder(p->left_pointer);
		p->printnode();
		if(p->right_pointer) inorder(p->right_pointer);
	}
	else 
		return; 
}
void PhoneBook::find(Person d)
{
	
	bool found = false;
	if(isEmpty()) {
		cout<<" Tree has no nodes, empty tree. "<<endl;
		return;
	}
	tree_node* current_node;
	tree_node* parent;
	current_node = root;
	while(current_node != NULL)	
	{
		if(current_node->data.fname == d.fname && current_node->data.lname == d.lname )	
		{
			found = true;
			current_node->storenode();
			break;
		}
		else	
		{
			parent = current_node;
			if(d > current_node->data) 
				current_node = current_node->right_pointer;
			else current_node = current_node->left_pointer;
		}
	}
	if(!found)
	{
		cout<<" Cannot find any data! "<<endl;
		return;
	}
} 
void PhoneBook::clear()
{
	root = NULL; 
}
void PhoneBook::tree_node::printnode()
{
	cout << left << setw(12) << data.fname << " ";
	cout << left << setw(12) << data.lname << " | " ;
	cout << left << setw(12) << data.phone;
	cout << endl;
}
void PhoneBook::store_inorder()
{
	store_inorder2(root);
}
void PhoneBook::store_inorder2(tree_node* p)
{
	if (p != NULL)
	{
		if (p->left_pointer) store_inorder2(p->left_pointer);
		p->storenode();
		if (p->right_pointer) store_inorder2(p->right_pointer);
	}
	else
	{
		return;
	}
}
void PhoneBook::tree_node::storenode() 
{
	cout << data.fname + " " + data.lname + " - " + data.phone;
	cout << "\n";
}
void PhoneBook::load(const string& fname) 
{
	ifstream in( fname.c_str() );
	string n,p;
	
	if ( in.is_open() ) 
	{
		while (!in.eof())
		{ 
			getline(in,n); 
			if(n.empty())
			{ 
				break;
			}
			char* cstr = new char[n.size()+1]; 
			strcpy(cstr,n.c_str()); 
			n.clear(); 
			n.assign(strtok(cstr,"-")); 
			p.assign(strtok(NULL," \n")); 
			Person pers(n,p); 
			insert(pers); 
		}
		in.close(); 
		if(!in.is_open())
		{
			cout << "Finished Loading File!\n";
		}
		else
		{
			cout << "Error Closing File!\n";
		}
	}
	else
	{
		cout << "Error opening file!\n";
	}
}
void PhoneBook::store(const string& fname) 
{
  ofstream out(fname.c_str());
  if (out.is_open()) 
  {
	  cout << "Opening for writing...\n";
  }
  else 
  {
	  cout << "Error opening file!\n";
  }
	  streambuf* sbuf = cout.rdbuf();
	  cout.rdbuf(out.rdbuf());
	  store_inorder();
	  
	  cout.rdbuf(sbuf);
	  cout << "Finished writing!\n";
	  out.close();
	  if(!out.is_open())
	  {
		  cout << "File Closed!\n";
		  return;
	  }
	  else
	  {
		  cout<<"Error Closing file!";
	  }
}
void PhoneBook::edit(Person d)
{
	bool found = false;
	if(isEmpty()) 
	{
		cout<<" This Tree is empty! "<<endl;
		return;
	}
	tree_node* current_node;
	tree_node* parent;
	current_node = root;
	while(current_node != NULL)	
	{
		if(current_node->data.fname == d.fname && current_node->data.lname == d.lname )	
		{
			found = true;
			current_node->data.phone = d.phone;
			current_node->storenode();
			break;
		}
		else	
		{
			parent = current_node;		
			if(d > current_node->data) 
				current_node = current_node->right_pointer;
			else current_node = current_node->left_pointer;
		}
	}
	if(!found)
	{
		cout<<" Data not found! "<<endl;
		return;
	}
}

// User Interface 
class UserInterface 
{
public:
	PhoneBook phonebook;
	UserInterface(); // default constructor
	string n, p;
	void create();
	void delete_name(); 
	void edit();
	void search();
	void display();
	void store();
	void menu();
};
UserInterface::UserInterface()
{
	phonebook.load("contact_info.txt");
}
void UserInterface::menu() 
{
	int choice;
	bool quit = false;
	while (!quit) 
	{
		std::cout << "1: Create a New Contact  " << endl;
		std::cout << "2: Search for a Contact  " << endl;
		std::cout << "3: Delete a Contact  " << endl;
		std::cout << "4: Edit a Contact  " << endl;
		std::cout << "5: Display all Contacts  " << endl;
		std::cout << "6: Terminate program" << endl << flush;
		cin >> choice;
		string n, p;
		if (choice == 1) 
		{
			create();
			continue;
		}
		if (choice == 2) 
		{
			search();
			continue;
		}
		if (choice == 3) 
		{
			delete_name();
			continue;
		}
		if (choice == 4) 
		{
			edit();
			continue;
		}
		if (choice == 5) 
		{
			display();
			continue;
		}
		if (choice == 6) 
		{
			quit = true;
			store();
			continue;
		}
		else
		{
			cout << '?' << endl;
		}
	}
}
void UserInterface::create() 
{
	cout << "Name: ";
	cin.ignore();
	getline(cin, n);
	cout << "Phone: ";
	getline(cin, p);
	Person pers(n, p);
	phonebook.insert(pers);
	cout << "Contact created.\n" << flush;
}
void UserInterface::delete_name() 
{
	cout << "Name: ";
	cin.ignore();
	getline(cin, n);
	Person pers(n);
	phonebook.remove(pers);
	cout << "Contact deleted.\n" << flush;
}
void UserInterface::search() 
{
	cout << "Name: ";
	cin.ignore();
	getline(cin, n);
	Person pers(n);
	cout << endl;
	phonebook.find(pers);
	cout << endl;
}
void UserInterface::display() 
{
	cout << endl;
	cout << left << setw(12) << "First Name" << " ";
	cout << left << setw(12) << "Last Name" << " | ";
	cout << left << "Phone Number" << endl;
	cout << "----------------------------------" << endl;
	phonebook.print_inorder();
	cout << endl;
}
void UserInterface::edit() 
{
	cout << "Name: ";
	cin.ignore();
	getline(cin, n);
	cout << "Number: ";
	getline(cin, p);
	Person pers(n, p);
	cout << endl;
	phonebook.edit(pers);
	cout << endl;
}
void UserInterface::store() 
{
	phonebook.store("contact_info.txt");
}
int main() 
{
	UserInterface ui;
	ui.menu();
};
