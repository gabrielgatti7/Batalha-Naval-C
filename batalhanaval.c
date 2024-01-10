#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// Coordenada Navio
typedef struct{
    int idNavio;
    char letra;
    int num;
} tCoordenada;

tCoordenada CriaCoordenada(int idNavio, char coordLetra, int coordNum);
int ObtemIdNavioCoordenada(tCoordenada coordenada);
char ObtemLetraCoordenada(tCoordenada coordenada);
int ObtemNumCoordenada(tCoordenada coordenada);





// Navio
#define TAM_MAX_NAVIO 5
typedef struct{
    char tipo[11];
    int id;
    int orientacao; // 0 - vertical   1 - horizontal
    int tamanho;
    int partesNaoAfundadas;
} tNavio;

tNavio CriaNavio(char tipoNavio[], int idNavio, int orientacaoNavio, 
char coordIniLetra, int coordIniNum);
int ObtemPartesNaoAfundadasNavio(tNavio navio);
tNavio DecrescePartesNaoAfundadasNavio(tNavio navio);
void ObtemTipoNavio(tNavio navio, char tipo[]);
int ObtemIdNavio(tNavio navio);





// Tabuleiro
#define TAM_TABU_LARG 10
#define TAM_TABU_ALT 'j'
#define MAX_NAVIOS 50
#define PECA_AGUA 'o'
#define PECA_NAVIO 'X'
#define PECA_VAZIO '.'
typedef struct{
    char matriz[TAM_TABU_LARG][TAM_TABU_LARG];
    char matrizAtual[TAM_TABU_LARG][TAM_TABU_LARG];
    char pecaAgua;
    char pecaNavio;
    char pecaVazio;
    tNavio navios[MAX_NAVIOS];
    int validadePosicaoNavios; // 0 - invalida   1 - valida
    int qntCarrier;
    int qntBattleship;
    int qntCruiser;
    int qntSubmarine;
    int qntDestroyer;
    tCoordenada coordenadasOcupadas[TAM_TABU_LARG * TAM_TABU_LARG];
    int qntNaviosNaoAfundados;
} tTabuleiro;
 
tTabuleiro CriaTabuleiro(FILE * pFileTabu);
int EhValidoTabuleiro(tTabuleiro tabuleiro);
int HaNaviosEncostadosTabuleiro(tTabuleiro tabuleiro);
int QntNaviosNaMesmaCoordTabuleiro(tTabuleiro tabuleiro,  char coordLetra, 
int coordNum);
int ObtemIdNavioCoordTabuleiro(tTabuleiro tabuleiro, char coordLetra, int coordNum);
int ObtemValidadePosicaoNaviosTabuleiro(tTabuleiro tabuleiro);
int ObtemQntCarrierTabuleiro(tTabuleiro tabuleiro);
int ObtemQntBattleshipTabuleiro(tTabuleiro tabuleiro);
int ObtemQntCruiserTabuleiro(tTabuleiro tabuleiro);
int ObtemQntSubmarineTabuleiro(tTabuleiro tabuleiro);
int ObtemQntDestroyerTabuleiro(tTabuleiro tabuleiro);
int ObtemQntNaviosNaoAfundadosTabuleiro(tTabuleiro tabuleiro);
void ImprimeMatrizTabuleiro(tTabuleiro tabuleiro);
void ImprimeMatrizTabuleiroNoArquivo(tTabuleiro tabuleiro, FILE * pFIle);
void ImprimeMatrizAtualTabuleiro(tTabuleiro tabuleiro);
int JaFoiAtingidaCoordTabuleiroAtual(tTabuleiro tabuleiro, char coordLetra, 
int coordNum);
int TemNavioNaCoordTabuleiro(tTabuleiro tabuleiro, char coordLetra, 
int coordNum);
tNavio ObtemNavioPeloIdTabuleiro(tTabuleiro tabuleiro, int idNavio);
tTabuleiro AlteraTiroMatrizAtualTabuleiro(tTabuleiro tabuleiro, char coordLetra, 
int coordNum);
tTabuleiro AlteraAguaMatrizAtualTabuleiro(tTabuleiro tabuleiro, char coordLetra, 
int coordNum);
tTabuleiro AlteraPartesNaoAfundadasNavioTabuleiro(tTabuleiro tabuleiro, 
int idNavio);
tTabuleiro DecresceQntNaviosNaoAfundadosTabuleiro(tTabuleiro tabuleiro);





// Jogada
typedef struct{
    char coordLetra;
    char coordNum;
    int resultado; // 0 - agua, 1 - tiro
} tJogada;

tJogada CriaJogada(char letra, int num, int resultado);
int ObtemResultadoJogada(tJogada jogada);
int ObtemCoordLetraJogada(tJogada jogada);
int ObtemCoordNumJogada(tJogada jogada);





// Jogador
#define TAM_NOME 16
#define ID_JOGADOR_1 1
#define ID_JOGADOR_2 2
typedef struct{
    int id;
    char nome[TAM_NOME];
    tTabuleiro tabuleiro;
    tJogada jogadas[TAM_TABU_LARG * TAM_TABU_LARG];
    int qntJogadasAgua;
    int qntJogadasTiro;
} tJogador;

tJogador CriaJogador(FILE * pFileTabu, int idJogador);
tJogador InicializaNomeJogador(tJogador jogador, char nome[]);
tTabuleiro ObtemTabuleiroJogador(tJogador jogador);
tTabuleiro ObtemTabuleiroAtualJogador(tJogador jogador);
void ObtemNomeJogador(tJogador jogador, char nome[]);
tJogador MarcaJogadaJogador(tJogador jogador, char letra, int num, 
int resultado);
tJogador AlteraTabuTiroJogador(tJogador jogador, char coordLetra, int coordNum);
tJogador AlteraTabuAguaJogador(tJogador jogador, char coordLetra, int coordNum);
tJogador AlteraTabuQntNaviosNaoAfundadosJogador(tJogador jogador);
int AfundouTodosNaviosDoJogador(tJogador jogador);
void EscreveArquivoResultadoJogador(FILE * pFile, tJogador jogadorDaVez,
tJogador outroJogador);
void EscreveArquivoEstatisticasJogador(FILE * pFile, tJogador jogadorDaVez,
tJogador outroJogador);





// Jogo
typedef struct{
    tJogador jogador1;
    tJogador jogador2;
    int preparado;
    int resultado; /* 0 - nao acabou, 1 - vitoria jogador 1
    2 - vitoria jogador 2, 3 - empate */
} tJogo;

tJogo InicializaJogo(char dir[]);
int SaoCompativeisTabuleirosJogo(tJogador jogador1, tJogador jogador2);
int EstaPreparadoJogo(tJogo jogo);
tJogo RealizarJogo(tJogo jogo);
tJogo JogadorEfetuaJogadaJogo(tJogo jogo, char nome1[], char nome2[], 
int jogadorDaVez);
void GeraResumoResultadoJogo(tJogo jogo, char dir[]);
void GeraEstatisticasJogo(tJogo jogo, char dir[]);

int FoiPrintadoNavioEstatisticas(int idNaviosJaPrintados[], 
int idNavio, int contPrintados);





int main (int argc, char * argv[]){
    if(argc <= 1){
        printf("ERRO: O diretorio de arquivos de configuracao nao foi informado\n");
        return 1;
    }
    
    tJogo jogo;
    jogo = InicializaJogo(argv[1]);

    // Se tabuleiros sao invalidos ou incompativeis o programa encerra
    if(!EstaPreparadoJogo(jogo)) return 0;

    // Se forem compativei comeca o jogo
    jogo = RealizarJogo(jogo);

    // Gera o arquivo de resumo do resultado apos o fim do jogo
    GeraResumoResultadoJogo(jogo, argv[1]);

    // Gerar o arquivo de estatisticas do jogo
    GeraEstatisticasJogo(jogo, argv[1]);
    return 0;
}





tCoordenada CriaCoordenada(int idNavio, char coordLetra, int coordNum){
    tCoordenada coordenada;
    coordenada.idNavio = idNavio;
    coordenada.letra = coordLetra;
    coordenada.num = coordNum;
    return coordenada;
}


int ObtemIdNavioCoordenada(tCoordenada coordenada){
    return coordenada.idNavio;
}


char ObtemLetraCoordenada(tCoordenada coordenada){
    return coordenada.letra;
}


int ObtemNumCoordenada(tCoordenada coordenada){
    return coordenada.num;
}





tNavio CriaNavio(char tipoNavio[], int idNavio, int orientacaoNavio, 
char coordIniLetra, int coordIniNum){
    tNavio navio;
    int i = 0;
    while(tipoNavio[i]){
        navio.tipo[i] = tipoNavio[i];
        i++;
    }
    navio.tipo[i] = '\0';
    navio.id = idNavio;
    navio.orientacao = orientacaoNavio;
    // Define o tamanho do navio de acordo com o tipo
    if(tipoNavio[0] == 'D'){
        navio.tamanho = 2;
    }
    if(tipoNavio[0] == 'S'){
        navio.tamanho = 3;
    }
    if(tipoNavio[0] == 'C' && tipoNavio[1] == 'r'){
        navio.tamanho = 3;
    }
    if(tipoNavio[0] == 'B'){
        navio.tamanho = 4;
    }
    if(tipoNavio[0] == 'C' && tipoNavio[1] == 'a'){
        navio.tamanho = 5;
    }
    navio.partesNaoAfundadas = navio.tamanho;

    return navio;
}


int ObtemPartesNaoAfundadasNavio(tNavio navio){
    return navio.partesNaoAfundadas;
}


tNavio DecrescePartesNaoAfundadasNavio(tNavio navio){
    navio.partesNaoAfundadas--;
    return navio;
}


void ObtemTipoNavio(tNavio navio, char tipo[]){
    int i = 0;
    while(navio.tipo[i]){
        tipo[i] = navio.tipo[i];
        i++;
    }
    tipo[i] = '\0';
}


int ObtemIdNavio(tNavio navio){
    return navio.id;
}





tTabuleiro CriaTabuleiro(FILE * pFileTabu){
    tTabuleiro tabuleiro;
    tabuleiro.pecaAgua = PECA_AGUA;
    tabuleiro.pecaNavio = PECA_NAVIO;
    tabuleiro.pecaVazio = PECA_VAZIO;
    tabuleiro.validadePosicaoNavios = 1;
    tabuleiro.qntBattleship = 0;
    tabuleiro.qntCarrier = 0;
    tabuleiro.qntCruiser = 0;
    tabuleiro.qntDestroyer = 0;
    tabuleiro.qntSubmarine = 0;

    // Marca todas as posicoes do tabuleiro com agua
    int i = 0, j = 0, l = 0;
    for(i='a'; i <= TAM_TABU_ALT; i++){
        for(j=0; j < TAM_TABU_LARG; j++){
            tabuleiro.matriz[l][j] = tabuleiro.pecaAgua;
        }
        l++;
    }

    // Marca todas as posicoes do tabuleiro de jogo com vazio
    i = 0, j = 0, l = 0;
    for(i='a'; i <= TAM_TABU_ALT; i++){
        for(j=0; j < TAM_TABU_LARG; j++){
            tabuleiro.matrizAtual[l][j] = tabuleiro.pecaVazio;
        }
        l++;
    }
    
    char tipoNavio[11], coordIniLetra;
    int idNavio, orientacaoNavio, coordIniNum, rtn, tamanhoNavio, b = 0;
    i = 0;
    while(!feof(pFileTabu)){
        // Leitura das informações de um navio
        rtn = fscanf(pFileTabu, "%[^;];%d;%d;%c%d", tipoNavio, &idNavio, &orientacaoNavio, 
        &coordIniLetra, &coordIniNum);
        fscanf(pFileTabu, "%*[^\n]");
        fscanf(pFileTabu, "\n");

        // Se nao conseguiu ler todos os dados do navio
        if(rtn != 5){
            printf("Falha ao ler informacoes do navio [%s] [%d]", tipoNavio, rtn);
            exit(1);
        }

        tabuleiro.navios[i] = CriaNavio(tipoNavio, idNavio, orientacaoNavio, 
        coordIniLetra, coordIniNum);

        // Obtem o tamanho do navio de acordo com o tipo e incrementa qnt
        if(tipoNavio[0] == 'D'){
            tabuleiro.qntDestroyer++;
            tamanhoNavio = 2;
        }
        if(tipoNavio[0] == 'S'){
            tabuleiro.qntSubmarine++;
            tamanhoNavio = 3;
        }
        if(tipoNavio[0] == 'C' && tipoNavio[1] == 'r'){
            tabuleiro.qntCruiser++;
            tamanhoNavio = 3;
        }
        if(tipoNavio[0] == 'B'){
            tabuleiro.qntBattleship++;
            tamanhoNavio = 4;
        }
        if(tipoNavio[0] == 'C' && tipoNavio[1] == 'a'){
            tabuleiro.qntCarrier++;
            tamanhoNavio = 5;
        }

        int coordNum = coordIniNum;
        char coordLetra = coordIniLetra;
        // Verifica se a coordenada inicial esta dentro do tabuleiro
        if(coordIniLetra > TAM_TABU_ALT){
            tabuleiro.validadePosicaoNavios = 0;
            return tabuleiro;
        }
        if(coordIniNum > TAM_TABU_LARG){
            tabuleiro.validadePosicaoNavios = 0;
            return tabuleiro;
        }
        
        // Preenche as coordenadas do navio e verifica se estao dentro do tabuleiro
        int a = 0;
        for(a=0; a < tamanhoNavio; a++){
            // Se o navio esta na horizontal
            if(orientacaoNavio == 1){
                // Se a coordenada passa do limite do tabuleiro
                if(coordNum > TAM_TABU_LARG){
                    tabuleiro.validadePosicaoNavios = 0;
                    return tabuleiro;
                }
                else{
                    tabuleiro.validadePosicaoNavios = 1;
                    // Marca a parte do navio no tabuleiro;
                    tabuleiro.matriz[coordLetra-'a'][coordNum-1] = tabuleiro.pecaNavio;
                }
                // Guarda a coordenada do navio em um vetor com todas as coordenadas
                // ocupadas do tabuleiro
                tabuleiro.coordenadasOcupadas[b] = CriaCoordenada(idNavio, coordLetra, 
                coordNum);
                coordNum++;
                b++;
                
            }

            // Se o navio esta na vertical
            if(orientacaoNavio == 0){
                // Se a coordenada passa do limite do tabuleiro
                if(coordLetra > TAM_TABU_ALT){
                    tabuleiro.validadePosicaoNavios = 0;
                    return tabuleiro;
                }
                else{
                    tabuleiro.validadePosicaoNavios = 1;
                    // Marca a parte do nvaio no tabuleiro;
                    tabuleiro.matriz[coordLetra-'a'][coordNum-1] = PECA_NAVIO;
                }
                // Guarda a coordenada do navio em um vetor com todas as coordenadas
                // ocupadas do tabuleiro
                tabuleiro.coordenadasOcupadas[b] = CriaCoordenada(idNavio, coordLetra, 
                coordNum);
                coordLetra += 1; // Muda para a prox letra do alfabeto;
                b++;
            }
        }
        i++;
        }
        tabuleiro.qntNaviosNaoAfundados = tabuleiro.qntBattleship +
        tabuleiro.qntCarrier + tabuleiro.qntCruiser + tabuleiro.qntDestroyer + 
        tabuleiro.qntSubmarine;
    return tabuleiro;
}


int ObtemValidadePosicaoNaviosTabuleiro(tTabuleiro tabuleiro){
    return tabuleiro.validadePosicaoNavios;
}


int ObtemQntCarrierTabuleiro(tTabuleiro tabuleiro){
    return tabuleiro.qntCarrier;
}


int ObtemQntBattleshipTabuleiro(tTabuleiro tabuleiro){
    return tabuleiro.qntBattleship;
}


int ObtemQntCruiserTabuleiro(tTabuleiro tabuleiro){
    return tabuleiro.qntCruiser;
}


int ObtemQntSubmarineTabuleiro(tTabuleiro tabuleiro){
    return tabuleiro.qntSubmarine;
}


int ObtemQntDestroyerTabuleiro(tTabuleiro tabuleiro){
    return tabuleiro.qntDestroyer;
}


int ObtemQntNaviosNaoAfundadosTabuleiro(tTabuleiro tabuleiro){
    return tabuleiro.qntNaviosNaoAfundados;
}


int QntNaviosNaMesmaCoordTabuleiro(tTabuleiro tabuleiro,  char coordLetra, 
int coordNum){
    int i = 0, cont = 0;
    int qntCoords = (tabuleiro.qntBattleship * 4) + (tabuleiro.qntCarrier * 5) + 
    (tabuleiro.qntCruiser * 3) + (tabuleiro.qntDestroyer * 2) + 
    (tabuleiro.qntSubmarine * 3);
    // Varre o vetor de coordenadas ocupadas do tabuleiro e retorna a ocorrencia
    // da coordenada passada como argumento
    while(i < qntCoords){
        if(coordNum == ObtemNumCoordenada(tabuleiro.coordenadasOcupadas[i]) && 
        coordLetra == ObtemLetraCoordenada(tabuleiro.coordenadasOcupadas[i]))
            cont++;
        i++;
    }
    return cont;
}


int ObtemIdNavioCoordTabuleiro(tTabuleiro tabuleiro,  char coordLetra, int coordNum){
    int i = 0;
    int qntCoords = (tabuleiro.qntBattleship * 4) + (tabuleiro.qntCarrier * 5) + 
    (tabuleiro.qntCruiser * 3) + (tabuleiro.qntDestroyer * 2) + 
    (tabuleiro.qntSubmarine * 3);
    // Varre as coordenadas ocupadas do tabuleiro e retorna o id do navio
    // que esta na coordenada passada como argumento
    while(i < qntCoords){
        if(coordNum == ObtemNumCoordenada(tabuleiro.coordenadasOcupadas[i]) && 
        coordLetra == ObtemLetraCoordenada(tabuleiro.coordenadasOcupadas[i]))
            return ObtemIdNavioCoordenada(tabuleiro.coordenadasOcupadas[i]);
        i++;
    }
    printf("FALHOU AO ENCONTRAR ID DO NAVIO [FUNC ObtemIdNavioCoordTabuleiro]\n");
    return 0;
}


int HaNaviosEncostadosTabuleiro(tTabuleiro tabuleiro){
    int j = 0, idNavioCoordAtual, idNavioProximo, l = 0, c = 0;
    char i = 'a';
    // Varre toda a matriz do tabuleiro
    for(i='a'; i <= TAM_TABU_ALT; i++){
        c = 0;
        for(j=1; j <= TAM_TABU_LARG; j++){
            if(tabuleiro.matriz[l][c] == PECA_NAVIO){
                // Verifica se ha navios sobrepostos na coordenada atual
                if(QntNaviosNaMesmaCoordTabuleiro(tabuleiro, i, j) > 1)
                    return 1;

                idNavioCoordAtual = ObtemIdNavioCoordTabuleiro(tabuleiro, i, j);

                // Verifica se ha partes de navios ao redor da coord atual

                // Diagonal superior esquerda
                if(i > 'a' && j > 1){
                    if(tabuleiro.matriz[l-1][c-1] == PECA_NAVIO){
                        return 1;
                    }
                }
                // Em cima
                if(i > 'a'){
                    if(tabuleiro.matriz[l-1][c] == PECA_NAVIO){
                        idNavioProximo = ObtemIdNavioCoordTabuleiro(tabuleiro, i-1, j);
                        if(idNavioCoordAtual != idNavioProximo) return 1;
                    }
                }
                // Diagonal superior direita
                if(i > 'a' && j < TAM_TABU_LARG){
                    if(tabuleiro.matriz[l-1][c+1] == PECA_NAVIO){
                        return 1;
                    }
                }
                // Esquerda
                if(j > 1){
                    if(tabuleiro.matriz[l][c-1] == PECA_NAVIO){
                        idNavioProximo = ObtemIdNavioCoordTabuleiro(tabuleiro, i, j-1);
                        if(idNavioCoordAtual != idNavioProximo) return 1;
                    }
                }
                // Direita
                if(j < TAM_TABU_LARG){
                    if(tabuleiro.matriz[l][c+1] == PECA_NAVIO){
                        idNavioProximo = ObtemIdNavioCoordTabuleiro(tabuleiro, i, j+1);
                        if(idNavioCoordAtual != idNavioProximo) return 1;
                    }
                }
                // Diagonal inferior esquerda
                if(i < TAM_TABU_ALT && j > 1){
                    if(tabuleiro.matriz[l+1][c-1] == PECA_NAVIO){
                        return 1;
                    }
                }
                // Em baixo
                if(i < TAM_TABU_ALT){
                    if(tabuleiro.matriz[l+1][c] == PECA_NAVIO){
                        idNavioProximo = ObtemIdNavioCoordTabuleiro(tabuleiro, i+1, j);
                        if(idNavioCoordAtual != idNavioProximo) return 1;
                    }
                }
                //Diagonal inferior direita
                if(i < TAM_TABU_ALT && j < TAM_TABU_LARG){
                    if(tabuleiro.matriz[l+1][c+1] == PECA_NAVIO){
                        return 1;
                    }
                }
            }
            c++;
        }
        l++;
    }
    return 0;
}


int EhValidoTabuleiro(tTabuleiro tabuleiro){
    if(ObtemValidadePosicaoNaviosTabuleiro(tabuleiro) == 0)
        return 0;    
    if(HaNaviosEncostadosTabuleiro(tabuleiro))
        return 0;
    return 1;
}


int JaFoiAtingidaCoordTabuleiroAtual(tTabuleiro tabuleiro, char coordLetra, 
int coordNum){
    if(tabuleiro.matrizAtual[coordLetra-'a'][coordNum-1] != tabuleiro.pecaVazio){
        return 1;
    }
    return 0;
}


int TemNavioNaCoordTabuleiro(tTabuleiro tabuleiro, char coordLetra, 
int coordNum){
    if(tabuleiro.matriz[coordLetra-'a'][coordNum-1] == tabuleiro.pecaNavio){
        return 1;
    }
    return 0;
}


tNavio ObtemNavioPeloIdTabuleiro(tTabuleiro tabuleiro, int idNavio){
    int i = 0;
    int qntNavios = tabuleiro.qntBattleship + tabuleiro.qntCarrier + 
    tabuleiro.qntCruiser + tabuleiro.qntDestroyer + 
    tabuleiro.qntSubmarine;
    while(i < qntNavios){
        if(ObtemIdNavio(tabuleiro.navios[i]) == idNavio){
            return tabuleiro.navios[i];
        }
        i++;
    }
    printf("ERRO FUNC ObtemNavioPeloIdTabuleiro");
    return tabuleiro.navios[0];
}


tTabuleiro AlteraTiroMatrizAtualTabuleiro(tTabuleiro tabuleiro, char coordLetra, 
int coordNum){
    tabuleiro.matrizAtual[coordLetra-'a'][coordNum-1] = tabuleiro.pecaNavio;
    return tabuleiro;
}


tTabuleiro AlteraAguaMatrizAtualTabuleiro(tTabuleiro tabuleiro, char coordLetra, 
int coordNum){
    tabuleiro.matrizAtual[coordLetra-'a'][coordNum-1] = tabuleiro.pecaAgua;
    return tabuleiro;
}


tTabuleiro AlteraPartesNaoAfundadasNavioTabuleiro(tTabuleiro tabuleiro, 
int idNavio){
    int i = 0;
    int qntNavios = tabuleiro.qntBattleship + tabuleiro.qntCarrier + 
    tabuleiro.qntCruiser + tabuleiro.qntDestroyer + 
    tabuleiro.qntSubmarine;
    while(i < qntNavios){
        if(ObtemIdNavio(tabuleiro.navios[i]) == idNavio){
            tabuleiro.navios[i] = DecrescePartesNaoAfundadasNavio(
                tabuleiro.navios[i]);
            return tabuleiro;
        }
        i++;
    }
    printf("ERRO FUNC AlteraPartesNaoAfundadasNavioTabuleiro\n");
    return tabuleiro;
}


tTabuleiro DecresceQntNaviosNaoAfundadosTabuleiro(tTabuleiro tabuleiro){
    tabuleiro.qntNaviosNaoAfundados--;
    return tabuleiro;
}


void ImprimeMatrizTabuleiro(tTabuleiro tabuleiro){
    char i = 'a';
    int j = 0, l = 0;
    for(i='a'; i <= TAM_TABU_ALT; i++){
        for(j=0; j < TAM_TABU_LARG; j++){
            printf("%c ", tabuleiro.matriz[l][j]);
        }
        printf("\n");
        l++;
    }
    printf("\n");
}


void ImprimeMatrizTabuleiroNoArquivo(tTabuleiro tabuleiro, FILE * pFIle){
    char i = 'a';
    int j = 0, l = 0;
    for(i='a'; i <= TAM_TABU_ALT; i++){
        for(j=0; j < TAM_TABU_LARG; j++){
            if(j+1 < TAM_TABU_LARG){
                fprintf(pFIle, "%c ", tabuleiro.matriz[l][j]);
            }
            else{
                fprintf(pFIle, "%c", tabuleiro.matriz[l][j]);
            }
        }
        if(i+1 <= TAM_TABU_ALT){
            fprintf(pFIle, "\n");
        }
        l++;
    }
}


void ImprimeMatrizAtualTabuleiro(tTabuleiro tabuleiro){
    char i = 'a';
    int j = 0, l = 0;
    for(i='a'; i <= TAM_TABU_ALT; i++){
        for(j=0; j < TAM_TABU_LARG; j++){
            if(j+1 < TAM_TABU_LARG){
                printf("%c ", tabuleiro.matrizAtual[l][j]);
            }
            else{
                printf("%c", tabuleiro.matrizAtual[l][j]);
            }
        }
        printf("\n");
        l++;
    }
}





tJogada CriaJogada(char letra, int num, int resultado){
    tJogada jogada;
    jogada.coordLetra = letra;
    jogada.coordNum = num;
    jogada.resultado = resultado;
    return jogada;
}


int ObtemResultadoJogada(tJogada jogada){
    return jogada.resultado;
}


int ObtemCoordLetraJogada(tJogada jogada){
    return jogada.coordLetra;
}


int ObtemCoordNumJogada(tJogada jogada){
    return jogada.coordNum;
}





tJogador CriaJogador(FILE * pFileTabu, int idJogador){
    tJogador jogador;
    jogador.id = idJogador;
    jogador.tabuleiro = CriaTabuleiro(pFileTabu);
    jogador.qntJogadasAgua = 0;
    jogador.qntJogadasTiro = 0;
    return jogador;
}


tJogador InicializaNomeJogador(tJogador jogador, char nome[]){
    int i = 0;
    while(nome[i]){
        jogador.nome[i] = nome[i];
        i++;
    }
    jogador.nome[i] = '\0';
    return jogador;    
}


tTabuleiro ObtemTabuleiroJogador(tJogador jogador){
    return jogador.tabuleiro;
}


void ObtemNomeJogador(tJogador jogador, char nome[]){
    int i = 0;
    while(jogador.nome[i]){
        nome[i] = jogador.nome[i];
        i++;
    }
    nome[i] = '\0';
}


tJogador MarcaJogadaJogador(tJogador jogador, char letra, int num, 
int resultado){
    int qntJogadas = jogador.qntJogadasAgua + jogador.qntJogadasTiro;
    jogador.jogadas[qntJogadas] = CriaJogada(letra, num, resultado);
    // Se acertou agua
    if(resultado == 0) jogador.qntJogadasAgua++;
    // Se acertou navio
    else if(resultado == 1) jogador.qntJogadasTiro++;
    return jogador;
}


tJogador AlteraTabuTiroJogador(tJogador jogador, char coordLetra, int coordNum){
    jogador.tabuleiro = AlteraTiroMatrizAtualTabuleiro(jogador.tabuleiro, 
    coordLetra, coordNum);
    jogador.tabuleiro = AlteraPartesNaoAfundadasNavioTabuleiro(jogador.tabuleiro, 
    ObtemIdNavioCoordTabuleiro(jogador.tabuleiro, coordLetra, coordNum));
    return jogador;
}


tJogador AlteraTabuAguaJogador(tJogador jogador, char coordLetra, int coordNum){
    jogador.tabuleiro = AlteraAguaMatrizAtualTabuleiro(jogador.tabuleiro, 
    coordLetra, coordNum);
    return jogador;
}


tJogador AlteraTabuQntNaviosNaoAfundadosJogador(tJogador jogador){
    jogador.tabuleiro = DecresceQntNaviosNaoAfundadosTabuleiro(jogador.tabuleiro);
    return jogador;
}


int AfundouTodosNaviosDoJogador(tJogador jogador){
    if(ObtemQntNaviosNaoAfundadosTabuleiro(jogador.tabuleiro) == 0)
        return 1;
    return 0;
}


void EscreveArquivoResultadoJogador(FILE * pFile, tJogador jogadorDaVez,
tJogador outroJogador){
    // Pega o nome do jogador
    char nomeJogador[TAM_NOME];
    ObtemNomeJogador(jogadorDaVez, nomeJogador);

    // Printa o nome no arquivo
    fprintf(pFile, "%s\n", nomeJogador);

    int i = 0, resultJogada, coordLetra, coordNum, idNavio;
    tNavio navio;
    char tipoNavio[11];
    int qntJogadas = jogadorDaVez.qntJogadasAgua + jogadorDaVez.qntJogadasTiro;
    // Pega cada jogada feita pelo jogador e imprime no arquivo
    while(i < qntJogadas){
        resultJogada = ObtemResultadoJogada(jogadorDaVez.jogadas[i]);
        coordLetra = ObtemCoordLetraJogada(jogadorDaVez.jogadas[i]);
        coordNum = ObtemCoordNumJogada(jogadorDaVez.jogadas[i]);
        // Se deu agua
        if(resultJogada == 0){            
            fprintf(pFile, "%c%d - Agua\n", coordLetra, coordNum);
        }
        // Se acertou navio
        else if(resultJogada == 1){
            // Pega informacoes do navio atingido e printa
            idNavio = ObtemIdNavioCoordTabuleiro(ObtemTabuleiroJogador(outroJogador),
            coordLetra, coordNum);
            navio = ObtemNavioPeloIdTabuleiro(ObtemTabuleiroJogador(outroJogador),
            idNavio);
            ObtemTipoNavio(navio, tipoNavio);
            fprintf(pFile, "%c%d - Tiro - %s - ID %.2d\n", coordLetra, coordNum, 
            tipoNavio, idNavio);
        }
        i++;
    }
    fprintf(pFile, "\n");
}


void EscreveArquivoEstatisticasJogador(FILE * pFile, tJogador jogadorDaVez,
tJogador outroJogador){
    // Pega o nome do jogador
    char nomeJogador[TAM_NOME];
    ObtemNomeJogador(jogadorDaVez, nomeJogador);

    // Printa o nome no arquivo
    fprintf(pFile, "%s\n", nomeJogador);

    fprintf(pFile, "Tiros Errados: %d\n", jogadorDaVez.qntJogadasAgua);
    fprintf(pFile, "Tiros Acertados: %d\n", jogadorDaVez.qntJogadasTiro);


    // Calculo da localizacao media
    int i = 0, coordNum;
    char coordLetra;
    float somaCoordenadasNum = 0, somaCoordenadasLetra = 0;
    int qntJogadas = jogadorDaVez.qntJogadasAgua + jogadorDaVez.qntJogadasTiro;

    // Soma as coordenadas das colunas e das linhas de cada jogada
    while(i < qntJogadas){
        coordLetra = ObtemCoordLetraJogada(jogadorDaVez.jogadas[i]);
        coordNum = ObtemCoordNumJogada(jogadorDaVez.jogadas[i]);
        somaCoordenadasLetra += coordLetra - 'a' + 1;
        somaCoordenadasNum += coordNum;
        i++;
    }

    // Obtem a localizacao media dividindo as somas pelo total de jogadas
    float locMediaLinha = somaCoordenadasLetra / qntJogadas;
    float locMediaColuna = somaCoordenadasNum / qntJogadas;

    fprintf(pFile, "Localizacao Media: (%.2f,%.2f)\n", locMediaLinha, locMediaColuna);


    // Calculo do desvio padrao da localizacao media
    float somatorioDesvioPadrao = 0;
    i = 0;
    while(i < qntJogadas){
        coordLetra = ObtemCoordLetraJogada(jogadorDaVez.jogadas[i]);
        coordNum = ObtemCoordNumJogada(jogadorDaVez.jogadas[i]);
        somatorioDesvioPadrao += (pow((coordLetra-'a'+1) - locMediaLinha, 2)) + 
        (pow(coordNum - locMediaColuna, 2));
        i++;
    }
    float desvioPadrao = sqrt(somatorioDesvioPadrao / qntJogadas); 

    fprintf(pFile, "Desvio Padrao da Localizacao: %.2f\n", desvioPadrao);


    // Imprime os navios atingidos do jogador em ordem alfabetica
    fprintf(pFile, "Navios de %s:\n", nomeJogador);
    int j = 0, idNavio, resultadoJogada, contPrintados = 0;
    i = 0;
    // Roda 5 vezes - o valor de j indica qual tipo de navio sera printado
    while(j < 5){
        i = 0;
        int idNaviosJaPrintados[MAX_NAVIOS];
        contPrintados = 0;

        // Passa por todas as jogadas feitas
        while(i < qntJogadas){
            resultadoJogada = ObtemResultadoJogada(outroJogador.jogadas[i]);

            // Se acertou algum navio na jogada
            if(resultadoJogada == 1){
                // Obtem informacoes do navio atingido
                coordLetra = ObtemCoordLetraJogada(outroJogador.jogadas[i]);
                coordNum = ObtemCoordNumJogada(outroJogador.jogadas[i]);
                idNavio = ObtemIdNavioCoordTabuleiro(ObtemTabuleiroJogador(
                    jogadorDaVez), coordLetra, coordNum);
                tNavio navio = ObtemNavioPeloIdTabuleiro(ObtemTabuleiroJogador(
                    jogadorDaVez), idNavio);
                char tipoNavio[11];
                ObtemTipoNavio(navio, tipoNavio);

                // J = 0 -> Battleship
                if(j == 0){
                    if(tipoNavio[0] == 'B'){
                        // Verifica pelo ID se o navio ja foi printado
                        if(!FoiPrintadoNavioEstatisticas(idNaviosJaPrintados,
                        idNavio, contPrintados)){
                            fprintf(pFile, "%.2d - %s - ID %.2d\n", i+1, tipoNavio,
                            idNavio);
                            idNaviosJaPrintados[contPrintados] = idNavio;
                            contPrintados++;
                        }
                    }
                }
                // J = 1 -> Carrier
                else if(j == 1){
                    if(tipoNavio[0] == 'C' && tipoNavio[1] == 'a'){
                        if(!FoiPrintadoNavioEstatisticas(idNaviosJaPrintados,
                        idNavio, contPrintados)){
                            fprintf(pFile, "%.2d - %s - ID %.2d\n", i+1, tipoNavio,
                            idNavio);
                            idNaviosJaPrintados[contPrintados] = idNavio;
                            contPrintados++;
                        }
                    }
                }
                // J = 2 -> Cruiser
                else if(j == 2){
                    if(tipoNavio[0] == 'C' && tipoNavio[1] == 'r'){
                        if(!FoiPrintadoNavioEstatisticas(idNaviosJaPrintados,
                        idNavio, contPrintados)){
                            fprintf(pFile, "%.2d - %s - ID %.2d\n", i+1, tipoNavio,
                            idNavio);
                            idNaviosJaPrintados[contPrintados] = idNavio;
                            contPrintados++;
                        }
                    }
                }
                // J = 3 -> Destroyer
                else if(j == 3){
                    if(tipoNavio[0] == 'D'){
                        if(!FoiPrintadoNavioEstatisticas(idNaviosJaPrintados,
                        idNavio, contPrintados)){
                            fprintf(pFile, "%.2d - %s - ID %.2d\n", i+1, tipoNavio,
                            idNavio);
                            idNaviosJaPrintados[contPrintados] = idNavio;
                            contPrintados++;
                        }
                    }
                }
                // J = 4 -> Submarine
                else if(j == 4){
                    if(tipoNavio[0] == 'S'){
                        if(!FoiPrintadoNavioEstatisticas(idNaviosJaPrintados,
                        idNavio, contPrintados)){
                            fprintf(pFile, "%.2d - %s - ID %.2d\n", i+1, tipoNavio,
                            idNavio);
                            idNaviosJaPrintados[contPrintados] = idNavio;
                            contPrintados++;
                        }
                    }
                }
            }
            i++;
        }
        j++;
    }
}





int SaoCompativeisTabuleirosJogo(tJogador jogador1, tJogador jogador2){
    // Verifica se os tabuleiros tem as mesmas qntds de cada navio
    if(ObtemQntBattleshipTabuleiro(jogador1.tabuleiro) == 
    ObtemQntBattleshipTabuleiro(jogador2.tabuleiro) && 
    ObtemQntCarrierTabuleiro(jogador1.tabuleiro) == 
    ObtemQntCarrierTabuleiro(jogador2.tabuleiro) &&
    ObtemQntCruiserTabuleiro(jogador1.tabuleiro) == 
    ObtemQntCruiserTabuleiro(jogador2.tabuleiro) &&
    ObtemQntDestroyerTabuleiro(jogador1.tabuleiro) == 
    ObtemQntDestroyerTabuleiro(jogador2.tabuleiro) &&
    ObtemQntSubmarineTabuleiro(jogador1.tabuleiro) == 
    ObtemQntSubmarineTabuleiro(jogador2.tabuleiro)){
        return 1;
    }
    return 0;
}


tJogo InicializaJogo(char dir[]){
    tJogo jogo;
    jogo.preparado = 0;

    // Obtem caminho dir dos tabuleiros
    char nome1[1000], nome2[1000];
    sprintf(nome1, "%s/tabu_1.txt", dir);
    sprintf(nome2, "%s/tabu_2.txt", dir);


    // Abre os arquivos tabu
    FILE * pFileTab1;
    FILE * pFileTab2;
    pFileTab1 = fopen(nome1, "r");
    pFileTab2 = fopen(nome2, "r");
    if(!pFileTab1){
        printf("Nao conseguiu ler arquivo tabu1: %s", nome1);
        exit(1);
    }
    if(!pFileTab2){
        printf("Nao conseguiu ler arquivo tabu2: %s", nome2);
        exit(1);
    }


    // Inicializa jogadores e gera seus tabuleiros
    jogo.jogador1 = CriaJogador(pFileTab1, ID_JOGADOR_1);
    jogo.jogador2 = CriaJogador(pFileTab2, ID_JOGADOR_2);

    fclose(pFileTab1);
    fclose(pFileTab2);


    int validos = 0;
    // Obtem caminho dir validacao tabuleiros txt
    char nomeDirValidacaoTabus[1000];
    sprintf(nomeDirValidacaoTabus, "%s/saida/validacao_tabuleiros.txt", dir);

    // Cria o validacao tabuleiros txt para escrita
    FILE * pFileValidacaoTabus;
    pFileValidacaoTabus = fopen(nomeDirValidacaoTabus, "w");

    // Verifica se tabuleiros sao validos e escreve no validacao tabus txt
    if(EhValidoTabuleiro(ObtemTabuleiroJogador(jogo.jogador1))){
        fprintf(pFileValidacaoTabus, "tabu_1.txt;valido\n");
        validos++;
    }
    else fprintf(pFileValidacaoTabus, "tabu_1.txt;invalido\n");

    if(EhValidoTabuleiro(ObtemTabuleiroJogador(jogo.jogador2))){
        fprintf(pFileValidacaoTabus, "tabu_2.txt;valido");
        validos++;
    }
    else fprintf(pFileValidacaoTabus, "tabu_2.txt;invalido");


    // Se os tabuleiros forem validos os compara
    if(validos == 2){
        // Se forem compativeis gera o arquivo inicializacao
        if(SaoCompativeisTabuleirosJogo(jogo.jogador1, jogo.jogador2)){
            // Se os tabus sao compativeis o jogo esta preparado
            jogo.preparado = 1;

            // Completa o validacao_tabuleiros
            fprintf(pFileValidacaoTabus, "\nTabuleiros compativeis entre si");

            // Leitura dos nomes dos jogadores
            char nomeJogador1[TAM_NOME];
            char nomeJogador2[TAM_NOME];
            printf("Nome do Jogador 1:\n");
            scanf("%s", nomeJogador1);
            printf("Nome do Jogador 2:\n");
            scanf("%s", nomeJogador2);
            scanf("%*[^\n]");
            scanf("\n");
            jogo.jogador1 = InicializaNomeJogador(jogo.jogador1, nomeJogador1);
            jogo.jogador2 = InicializaNomeJogador(jogo.jogador2, nomeJogador2);

            // Obtem caminho dir inicializacao txt
            char nomeDirInicializacao[1000];
            sprintf(nomeDirInicializacao, "%s/saida/inicializacao.txt", dir);

            // Cria o inicializacao txt para escrita
            FILE * pFileInicializacao;
            pFileInicializacao = fopen(nomeDirInicializacao, "w");

            // Escreve no inicializacao txt
            fprintf(pFileInicializacao, "%s\n", nomeJogador1);
            ImprimeMatrizTabuleiroNoArquivo(ObtemTabuleiroJogador(jogo.jogador1), 
            pFileInicializacao);
            fprintf(pFileInicializacao, "\n\n%s\n", nomeJogador2);
            ImprimeMatrizTabuleiroNoArquivo(ObtemTabuleiroJogador(jogo.jogador2), 
            pFileInicializacao);

            fclose(pFileInicializacao);
        }
        else{
            fprintf(pFileValidacaoTabus, "\nTabuleiros incompativeis entre si");
        }
    }

    fclose(pFileValidacaoTabus);    
    return jogo;
}


int EstaPreparadoJogo(tJogo jogo){
    return jogo.preparado;
}


tJogo JogadorEfetuaJogadaJogo(tJogo jogo, char nome1[], char nome2[], 
int jogadorDaVez){
    int jogadaValida = 0, rtn = 0, coordNum = 0, flag = 0, cont = 0;
    char coordLetra, c;

    if(jogadorDaVez == 1)
        printf("\nJogada de %s:\n\n", nome1);
    else
        printf("\nJogada de %s:\n\n", nome2);
    
    while(jogadaValida == 0){
        scanf("%c", &coordLetra);
        scanf("%c", &c);

        // rtn = 2 -> Leu um caractere e um numero,  rtn = 1 -> leu um caractere
        // e nao leu um numero
        // flag = 0 -> informou somente a coordenada,  flag = 1 -> informou 
        // outro(s) caractere(s) alem da coordenada

        if(c == '\n'){
            rtn = 1;
            flag = 0;
        }
        // Se c nao eh numero
        else if(c < '0' || c > '9'){
            rtn = 1;
            flag = 1;
        }
        // Se c eh numero
        else{
            rtn = 2;
            coordNum = c - '0';
            // Roda ate ler um caractere que nao seja numero ou nao conseguir ler nada
            while(1){
                if(scanf("%c", &c) != 1){
                    flag = 0;
                    break;
                }
                if(c < '0' || c > '9'){
                    if(c == '\n') flag = 0;
                    else flag = 1;
                    break;
                }
                // Se for numero, completa o numero da coordenada
                else{
                    coordNum = (coordNum*10) + (c - '0');
                }
            }
        }

        // Se conseguir ler um caractere e um numero
        if(rtn == 2){

            // Se a coordenada esta no tabuleiro
            if((coordLetra >= 'a' && coordLetra <= TAM_TABU_ALT) &&
            (coordNum >= 1 && coordNum <= TAM_TABU_LARG)){
                
                // Se informou mais caracteres alem da coordenada
                if(flag == 1){

                    // Printa a jogada invalida
                    printf("%c%d%c", coordLetra, coordNum, c);
                    while(1){
                        scanf("%c", &c);
                        if(c == '\n') break;
                        else printf("%c", c);
                    }
                    if(jogadorDaVez == 1)
                        printf(":Jogada invalida! Jogue novamente %s:\n\n", nome1);
                    else
                        printf(":Jogada invalida! Jogue novamente %s:\n\n", nome2);
                    jogadaValida = 0;
                }
                // Se informou somente a coordenada
                else{
                    if(jogadorDaVez == 1){
                        if(JaFoiAtingidaCoordTabuleiroAtual(ObtemTabuleiroJogador(
                            jogo.jogador2), coordLetra, coordNum)){
                            printf("%c%d:Jogada invalida! Jogue novamente %s:\n\n", 
                            coordLetra, coordNum, nome1);
                            jogadaValida = 0;
                        }
                        // Se a coordenada ainda nao foi jogada 
                        else{
                            jogadaValida = 1;
                            // Se acertou algum navio
                            if(TemNavioNaCoordTabuleiro(ObtemTabuleiroJogador(
                            jogo.jogador2), coordLetra, coordNum)){
                                // Guarda a jogada feita e seu resultado
                                jogo.jogador1 = MarcaJogadaJogador(jogo.jogador1, 
                                coordLetra, coordNum, 1);

                                // Marca tiro na matriz atual
                                jogo.jogador2 = AlteraTabuTiroJogador(jogo.jogador2,
                                coordLetra, coordNum);

                                // Obtem o navio atingido
                                int idNavAtingido = (ObtemIdNavioCoordTabuleiro(
                                    ObtemTabuleiroJogador(jogo.jogador2), coordLetra,
                                    coordNum));
                                tNavio navioAtingido = ObtemNavioPeloIdTabuleiro(
                                    ObtemTabuleiroJogador(jogo.jogador2), 
                                    idNavAtingido);
                                int partesNaoAfundadasNavAtingido = 
                                    ObtemPartesNaoAfundadasNavio(navioAtingido);

                                // Se o navio afundou
                                if(partesNaoAfundadasNavAtingido == 0){
                                    char tipo[11];
                                    ObtemTipoNavio(navioAtingido, tipo);
                                    printf("%c%d:Afundou %s\n\n", coordLetra, coordNum, 
                                    tipo);
                                    jogo.jogador2 = AlteraTabuQntNaviosNaoAfundadosJogador(
                                    jogo.jogador2);
                                }
                                else printf("%c%d:Tiro!\n\n", coordLetra, coordNum);
                            }
                            // Se nao acertou nenhum navio
                            else{
                                // Guarda a jogada feita e seu resultado
                                jogo.jogador1 = MarcaJogadaJogador(jogo.jogador1, 
                                coordLetra, coordNum, 0); 
                                // Marca agua na matriz atual
                                jogo.jogador2 = AlteraTabuAguaJogador(jogo.jogador2,
                                coordLetra, coordNum);
                                printf("%c%d:Agua\n\n", coordLetra, coordNum);
                            }
                        }
                    }
                    else if(jogadorDaVez == 2){
                        if(JaFoiAtingidaCoordTabuleiroAtual(ObtemTabuleiroJogador(
                            jogo.jogador1), coordLetra, coordNum)){
                            printf("%c%d:Jogada invalida! Jogue novamente %s:\n\n", 
                            coordLetra, coordNum, nome2);
                            jogadaValida = 0;
                        }
                        // Se a coordenada ainda nao foi jogada 
                        else{
                            jogadaValida = 1;
                            // Se acertou algum navio
                            if(TemNavioNaCoordTabuleiro(ObtemTabuleiroJogador(
                            jogo.jogador1), coordLetra, coordNum)){

                                // Guarda a jogada feita e seu resultado
                                jogo.jogador2 = MarcaJogadaJogador(jogo.jogador2, 
                                coordLetra, coordNum, 1);

                                // Marca tiro na matriz atual
                                jogo.jogador1 = AlteraTabuTiroJogador(jogo.jogador1,
                                coordLetra, coordNum);

                                // Obtem o navio atingido
                                int idNavAtingido = (ObtemIdNavioCoordTabuleiro(
                                    ObtemTabuleiroJogador(jogo.jogador1), coordLetra,
                                    coordNum));
                                tNavio navioAtingido = ObtemNavioPeloIdTabuleiro(
                                    ObtemTabuleiroJogador(jogo.jogador1), 
                                    idNavAtingido);
                                int partesNaoAfundadasNavAtingido = 
                                    ObtemPartesNaoAfundadasNavio(navioAtingido);

                                // Se o navio afundou
                                if(partesNaoAfundadasNavAtingido == 0){
                                    char tipo[11];
                                    ObtemTipoNavio(navioAtingido, tipo);
                                    printf("%c%d:Afundou %s\n\n", coordLetra, coordNum, 
                                    tipo);
                                    jogo.jogador1 = AlteraTabuQntNaviosNaoAfundadosJogador(
                                    jogo.jogador1);
                                }
                                else printf("%c%d:Tiro!\n\n", coordLetra, coordNum);
                            }
                            // Se nao acertou nenhum navio
                            else{
                                // Guarda a jogada feita e seu resultado
                                jogo.jogador2 = MarcaJogadaJogador(jogo.jogador2, 
                                coordLetra, coordNum, 0); 
                                // Marca agua na matriz atual
                                jogo.jogador1 = AlteraTabuAguaJogador(jogo.jogador1,
                                coordLetra, coordNum);
                                printf("%c%d:Agua\n\n", coordLetra, coordNum);
                            }
                        }
                    }
                }                        
            }
            // Se a coordenada nao esta no tabuleiro
            else{
                // Se tiver mais caracteres alem da coordenada
                if(flag == 1){
                    // Printa a jogada invalida
                    printf("%c%d%c", coordLetra, coordNum, c);
                    while(1){
                        scanf("%c", &c);
                        if(c == '\n') break;
                        else printf("%c", c);
                    }
                    if(jogadorDaVez == 1)
                        printf(":Jogada invalida! Jogue novamente %s:\n\n", nome1);
                    else
                        printf(":Jogada invalida! Jogue novamente %s:\n\n", nome2);
                    jogadaValida = 0;
                }
                // Se informou somente a coordenada
                else{
                    if(jogadorDaVez == 1)
                        printf("%c%d:Jogada invalida! Jogue novamente %s:\n\n", 
                        coordLetra, coordNum, nome1);
                    else
                        printf("%c%d:Jogada invalida! Jogue novamente %s:\n\n", 
                        coordLetra, coordNum, nome2);                    
                    jogadaValida = 0;
                }
            }
        }
        // Se nao conseguir ler um caractere e um numero
        else if(rtn == 1){

            // Se leu mais de um caractere
            if(flag == 1){
                // Printa a jogada invalida
                printf("%c%c", coordLetra, c);
                while(1){
                    scanf("%c", &c);
                    if(c == '\n') break;
                    else printf("%c", c);
                }
                if(jogadorDaVez == 1)
                    printf(":Jogada invalida! Jogue novamente %s:\n\n", nome1);
                else
                    printf(":Jogada invalida! Jogue novamente %s:\n\n", nome2);                
                jogadaValida = 0;
            }
            // Se leu somente um caractere
            else{
                if(jogadorDaVez == 1)
                    printf("%c:Jogada invalida! Jogue novamente %s:\n\n", coordLetra,
                    nome1);
                else
                    printf("%c:Jogada invalida! Jogue novamente %s:\n\n", coordLetra,
                    nome2);                
                jogadaValida = 0;
            }

        }
    }
    if(jogadorDaVez == 1)
        printf("Tabuleiro atual de %s apos a jogada de %s\n", nome2, nome1);
    else
        printf("Tabuleiro atual de %s apos a jogada de %s\n", nome1, nome2);
    
    return jogo;    
}





tJogo RealizarJogo(tJogo jogo){
    // Pega o nome dos jogadores
    char nome1[TAM_NOME];
    ObtemNomeJogador(jogo.jogador1, nome1);
    char nome2[TAM_NOME];
    ObtemNomeJogador(jogo.jogador2, nome2);

    int venceu1 = 0, venceu2 = 0;
    // Ate ter algum vencedor ou empate
    while(1){
        // Jogada do jogador 1
        jogo = JogadorEfetuaJogadaJogo(jogo, nome1, nome2, 1);
        ImprimeMatrizAtualTabuleiro(ObtemTabuleiroJogador(jogo.jogador2));
        if(AfundouTodosNaviosDoJogador(jogo.jogador2)){
            venceu1 = 1;
        }

        // Jogada do jogador 2
        jogo = JogadorEfetuaJogadaJogo(jogo, nome1, nome2, 2);
        ImprimeMatrizAtualTabuleiro(ObtemTabuleiroJogador(jogo.jogador1));
        if(venceu1 == 1 && !AfundouTodosNaviosDoJogador(jogo.jogador1)){
            // JOGADOR 1 GANHOU
            jogo.resultado = 1;
            printf("\nVencedor: %s\n", nome1);
        }
        else if(venceu1 == 1 && AfundouTodosNaviosDoJogador(jogo.jogador1)){
            // EMPATOU
            jogo.resultado = 3;
            venceu2 = 1;
            printf("\nEmpate\n");
        }        
        else if(venceu1 == 0 && AfundouTodosNaviosDoJogador(jogo.jogador1)){
            // JOGADOR 2 GANHOU
            jogo.resultado = 2;
            venceu2 = 1;
            printf("\nVencedor: %s\n", nome2);
        }

        if(venceu1 == 1 || venceu2 == 1) break;
    }
    return jogo;
}


void GeraResumoResultadoJogo(tJogo jogo, char dir[]){
    // Obtem caminho dir resultado txt
    char nomeDirResultado[1000];
    sprintf(nomeDirResultado, "%s/saida/resultado.txt", dir);

    // Cria o resultado txt para escrita
    FILE * pFileResultado;
    pFileResultado = fopen(nomeDirResultado,"w");

    // Escreve as jogadas do jogador 1
    EscreveArquivoResultadoJogador(pFileResultado, jogo.jogador1, jogo.jogador2);
    // Escreve as jogadas do jogador 2
    EscreveArquivoResultadoJogador(pFileResultado, jogo.jogador2, jogo.jogador1);

    // Escreve o resultado do jogo
    char nomeJogador1[TAM_NOME];
    char nomeJogador2[TAM_NOME];
    ObtemNomeJogador(jogo.jogador1, nomeJogador1);
    ObtemNomeJogador(jogo.jogador2, nomeJogador2);
    if(jogo.resultado == 1) fprintf(pFileResultado, "Vencedor: %s", 
    nomeJogador1);
    else if(jogo.resultado == 2) fprintf(pFileResultado, "Vencedor: %s", 
    nomeJogador2);
    else if(jogo.resultado == 3) fprintf(pFileResultado, "Empate");

    fclose(pFileResultado);
}


int FoiPrintadoNavioEstatisticas(int idNaviosJaPrintados[], 
int idNavio, int contPrintados){
    int i = 0;
    for(i=0; i < contPrintados; i++){
        if(idNavio == idNaviosJaPrintados[i])
            return 1;
    }
    return 0;
}


void GeraEstatisticasJogo(tJogo jogo, char dir[]){
    // Obtem caminho dir estatisticas txt
    char nomeDirEstatisticas[1000];
    sprintf(nomeDirEstatisticas, "%s/saida/estatisticas.txt", dir);

    // Cria o estatisticas txt para escrita
    FILE * pFileEstatisticas;
    pFileEstatisticas = fopen(nomeDirEstatisticas,"w");

    // Escreve as estatisticas do jogador 1
    EscreveArquivoEstatisticasJogador(pFileEstatisticas, jogo.jogador1, 
    jogo.jogador2);
    fprintf(pFileEstatisticas, "\n");
    // Escreve as estatisticas do jogador 1
    EscreveArquivoEstatisticasJogador(pFileEstatisticas, jogo.jogador2, 
    jogo.jogador1);

    fclose(pFileEstatisticas);
}