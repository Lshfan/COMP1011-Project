#include <string>
#include <iostream>
#include "SHA1.hpp"
#include "SHA1.hpp"
#include <fstream>

using namespace std;
struct block {
	string prehash;
	string value;
	string curhash;
	int number1;
};
struct chain {
	int number2;
	struct block arr[100];
};
void addition(chain*ptr) {
	int a;
	int b;
	cout << "please enter the block number " <<endl;
	cin >> a;
	b = a + ptr->number2;
	string prehash = "";
	string value = "";
	if (ptr->number2 != 0) {
		prehash = ptr->arr[ptr->number2 - 1].curhash;
	}
	cout << "please enter the value of block" << endl;
	cin >> value;
	string input(value);
	SHA1 checksum;
	checksum.update(input);
	char curhash[41];
	strcpy_s(curhash, checksum.final().c_str());
	ofstream ofs("text.txt");
	ptr->arr[a-1].value = value;
	ptr->arr[a-1].number1 = a;
	ptr->arr[a-1].curhash = curhash;
	ptr->arr[a-1].prehash = prehash;
	prehash = curhash;
	ofs << ptr->arr[a - 1].value << endl;
	ofs << ptr->arr[a - 1].number1 << endl;
	ofs << ptr->arr[a - 1].curhash << endl;
	ofs << ptr->arr[a - 1].prehash << endl;
	cout << "the current hash is: " << curhash << endl;
}
void seeking(chain* ptr) {
	int a;
	cout << "please choose the method of seeking" << endl;
	cout << "1.according to the block number" << endl;
	cout << "2.according to the current hash" << endl;
	cout << "3.according to the value" << endl;
	cin >> a;
	string b;
	string c;
	if (a == 1) {
		int number = 0;
		cout << "please enter the block number you want to seek " << endl;
		cin >> number;
		ifstream ifs;
		ifs.open("text.txt", ios::in);
		char buf[1024] = { 1024 };
		while (ifs >> buf) {
			cout << buf << endl;
		}
		ifs.close();
	}
	else if (a == 2) {
		cout << "please enter the current hash " << endl;
		cin >> b;
		int i = 0;
		while (i < ptr->number2) {
			if (ptr->arr[i].curhash == b) {
				ifstream ifs;
				ifs.open("text.txt", ios::in);
				char buf[1024] = { 1024 };
				while (ifs >> buf) {
					cout << buf << endl;
				}
				ifs.close();
			}
				
			i++;
		}
	}
	else if (a == 3) {
		cout << "please enter the value " << endl;
		cin >> c;
		int j = 0;
		while (j < ptr->number2) {
			if (ptr->arr[j].value == c) {
				ifstream ifs;
				ifs.open("text.txt", ios::in);
				char buf[1024] = { 1024 };
				while (ifs >> buf) {
					cout << buf << endl;
				}
				ifs.close();
			}
			j++;
		}
	}
}
void checking(chain*ptr){
	int x = 0;
	while (x < ptr->number2-1) {
		if (ptr->arr[x].curhash == ptr->arr[x + 1].prehash) {
			cout << "the blocks are integral" << endl;
		}
		else
			cout << "the blocks are not integral" << endl;
		x++;
	}
}
int main(){
	while (true) {
		chain block;
		int num;
		block.number2 = 0;
		cout << "1. add a new block " << endl;
		cout << "2. seek the data " << endl;
		cout << "3. check the integrity " << endl;
		cout << "4. quit" << endl;
		cin >> num;
		if (num == 1) {
			addition(&block);
		}
		else if (num == 2) {
			seeking(&block);
		}
		else if (num == 3) {
			checking(&block);
		}
		else if (num == 4) {
			cout << "Bye!";
			break;
		}
	}
}

