# FIFOMemoriaVirtual

#### Desenvolvido por: Jonathan Rodrigues e Nikolas Gabriel

Este programa foi desenvolvido para um trabalho da disciplina de Sistemas Operacionais, do 5° período do curso de Sistemas de Informação. Utilizamos a linguagem C++. Trata-se de um mini simulador de Alocação de Memória, utilizando o algoritmo FIFO.

Basicamente, o programa lê um arquivo ".txt" que deve conter na primeira linha, respectivamente: o tamanho em bytes da memória virtual, o tamanho em bytes da memória física e o tamanho em bytes da página/moldura. A segunda linha deve conter um valor X indicando a quantidade de acessos que serão feitos à memória. As próximas X linhas devem conter os endereços de memória que serão acessados. 

Com o arquivo de entrada contendo as informações como descritas acima, o programa deve gerar um arquivo contendo na primeira linha o número total de cópias de páginas realizadas da memória virtual para a memória principal, e na segunda linha a listagem na ordem crescente de todas as páginas que estiverem presentes na memória ao final da simulação.


