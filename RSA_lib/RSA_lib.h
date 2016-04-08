#ifndef RSA_LIB_H
#define RSA_LIB_H

#include<iostream>
#include <ctime>
using namespace std;
using std::swap;
using std::rand;

//Алгоритм "решето Эратосфена". Выбирает все простые числа
//до заданного (случайно сгенерированного).
unsigned long long sundaram(unsigned long long);

//Алгоритм Евклида. Алгоритм для нахождения наибольшего
//общего делителя двух целых чисел. Используется для проверки
//чисел на взаимопростоту.
unsigned long long gcd(unsigned long long, unsigned long long);

// Функция Эйлера.
inline unsigned long long eiler_function(unsigned long long p_simple, unsigned long long q_simple) { return (p_simple - 1)*(q_simple - 1); }

//Генерирование публичной экспоненты - е и проверка её на взаимопростоту
//с числом ((p_simple-1)*(q_simple-1)).
unsigned long long generete_public_exponent(unsigned long long, unsigned long long, unsigned long long);

//Генерирование приватной экспоненты - d, для которой является истинным
//соотношение (e*d)%((p_simple-1)*(q_simple-1))=1.
unsigned long long generete_private_exponent(unsigned long long, unsigned long long, unsigned long long);
// Возведение в степень по модулю.
long long modular_pow(long long, unsigned long long, unsigned long long);

//Шифрование.
void to_encrypt(char*, long long*, unsigned long long, unsigned long long, unsigned int);
//Расшифрование.
void to_decrypt(long long*, long long*, unsigned long long, unsigned long long, unsigned int);
_declspec(dllexport)  void _stdcall RSA_Generations_Keys(unsigned long long*, unsigned long long*, unsigned long long*);
_declspec(dllexport) long long* _stdcall RSA_Encrypting(char*, long long*, unsigned long long, unsigned long long, unsigned int);
_declspec(dllexport) long long* _stdcall RSA_Decrypting(long long*, long long*, unsigned long long, unsigned long long, unsigned int);

#endif;

