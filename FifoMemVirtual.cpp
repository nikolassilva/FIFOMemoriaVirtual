//Gerencia de Memoria - Algoritmo FIFO
//Integrantes: Jonathan F Rodrigues e Nikolas Gabriel

#include <iostream>
#include <fstream>
#include <queue>
#include <cstring>

using namespace std;

ifstream arqEntrada ("entrada.txt");
ofstream arqSaida ("saida.txt");

int tamVirtual;
int tamFisica;
int tamMoldura;

// Function to push element in last by popping from front until size becomes 0
void FrontToLast(queue<int>& q, int qsize)
{
    // Base condition
    if (qsize <= 0)
        return;

    // pop front element and push this last in a queue
    q.push(q.front());
    q.pop();

    // Recursive call for pushing element
    FrontToLast(q, qsize - 1);
}

// Function to push an element in the queue while maintaining the sorted order
void pushInQueue(queue<int> &q, int temp, int qsize)
{
    // Base condition
    if (q.empty() || qsize == 0) {
        q.push(temp);
        return;
    }

    // If current element is less than the element at the front
    else if (temp <= q.front()) {

        // Call stack with front of queue
        q.push(temp);

        // Recursive call for inserting a front element of the queue to the last
        FrontToLast(q, qsize);
    }
    else {

        // Push front element into last in a queue
        q.push(q.front());
        q.pop();

        // Recursive call for pushing element in a queue
        pushInQueue(q, temp, qsize - 1);
    }
}

// Function to sort the given queue using recursion
void sortQueue(queue<int>& q)
{

    // Return if queue is empty
    if (q.empty())
        return;

    // Get the front element which will be stored in this variable throughout the recursion stack
    int temp = q.front();

    // Remove the front element
    q.pop();

    // Recursive call
    sortQueue(q);

    // Push the current element into the queue according to the sorting order
    pushInQueue(q, temp, q.size());
}

//Function to print the queue
void printQueue(queue<int> q)
{
	while (!q.empty()){
		cout<<q.front()/tamMoldura<<" ";
		arqSaida<<q.front()/tamMoldura<<" ";
		q.pop();
	}
	cout<<endl;
}

void FIFO (queue<int> q, int acessos){

    int slots = tamFisica/tamMoldura; //quantidade de slots da memoria
    int copias = 0; // quantidade de swaps
    queue <int> principal; // fila que representa a memoria principal

    for(int i=0;i<acessos;i++){

        //verifica se a memoria principal esta vazia
        //caso positivo carrega o primeiro endereco da fila
        if(principal.empty()){
            principal.push(q.front());
            q.pop();
        } else {

            bool repetida = false; //indica se a pagina ja esta na memoria principal
            int pgNova = q.front()/tamMoldura; //armazena a pagina referente ao primeiro endereco na fila
            int tam = principal.size(); // quantidade de paginas na memoria principal
            queue<int> bkp = principal; // copia da memoria principal

            //percorre todas as paginas na memoria principal
            for(int i=0;i<tam;i++){
            int pgFrente = principal.front()/tamMoldura; // armazena a pagina referente ao primeiro endereco na memoria

                //verifica se a nova pagina ja esta na memoria principal
                //caso positivo a nova pagina é descartada
                //caso negativo a pagina que esta a frente da memoria principal é descartada,
                //a proxima pagina na memoria vem pra frente e o programa repete a comparacao
                if(pgNova==pgFrente){
                    repetida=true;
                    q.pop();
                    break;
                } else {
                    principal.pop();
                }
            }

            //recuperac o estado da memoria principal antes da checagem de duplicidade
            principal = bkp;

            //se a pagina é repetida o programa retorna ao inicio
            //do contrario:
            //se existir slot vazio a nova pagina e carregada diretamente
            //do contrario o FIFO é realizado e o numero de copias é incrementado
            if(repetida==false){
                if(principal.size()<slots){
                    principal.push(q.front());
                    q.pop();
                } else {
                    principal.pop();
                    principal.push(q.front());
                    q.pop();
                    copias++;
                }
            }
        }

        printQueue(principal);
    }

sortQueue(principal);

cout<<"Swaps "<<copias<<endl;
arqSaida<<copias<<endl;

cout<<"Paginas restantes ";
printQueue(principal);

}

int main() {

    if(arqEntrada.is_open()){

        string linha;
        int qntdAcessos;

        // leitura da primeira linha do arquivo
        getline(arqEntrada, linha);

        char aux[127];
        strcpy(aux, linha.c_str());

        //leitura do tamanho da memoria virtual
        char *dados = strtok(aux, " ");
        tamVirtual = atoi(dados);

        //leitura do tamanho da memoria fisica
        dados = strtok(NULL, " ");
        tamFisica = atoi(dados);

        //leitura do tamanho da moldura
        dados = strtok(NULL, " ");
        tamMoldura = atoi(dados);

        //leitura quantidade acessos
        getline(arqEntrada, linha);
        qntdAcessos = stoi(linha);

        queue <int> filaEnderecos;

        //fila de paginas acessadas
        for (int i=0; i<qntdAcessos; i++){
            getline(arqEntrada, linha);
            filaEnderecos.push(stoi(linha));
        }

        printQueue(filaEnderecos);

        //chamada da funcao
        FIFO(filaEnderecos, qntdAcessos);

        } else {
            cout<<"Erro ao abrir o arquivo de entrada."<<endl;
        }

    return 0;
}
