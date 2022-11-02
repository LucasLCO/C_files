#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aluno{
       char CPF[13];                    
       char nome[80];                 
       int numaula;                   
}aluno;

typedef struct luta{
       int regaula;                   
       int qaluno;                   
       char modalidade[20];      
       int grau;                           
       float valor;                          
}luta;
 
void aloca_al(aluno **al, int cont);
void aloca_lu(luta **lu, int cont);
void cadastra_lu(luta *lu);
void cadastra_al(luta *lu, aluno *al, int cont);
int confere_luta(luta *lu);
void mostra_lu(luta *lu);
void encerra(luta *lu, aluno *al, int cont);
int busca_vago(aluno *al, int cont);


int main(void){
	aluno *al = NULL;
	luta *lu = NULL;
	int op, vago, cont=0;
	aloca_lu(&lu,3);
	cadastra_lu(lu);
	do{
		printf("\n[1]Matricula\n[2]Encerra Matricula\n[3]FIM\n: ");
		scanf("%i",&op);
		fflush(stdin);
		switch(op){
			case 1:
			vago = busca_vago(al, cont);
			if(vago == -1){
				aloca_al(&al, cont+1);
				cont++;
			}
			cadastra_al(lu,al,cont);

				break;
			case 2:
			encerra(lu, al, cont);
				break;
		}
	}while(op!=3);

}


void aloca_al(aluno **al, int cont){
	if((*al=(aluno *)realloc(*al,cont*sizeof(aluno)))==NULL)
		exit(1);
}

void aloca_lu(luta **lu, int cont){
	if((*lu=(luta *)realloc(*lu,cont*sizeof(luta)))==NULL)
		exit(1);
}

int confere_luta(luta *lu){
	char modalidade[50];
	int i, grau;
	printf("\nModalidade: ");
	gets(modalidade);
	fflush(stdin);
	printf("\nGrau: ");
	scanf("%i",&grau);
	fflush(stdin);
	for(i=0;i<3;i++,lu++){
		if((strcasecmp(lu->modalidade,modalidade))==0 && lu->grau==grau)
			return (lu->regaula);
	}
	return -1;
}

void cadastra_lu(luta *lu){
	strcpy(lu->modalidade,"JIU-JITSU");
	lu->grau=1;
	lu->regaula=0;
	lu->valor=100;
	lu->qaluno=0;
	lu++;
	strcpy(lu->modalidade,"BOXE");
	lu->grau=2;
	lu->regaula=1;
	lu->valor=200;
	lu->qaluno=0;
	lu++;strcpy(lu->modalidade,"JUDO");
	lu->grau=3;
	lu->regaula=2;
	lu->valor=300;
	lu->qaluno=0;
}

void cadastra_al(luta *lu, aluno *al, int cont){
	al+=cont-1;
	printf("\nNome: ");
	gets(al->nome);
	fflush(stdin);
	printf("\nCPF: ");
	gets(al->CPF);
	fflush(stdin);
	mostra_lu(lu);
	if((al->numaula=confere_luta(lu))==-1)
		printf("Carro escolhido nao existe");
	fflush(stdin);
	lu+=al->numaula;
	lu->qaluno++;
}

void mostra_lu(luta *lu){
	int i;
	printf("\nAulas Disponiveis:");
	printf("\nAula\tModalidade\tGrau\tQuantidade\tValor\n");
	for(i=0;i<3;i++,lu++)
		printf("%i\t%s\t%c\t%i\tR$%.2f\n",lu->regaula,lu->modalidade,lu->grau,lu->qaluno,lu->valor);

}

void encerra(luta *lu, aluno *al, int cont){
	int i;
	char cpf[13];
	printf("CPF: ");
	gets(cpf);
	fflush(stdin);
	for(i=0; i<cont; i++){
		if((strcmp(al->CPF,cpf))==0){
			lu+=al->numaula;
			printf("\nNome: %s\nCPF: %s\nNumero Aula: %i",al->nome,al->CPF,al->numaula);
			printf("\nModalidade: %s\nGrau:%i \nValor: R$%.2f",lu->modalidade,lu->grau,lu->valor);
			al->numaula=-1;
			lu->qaluno--;
		}
	}
}	

int busca_vago(aluno *al, int cont){
	int i;
	for(i=0; i<cont; i++,al++){
		if(al->numaula==-1)
			return i;
	}
	return -1;

}