#ifndef MEUSTIPOS
#define MEUSTIPOS

// Tipos inteiros com tamanho fixo
typedef char I8;               // inteiro de 8 bits, pode ser negativo (-128 a 127)
typedef unsigned char U8;      // inteiro de 8 bits, somente positivo (0 a 255)
typedef short int I16;         // inteiro de 16 bits com sinal
typedef unsigned short int U16;// inteiro de 16 bits sem sinal
typedef int I32;               // inteiro de 32 bits com sinal
typedef unsigned int U32;      // inteiro de 32 bits sem sinal
typedef long int I64;          // inteiro de 64 bits com sinal
typedef unsigned long int U64; // inteiro de 64 bits sem sinal

// Tipos reais
typedef float R32;             // 32 bits (float)
typedef double R64;            // 64 bits (double)
typedef long double R128;      // 128 bits (long double)

// Tipo boolean
typedef enum {
    false,
    true
} boolean;

#endif
