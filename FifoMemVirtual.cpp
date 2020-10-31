//Gerencia de Memoria - Algoritmo FIFO
//Integrantes: Jonathan F Rodrigues e Nikolas Gabriel

#include <iostream>
#include <fstream>
#include <queue>
#include <cstring>

using namespace std;

ifstream inputFile ("entrada.txt");
ofstream outputFile ("saida.txt");

int tamVirtual;
int physicalMemSize;
int frameSize;

// Function to push element in last by popping from front until size becomes 0
void FrontToLast(queue<int>& targetQueue, int qsize)
{
    // Base condition
    if (qsize <= 0)
        return;

    // pop front element and push this last in a queue
    targetQueue.push(targetQueue.front());
    targetQueue.pop();

    // Recursive call for pushing element
    FrontToLast(targetQueue, qsize - 1);
}

// Function to push an element in the queue while maintaining the sorted order
void pushInQueue(queue<int> &targetQueue, int temp, int qsize)
{
    // Base condition
    if (targetQueue.empty() || qsize == 0) {
        targetQueue.push(temp);
        return;
    }

    // If current element is less than the element at the front
    else if (temp <= targetQueue.front()) {

        // Call stack with front of queue
        targetQueue.push(temp);

        // Recursive call for inserting a front element of the queue to the last
        FrontToLast(targetQueue, qsize);
    }
    else {

        // Push front element into last in a queue
        targetQueue.push(targetQueue.front());
        targetQueue.pop();

        // Recursive call for pushing element in a queue
        pushInQueue(targetQueue, temp, qsize - 1);
    }
}

// Function to sort the given queue using recursion
void sortQueue(queue<int>& targetQueue)
{

    // Return if queue is empty
    if (targetQueue.empty())
        return;

    // Get the front element which will be stored in this variable throughout the recursion stack
    int temp = targetQueue.front();

    // Remove the front element
    targetQueue.pop();

    // Recursive call
    sortQueue(targetQueue);

    // Push the current element into the queue according to the sorting order
    pushInQueue(targetQueue, temp, targetQueue.size());
}

void writeQueue(queue<int> targetQueue){
    while (!targetQueue.empty()){
		outputFile<<targetQueue.front()/frameSize<<" ";
		targetQueue.pop();
	}
	outputFile<<endl;
}

//Function to print the queue
void printQueue(queue<int> targetQueue)
{
	while (!targetQueue.empty()){
		cout<<targetQueue.front()/frameSize<<" ";
		targetQueue.pop();
	}
	cout<<endl;
}

//função para verificar se a página referente ao endereço está na memória
bool checkRepetition(queue<int> mainMemory, int address) {
    int pageAddress = address/frameSize;
    int sizeMemory = mainMemory.size();
    for(int j=0; j<sizeMemory; j++){
        int frontMemoryPage = mainMemory.front()/frameSize;
        if(pageAddress == frontMemoryPage) {
           return true;
        }
        else{
           mainMemory.pop();
        }
    }

    return false;
}

void FIFO (queue<int> addressQueue, int numberAccesses){

    int memPhysicalCapacity = physicalMemSize/frameSize; //quantidade de memPhysicalCapacity da memoria
    int swaps = 0; // quantidade de swaps
    queue <int> mainMemory; // fila que representa a memoria mainMemory

    for(int i=0;i<numberAccesses;i++){
            //se a pagina é checkRepetition o programa retorna ao inicio
            //do contrario:
            //se existir slot vazio a nova pagina e carregada diretamente
            //do contrario o FIFO é realizado e o numero de swaps é incrementado
            if(!checkRepetition(mainMemory, addressQueue.front())){
                if(mainMemory.size()<memPhysicalCapacity){
                    mainMemory.push(addressQueue.front());
                    addressQueue.pop();
                } else {
                    mainMemory.pop();
                    mainMemory.push(addressQueue.front());
                    addressQueue.pop();
                    swaps++;
                }
            }
            else{
                addressQueue.pop();
            }

        printQueue(mainMemory);
    }

    sortQueue(mainMemory);

    cout<<"Swaps "<<swaps<<endl;
    outputFile<<swaps<<endl;

    cout<<"Remaining Pages ";
    printQueue(mainMemory);
    writeQueue(mainMemory);

}

int main() {

    if(inputFile.is_open()){

        string line;
        int numberAccesses;

        // leitura da primeira line do arquivo
        getline(inputFile, line);

        char aux[127];
        strcpy(aux, line.c_str());

        //leitura do tamanho da memoria virtual
        char *data = strtok(aux, " ");
        tamVirtual = atoi(data);

        //leitura do tamanho da memoria fisica
        data = strtok(NULL, " ");
        physicalMemSize = atoi(data);

        //leitura do tamanho da moldura
        data = strtok(NULL, " ");
        frameSize = atoi(data);

        //leitura quantidade accesses
        getline(inputFile, line);
        numberAccesses = stoi(line);

        queue <int> addressQueue;

        //fila de paginas acessadas
        for (int i=0; i<numberAccesses; i++){
            getline(inputFile, line);
            addressQueue.push(stoi(line));
        }

        printQueue(addressQueue);

        //chamada da funcao
        FIFO(addressQueue, numberAccesses);

        } else {
            cout<<"Error: Input file is Wrong!!!"<<endl;
        }

    return 0;
}
