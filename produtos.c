#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "produtos.h"
#include "validacao.h"
#include "entradas.h"
#include "vendedor.h"
#include "funcoesgerais.h"

void mProduto(){
int sair;
FILE *fp;

fp=fopen("produto.dat","rb+");
if(fp==NULL)
fp=fopen("produto.dat","wb+");
if(fp!=NULL){

do{
  printf("\n|----------------Menu de Produtos-----------------------");
 printf("\n|O que deseja Fazer");
 printf("\n|1-Cadastrar Produtos");
 printf("\n|2-Alterar Nome dos Produtos");
 printf("\n|3-Consultar Produtos");
 printf ("\n|4Excluir Produto");
 printf ("\n|5-Menu pricipal");
 printf("\n|Op��o:");
 scanf ("%d",&sair);

switch(sair){

case 1:

cadProduto(fp);
break;

case 2:
alterProduto(fp);
break;
case 3:
consProduto(fp);
break;

case 4:
 delProduto(fp);
break;
}

}while(sair!=5);



fclose(fp);
}else
    printf("Impossivel abrir o arquivo");
return;
}

//---------------FUN��O DE CADASTRO------------------------------


void cadProduto(FILE *file){
t_produto novo;
int menu;
unsigned long posicao;

do{
novo.id=novo_IDP(file);
printf("\nID do produto:|%lu",novo.id);
recebe_nome(novo.nome);
novo.quantidadeEstoque=0;
printf("\nForne�a o valor unitario:|");
setbuf(stdin,NULL);
scanf("%f",&novo.precoUnitario);

setbuf(stdin,NULL);

posicao=novo.id-1;

fseek(file,sizeof(t_produto)*posicao,SEEK_SET);
fwrite(&novo,sizeof(t_produto),1,file);
    printf("\n----------------------------------CADASTRO CONCLUIDO------------------------------------------------------------");
printf("\nDeseja continuar cadastrando???");
printf("\n1-Sim|2-N�o");
printf("\nOp��o:");
scanf("%d",&menu);
}while(menu==1);





}

//-------------------------FUN��O ID--------------------------

unsigned long novo_IDP(FILE *file){

unsigned long id;
t_produto novo;

id=1;
fseek(file,0,SEEK_SET);
while(fread(&novo,sizeof (t_produto),1,file)==1){

if(novo.id==0)
break;
id++;

}

return id;


}
//-----------------------------FIM DO CADASTRO--------------------------

//-----------------------------ALTERA��O-----------------------

void alterProduto(FILE *file){
unsigned long id,posicao;
int achou,s_n;

t_produto novo;
do{

  printf("\n-----------------Menu de Altera��o de Nome-----------------------");
printf("\nForne�a o Id que deseja alterar:");
scanf("%lu",&id);

if(id!=0){
achou =0;
posicao=0;
fseek(file,0,SEEK_SET);
while(fread(&novo,sizeof (t_produto),1,file)==1&&achou==0){

if(id==novo.id){
  achou=1;}else posicao ++;

  }
  if(achou==1){

 fseek(file,sizeof(t_produto)*posicao,SEEK_SET);
  fread(&novo,sizeof(t_produto),1,file);

    printf("\n|---------------Dados atuais--------------------|");
    printf("\n|ID:%lu",novo.id);
    printf("\n|Nome:%s",novo.nome);
    printf("\n|Quantidade em estoque:%du",novo.quantidadeEstoque);
    printf("\n|Pre�o Unitario:%f",novo.precoUnitario);
    printf("\n|-----------------------------------------------|");

    printf("\nDeseja Realmente alterar?");
    printf("\n|1-Sim|n2-N�o\n|Op��o:");
    scanf ("%d",&s_n);

    if(s_n==1){

    printf("\nDeseja alterar o nome???");

   printf("\n|1-Sim|n2-N�o\n|Op��o:");
    scanf("%d",&s_n);

        if(s_n==1)
        recebe_nome(novo.nome);

fseek(file,sizeof(t_produto)*posicao,SEEK_SET);
fwrite(&novo,sizeof(t_produto),1,file);

    }
    printf("\n|---------------Altera��o Concluida--------------------|");
    printf("\n|-----------------Dados atuais-------------------------|");
    printf("\n|ID:%lu",novo.id);
    printf("\n|Nome:%s",novo.nome);
    printf("\n|Quantidade em estoque:%du",novo.quantidadeEstoque);
    printf("\n|Pre�o Unitario:%f",novo.precoUnitario);
    printf("\n|-----------------------------------------------|");




  }else printf("\n---------ID n�o encontrado---------");

}else printf("------------ID N�O ENCONTRADO----------");

    printf("\nFazer mais alguma altera��o???");
    printf("\n|1-Sim|n2-N�o\n|Op��o:");
    scanf ("%d",&s_n);
}while(s_n==1);



}
//------------------------FIM DA ALTERA��O--------------------

//------------------------CONSULTA----------------------------

void consProduto(FILE *file){
int tipo=2;
int opcao,s_n;
unsigned long id;
char prefixo[100];

do{
printf("\n|-----------------Menu de Consulta-----------------------|");
printf("\n|-----------Como deseja realizar a consulta?-------------|");
printf("\n|1-Consulta por id");
printf("\n|2-Consulta por prefixo");
printf("\n|3-Listar Todos os Produtos");
printf("\n|4-Voltar");
printf("\n|Op��o:");
scanf("%d",&opcao);


switch(opcao){

case 1:
do{
 printf("\n|-----------------Busca Por ID---------------------------|");
printf("\n|Forne�a o id:");
scanf("%lu",&id);
if(id!=0)
busca_ID(file,id,tipo);
else
printf("----------ID N�O ENCONTRADO--------------");

    printf("\nFazer mais alguma consulta por ID???");
    printf("\n|1-Sim|n2-N�o\n|Op��o:");
    scanf ("%d",&s_n);


}while(s_n==1);
break;


case 2:

    do{    printf("\n|---------------Busca Por Prefixo-------------------------|");
         printf("\n|Forne�a o Prefixo:");
          setbuf(stdin,NULL);
            fgets(prefixo,100,stdin);
             retira_n(prefixo);
               nome_maiusculo(prefixo);
                 busca_prefixo(file,prefixo,tipo);


    printf("\nFazer mais alguma consulta por prefixo???");
    printf("\n|1-Sim|n2-N�o\n|Op��o:");
    scanf ("%d",&s_n);

    }while(s_n==1);





case 3:
 listagem(file,tipo);

break;

}
}while(opcao!=4);
}


void delProduto(FILE *file){
unsigned long id,posicao;
int achou,s_n;
t_produto excluir;

do{
printf("\nForne�a o Id do produto que deseja excluir");
scanf("%lu",&id);

achou=0;
posicao=0;
fseek(file,0,SEEK_SET);
while(fread(&excluir,sizeof(t_produto),1,file)==1&&achou==0){

 if(id==excluir.id){
    achou=1;}else posicao++;
 }
  fseek(file,sizeof(t_produto)*posicao,SEEK_SET);
    fread(&excluir,sizeof(t_produto),1,file);
if(achou==1 && excluir.id!=0){
            printf("\n|-----------------------------------------------|");
    printf("\n|ID:%lu",excluir.id);
    printf("\n|Nome:%s",excluir.nome);
    printf("\n|Quantidade em Estoque:%d",excluir.quantidadeEstoque);
    printf("\n|Pre�o Unitario:R$%.2f",excluir.precoUnitario);
    printf("\n|-----------------------------------------------|");


    printf("\nDeseja Realmente excluir?");
    printf("\n|1-Sim|n2-N�o\n|Op��o:");
    scanf ("%d",&s_n);

    if(s_n==1){

        excluir.id=0;
        fseek(file,sizeof(t_produto)*posicao,SEEK_SET);
        fwrite(&excluir,sizeof(t_produto),1,file);

    }else printf("Nada foi excluido");
}else printf("ID N�O ENCONTRADO");
    printf("\nFazer mais alguma exclus�o???");
    printf("\n|1-Sim|n2-N�o\n|Op��o:");
    scanf ("%d",&s_n);

    }while(s_n==1);


}

void mAlteraPreco(){
int opcao,mais_menos,s_n=1,achou=0,teste;
FILE *file,*historico;
unsigned long id,posicao;
t_produto produto;
historico_preco alteracao;
float valor,aux;

file=fopen("produto.dat","rb+");
if(file==NULL){printf("\n=====ARQUIVO DE PRODUTOS VAZIO=====");
return;
}
do{printf("\n|==========MENU DE ALTERA��O DE PRE�OS==========");
printf("\n|O que deseja fazer?");
printf("\n|1-Altera o pre�o de um determinado produto|");
printf("\n|2-Altera o pre�o de todos os produtos|");
printf("\n|3-Sair|");
scanf("%d",&opcao);
if(opcao==3)
    return;
printf("\n|Deseja aumentar ou reduzir o pre�o");
printf("\n1-Aumentar|2-Reduzir");
printf("\nop��o:|");
scanf("%d",&mais_menos);

switch(opcao){

case 1:
do{    printf("\n|Forne�a o id do produto que deseja alterar:");
        scanf("%lu",&id);
  fseek(file,0,SEEK_SET);
  posicao=0;
  while(fread(&produto,sizeof(t_produto),1,file)==1&&achou==0){
    if(id==produto.id){
      achou=1;
      break;
    }else posicao++;

  }

  if(achou==1){printf("\n|Deseja alterar o valor em quantos porcento??");
  scanf("%f",&valor);
   if(mais_menos==1){
          aux=produto.precoUnitario*valor/100;
       produto.precoUnitario=produto.precoUnitario+aux;
   }else{
       aux=produto.precoUnitario*valor/100;
       produto.precoUnitario=produto.precoUnitario-aux;
   }
   alteracao.valor=produto.precoUnitario;
      fseek(file,sizeof(t_produto)*posicao,SEEK_SET);
    fwrite(&produto,sizeof(t_produto),1,file);

historico=fopen("HistoricoPreco.dat","rb+");
if(historico==NULL)
historico=fopen("HistoricoPreco.dat","wb+");
if(historico==NULL){
fclose(historico);
return;}

  data_sistema(alteracao.dataAlteracao);
printf("\n|Data do sistema:%s",alteracao.dataAlteracao);
printf("\n|Deseja manter a data do sistema?");
printf("\n1-Sim|2-N�o");
printf("\nOp��o:|");
scanf("%d",&s_n);
if(s_n!=1){
do{teste=recebe_data(alteracao.dataAlteracao);
if(teste==0){
    printf("\n====Data Invalida====");
}

}while(teste==0);
}
alteracao.idProduto=id;

fseek(historico,0,SEEK_END);
fwrite(&alteracao,sizeof(historico_preco),1,historico);

printf("\n======ALTERA��O CONCLUIDA=========\nRETORNANDO AO MENU PRINCPAL...");
fclose(historico);
fclose(file);
return;



  }else
  printf("\n========ID invalida========");

   }while(achou==0);


break;

case 2:
historico=fopen("HistoricoPreco.dat","rb+");
if(historico==NULL)
historico=fopen("HistoricoPreco.dat","wb+");
if(historico==NULL){
fclose(historico);
return;}

printf("\n|Deseja alterar o valor em quantos porcento??");
  scanf("%f",&valor);
  data_sistema(alteracao.dataAlteracao);
printf("\n|Data do sistema:%s",alteracao.dataAlteracao);
printf("\n|Deseja manter a data do sistema?");
printf("\n1-Sim|2-N�o");
printf("\nOp��o:|");
scanf("%d",&s_n);
if(s_n!=1){
do{teste=recebe_data(alteracao.dataAlteracao);
if(teste==0){
    printf("\n====Data Invalida====");
}

}while(teste==0);
}
posicao=0;
fseek(file,0,SEEK_SET);
while(fread(&produto,sizeof(t_produto),1,file)==1){
if(produto.id!=0){
   if(mais_menos==1){
          aux=produto.precoUnitario*valor/100;
       produto.precoUnitario=produto.precoUnitario+aux;
   }else{
       aux=produto.precoUnitario*valor/100;
       produto.precoUnitario=produto.precoUnitario-aux;
   }
   alteracao.valor=produto.precoUnitario;
   //alterando o pre�o de cada produto em determinada %
      fseek(file,sizeof(t_produto)*posicao,SEEK_SET);
    fwrite(&produto,sizeof(t_produto),1,file);

  alteracao.idProduto=produto.id;
fseek(historico,0,SEEK_END);
fwrite(&alteracao,sizeof(historico_preco),1,historico);
printf("\nTESTE");
}
posicao ++;
fseek(file,sizeof(t_produto)*posicao,SEEK_SET);
}
printf("\n======ALTERA��O CONCLUIDA=========\nRETORNANDO AO MENU PRINCPAL...");
fclose(historico);
fclose(file);
return;



    break;
default:
    printf("\nForne�a uma op��o valida");
    break;
}




}while(opcao==1 || opcao==2);






}
