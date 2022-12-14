#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

typedef struct cliente{
	char CPF[13];
	char nome[80];
	int numcar;
}cliente;

typedef struct carro{
	int regcar;
	int qcarro;
	char modelo;
	char marca[20];
	float valor;
}carro;


void realoca_cl(cliente **cl, int cont);
void realoca_ca(carro **ca, int cont);
int carro_confere(carro *ca);
void cadastra_cl(cliente *cl, carro *ca, int cont);
void cadastra_carro(carro *ca);
void rev(cliente *cl, carro *ca,int cont);
void mostra(carro *ca);
int busca_vago(cliente *cl,int cont);


int main(void){
	cliente *cl = NULL;
	carro *ca = NULL;
	int op, cont = 0, vazio = 0;
	realoca_ca(&ca, 3);
	cadastra_carro(ca);
	do{
		printf("\n[1]Cadastro Cliente\n[2]Encerrar Revisao\n[3]Fim\n: ");
		scanf("%i",&op);
		fflush(stdin);
		switch(op){
			case 1:
				vazio = busca_vago(cl,cont);
				if(vazio == -1){	
					realoca_cl(&cl,cont+1);
					cont++;
				}
				cadastra_cl(cl,ca,cont);
				break;
				
			case 2:
				rev(cl,ca,cont);
				break;
		}
		
	}while(op != 3);	
}


void realoca_cl(cliente **cl, int cont){
	if((*cl = (cliente *)realloc(*cl, cont * sizeof(cliente)))==NULL)
		exit(1);
}


void realoca_ca(carro **ca, int cont){
	if((*ca = (carro *)realloc(*ca, cont * sizeof(carro)))==NULL)
		exit(1);
}


int carro_confere(carro *ca){
	char marca[50], modelo;
	int i;
	printf("\nMarca: ");
	gets(marca);
	fflush(stdin);
	printf("\nModelo: ");
	scanf("%c",&modelo);
	fflush(stdin);
	modelo = toupper(modelo);
	for(i=0;i<3;i++,ca++){
		if((strcasecmp(ca->marca,marca))==0 && ca->modelo==modelo)
			return (ca->regcar);
	}
	return -1;
}


void cadastra_cl(cliente *cl, carro *ca, int cont){
	cl += cont-1;
	printf("\nCPF: ");
	gets(cl->CPF);
	fflush(stdin);
	printf("\nNome: ");
	gets(cl->nome);
	fflush(stdin);
	mostra(ca);
	if((cl->numcar=carro_confere(ca))==-1)
		printf("Carro escolhido nao existe");
	ca+=cl->numcar;
	ca->qcarro++;
}


void cadastra_carro(carro *ca){
	strcpy(ca->marca,"HONDA");
	ca->regcar = 0;
	ca->valor = 200;
	ca->modelo = 'M';
	ca->qcarro = 0;
	ca++;
	strcpy(ca->marca,"FIAT");
	ca->regcar = 1;
	ca->valor = 400;
	ca->modelo = 'G';
	ca->qcarro = 0;
	ca++;
	strcpy(ca->marca,"BMW");
	ca->regcar = 2;
	ca->valor = 600;
	ca->modelo = 'P';
	ca->qcarro = 0;
}


void rev(cliente *cl, carro *ca,int cont){
	char cpf[13];
	int i, j;
	printf("\nDigite o CPF: ");
	gets(cpf);
	for(i=0; i<cont; i++, cl++){
		if((strcmp(cl->CPF,cpf))==0){
			ca+=cl->numcar;	
			printf("\nNome: %s\nCPF: %s",cl->nome,cl->CPF);
			printf("\nMarca: %s\nModelo: %c\nreg: %i",ca->marca,ca->modelo,cl->numcar);
			printf("\nPreco: R$%.2f", ca->valor);
			printf("\n----------Finalizado-----------");
			cl->numcar=-1;
			ca->qcarro-=1;
		}
	}
}


void mostra(carro *ca){
	int i;

	printf("\nCarros Disponiveis:");
	printf("\nRegistro\tMarca\t\tModelo\t\tQuantidade\tValor\n");
	for(i=0;i<3;i++,ca++)
		printf("%i\t\t%s\t\t%c\t\t%i\t\tR$%.2f\n",ca->regcar,ca->marca,ca->modelo,ca->qcarro,ca->valor);
}


int busca_vago(cliente *cl,int cont){
	int i;
	for(i=0; i<cont; i++, cl++){
		if(cl->numcar == -1)
			return i;
	}

	return -1;

}