#include <iostream>
#include <fstream>

using namespace std;
ifstream file;

//função auxiliar para converter saida bool em sim ou não
string simNao(bool teste){
    if(teste == true){
        return "Sim";
    }else{
        return "Não";
    }
}


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
//cria uma matriz de adjacencia de acordo com a matriz de ligações:
int **matrizAdj(int **ligacao, int aresta, int vertice){
    int **matrizAdj = geraMatriz(vertice, vertice);

    for(int i=0; i<aresta; i++){
            matrizAdj[ligacao[i][0]-1][ligacao[i][1]-1] = 1;
            matrizAdj[ligacao[i][1]-1][ligacao[i][0]-1] = 1;
        }
    cout<<"\n-----------------Matriz de Adjacencia--------------\t\n";
    for (int i=0; i<vertice;i++){
        for(int j =0; j<vertice; j++){
            cout<<matrizAdj[i][j]<<"\t";
        }cout<<endl;
    }
    return matrizAdj;


 }
//------------------------------------------------------------------------------------------------
//cria uma matriz de incidencia de acordo com a matriz de ligações:
 int **matrizInc(int** ligacoes, int aresta, int vertice){
    int **matrizInc = geraMatriz(aresta, vertice);
     for (int i = 0; i < aresta; i++){
        matrizInc[i][ligacoes[i][0] - 1] += 1;
        matrizInc[i][ligacoes[i][1] - 1] += 1;
    }
    cout<<"\n-----------------Matriz de incidencia--------------\t\n";
    for (int i=0; i<aresta;i++){
        for(int j =0; j<vertice; j++){
            cout<<matrizInc[i][j]<<"\t";
        }cout<<endl;
    }

    return matrizInc;
 }
 //------------------------------------------------------------------------------------------------
//testar se é multigrafo:
bool testaVetores(int * vetAux, int *vetAux2, int vertice){
    for(int i =0; i<vertice;i++){
        if (vetAux[i] != vetAux2[i]){
            return false;
        }
    }return true;
}

bool testaMultigrafo(int **mInc, int aresta, int vertice){
    int* vetAux = new int[vertice];
    for(int i = 0; i<aresta-1; i++){
        vetAux = mInc[i];
        for(int j= i+1;j<aresta;j++){
            if(testaVetores(vetAux, mInc[j], vertice)){
                return true;
            }
        }
    }


    return false;
}


//------------------------------------------------------------------------------------------------
//verifica a existencia de laços:
 bool verificaLaco(int **mAdj, int vertice){
    for(int i =0; i<vertice; i++){
            if(mAdj[i][i] != 0){
                return true;
        }
    }
    return false;
 }
 //------------------------------------------------------------------------------------------------
//verifica se o grafo é simples:
bool testaSimples(bool mult, bool laco){
    if(mult ==1 || laco ==1){
        return false;
    }return true;
}




//------------------------------------------------------------------------------------------------
//ver o grau do vertice
int * grauVertice(int **mInc, int aresta, int vertice){ 
    int soma = 0;
    int * vetGraus;
    vetGraus = new int [vertice];

    for(int i = 0; i < vertice; i++){
        soma = 0;
        for(int j = 0; j < aresta; j++){
            soma += mInc[j][i];
        }
        vetGraus[i] = soma;
        
    }

    return vetGraus;

}


void imprimeGrau(int * vetGrau, int vertice){
    for(int i=0;i<vertice;i++){
        cout<<"Grau do vertice "<<i+1<<": ";
        cout<<vetGrau[i]<<endl;
    }cout<<endl;

}
//------------------------------------------------------------------------------------------------
//testa se é completo:
bool testaCompleto(int **mAdj, int vertice){ 

    int contador = 0;

    for(int i = 0; i < vertice; i++){
        for(int j = 0; j < vertice; j++){
            if(mAdj[i][j] == 0){
                contador++;

            }
        }
    }

    if(contador == vertice){
        return true;
    }

    return false;

}

//------------------------------------------------------------------------------------------------
//testa se é regular:
bool testaRegular(int * vGrau, int vertice){
    int contador=0;
    for(int i = 0; i<vertice-1; i++){
        if(vGrau[0] != vGrau[i+1]){
         return false;
        }
    }
    return true;
}

//------------------------------------------------------------------------------------------------
//testar se é reflexivo:
bool testaReflexivo(int **mAdj, int vertice){ 

    int contador = 0;

    for(int i = 0; i < vertice; i++){
        if(mAdj[i][i] != 0){
                contador++;
        }
    }
    if(contador == vertice){

        return true;

    }

    return false;

}
//------------------------------------------------------------------------------------------------
//testar se é vazio ou nulo:
void testaNulo(int n){
    if (n ==1){
        cout<<"Grafo Nulo";
        exit(0);
    }
}

bool testaVazio(int **mAdj, int aresta,int vertice){
    if(vertice >0){
        for(int i =0;i<vertice;i++){
            for(int j=0;j<vertice;j++){
                if(mAdj[i][j]!= 0){
                        return false;
                    }
                }
            }
        }else{
            if(aresta==0, vertice==0){
                testaNulo(1);
            }
        }
    return true;
    }


//------------------------------------------------------------------------------------------------
//testar se é trivial:
bool testaTrivial(int vertice, bool vazio){
    if(vertice ==1 && vazio){
        return true;
    }return false;

}

//------------------------------------------------------------------------------------------------
//função principal, que implementa leitura do arquivo e chamadas de função: 
int main(){
    int vertice;

   
    int aresta;
    int **mAdj;
    int **mInc;
    int *vetorGrau;
    int **ligacoes;
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

    mAdj= matrizAdj(ligacoes, aresta, vertice);
    mInc = matrizInc(ligacoes, aresta, vertice);  
    vetorGrau = grauVertice(mInc, aresta, vertice);
   
    bool temLaco = verificaLaco(mAdj, vertice);
    bool completo = testaCompleto(mAdj, vertice);
    bool regular = testaRegular(vetorGrau, vertice);
    bool reflexivo = testaReflexivo(mAdj, vertice);
    bool multigrafo = testaMultigrafo(mInc, aresta, vertice);
    bool vazio = testaVazio(mAdj, aresta, vertice);
    bool trivial = testaTrivial(vertice, vazio);
    bool simples = testaSimples (multigrafo, temLaco);

    cout << "--------------------------------------------------------------------------------------------------------------------------\n";  
    cout<<"\nDados do grafo apresentado:\n"<<endl;
    cout<<"É simples? "<<simNao(simples)<<endl;
    if (simples && !vazio){
        cout<<"é completo? "<<simNao(completo)<<endl;
        cout<<"é regular? "<<simNao(regular)<<endl;
        cout<<"\nGrau dos vertices:"<<endl;
        imprimeGrau(vetorGrau, vertice);
        cout << "--------------------------------------------------------------------------------------------------------------------------\n";  
    }else{
        cout<<"É vazio? "<<simNao(vazio)<<endl;
        cout<<"É trivial? "<<simNao(trivial)<<endl;
        cout<<"É multigrafo? "<<simNao(multigrafo)<<endl;
        cout<<"Possui laço? "<<simNao(temLaco)<<endl;
        cout << "--------------------------------------------------------------------------------------------------------------------------\n";  
    
        cout<<"é reflexivo? "<<simNao(reflexivo)<<endl;
        cout << "--------------------------------------------------------------------------------------------------------------------------\n";

    }
   
   
 
    return 0;
}


