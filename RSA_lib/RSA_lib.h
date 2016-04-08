#ifndef RSA_LIB_H
#define RSA_LIB_H

#include<iostream>
#include <ctime>
using namespace std;
using std::swap;
using std::rand;

//�������� "������ ����������". �������� ��� ������� �����
//�� ��������� (�������� ����������������).
unsigned long long sundaram(unsigned long long);

//�������� �������. �������� ��� ���������� �����������
//������ �������� ���� ����� �����. ������������ ��� ��������
//����� �� ��������������.
unsigned long long gcd(unsigned long long, unsigned long long);

// ������� ������.
inline unsigned long long eiler_function(unsigned long long p_simple, unsigned long long q_simple) { return (p_simple - 1)*(q_simple - 1); }

//������������� ��������� ���������� - � � �������� � �� ��������������
//� ������ ((p_simple-1)*(q_simple-1)).
unsigned long long generete_public_exponent(unsigned long long, unsigned long long, unsigned long long);

//������������� ��������� ���������� - d, ��� ������� �������� ��������
//����������� (e*d)%((p_simple-1)*(q_simple-1))=1.
unsigned long long generete_private_exponent(unsigned long long, unsigned long long, unsigned long long);
// ���������� � ������� �� ������.
long long modular_pow(long long, unsigned long long, unsigned long long);

//����������.
void to_encrypt(char*, long long*, unsigned long long, unsigned long long, unsigned int);
//�������������.
void to_decrypt(long long*, long long*, unsigned long long, unsigned long long, unsigned int);
_declspec(dllexport)  void _stdcall RSA_Generations_Keys(unsigned long long*, unsigned long long*, unsigned long long*);
_declspec(dllexport) long long* _stdcall RSA_Encrypting(char*, long long*, unsigned long long, unsigned long long, unsigned int);
_declspec(dllexport) long long* _stdcall RSA_Decrypting(long long*, long long*, unsigned long long, unsigned long long, unsigned int);

#endif;

