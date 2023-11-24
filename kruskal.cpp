#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
#define N 9
using namespace std;

class aresta{
    public:
    int v1,v2,peso;
};

class grafo{
    public:
    vector<int> vertices;
    vector<aresta> arestas;
};


vector<aresta> A_resultado;
vector<set<int>> floresta(N);

bool comparacao(const aresta& a1, const aresta& a2){
    return a1.peso < a2.peso;
}

void printA_resultado(int x){
    int sum=0;
    cout << "A: ";
    for(const aresta& a : A_resultado){
        cout << "{" << a.v1 << ", " << a.v2 << "} ";
        sum = sum + a.peso;
    }
    cout << endl;
    if(x==1){
        cout << "Peso minimo: " << sum << endl;
    }
}

void printFloresta(){
    cout << "Floresta: ";
    for(int i = 0; i < N; i++){
        cout << "{";
        for(int num : floresta[i]){
            cout << "(" <<num << ")";
        }
        cout << "} ";
    }
    cout << endl;
}

void kruskal(grafo graph){
    A_resultado.clear();

    for(int i=0;i<N;i++){
        floresta.at(i).insert(graph.vertices.at(i));
    }
    
    sort(graph.arestas.begin(), graph.arestas.end(), comparacao);

    for(const aresta& a : graph.arestas){
        for(int i = 0; i < N; i++){
            //percorre pelo vetor 
            for(int num : floresta[i]){ //i = conjunto atual
                //percorre pelos conjuntos
                if(num == a.v1 || num == a.v2){
                    int v3;
                    if(num == a.v1)
                        v3 = a.v2;
                    else
                        v3 = a.v1;
                        
                    if(floresta.at(i).find(v3) == floresta.at(i).end()){
                        //nao achou o vertice a ser unido no mesmo conjunto
                        for(int j = num; j < N; j++){
                            for(int del : floresta[j]){ //j = conjunto que o vertice a ser unido vai estar
                                if(del == v3){
                                    floresta.at(i).insert(floresta.at(j).begin(), floresta.at(j).end());
                                    floresta.at(j).clear();
                                    break;
                                }
                            }
                        }
                        printFloresta();
                        A_resultado.push_back(a);
                        printA_resultado(0);
                        cout << endl;
                    }
                    break;
                }
            }
        }
    }
}

int main(){

    int qt_arestas;
    grafo graph;
    
    cout << "Qt. Arestas: "; cin >> qt_arestas;
    
    for(int i=0;i<N;i++){
        graph.vertices.insert(graph.vertices.begin() + i, i+1);
    }
    
    aresta aux;
    cout << "Digite as arestas no formato: v1 v2 peso" << endl;
    for(int i=0;i<qt_arestas;i++){
        cin >> aux.v1 >> aux.v2 >> aux.peso;
        graph.arestas.insert(graph.arestas.begin() + i, aux);
    }
    
    kruskal(graph);
    printA_resultado(1);
    return 0;
}
/*
v1 v2 peso
1 2 1
2 3 2
1 4 4
4 2 6
4 5 3
2 5 4
5 3 5
5 6 8
3 6 6
4 7 4
5 7 7
7 6 3
*/
