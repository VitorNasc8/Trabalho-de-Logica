#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "funcoesGerais.h"
#include "entradas.h"
#include "nomearquivos.h"
#include "validacoes.h"
#include "fornecedor.h"
#include "menuFornecedor.h"

void mFornecedor(){
    setlocale(LC_ALL,"pt-BR");
    int sair;
    FILE *f;
    if(abrirArquivo(ARQ_FORNECEDOR,&f)){

        do{
             menuInicial("Fornecedores");
             scanf ("%d",&sair);


            switch(sair){

            case 1:
                cadastrarFornecedor(f);
            break;
            case 2:
                if(registroValidosFornecedor(f))
                    alteraFornecedor(f);
                else
                    printf("\nNenhum fornecedor cadastrado!");
            break;
            case 3:
                if(registroValidosFornecedor(f))
                   consultaFornecedor(f);
                else
                    printf("\nNenhum fornecedor cadastrado!");
            break;
            case 4:
                menuExcluirFornecedor(f);
            break;

            }
        }while(sair!=5);
        fclose(f);

    }else
        printf("\nImpossivel abrir o arquivo");

}

void cadastrarFornecedor(FILE *f){

    TFornecedor fornecedor = novoFornecedor();
    if(!fornecedor){
        printf("\nImpossivel alocar mem�ria");
        return;
    }
    char cnpj[15],nome[100],email[50],telefone[15];
    int s_n,teste,repetido;
    unsigned long id;

    do{

        printf("\n-----------------Menu de Cadastro de Fornecedor-----------------------");
        printf("\nForne�a os campos solicitados para o cadastro:");

        id = novoIdFornecedor(f);
        printf("\nID Fornecedor: %lu",id);
        do{
            recebeCnpj(cnpj);
            teste = validaCnpj(cnpj);
            if(!teste)
                printf("\n===========CNPJ INVALIDO=============");
            else{
                repetido = buscaCnpjFornecedor(cnpj,f);
                if(repetido!=-1)
                    printf("\nEste CNPJ j� est� cadastrado");
            }
        }while(!teste || repetido!=-1);

        do{
          recebeNome(nome);
          padronizaString(nome);
          repetido = buscaNomeFornecedor(nome,f);
          if(repetido!=-1)
            printf("\nEste Nome j� est� cadastrado!");
        }while(repetido!=-1);
            recebeEmail(email);
            padronizaString(email);
            recebeTelefone(telefone);

        inicializarFornecedor(fornecedor,id,nome,cnpj,email,telefone);
        inserirFornecedorNaPosicao(fornecedor,f,id-1);

        printf("\nCadastro realizado com sucesso");
        printf("\nDeseja cadastrar outro Fornecedor?\n1-Sim | 2-N�o: ");
        scanf("%d",&s_n);
    }while(s_n==1);
    liberaFornecedor(fornecedor);

}
void alteraFornecedor(FILE *f){
    unsigned long id,posicao;
    char aux[100];
    int s_n,teste;


    TFornecedor fornecedor = novoFornecedor();
    if(!fornecedor){
        printf("\nN�o foi possivel alocar mem�ria!");
        return;
    }

    do{

        printf("\n-----------------Menu de Altera��o de Fornecedor-----------------------");
        id = recebeId();
        if(id>0){
            posicao = buscaIdFornecedor(id,f);
            if(posicao!=-1){

                atribuirDadosFornecedor(fornecedor,posicao,f);
                printf("\n|-----------------Dados atuais-------------------------|");
                printaDadosFornecedor(fornecedor);
                printf("\nDeseja Realmente alterar?");
                printf("\n|1-Sim | 2-N�o: ");
                scanf ("%d",&s_n);

                if(s_n==1){

                    if(perguntaAlteracao("Nome")==1){
                        do{
                            recebeNome(aux);
                            padronizaString(aux);
                            teste = buscaNomeFornecedor(aux,f);
                            if(teste!=-1){
                                printf("\nEste Nome j� est� cadastrado!");
                                printf("\nDeseja sair da altera��o de nome?\n1-Sim | 2-N�o: ");
                                scanf("%d",&s_n);
                            }else
                                setNomeFornecedor(fornecedor,aux); 
                        }while(teste!=-1 && s_n!=1);
                    }

                    if(perguntaAlteracao("Email")==1){

                        recebeEmail(aux);
                        padronizaString(aux);
                        setEmailFornecedor(fornecedor,aux);

                    }
                    if(perguntaAlteracao("Telefone")==1){
                        recebeTelefone(aux);
                        padronizaString(aux);
                        setTelefoneFornecedor(fornecedor,aux);
                    }
                    inserirFornecedorNaPosicao(fornecedor,f,posicao);
                    printf("\n|---------------Altera��o Concluida--------------------|");
                    printf("\n|-----------------Dados atuais-------------------------|");
                    printaDadosFornecedor(fornecedor);
                }

            }else
                printf("\n---------ID n�o encontrado---------");
        }else
            printf("\n---------ID Inv�lido---------");

        printf("\nFazer mais alguma altera��o?");
        printf("\n|1-Sim|n2-N�o: ");
        scanf ("%d",&s_n);


    }while(s_n==1);
    liberaFornecedor(fornecedor);

}

void printaDadosFornecedor(TFornecedor fornecedor){
    char aux[100];
    printf("\n|-----------------------------------------------|");
    printf("\n|ID:%lu",getIdFornecedor(fornecedor));
    getNomeFornecedor(fornecedor,aux);
    printf("\n|NOME:%s",aux);
    getCnpjFornecedor(fornecedor,aux);
    printf("\n|CNPJ:%s",aux);
    getEmailFornecedor(fornecedor,aux);
    printf("\n|EMAIL:%s",aux);
    getTelefoneFornecedor(fornecedor,aux);
    printf("\n|TELEFONE:%s",aux);
    printf("\n|-----------------------------------------------|");

}

void listaTodosFornecedor(FILE *arq){
    TFornecedor busca=novoFornecedor();
    int cont=0;
    fseek(arq,0,SEEK_SET);
    while(fread(busca,tamStructFornecedor(),1,arq)==1){
        if(getIdFornecedor(busca)>0){
            printaDadosFornecedor(busca);
            cont++;
        }

    }
    if(!cont)
        printf("\nNenhum Registro encontrado");
     liberaFornecedor(busca);
}

void consultaFornecedor(FILE *f){
    int opcao;
    unsigned long id,posicao,cont;
    char cnpj[15],prefixo[100];
    TFornecedor fornecedor = novoFornecedor();
        if(!fornecedor){
            printf("\nN�o foi possivel alocar mem�ria!");
            return;
        }
    do{
        printf("\n|-----------------Menu de Consulta-----------------------|");
        printf("\n|-----------Como deseja realizar a consulta?-------------|");
        printf("\n|1-Consulta por id");
        printf("\n|2-Consulta por CNPJ ");
        printf("\n|3-Consulta por Prefixo");
        printf("\n|4-Listar todos os fornecedores");
        printf("\n|5-Voltar");
        printf("\n|Op��o:");
        scanf("%d",&opcao);
    switch (opcao){

    case 1:
            do{
                printf("\n|-----------------Busca Por ID Fornecedor---------------------------|");
                id = recebeId();
                if(id>0){
                    posicao = buscaIdFornecedor(id,f);
                    if(posicao!=-1){
                        atribuirDadosFornecedor(fornecedor,posicao,f);
                        printaDadosFornecedor(fornecedor);
                    }else
                        printf("\nID N�o Encontrado");
                }
                else
                    printf("\nID Inv�lido!");
            }while(perguntaBusca("ID")==1);

        break;
        case 2:


            do{
                printf("\n|-----------------Busca Por CNPJ---------------------------|");
                recebeCnpj(cnpj);
                if(validaCnpj(cnpj)){
                    posicao = buscaCnpjFornecedor(cnpj,f);
                    if(posicao!=-1){
                        atribuirDadosFornecedor(fornecedor,posicao,f);
                        printaDadosFornecedor(fornecedor);
                    }else
                        printf("\nCNPJ N�o Encontrado!");

                }else
                    printf("\nCNPJ Inv�lido!");
            }while(perguntaBusca("CNPJ")==1);
        break;

        case 3:

            do{
                printf("\n|---------------Busca Por Prefixo-------------------------|");
                recebePrefixo(prefixo);
                padronizaString(prefixo);
                posicao = -1;
                cont = 0;
                do{
                    posicao = buscaPrefixoFornecedor(prefixo,f,posicao + 1);

                    if(posicao!=-1){
                        atribuirDadosFornecedor(fornecedor,posicao,f);
                        printaDadosFornecedor(fornecedor);
                        cont++;
                    }
                }while(posicao!=-1);
                if(!cont)
                    printf("\nNenhum registro encontrado com esse prefixo!");
            }while(perguntaBusca("Prefixo")==1);
        break;


        case 4:
         listaTodosFornecedor(f);


        break;
        case 5:
        break;
    }

    }while(opcao!=5);

    liberaFornecedor(fornecedor);

}

void menuExcluirFornecedor(FILE *f){
   unsigned long id,posicao;
   TFornecedor fornecedor = novoFornecedor();
    if(!fornecedor){
        printf("\nN�o foi possivel alocar mem�ria!");
        return;
    }
    do{
        if(registroValidosFornecedor(f)){
            printf("\n-----------------Menu de Exclus�o de Fornecedor-----------------------");
            id = recebeId();
            if(id>0){
                posicao = buscaIdFornecedor(id,f);
                if(posicao!=-1){
                    atribuirDadosFornecedor(fornecedor,posicao,f);
                    printaDadosFornecedor(fornecedor);
                    if(confirmaExclusao("fornecedor")==1){
                        excluirFornecedor(fornecedor,f,posicao);
                        printf("\nFornecedor Excluido com sucesso!");
                    }else
                        printf("\nNada foi excluido!");

                }else
                    printf("\nNenhum registro encontrado com esse ID!");
            }else
                printf("\nID Inv�lido!");
        }else{
            printf("Nenhum fornecedor cadastrado!");
            liberaFornecedor(fornecedor);
            return;
        }


    }while(perguntaExclusao()==1);
    liberaFornecedor(fornecedor);
}
