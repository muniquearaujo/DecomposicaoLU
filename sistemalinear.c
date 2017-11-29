#include<stdio.h>
#include<stdlib.h>
			
FILE *fp,*fi;

//Função Imprime
void imprime(double **M, int dim)
{
	int i,j;
	for(i=0;i<dim;i++)
	{
		for(j=0;j<(dim+1);j++)
		{
			printf("%lf\t", M[i][j]);
		}
		printf("\n");
	}
}
//Função Pivoteamento
int pivot(double **M, int dim)
{
	int i,j,k,aux,t=0;
	
	for(j=0;j<(dim+1);j++)				
	{
		for(i=j;i<dim;i++)
		{
			if(M[i][i]<M[i][j])
			{
				for(k=0;k<(dim+1);k++)
				{
					aux=M[i][k];
					M[i][k]=M[j][k];
					M[j][k]=aux;
				}
				t++;
				i++;
			}
		}
	}			
			
	printf("\n\nMatriz com Pivoteamento:\n");
	imprime(M,dim);
	return(t);
}

//Função de Triangularização
void zera(double **M, int dim)
{
	int i,j,k;
	double num;
	
	for(j=0;j<(dim+1);j++)
	{
		for(i=0;i<dim; i++)
		{
			if(i>j)
			{
				num=-(M[i][j]/M[j][j]);
				for(k=0;k<(dim+1);k++)
				{
					M[i][k]=num*M[j][k]+M[i][k];
				}
			}
		}
	}	
	printf("\n\nMatriz Triangular Superior:\n");
	imprime(M,dim);	
	
}

//Função para fazer a substituição reversa

void solucao(double **M, int dim)
{
	double x[dim], soma=0.0;
	int i,j;

	x[dim-1]=M[dim-1][(dim+1)-1]/M[dim-1][(dim+1)-2];
	
	for(i=dim-2;i>=0;i--)
	{
		soma=0;
		for(j=i+1;j<dim;j++)
		{
			soma=soma+M[i][j]*x[j];
		}
		x[i]=(M[i][dim]-soma)/M[i][i];
	}
	
	//Impressão dos valores na tela
	printf("\nA solução do sistema será:\n");
	for(i=0;i<dim;i++)
	{
		printf("x%d",i+1);
		printf(":%lf\n", x[i]);
	}
	
}

//Função para o cálculo do Determinante
void determinante(double **M, int dim, int n)
{
	double v,prod=1.0, soma=0.0;
	int i,j;
	for(i=0;i<dim;i++)
	{
		for(j=0;j<(dim+1);j++)
		{
			if(i==j)
			{
				//se número de troca positivo
				if(n%2==0)
				{
					v=M[i][j];
					prod=prod*v;
				}
				//se número de troca negativo
				else
				{
					v=-M[i][j];
					prod=prod*v;
				}
			}
		}
	}
	printf("\nO Valor de Determinante é:%lf\n", prod);
}

//Decomposição LU
int dLU(double **M, int dim)
{   
	//declaração
	int i,j,k, cont=0;
	double **L, **U, s1=0.0, s2=0.0;
	
	//alocação 
	L = malloc( dim*sizeof(double*));
	U = malloc( dim*sizeof(double*));
	
	//preenchendo a primeira linha de L da primeira coluna 
	for(i=0;i<dim;i++)
    	{ 
		L[i] = malloc((dim)*sizeof(double));	
		L[i][0] = M[i][0]; 
    	}
    	
    	//preenchendo a matriz U
    	i=0;
    	for(j=0;j<dim;j++)
    	{   
        	U[i] = malloc((dim)*sizeof(double)); 
        	
        	if(i==j)
    		{  
    			U[i][j] = 1.0;
    	   		i++;
    		}
    		
    		//cada coluna com a linha fixa recebe essa valor:
        	U[0][j] = M[0][j]/L[0][0];
        	cont++;
        
    	}
    	//começando da segunda linha e segunda coluna, já que a primeira ja está preenchida.
    	for(i=1;i<dim;i++)
    	{     
    	  	for(j=1;j<dim;j++)
    	  	{		 
    	        
    	        	for(k=0;k<j-1;k++)
    	        	{   
    	        		
    	        		s1+= U[k][i]*L[i][k];
    	            		cont+=2;
    	        	}
    	        	
    	        	L[i][j] = M[i][j] - s1;
    	        	cont++;
    	  	}
    	  	for(j=i+1;j<dim-1;j++)
    	  	{     
    	      		for(k=0;k<i-1;i++)
    	      		{
    	      			s2+= U[k][j]*L[i][k]; 
    	           		cont=+2;
    	      
    	    		} 
    	    		
	      		U[i][j] = (M[i][j] - s2)/L[i][i];  
    	      		cont++;
    	  	}
   	}
   	
   	printf("\nImpressão da matriz L:\n ");
   	imprime(L,dim);
   	
   	printf("\nImpressão da matriz U:\n ");
   	imprime(U,dim);
   	
   	return(cont);   	                     
}				
int main(int argc, char **argv)
{
	int i, j,k, num, t, dim, interacao;
	double **M,a;
	
	//Abrindo arquivo para escrita
	fp=fopen(argv[1], "r"); 
	fi=fopen(argv[2],"a");
	
	i=fscanf(fp, "%d", &dim);
	
	M=malloc(dim*sizeof(double*));
	
	for(i=0;i<dim;i++)
	{
		M[i]=malloc((dim+1)*sizeof(double));
	}	
	i=j=0;
	while(fscanf(fp,"%lf", &a)!=EOF)
	{
		M[i][j]=a;
		j++;
		if(j==dim+1)
		{
			j=0;
			i++;
		}
	}
	
	printf("\nImpressão da Matriz:\n");
	//chamando a função
	imprime(M,dim);
	
	//chamando a função
	t=pivot(M,dim);
	printf("\nNúmero de trocas:%d\n\n", t);
	
	//chamando a função
	zera(M,dim);
	
	//chamando a função
	solucao(M, dim);
	
	//chamando a função
	determinante(M, dim, t);
	
	//chamando a função
	interacao=dLU(M,dim);
	printf("Número de interações para dimensão %d: %d\n",dim, interacao);
	
	//arquivo para fazer o gráfico
	fprintf(fi,"%d\t%d\n",dim,interacao);
	
	fclose(fp);
}
