#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

fstream fs;

struct QA
{
	string sen;
	QA* left=NULL , * right=NULL;
};

QA* newQA(string data)// tao node moi
{
	QA* tmp = new QA;
	tmp->sen = data;
	return tmp;
}

QA* input(QA* &root )// Phan 1: doc du lieu tu file thanh cay BST
{
	if (fs.eof()) return NULL;
	string tmp;
	getline(fs, tmp);
	root = newQA(tmp);
	if (tmp.substr(0, 2) == "#A") return root;// Neu la nodee la thi khong di tiep
	if (root->left==NULL) root->left = input(root->left);// tiep tuc di xuong cay con trai va phai
	if (root->right==NULL) root->right = input(root->right);
	return root;
}

void update(QA* &temp, vector<string> vans)//Cap nhat them con vat moi tu nguoi choi
{
	cout << "I don't know it!\n";
	cout << "Would you like to teach me? (y/n): ";
	char choice;
	cin >> choice;
	if (choice == 'n') return;
	cout << "I asked the following: \n";
	for (int i = 0; i < vans.size(); i++) cout << vans[i];		//lap lai cau hoi
	string ques, ans;
	cout << "Enter a new animal in the form of a question, e.g., 'Is it a whale?': ";
	cin.ignore();
	getline(cin, ans);
	cout << "Now enter a question for which the answer is 'yes' for your new animal,\nand which does not contradict your previous answers: ";
	getline(cin, ques);
	temp->right = newQA(temp->sen);//chuyen cau tra loi qua node phai
	temp->sen = "#Q " + ques;		//node se chuyen thanh cau hoi moi duoc nguoi choi nhap
	temp->left = newQA("#A " + ans);	// con vat dung cho cau hoi moi
}

bool play(QA* root) // Tra ve true neu doan dung va false neu khong doan duoc con vat
{
	char ans='y';
	QA* temp=root;
	vector<string> vans;
	string sen;
	while (root)//Chay den het Node cau tra loi #A
	{
		cout << root->sen.substr(3, root->sen.length() - 3) << " (y/n): "; // xuat ra cau hoi bo phan dau (#Q, #A)
		cin >> ans;
		temp = root;
		if (ans == 'y')
		{
			sen = root->sen.substr(3, root->sen.length() - 3) + " YES\n"; // Luu lai cau hoi va cau tra loi YES cua nguoi choi
			vans.push_back(sen);
			root = root->left;
		}
		else
		{
			sen = root->sen.substr(3, root->sen.length() - 3) + " NO\n"; //Luu lai cau hoi va cau tra loi No cua nguoi choi
			vans.push_back(sen);
			root = root->right;
		}
	}
	if (ans == 'y') //Doan dung
	{
		cout << "I wont! I guessed it!\n";
		return true;
	}
	update(temp, vans);//Neu khong doan duoc thi them con vat moi
	return false;
}

void save(QA* root)// Luu lai cay BST vao file theo cau truc NLR
{
	fs << root->sen << endl;
	if (root->left) save(root->left);
	if (root->right) save(root->right);
	return;
}

int main()
{
	QA* root = NULL;
	fs.open("Animal_game.txt");
	root=input(root);
	fs.close();
	int choice;
	bool again=true;//Kiem tra xem da doan ra ten con vat chua
	do
	{
		if (again)
		{
			cout << "_____Animal---game_____\n";
			cout << "1.Play\n";
			cout << "2.Save game\n";
			cout << "0.Exit\n";
			cout << "Your choice (0->2): ";
			cin >> choice;
		}
		again = true;
		switch (choice)
		{
		case 1: 
		{
			again = play(root);
			if (!again)
			{
				cout << "What do you want to do next?\n1.Countinue\n2.Save and exit\nYour choice(1->2): "; // Sau khi them con vat thi nguoi choi co muon tiep tuc khong
				cin >> choice;
			}
		}
			break;
		case 2: 
		{
			fs.open("Animal_game.txt", ios::trunc);// Xoa file cu va ghi du lieu moi vao
			save(root);
			fs.close();
			choice = 0;
		}
			break;
		}
	} while (choice != 0);
	return 0;
}