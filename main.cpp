//books.txt is automatically read as the program starts.  Data is saved in saved.txt when the program ends.
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct book
{
	string title;
	string author;
	string publisher;
	int year;
	string isbn;
	book* next;
	book(string, string, string, int, string, book*);
};

book::book(string tempTitle, string tempAuthor, string tempPublisher, int tempYear, string tempIsbn, book* tempNext)
:title(tempTitle), author(tempAuthor), publisher(tempPublisher), year(tempYear), isbn(tempIsbn), next(tempNext)
{}

typedef book* bookPtr;

void getline(istream &stream, string &str, char delimiter)
{	char temp[500];

	stream.get(temp, 500, delimiter);
	stream.ignore(500, delimiter);
	str = temp;
}

void getline(istream &stream, int &num, char delimiter)
{	int temp;

	stream >> temp;
	stream.ignore(500, delimiter);
	num= temp;
}

void readFile(bookPtr &root);
void insert (bookPtr &root);
void delTitle(bookPtr &root);
bookPtr locateNode(bookPtr temp, string tit);
void delIsbn(bookPtr &root);
bookPtr locateNodeIsbn(bookPtr temp, string isb);
void searchIsbn(bookPtr temp);
void printList(bookPtr temp);
void printAuthor(bookPtr temp);
void saveFile(bookPtr temp);
int countNodes(bookPtr temp);

int main()
{
	int choice;
	bookPtr root = NULL;
	readFile(root);

	do
	{
		cout << "Menu: Select your option\n\n";
		cout << "(1) Add a book to the list\n";
		cout << "(2) Delete a book based on Title\n";
		cout << "(3) Delete a book based on ISBN\n";
		cout << "(4) Search for a book by ISBN.\n";
		cout << "(5) List all books.\n";
		cout << "(6) List all books by an author.\n";
		cout << "(7) Quit.\n\n";
		cout << "Enter your choice ---> ";

		cin >> choice;

		if (1 <= choice && choice <= 6)
		{	
			switch (choice)
			{
			case 1:
				insert(root);
				break;
			case 2:
				delTitle(root);
				break;
			case 3:
				delIsbn(root);
				break;
			case 4:
				searchIsbn(root);
				break;
			case 5:
				printList(root);
				break;
			case 6:
				printAuthor(root);
				break;
			default:
				cout << "Invalid choice.  Enter again.\n\n";
				break;
			}
		}	
	}
	while (choice != 7);
	saveFile(root);
	return 0;
}

void readFile(bookPtr &root)
{
	int numBooks, yea;
	string tit, aut, pub, isb;
	ifstream infile ("books.txt", ios::in);
	infile >> numBooks;
	infile.ignore(500,'\n');
	for (int count = 0; count < numBooks; count++)
	{
		getline(infile, tit, '\n');
		getline(infile, aut, '\n');
		getline(infile,pub, '\n');
		getline(infile,yea, '\n');
		getline(infile, isb, '\n');

		root = new book (tit, aut, pub, yea, isb, root);
	}
}

void insert (bookPtr &root)
{
	string tit, aut, pub, isb;
	int yea;

	cout << "Title:\t\t\t";
	cin.ignore(500,'\n');
	getline(cin, tit, '\n');
	cout << "Author:\t\t\t";
	getline(cin, aut, '\n');
	cout << "Publisher:\t\t";
	getline(cin,pub, '\n');
	cout << "Year:\t\t\t";
	getline(cin,yea, '\n');
	cout << "ISBN:\t\t\t";
	getline(cin, isb, '\n');

	root = new book (tit, aut, pub, yea, isb, root);
}

void delTitle(bookPtr &root)
{
	string tit;
	
	cout << "Book Title:\t\t\t";
	cin.ignore(500,'\n');
	getline(cin, tit, '\n');

	bookPtr p = locateNode(root, tit);

	if (p == NULL)
		cout << "\nDeletion cannot be done.\n\n";
	else if (root == p)
		root = p->next;
	else
	{
		bookPtr q = root;
		while (q->next != p)
			q = q->next;
		q->next = p->next;
	}
	delete p;
}

bookPtr locateNode(bookPtr temp, string tit)
{
	while (temp != NULL)
	{
		if (temp->title == tit)
		{
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

void delIsbn(bookPtr &root)
{
	string isb;
	
	cout << "Book ISBN:\t\t\t";
	cin.ignore(500,'\n');
	getline(cin, isb, '\n');

	bookPtr p = locateNodeIsbn(root, isb);

	if (p == NULL)
		cout << "\nDeletion cannot be done.\n\n";
	else if (root == p)
		root = p->next;
	else
	{
		bookPtr q = root;
		while (q->next != p)
			q = q->next;
		q->next = p->next;
	}
	delete p;
}

bookPtr locateNodeIsbn(bookPtr temp, string isb)
{
	while (temp != NULL)
	{
		if (temp->isbn == isb)
		{
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

void searchIsbn(bookPtr temp)
{
	string isb;

	cout << "Book ISBN:\t\t\t";
	cin.ignore(500,'\n');
	getline(cin, isb, '\n');
	
	while (temp != NULL)
	{
		if (isb == temp->isbn)
		{
			cout << temp->title << "\n";
			cout << temp->author << "\n"; 
			cout << temp->publisher << "\n";
			cout << temp->year << "\n";
			cout << temp->isbn << "\n\n";
		}
		temp = temp->next;
	}
	cout << "\n";
}

void printList(bookPtr temp)
{
	while (temp != NULL)
	{
		cout << temp->title << "\n";
		cout << temp->author << "\n"; 
		cout << temp->publisher << "\n";
		cout << temp->year << "\n";
		cout << temp->isbn << "\n\n";
		temp = temp->next;
	}
	cout << "\n";
}

void printAuthor(bookPtr temp)
{
	string aut;

	cout << "Author name:\t\t\t";
	cin.ignore(500,'\n');
	getline(cin, aut, '\n');
	
	while (temp != NULL)
	{
		if (temp->author == aut)
		{
			cout << temp->title << "\n";
			cout << temp->author << "\n"; 
			cout << temp->publisher << "\n";
			cout << temp->year << "\n";
			cout << temp->isbn << "\n\n";
		}
		temp = temp->next;
	}
	cout << "\n";
}

void saveFile(bookPtr temp)
{
	int count = countNodes(temp);
	ofstream outFile("saved.txt",ios::out);
	
	outFile << count << "\n";
	while (temp != NULL)
	{
		outFile << temp->title << "\n";
		outFile << temp->author << "\n"; 
		outFile << temp->publisher << "\n";
		outFile << temp->year << "\n";
		outFile << temp->isbn << "\n";
		temp = temp->next;
	}
	cout << "\n";
}

int countNodes(bookPtr temp)
{
	int countB = 0;
	while (temp != NULL)
	{
		countB++;
		temp = temp->next;
	}
	return countB;
}

