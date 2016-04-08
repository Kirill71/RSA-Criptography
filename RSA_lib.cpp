// RSA_lib.cpp: определяет экспортированные функции для приложения DLL.
//

#include "stdafx.h"
#include"RSA_lib.h"

/////////////////////////////////////////////////////////////////////
//Алгоритм "решето Сундорама". Выбирает все простые числа
//до заданного (случайно сгенерированного).

unsigned long long sundaram(unsigned long long n)
{
	bool *a = new bool[n];
	unsigned long long i, j, k;
	memset(a, false, sizeof(bool) * n);
	for (i = 1; 3 * i + 1 < n; ++i)
	{
		for (j = 1; (k = i + j + 2 * i*j) < n && j <= i; ++j)
			a[k] = true;
	}
	//Выбирает из списка простых чисел ближайшее к заданному.
	for (i = n - 1; i >= 1; --i)
		if (a[i] == false) return (2 * i + 1);
	delete[] a;
}


/////////////////////////////////////////////////////////////////////
//Алгоритм Евклида. Алгоритм для нахождения наибольшего
//общего делителя двух целых чисел. Используется для проверки
//чисел на взаимопростоту.
unsigned long long gcd(unsigned long long a, unsigned long long b)
{
	while (b)
	{
		a %= b;
		swap(a, b);
	}
	return abs((long long)a);
}

long long modular_pow(long long base, unsigned long long exp, unsigned long long  modul)
{
	long long d = 1;
	unsigned long long  mask = 0x8000000000000000;
	long long modulus = modul;
	unsigned int shift = 63;
	for (unsigned int i = 0; i < 64; ++i)
	{
		d = (d*d) % modulus;
		if ((exp&mask) >> shift)d = (d*base) % modulus;
		mask >>= 1;
		--shift;
	}
	return d;
}

void to_encrypt(char* text, long long* encrypt_text, unsigned long long public_exponent, unsigned long long modul, unsigned int size)
{
	for (unsigned int i = 0; i < size; ++i)
		encrypt_text[i] = modular_pow(text[i], public_exponent, modul);
}


void to_decrypt(long long*encrypt_text, long long*decrypt_text, unsigned long long private_exponent, unsigned long long modul, unsigned int size)
{
	for (unsigned int i = 0; i < size; ++i)
		decrypt_text[i] = modular_pow(encrypt_text[i], private_exponent, modul);
}

_declspec(dllexport)  void _stdcall RSA_Generations_Keys(unsigned long long* public_exponent, unsigned long long* private_exponent, unsigned long long* modul)
{
	unsigned long long p =0, q =0;
	unsigned long long p_simple =0, q_simple = 0;
	do
	{
		p = 1500 + rand() % 3499;
		q = 1500 + rand() % 3499;
		p_simple = sundaram(p);
		q_simple = sundaram(q);

	} while (p_simple == q_simple);
	//Находим число n.
	*modul = p_simple*q_simple;

	unsigned long long eiler_number= eiler_function(p_simple,q_simple);
	*public_exponent = generete_public_exponent(eiler_number, *public_exponent, *modul);

	*private_exponent = generete_private_exponent(*private_exponent, *public_exponent, eiler_number);
}

_declspec(dllexport) long long* _stdcall RSA_Encrypting(char* text, long long*encrypt_text, unsigned long long public_exponent, unsigned long long modul, unsigned int size)
{
	to_encrypt(text, encrypt_text, public_exponent, modul, size);
	return encrypt_text;
}

_declspec(dllexport) long long* _stdcall RSA_Decrypting(long long* encryp_text, long long* decrypt_text, unsigned long long private_exponent, unsigned long long modul, unsigned int size)
{
	to_decrypt(encryp_text, decrypt_text, private_exponent, modul, size);
	return decrypt_text;
}

unsigned long long generete_public_exponent(unsigned long long eiler_number, unsigned long long public_exponent, unsigned long long n)
{
	unsigned long long e_simple = 0;
	while (e_simple != 1)
	{
		public_exponent = 2 + rand() % 1000 - 2;
		if ((e_simple = gcd(public_exponent, eiler_number)) == 1) return public_exponent;
	}
}

unsigned long long generete_private_exponent(unsigned long long private_exponent, unsigned long long public_exponent, unsigned long long eiler_number)
{
	while (((public_exponent*++private_exponent) % eiler_number) != 1);
	return private_exponent;
}

