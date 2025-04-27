#include <iostream>
using namespace std;

//Criação de funções para organizar melhor o código
void mostrarTabuleiro(char tabuleiro[]){ //Mostra o tabuleiro no terminal
    cout << " " << tabuleiro[0] << " | " << tabuleiro[1] << " | " << tabuleiro[2] << endl;
    cout << "-----------" << endl;
    cout << " " << tabuleiro[3] << " | " << tabuleiro[4] << " | " << tabuleiro[5] << endl;
    cout << "-----------" << endl;
    cout << " " << tabuleiro[6] << " | " << tabuleiro[7] << " | " << tabuleiro[8] << endl;
}; //No início do jogo, irá exibir os números que estão indicados no char tabuleiro, entretanto no decorrer do jogo, esses espaços serão substituídos pelo sinal colocado pelo jogador

void jogar(char tabuleiro[], char jogador){ //Essa função lê a jogada do usuário, verifica se é válida e se for grava ela na posição do tabuleiro
    int posicao;
    while(true){ //(jogador == 'X' ? 1 : 2) é uma versão reduzida do if
        cout << "Jogador" << (jogador == 'X' ? 1 : 2) << " (" << jogador << "), escolha uma posição (1-9): "; //Apresenta a pergunta para o jogador verificando se ele é o 1 ou o 2
        cin >> posicao; //Lê o valor inserido pelo jogador
        //O cin espera receber um valor que seja o indicado anteriomente (ex: int), se for recebido outro valor ele não entende
        //Para verificar isso usamos o cin.fail()
        //Quando o cin falha, ele trava, logo para resolver isso utiliza-se o cin.clear() que remove o erro
         if(cin.fail()){ //Esse if verifica se a entrada foi válida ou não
            cin.clear();//Se a entrada falhou, pede pra limpar
            cin.ignore(1000, '\n'); //Ignora o resto da linha e limpa o buffer (memória temporária da entrada). Com isso ele ignora até 1000 caracteres ou até encontrar uma nova linha (\n)
            cout << "Entrada inválida! Digite um número de 1 a 9." << endl;
            continue;   
        }
        posicao--; //MUITO IMPORTANTE! Esse cara aqui serve pra diminuir 1 do valor colocado pelo jogador devido a diferença de posições nos arrays (visto que eles começam com o índice 0)
        if(posicao >= 0 && posicao < 9 && tabuleiro[posicao] != 'X' && tabuleiro[posicao] != 'O'){ //Verifica se é jogada em um local válido e livre
            tabuleiro[posicao] = jogador; //Se sim, irá colocar o símbolo do jogador na posição indicada pelo mesmo
            break;
        }
        else cout << "Posição inválida ou já ocupada! Escolha outra posição." << endl;
    }
};
bool verificarVitoria(char tabuleiro[], char jogador){ //Verifica se há uma sequência de 3 casas iguais, houver retorna true
    if((tabuleiro[0] == tabuleiro[1] && tabuleiro[1] == tabuleiro[2]) || (tabuleiro[3] == tabuleiro[4] && tabuleiro[4] == tabuleiro[5]) || (tabuleiro[6] == tabuleiro[7] && tabuleiro[7] == tabuleiro[8])) return true; //Verifica as linhas horizontais
    if((tabuleiro[0] == tabuleiro[3] && tabuleiro[3] == tabuleiro[6])||(tabuleiro[1] == tabuleiro[4] && tabuleiro[4] == tabuleiro[7])||(tabuleiro[2] == tabuleiro[5] && tabuleiro[5] == tabuleiro[8])) return true; //Verifica as linhas verticais
    if((tabuleiro[0] == tabuleiro[4] && tabuleiro[4] == tabuleiro[8])||(tabuleiro[2] == tabuleiro[4] && tabuleiro[4] == tabuleiro[6])) return true; //Verifica as diagonais
    return false;
};

bool verificarEmpate(char tabuleiro[]){//Verifica se houve empate ou não
    for(int i = 0; i < 9; i++){ //O vetor for percorre todas as casas
        if(tabuleiro[i] != 'X' && tabuleiro[i] != 'O') return false; //E verifica se há posições vazias, se houver retorna false
    }
    return true; //Se não se encaixar na situação anterior, retorna true
    //Sabemos que será empate pq a função verificarVitoria será chamada antes dessa do empate, logo se não se encaixa em vitória e nem em casas vazias, é um empate
};

void reiniciarTabuleiro(char tabuleiro[]){ //Faz a limpeza do tabuleiro, voltando a configuração de números
    for(int i = 0; i < 9; i++){ //Percorre o tabuleiro inteiro
       tabuleiro[i] = '1'+i; //Pega a posição em que se encontra (índice i) e soma +1
    }
};

int main(){
    char tabuleiro[9] = {'1','2','3','4','5','6','7','8','9'}; //char que apresenta o número de casas
    char jogadorAtual = 'X'; //char indicando o jogador X
    bool jogoAtivo = true; //Criação de uma bool para verificar quando o jogo está ocorrendo ou não
    
    while (jogoAtivo){ //Enquanto o jogo estiver ocorrendo
        mostrarTabuleiro(tabuleiro); //Apresenta o tabuleiro no terminal 
        jogar(tabuleiro, jogadorAtual); //Inicia o jogo atribuindo como jogador primário o que usa o X 
        
        if(verificarVitoria(tabuleiro, jogadorAtual)){ //Aqui é realizada a verificação de vitória  
            mostrarTabuleiro(tabuleiro); //Aqui mostra o tabuleiro 
            cout << "Parabéns! Jogador " << (jogadorAtual == 'X' ? 1 : 2) << " venceu!" << endl;
            char resposta;
            cout << "Deseja jogar novamente? (S/N): ";
            cin >> resposta;
            if(resposta == 'S' || resposta == 's'){
                reiniciarTabuleiro(tabuleiro); //Aqui é aplicada a função que "limpa" o tabuleiro
                jogadorAtual = 'X'; //Inicia-se novamente como primeiro jogador o com X
            } 
            else{
                jogoAtivo = false; //Se o jogador não quiser mais jogar, acaba o jogo
            }
        } 
        else if(verificarEmpate(tabuleiro)){ //Diferente das situações acima, verifica-se se há empate
            mostrarTabuleiro(tabuleiro); //Mostra o tabuleiro
            cout << "Empate! Nenhum jogador venceu." << endl;
            char resposta;
            cout << "Deseja jogar novamente? (S/N): ";
            cin >> resposta;
            if(resposta == 'S' || resposta == 's'){
                reiniciarTabuleiro(tabuleiro);
                jogadorAtual = 'X';
            } 
            else{
                jogoAtivo = false;
            }
        }
        else{
            jogadorAtual = (jogadorAtual == 'X') ? 'O' : 'X';
        }
    }
}