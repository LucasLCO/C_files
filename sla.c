#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>


typedef struct cliente{
	char CPF[13];
	char nome[80];
	int regsala;
	int qtdepoltronas;
}cliente;

typedef struct sala{
	int numsala;
	char filme[50];
	int poltronas;
	float valor;
}sala;

void aloca_cliente(cliente **cl, int cont);
void aloca_sala(sala **sa, int cont);
void cadastra_cl(cliente *cl, sala *sa, int cont);
int confere_sa(sala *sa);
void cadastra_sa(sala *sa);
void mostra(sala *sa);
void rm(cliente *cl,sala *sa,int cont);
void reservados(cliente *cl,sala *sa,int cont);
int busca_vago(cliente *cl,int cont);

int main(){
	cliente *cl = NULL;
	sala *sa = NULL;
	int op, cont = 0,vazio;
	aloca_sala(&sa,3);
	cadastra_sa(sa);
	do{
		printf("\n[1]Ingresso  [2]Cancelamento  [3]Reservados  [4]Catalogo  [5]Sair\n: ");
		scanf("%i",&op);
		fflush(stdin);
		switch(op){
			case 1:
				vazio = busca_vago(cl,cont);
				if(vazio == -1)
				{
					aloca_cliente(&cl,cont+1);
					vazio = cont;
					cont++;
				}
				cadastra_cl(cl+vazio,sa,cont);
				break;
			case 2:
				rm(cl,sa, cont);
				break;
			case 3:
				reservados(cl,sa,cont);
				break;
			case 4:
				mostra(sa);
				break;
		}		
	}while(op!=5);
	return 0;
}

void aloca_cliente(cliente **cl, int cont){
	if((*cl=(cliente*)realloc(*cl,sizeof(cliente)*cont))==NULL)
		exit(1);
}

void aloca_sala(sala **sa, int cont){
	if((*sa=(sala*)realloc(*sa,sizeof(sala)*cont))==NULL)
		exit(1);
}

void cadastra_sa(sala *sa){
		sa->numsala = 1;
		strcpy(sa->filme,"BATMAN");
		sa->poltronas = 30;
		sa->valor = 50;
		sa++;
		sa->numsala = 2;
		strcpy(sa->filme,"COCO");
		sa->poltronas = 30;
		sa->valor = 50;
		sa++;
		sa->numsala = 3;
		strcpy(sa->filme,"AVENGERS");
		sa->poltronas = 30;
		sa->valor = 50;
}

void mostra(sala *sa){
	int i;
	for(i=0;i<3;i++,sa++)
		printf("Sala: %i\nFilme: %s\nPoltronas: %i\nValor R$%.2f\n\n",sa->numsala,sa->filme,sa->poltronas,sa->valor);
}

int confere_sa(sala *sa){
	char filme[50];
	int i;
	printf("\nFilme: ");
	gets(filme);
	for(i=0;i<3;i++,sa++){
		if((strcasecmp(sa->filme,filme))==0)
			return sa->numsala;
	}
	return -1;
}

void cadastra_cl(cliente *cl, sala *sa, int cont){
	cl+=cont-1;
	printf("\nNome: ");
	gets(cl->nome);
	fflush(stdin);
	printf("\nCPF: ");
	gets(cl->CPF);
	fflush(stdin);
	mostra(sa);
	fflush(stdin);
	do{
		if((cl->regsala=confere_sa(sa))==-1)
			printf("\nErro de Reserva");
		printf("\nQtde Poltronas: ");
		scanf("%i",&(cl->qtdepoltronas));
}while(cl->regsala==-1 && cl->qtdepoltronas>30);
	sa+=cl->regsala-1;
	sa->poltronas-=cl->qtdepoltronas;
	printf("\nCadastro Realizado Com Sucesso!");

}

void rm(cliente *cl,sala *sa, int cont){
	char cpf[13];
	int i;
	printf("\nCPF: ");
	gets(cpf);
	fflush(stdin);
	for(i=0;i<cont;i++,cl++){
		if((strcmp(cl->CPF,cpf))==0){
			sa+=cl->regsala-1;
			cl->regsala=-1;
			sa->poltronas+=cl->qtdepoltronas;
			printf("\nNOME [%s]",cl->nome);
			printf("\nCPF [%s]",cl->CPF);
			printf("\nREGISTRO [%i]",sa->numsala);
			printf("\nFILME: [%s]",sa->filme);
			printf("\nNUMERO DE POLTRONAS [%i]",sa->poltronas);
			printf("\nVALOR A SER PAGO [%.2f]",(float)(sa->valor)*cl->qtdepoltronas);
			printf("\n%s Removido com sucesso.",cl->nome);
		}
	}
}

void reservados(cliente *cl,sala *sa,int cont){
	int i;
	for(i=0;i<cont;i++,cl++){
		if(cl->regsala!=1){
			sa+=cl->regsala-1;
			printf("\nNOME [%s]",cl->nome);
			printf("\nCPF [%s]",cl->CPF);
			printf("\nREGISTRO [%i]",sa->numsala);
			printf("\nFILME: [%s]",sa->filme);
			printf("\nNUMERO DE POLTRONAS [%i]",sa->poltronas);
		}
	}
}


int busca_vago(cliente *cl,int cont){
	int i;
	for(i=0; i<cont; i++, cl++){
		if(cl->regsala == -1)
			return i;
	}

	return -1;

}