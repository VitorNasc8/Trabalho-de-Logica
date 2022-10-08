#ifndef VALIDACOES_H_INCLUDED
#define VALIDACOES_H_INCLUDED

/*
    varifica se o cpf � v�lido atr�ves da soma dos digitos
    retrona 1 se for v�lido e 0 se for inv�lido
*/
int validaCpf(char *cpf);
/*
    varifica se a string possui apenas numeros
    retrona 1 se for apenas numeros e 0 caso contr�rio
*/
int apenasNumeros(char *numero);
/*
    varifica se o cnpj � v�lido atr�ves dos digitos validadores
    retrona 1 se for v�lido e 0 se for inv�lido
*/
int validaCnpj(char *cnpj);
int restoSomaCNPJ(int *cnpj,int *multiplicador,int tam);
/*
    varifica se a data � v�lida
    retrona 1 se for v�lida e 0 se for inv�lida
*/
int validaData(char *data);
#endif // VALIDACOES_H_INCLUDED
