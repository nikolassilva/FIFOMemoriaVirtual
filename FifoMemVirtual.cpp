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

//função para verificar se a página referente ao endereço está na memória
bool repetida(queue<int> aux, int endereco) {
    int pagEndereco = endereco/tamMoldura;
    int tam = aux.size();
    for(int j=0; j<tam; j++){
        int pagFrenteMemoria = aux.front()/tamMoldura;
        if(pagEndereco == pagFrenteMemoria) {
           return true;
        }
        else{
           aux.pop();
        }
    }

    return false;
}

void FIFO (queue<int> q, int acessos){

    int slots = tamFisica/tamMoldura; //quantidade de slots da memoria
    int copias = 0; // quantidade de swaps
    queue <int> principal; // fila que representa a memoria principal

    for(int i=0;i<acessos;i++){
            //se a pagina é repetida o programa retorna ao inicio
            //do contrario:
            //se existir slot vazio a nova pagina e carregada diretamente
            //do contrario o FIFO é realizado e o numero de copias é incrementado
            if(!repetida(principal, q.front())){
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
            else{
                q.pop();
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
