#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "validacoes.h"
#include "entradas.h"
#include "funcoesgerais.h"


int recebeString(char *str,int tamStr,char *nomeCampo,int apenasNumeros){

    setbuf(stdin,NULL);
    printf("\nForne�a o %s: ",nomeCampo);
    if(apenasNumeros)
        printf("(Utilize apenas numeros): ");
    fgets(str,tamStr,stdin);
    setbuf(stdin,NULL);
    retiraN(str);
    return strlen(str);

}

unsigned long recebeId(){
    unsigned long id;
    printf("\n|Forne�a o id:");
    scanf("%lu",&id);
    return id;
}

void recebeNome(char *nome){
    int tam=0;
    do{
        tam=recebeString(nome,100,"Nome",0);

        if(!tam)
            printf("\n-------------------------Nome n�o pode ser vazio!!!----------------------------------------");
    }while(!tam);
}


//---------------------------------------FUN��O DE ARMAZENAMENTO E VALIDA��O DE CPF------------------------------
void recebeCpf(char *cpf){
    const int TAM_CPF = 12;
    int tam=0;
    do {
        tam = recebeString(cpf,TAM_CPF,"CPF",0);
        if(!tam)
            printf("\n-------------------------CPF n�o pode ser vazio!!!----------------------------------------");
    }while(!tam);
    return;
}

void recebeEmail(char *email){
    int tam;

    do{
        tam=recebeString(email,50,"Email",0);
        if(!tam)
            printf("\n-------------------------E-mail n�o pode ser vazio!!!----------------------------------------");

    }while(!tam);
}

void recebeTelefone(char *telefone){

    int tam,teste;

    do{
        teste=0;
        tam=recebeString(telefone,15,"Telefone",1);
        if(!tam)
            printf("\n-------------------------Telefone n�o pode ser vazio!!!----------------------------------------");
        else {
            teste=apenasNumeros(telefone);
            if(!teste)
                printf("\n-----Utilize apenas numeros!!!-----");
        }
    }while(!teste);
}

void recebePrefixo(char *pre){
    int tam;
    do{
        tam = recebeString(pre,100,"Prefixo",0);
        if(!tam)
            printf("\n-------------------------Prefixo n�o pode ser vazio!!!----------------------------------------");
    }while(!tam);
}

void recebeData(char *data){
    int tam;
    do{
        tam = recebeString(data,11,"Data (DD-mm-AAAA)",0);
        if(!tam)
            printf("\n-------------------------Data n�o pode ser vazia!!!----------------------------------------");
    }while(!tam);
}

void recebeNomeTXT(char *nomeArquivo){
    int tam;
    do{
        tam = recebeString(nomeArquivo,50,"Nome do arquivo sem extens�o",0);
        if(!tam)
            printf("\n-------------------------nome n�o pode ser vazio!----------------------------------------");
    }while(!tam);

    strcat(nomeArquivo,".txt");
}

unsigned int recebeQuantidade(){
    unsigned int qtde;
    do{
        printf("\n|Forne�a a quantidade:");
        scanf("%u",&qtde);
        if(qtde<=0)
            printf("\nQuantidade deve ser maior que 0!");
    }while(qtde<=0);
    return qtde;
}

float recebePreco(){
    float preco;
    do{
        printf("\n|Forne�a o Valor do produto R$ ");
        scanf("%f",&preco);
        if(preco<=0)
            printf("\nPre�o deve ser maior que 0!");
    }while(preco<=0);
    return preco;
}

int perguntaAlteracao(char *nomeCampo){
    int s_n;
    do{
        printf("\nDeseja alterar o %s?", nomeCampo);
        printf("\n|1-Sim | 2-N�o: ");
        scanf("%d",&s_n);
        if (s_n!=1 && s_n!=2)
            printf("\nOp��o inv�lida");
    }while (s_n!=1 && s_n!=2);

    return s_n;
}

int perguntaBusca(char *nomeCampo){
    int s_n;
    do{
        printf("\nDeseja realizar mais alguma consulta por %s?", nomeCampo);
        printf("\n|1-Sim | 2-N�o: ");
        scanf("%d",&s_n);
        if (s_n!=1 && s_n!=2)
            printf("\nOp��o inv�lida");
    }while (s_n!=1 && s_n!=2);

    return s_n;
}

int confirmaExclusao(char *nomeStruct){
    int s_n;
    do{
        printf("\nDeseja realmente excluir este(a) %s?", nomeStruct);
        printf("\n|1-Sim | 2-N�o: ");
        scanf("%d",&s_n);
        if (s_n!=1 && s_n!=2)
            printf("\nOp��o inv�lida");
    }while (s_n!=1 && s_n!=2);

    return s_n;
}

int perguntaExclusao(char *nomeStruct){
    int s_n;
    do{
        printf("\nDeseja realizar mais alguma exclus�o?");
        printf("\n|1-Sim | 2-N�o: ");
        scanf("%d",&s_n);
        if (s_n!=1 && s_n!=2)
            printf("\nOp��o inv�lida!");
    }while (s_n!=1 && s_n!=2);

    return s_n;
}

int perguntaRelatorioDatas(){
    int opcao;
    do{
        printf("\nQual relat�rio deseja?");
        printf("\n1-Data especifica | 2-Intervalo de datas");
        scanf("%d",&opcao);
        if(opcao!=1 && opcao!=2)
            printf("\nOp��o inv�lida");
    } while (opcao!=1 && opcao!=2);
    
    return opcao;
}

int perguntaRelatorio(){
    int opcao;
    do{
        printf("\nComo deseja receber o relatorio??");
        printf("\n1-Arquivo de Texto | 2-Tela");
        printf("\nOp��o:|");
        scanf("%d",&opcao);
        if(opcao!=1 && opcao!=2)
            printf("\nOp��o inv�lida");
    } while (opcao!=1 && opcao!=2);
    return opcao;
}

void menuInicial(char *nomeStruct){
     printf("\n|----------------Menu de %s-----------------------",nomeStruct);
     printf("\n|O que deseja Fazer");
     printf("\n|1-Cadastrar %s",nomeStruct);
     printf("\n|2-Alterar %s",nomeStruct);
     printf("\n|3-Consultar %s",nomeStruct);
     printf ("\n|4-Excluir %s",nomeStruct);
     printf ("\n|5-Menu pricipal");
     printf("\n|Op��o:");

}

void recebeCnpj(char *cnpj){
    const int TAM_CNPJ = 15;
    int tam=0;
    do {
        tam = recebeString(cnpj,TAM_CNPJ,"CNPJ",1);
        if(!tam)
            printf("\n-------------------------CNPJ n�o pode ser vazio!!!----------------------------------------");
    }while(!tam);
    return;
}




