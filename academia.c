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
 
void aloca_l(luta **pl, int cont);
void cadastra_l(luta *pl);
void aloca_a(aluno **pa, int cont);
void cadastra_a(aluno *pa, luta *pl);
void enc(aluno *pa, luta *pl, int cont);
int busca_vago(aluno *cl,int cont);
 
void main(){
	int op, cont=0, vago;
	luta *pl=NULL;
	aluno *pa=NULL;
	aloca_l(&pl, 3);
	cadastra_l(pl);
	do{
		system("cls");
		printf("[1]Matricula\n[2]Encerra Matricula\n[3]Fim\nOpcao: ");
		scanf("%i", &op);
		fflush(stdin);
		switch(op)
		{
			case 1:
				vago = busca_vago(pa,cont);
				if(vago == -1){	
					aloca_a(&pa,cont+1);
					cont++;
				}
				cadastra_a(pa,pl);
				cont++;
				break;
			case 2:
				enc(pa, pl, cont);
				printf("\nMatricula Encerrada com Sucesso\n\n");
				system("pause");
				break;
		}
	}while(op!=3);
}

void aloca_l(luta **pl, int cont){
	if((*pl=(luta*)realloc(*pl, cont*sizeof(luta)))==NULL)
		exit(1);
}

void cadastra_l(luta *pl){
	int i;
	pl->qaluno=0;
	strcpy(pl->modalidade, "Jiu-Jitsu");
	pl->valor=50;
	pl->grau=1;
	pl->regaula=1;
	pl++;
	pl->qaluno=0;
	strcpy(pl->modalidade, "MMA");
	pl->valor=75.50;
	pl->grau=2;
	pl->regaula=2;
	pl++;			
	pl->qaluno=0;
	strcpy(pl->modalidade, "Boxe");
	pl->valor=100;
	pl->grau=3;
	pl->regaula=3;
}

void aloca_a(aluno **pa, int cont){
	if((*pa=(aluno*)realloc(*pa, cont*sizeof(aluno)))==NULL)
		exit(1);
} 

void cadastra_a(aluno *pa, luta *pl){
	int i;
	for(i=0; i<3; i++, pl++)
	{
		printf("\nModalidade: %s\n Numreg: %d\n Alunos: %d\n Valor: %.2f\n", pl->modalidade, pl->regaula, pl->qaluno, pl->valor);
	}
	for(i=0; i<3; i++, pl--)
		printf("");
	printf("\nDigite o cpf do aluno: ");
	gets(pa->CPF);
	fflush(stdin);
	printf("\nDigite seu nome: ");
	gets(pa->nome);
	fflush(stdin);
	printf("\nDigite o numero do registro de aula: ");
	scanf("%d", &(pa->numaula));
	fflush(stdin);
	pa+=pa->numaula-1;
	pl->qaluno++;
} 
void enc(aluno *pa, luta *pl, int cont){
	int i;
	char cpf[13];
	printf("\nDigite seu cpf: ");
	gets(cpf);
	fflush(stdin);
	for(i=0; i<cont; i++, pa++){
		if((strcmp(pa->CPF, cpf))==0){
			pl+=pa->numaula-1;
			printf("\nCPF: %s\nNome: %s\nNumero de Aula: %d", pa->CPF, pa->nome, pa->numaula);
			printf("\nModalidade: %s\n", pl->modalidade);
			printf("Valor: %.2f", pl->valor);
			pl->qaluno--;
			pa->numaula=-1;
		}
	} 
}

int busca_vago(aluno*pa,int cont){
	int i;
	for(i=0; i<cont; i++){
		if(pa->numaula == -1)
			return i;
	}

	return -1;

}///ta bugado