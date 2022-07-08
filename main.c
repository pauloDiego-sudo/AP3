#include <stdio.h>
#include <string.h>
#include <time.h>
//Autor: Paulo Diego De Meneses

void limpa_linha(void){
  int i, c=50;
  printf("\r");
  for(i=0;i<c;i++){
    printf(" ");
  }
  printf("\r");
}
void carregamento(void){ //função da tela de carregamento, aparece se o arquivo não existir :)
  int i, j,c=50;
  system("clear");//limpa tela
  printf("\nInstalando o programa: \n"); //desculpa para criar o arquivo :v (o usuário não precisa saber disso)      
  for(i=0;i<=100;i++){
    printf ("%d%% ",i);      
    fflush (stdout);
    for(j=0;j<i%10;j++){
        printf(".");
     }
    fflush(stdout);
    usleep(50000);
    limpa_linha();                    
  }
 printf("\n\n Programa instalado! \n Rode o programa novamente!\n\n");       
}

int main(void) {
 FILE *arq;
  typedef struct{ //cada produto tem um nome e uma quantidade
    char nome[32];
    int qtd;
  } produto;
  char aux[32], txt[100]; //variáveis auxiliares para ler o arquivo
  arq = fopen("arq.txt","r");
  if(arq == NULL){ //verifica a existência do arquivo
    //printf("Instalando o programa! \n");
    arq= fopen("arq.txt","w"); //se não existe então ele cria
    if(arq != NULL){
      carregamento();
      fclose(arq);
    }
  }
  else{
    int i=0,j,n,m,l,opc=-1;
    produto p,pp;
    while(opc!=0){
      printf("Escolha uma opção: \n 1-Cadastrar produto \n 2-Listar produtos \n 3-Ver um produto \n 4-Alterar produto \n 0-Sair Do Programa \n ");
      scanf("%d",&opc);
      switch(opc){
        case 0:
          break;
        default:
          printf("Escolha uma opção VÁLIDA \n ");
          break;
        case 1:
          arq= fopen("arq.txt","a+"); //abrindo o arquivo para adição e leitura
          char a[32],flag,flag2; //variáveis auxiliares de controle
          produto pr; 
          int parar = 1; //variável flag para indicar a parada do cadastro
          while(parar != 0){
          printf("Digite o nome do produto: ");
          scanf("%s", pr.nome);
          rewind(arq); //volta para o começo do arquivo
          do{ //confere se o produto já existe
           fscanf(arq,"%s",a);
            if( strcmp(pr.nome,a)==0){
              printf("Produto já cadastrado! \n");
              parar = 0; //se existir, ele retorna 0 como flag
            break;
            }
            else if((flag=getc(arq)) == EOF){ //caso o produto não exista, ele chega ao final do arquivo
              flag=EOF;
            } 

          } while( fgets(txt,100,arq) != NULL );
          if(parar != 0){ //caso o produto não exista
            printf("Digite a quantidade do produto: ");
            scanf("%d", &pr.qtd);
            if(flag==EOF){ //o ultimo produto no final do arquivo ele sempre vai deixar uma linha a mais apenas para conveniencia do código
              fprintf(arq,"%s %d\n",pr.nome,pr.qtd);
             }
            else{ //os outros acima irão deixar uma linha antes
              fprintf(arq,"\n%s %d",pr.nome,pr.qtd);
             }
            }
          else if(parar ==0){ //caso o produto exista, ele para o cadastro
              break;
            }
            printf("Deseja cadastrar outro produto? (0 para não) : "); //pergunta se quer cadastrar outro produto
            scanf("%d",&parar);
        }
        fclose(arq);
        break;
        case 2: //lista todos os produtos
          arq = fopen("arq.txt","r"); //abre para leitura
          produto pa; //variável produto auxiliar
          do{
            fscanf(arq,"%s",pa.nome);
            fscanf(arq,"%d",&pa.qtd);

            printf("Nome: %s \n Quantidade: %d \n",pa.nome,pa.qtd);
            printf("\n");

          }while(fgets(txt,100,arq) != NULL);
         fclose(arq);
        break;
        case 3: //pega o produto e o valor que quero checar
          arq = fopen("arq.txt","r"); 
          int fl=0;
          printf("Qual produto checar? \n");
          scanf("%s",p.nome);
          do{
           fscanf(arq,"%s %d",aux,&p.qtd);
            if( strcmp(p.nome,aux)==0){
              fl=0;
            break;
            }
            else{fl=1;}
          } while( fgets(txt,100,arq) != NULL );
          if(fl==0){
            printf("Produto: %s \nQuantidade: %d \n ",p.nome,p.qtd);
          }
          else{
            printf("\nProduto não cadastrado! tente novamente \n");
          }
          fclose(arq);
        break;
        case 4: //muda a quantidade de um produto
          arq = fopen("arq.txt","r");
          int linha=0,linhas=-1,f=0;
          printf("Qual produto deseja mudar? \n");
          scanf("%s",p.nome);
          do{ //armazena a linha onde está o produto que quero mudar
           fscanf(arq,"%s",aux);
            linha++;
            if( strcmp(p.nome,aux) ==0){
              f=0;
            break;
            }
            else{ f=1;}
          } while( fgets(txt,100,arq) != NULL );
          rewind(arq); //volta para o começo do arquivo
          
          do{ //conta a quantidade de linhas do arquivo
            linhas++;
          } while( fgets(txt,100,arq) != NULL );
          rewind(arq); //volta para o começo
          
          int k=0,ax=0; //variáveis de controle
          produto product[linhas]; //cria um vetor com os produtos no arquivo
        if(f==0){
          printf("Nova Quantidade: \n ");
          scanf("%d",&p.qtd);
          do{ //armazena os produtos no vetor
            fscanf(arq,"%s %d",product[k].nome,&product[k].qtd);
            k++;
          } while( fgets(txt,100,arq) != NULL );
          rewind(arq);
          
          arq = fopen("arq.txt","w");
          for(ax=0;ax<linhas;ax++){ //escreve no arquivo com o valor do produto trocado
            if(ax==linha-1){ //garante que ele coloca o produto na posição certa
              fprintf(arq,"%s %d\n",p.nome,p.qtd);
            }
            else{
               fprintf(arq,"%s %d\n",product[ax].nome,product[ax].qtd);
            }
            }
          }
          else{printf("\nProduto não cadastrado!\n");}
          fclose(arq);
          break;
        }
      }
  }
  return 0;
}
