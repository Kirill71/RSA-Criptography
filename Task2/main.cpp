#include<locale>
#include<iostream>
#include <iomanip>
#include<Windows.h>

using std::cout;
using std::endl;
using std::setw;
using std::cin;

const int MAX = 100; // Длина шифруемого текста.

typedef void(_stdcall RSA_Generations_Keys(unsigned long long*, unsigned long long*, unsigned long long*));
typedef  long long* (_stdcall RSA_Encrypting(char*,  long long*, unsigned long long, unsigned long long, unsigned int));
_declspec(dllexport) long long* _stdcall RSA_Decrypting(long long*, long long*, unsigned long long, unsigned long long, unsigned int);
char lang(char);

int main()
{
	SetConsoleCP(1251); // Ввод с консоли в кодировке 1251
	SetConsoleOutputCP(1251);
	srand((unsigned)time(NULL)); 
	unsigned long long e = 0, d = 0, n = 0;
	unsigned choice = 0;
	char  lang_array[9][100]{'0'};
	RSA_Generations_Keys *ptr_2_RSA_Generations_Keys = NULL;
	RSA_Encrypting *ptr_2_RSA_Encrypting = NULL;
	HMODULE h = LoadLibrary("RSA_lib.dll");
	if (h==NULL)  return -1;
	cout << "Choose your language: 1 Russian, 2 English, 3-Ukrainian" << endl;
	cout << "Enter your choice:" << endl;
	do
	{
		cin >> choice;
		if (choice<4&&choice>0) break; else cout<<"Incorrect choice";
	} while (true);
	system("cls");
	unsigned end = lang(choice) + 9;
	for (unsigned i = lang(choice), k=0; i < end; ++i,++k)
		LoadString(h, i,lang_array[k], sizeof(lang_array[k]));
	cout << lang_array[0] << endl << endl;
	ptr_2_RSA_Generations_Keys = (RSA_Generations_Keys*)GetProcAddress(h, "RSA_Generations_Keys");
	if (h==NULL) return -1;
	ptr_2_RSA_Encrypting = (RSA_Encrypting*)GetProcAddress(h, "RSA_Encrypting");
	if (h==NULL)return -1;
	ptr_2_RSA_Generations_Keys(&e, &d, &n);
	//Сгенерированные ключи.
	cout << '{' << setw(12) << e << ',' << setw(12) << n << '}' << lang_array[1] << endl;
	cout << '{' << setw(12) << d << ',' << setw(12) << n << '}' << lang_array[2] << endl << endl;
	//Ввод шифруемых данных.
	char *text = new char[MAX];
	cout << lang_array[3] << endl;
	cin.ignore();
	cin.getline(text,MAX);
	unsigned int size = strlen(text);
	//Массив для хранения шифротекста.
	long long *encrypt_text = new long long[size];
	long long *decrypt_text = new long long[size];
	//Получение из введённых данных десятичного кода ASCII и
	//дальнейшее его преобразование по формуле c[i] = (m[i]^e)%n.

	cout << endl << setw(5) << lang_array[4] << setw(10) <<lang_array[5]
		<< setw(16) << lang_array[6] << setw(16)
		<< lang_array[7] << setw(14) << lang_array[8] << endl
		<< "------------------------------------------------------------" << endl;
	//шифрование
	encrypt_text = ptr_2_RSA_Encrypting(text, encrypt_text, e, n, size);
	//расшифрровать
	decrypt_text=RSA_Decrypting(encrypt_text, decrypt_text, d, n, size);
	FreeLibrary(h);
	for (unsigned int i = 0; i < strlen(text); ++i)
		cout << setw(3) << text[i] << setw(12) << (int)text[i] << setw(16)
		<< encrypt_text[i] << setw(14) << decrypt_text[i] << setw(14) << (char)decrypt_text[i] << endl;
	delete[] text;
	delete[] encrypt_text;
	delete[] decrypt_text;

	system("pause");
	return 0;
}

char lang(char choice)
{
	switch (choice)
	{
		case 1: {return 0;}
		case 2: {return 9;}
		case 3: {return 18;}
	}
	return '?';
}