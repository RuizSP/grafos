//Algoritmo para encontrar centro, anticentro, mediana, somatório, máximo e minimo de um grafo direcionado
//O programa utiliza o algoritmo de dijkstra para encontrar o menor caminho entre cada vertice
//O algoritmo de dijkstra foi feito com base nessa implementação: https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/
//Adapatada para aceitar uma entrada qualquer entrada de forma dinamica e retornar um vetor com a distancia de um vertice de referencia e cada um dos outros vertices 

#include <iostream>
#include <fstream>
#include <climits>

using namespace std;
ifstream file;

// Funções de impressão:
void imprimiVet(int * vet, int tamanho){
    for(int i=0;i < tamanho; i++){
        cout<<vet[i]<<" ";
    }cout<<endl;
}

void imprimiVet2(int * vet, int tamanho){
    for(int i=0;i < tamanho; i++){
        cout<<vet[i]<<" ";
    }cout<<endl;
}
//------------------------------------------------------------------------------------------------

//Gera matriz genérica preenchida com zero:
int **geraMatriz(int l, int c){
    int **matriz;
    matriz = new int * [l];
    for (int i=0; i<l;i++){
        matriz[i] = new int [c];
    }
    for (int i=0; i<l;i++){
        for(int j =0; j<c;j++){
            matriz[i][j] = 0 ; 
        }
    }
    return matriz;
}
//------------------------------------------------------------------------------------------------

//Gera uma matriz com as ligações dos vértices de acordo com o arquivo:
int **ligacao(int aresta){
    int ** liga;
    string texto;
    liga = geraMatriz(aresta,2);
    for(int i = 0; i<aresta;i++){
        getline(file, texto);
        liga[i][0] = stoi(texto.substr(0, texto.find(";")));
        liga[i][1] = stoi(texto.substr(texto.find(";")+1, texto.size()-texto.find(";")));
    }

    cout<<"\n-----------------ligacoes--------------\t\n";
    for (int i=0; i<aresta;i++){
        for(int j =0; j<2; j++){
            cout<<liga[i][j]<<"\t";
        }cout<<endl;
    }

    return liga; 

}
//------------------------------------------------------------------------------------------------

//Gera um vetor com os pesos das arestas de acordo com o arquivo:
int * vPeso(int aresta){
	int*pesos;
	pesos = new int[aresta];
	fstream arquivo;
	arquivo.open("grafos.txt");
	string texto;

	getline(arquivo, texto);
	getline(arquivo, texto);
	for(int i = 0; i<aresta;i++){
    	getline(arquivo, texto);
        pesos[i] = stoi(texto.substr(texto.find(";")+4, texto.size()));

    }
    arquivo.close();
	cout<<"\n-----------------Pesos--------------\t\n";
    for (int i=0; i<aresta;i++){
            cout<<pesos[i]<<"\t";
        }cout<<endl;
    return pesos;

}
//------------------------------------------------------------------------------------------------

//cria uma matriz de adjacencia ponderada de acordo com a matriz de ligações:
int **matrizAdj(int **ligacao,int*pesos, int aresta, int vertice){
    int **matrizAdj = geraMatriz(vertice, vertice);

    for(int i=0; i<aresta; i++){
            matrizAdj[ligacao[i][0]-1][ligacao[i][1]-1] = pesos[i];
        }
    cout<<"\n-----------------Matriz de Adjacencia Ponderada--------------\t\n";
    for (int i=0; i<vertice;i++){
        for(int j =0; j<vertice; j++){
            cout<<matrizAdj[i][j]<<"\t";
        }cout<<endl;
    }
    return matrizAdj;
}

//------------------------------------------------------------------------------------------------

//Encontra o menor caminho entre um vertice de referencia e todos os outros vertices do graffo:
int distanciaMinima(int * dist, bool * sptSet, int vertice){
    int min = INT_MAX, indiceMinimo;
    for(int i =0; i< vertice; i++){
        if(sptSet[i]==false && dist[i]<= min){
            min = dist[i];
            indiceMinimo = i;
        }
    }
    return indiceMinimo;
}
int * dijkstra(int **mAdj, int vReferencia, int vertice ){
    int * dist= new int[vertice];
    bool * sptSet = new bool[vertice];
    for(int i=0; i<vertice; i++){
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }
   
    dist[vReferencia] = 0;

    for(int i = 0; i< vertice-1; i++){
        int u = distanciaMinima(dist, sptSet, vertice);
        sptSet[u] = true;
        for (int j=0; j< vertice; j++ ){
            if(!sptSet[j] && mAdj[u][j] && dist[u] != INT_MAX && dist[u]+mAdj[u][j]< dist[j]){
                dist[j] = dist[u] + mAdj[u][j];
            } 
        }
    }
    return dist;
 }
//------------------------------------------------------------------------------------------------

//Gera a matriz de excentricidade 
//Esta função chama a função dijkstra para cada vertice i, tomando-o como vertice de referencia
//Adiciona cada valor do vetor de distancias dist, para uma matriz;   
 int **matrizExc(int ** mAdj, int vertice){
    int ** mExc = geraMatriz(vertice, vertice);
    for (int i =0; i< vertice; i++){
        int * dist = dijkstra(mAdj, i, vertice);
        for (int j =0; j<vertice; j++){
                mExc[i][j] = dist[j];
        }
    }
    cout<<"\n-----------------Matriz de excentricidade--------------\t\n";
    for (int i=0; i<vertice;i++){
        for(int j =0; j<vertice; j++){
            cout<<mExc[i][j]<<"\t";
        }cout<<endl;
    }
    return mExc;
 }
//------------------------------------------------------------------------------------------------

//faz o somatório de cada linha da matriz
int * somaLinha(int **mExcentricidade, int n){
    int soma = 0;
    int* somatorio = new int[n];
    for(int i = 0; i<n;i++){
        soma = 0;
        for(int j=0; j< n;j++){
            soma += mExcentricidade[i][j];
        }
            somatorio[i] = soma;
    }
    return somatorio;
}
//------------------------------------------------------------------------------------------------

//faz o somatório de cada coluna da matriz
int * somaColuna(int ** matrizExc, int n){
    int soma=0;
    int* somatorioCol = new int[n];
    for(int i = 0; i<n;i++){
        soma = 0;
        for(int j=0; j< n;j++){
            soma += matrizExc[j][i];
        }
            somatorioCol[i] = soma;
    }
    return somatorioCol;
} 
//------------------------------------------------------------------------------------------------

//encontra o valor maximo de cada linha e salva em um vetor
int * maxLinha(int **mExcentricidade, int n){
    int * listaMax = new int[n];
    for(int i =0;i<n ;i++){
        listaMax[i] = mExcentricidade[i][0];
        for(int j =0;j<n;j++){
            if (mExcentricidade[i][j]>listaMax[i]){
             listaMax[i] = mExcentricidade[i][j];
            }
        
        }
    }
    return listaMax;
}
//------------------------------------------------------------------------------------------------

//encontra o valor maximo de cada coluna e salva em um vetor
int *colunaMax(int ** matrizExc, int n){
    int * maxCol = new int[n];
    for(int i =0;i<n ;i++){
        maxCol[i] = matrizExc[0][i];
        for(int j =0;j<n;j++){
            if (matrizExc[j][i]>maxCol[i]){
                maxCol[i] = matrizExc[j][i];
            }
        
        }
    }
    return maxCol;
}
//------------------------------------------------------------------------------------------------

//encontra o valor minimo de cada linha e salva em um vetor
int * minLinha(int **mExcentricidade, int *maximoLinha,  int n){
    int * listaMin = new int[n];
    for(int i =0;i<n ;i++){
        listaMin[i] = maximoLinha[i];
        for(int j =0;j<n;j++){
            if (mExcentricidade[i][j]<listaMin[i] && mExcentricidade[i][j] != 0 ){
             listaMin[i] = mExcentricidade[i][j];
            }        
        }
    }
    return listaMin;
}
//------------------------------------------------------------------------------------------------

//encontra o valor minimo de cada coluna e salva em um vetor   
int * colunaMin(int ** matrizExc,int *maxCol, int n){
    int * minCol = new int[n];
    for(int i =0;i<n ;i++){
        minCol[i] = maxCol[i];
        for(int j =0;j<n;j++){
            if (matrizExc[j][i]<minCol[i] && matrizExc[j][i] != 0 ){
             minCol[i] = matrizExc[j][i];
            }
        
        }
    }
    return minCol;

}   
//------------------------------------------------------------------------------------------------

//encontrar mediana exterior:
void medianaExt(int * somatorioLinha, int n){
    int minSom = somatorioLinha[0];
    for (int i= 0; i<n;i++ ){
        if (somatorioLinha[i]<minSom){
            minSom = somatorioLinha[i];
        }
    }
    cout<<"\nMediana exterior: ";
    for(int i =0; i<n;i++){
        if(somatorioLinha[i]==minSom){
          cout<<i+1<<" ";
        }
    }cout<<endl;
}
//------------------------------------------------------------------------------------------------

//encontrar centro exterior:
void centroExt(int * maximoLinha, int n){  
    int min = maximoLinha[0];
    for (int i= 0; i<n;i++ ){
        if (maximoLinha[i]<min){
            min = maximoLinha[i];
        }
    }
    cout<<"\nCentro exterior: ";
    for(int i =0; i<n;i++){
        if(maximoLinha[i]==min){
            cout<<i+1<<" ";
        }
    }cout<<endl;
    
}
//------------------------------------------------------------------------------------------------

//encontrar anticentro exterior:
void anticentroExt(int *minimoLinha,int n){
    int maxMin = minimoLinha[0]; 
    for (int i= 0; i<n;i++ ){
        if (minimoLinha[i]>maxMin){
            maxMin = minimoLinha[i];
        }
    }
    cout<<"\nAnticentro exterior: ";
    for(int i =0; i<n;i++){
        if(minimoLinha[i]==maxMin){
           cout<< i+1<<" ";
        }
    }cout<<endl;

}
//------------------------------------------------------------------------------------------------
//encontrar mediana inetrior:
void medianaInt(int * somatorioColuna, int n){
    int minSom = somatorioColuna[0];
    for (int i= 0; i<n;i++ ){
        if (somatorioColuna[i]<minSom){
            minSom = somatorioColuna[i];
        }
    }
    cout<<"\nMediana interior: ";
    for(int i =0; i<n;i++){
        if(somatorioColuna[i]==minSom){
            cout<< i+1<<" ";
        }
    }cout<<endl;
}
//------------------------------------------------------------------------------------------------

//encontrar centro interior:
void centroInt(int * maximoColuna, int n){  
    int min = maximoColuna[0];
    for (int i= 0; i<n;i++ ){
        if (maximoColuna[i]<min){
            min = maximoColuna[i];
        }
    }
    cout<<"\nCentro interior: ";
    for(int i =0; i<n;i++){
        if(maximoColuna[i]==min){
            cout<< i+1<<" ";
        }
    }cout<<endl;
    
}
//------------------------------------------------------------------------------------------------

//encontrar anticentro interior:
void anticentroInt(int *minimoColuna,int n){
    int maxMin = minimoColuna[0]; 
    for (int i= 0; i<n;i++ ){
        if (minimoColuna[i]>maxMin){
            maxMin = minimoColuna[i];
        }
    }
    cout<<"\nAnticentro interior: ";
    for(int i =0; i<n;i++){
        if(minimoColuna[i]==maxMin){
           cout<< i+1<<" ";
        }
    }cout<<endl;

}


int main(){
    int vertice;
    int aresta;
    int **mAdj;
    int **mInc;
    int *vetorGrau;
    int **ligacoes;
	int *pesos;
    string texto;

    //leitura de arquivo:
    file.open("grafos.txt");
    if(!file.is_open()){
        cout<<"Não foi possivel abrir o arquivo"<<endl;
        exit(0);
    }else{
        getline(file, texto);
        vertice = stoi(texto);
        getline(file, texto);
        aresta = stoi(texto);
        ligacoes = ligacao(aresta);
        file.close();
    }
    //-----------------------------------
	pesos = vPeso(aresta);
    mAdj = matrizAdj(ligacoes, pesos, aresta, vertice);
    int ** mExc = matrizExc(mAdj, vertice);

    int * somatorioLinha = somaLinha(mExc, vertice); 
    int * maximoLinha = maxLinha(mExc, vertice);
    int * minimoLinha = minLinha(mExc, maximoLinha,vertice);

    int * somatorioColuna = somaColuna(mExc, vertice);
    int * maximoColuna = colunaMax(mExc, vertice);
    int * minimoColuna = colunaMin(mExc, maximoColuna, vertice);

    cout<<"\nRespostas: "<<endl;

    cout<<"somatorio de cada linha: ";
    imprimiVet(somatorioLinha, vertice);
    cout<<"máximo de cada linha: ";
    imprimiVet(maximoLinha, vertice);
    cout<<"minimo de cada linha: ";
    imprimiVet(minimoLinha, vertice);

    cout<<"somatorio de cada coluna: ";
    imprimiVet(somatorioColuna, vertice);
    cout<<"máximo de cada coluna: ";
    imprimiVet(maximoColuna, vertice);
    cout<<"minimo de cada coluna: ";
    imprimiVet(minimoColuna, vertice);

    centroExt(maximoLinha, vertice);
    medianaExt(somatorioLinha, vertice);
    anticentroExt(minimoLinha, vertice);
    centroInt(maximoColuna, vertice);
    medianaInt(somatorioColuna, vertice);
    anticentroInt(minimoColuna, vertice);
    return 0;
}
