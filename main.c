#include <stdio.h>
#include <stdlib.h>

// Função responsavel por gerar todas as combinações possíveis de arquivos nos pen drives
// Recebe como entrada os tamanhos dos arquivos, o número de arquivos, o espaço disponível, um array para manter o controle dos arquivos visitados e a posição atual na lista de arquivos.
void gerarCombinacoes(int *tamanho_arquivos, int num_arquivos, int espaco_pendrive, int *visitados, int posicao) {
  int soma = 0;
  int somab = 0;

  // Verifica se todas as posições da lista de arquivos foram visitadas
  if (posicao == num_arquivos) {
    for (int i = 0; i < num_arquivos; i++) {
      if (visitados[i]) {
        soma += tamanho_arquivos[i];
      }
    }

    // Verifica se a soma dos tamanhos dos arquivos não excede o espaço disponível em ambos os pen drives
    if (posicao == num_arquivos) {
      for (int i = 0; i < num_arquivos; i++) {
        if (!visitados[i]) {
          somab += tamanho_arquivos[i];
        }
      }
      if (soma <= espaco_pendrive && somab <= espaco_pendrive) {
        // Imprime os arquivos nos pen drives A e B
        printf("Pen drive A: ");
        for (int i = 0; i < num_arquivos; i++) {
          if (visitados[i]) {
            printf("%d ", tamanho_arquivos[i]);
          }
        }
        printf("\n");

        printf("Pen drive B: ");
        for (int i = 0; i < num_arquivos; i++){
          if (!visitados[i]) {
            printf("%d ", tamanho_arquivos[i]);
          }
        }
        printf("\n\n");
      }
      return;
    }
  }

  // Verifica se o tamanho do arquivo na posição atual cabe no espaço disponível
  if (tamanho_arquivos[posicao] <= espaco_pendrive) {
    visitados[posicao] = 1;
    gerarCombinacoes(tamanho_arquivos, num_arquivos, espaco_pendrive, visitados, posicao+1);
    visitados[posicao] = 0;
  }

  // Chama a função recursivamente para a próxima posição na lista de arquivos
  gerarCombinacoes(tamanho_arquivos, num_arquivos, espaco_pendrive, visitados, posicao+1);
}

// Função responsavel por organizar os arquivos de um pendrive para o outro
void reorganizarArquivos(int *tamanho_arquivos, int num_arquivos, int espaco_total) {
  int *comb_atual = (int *)malloc(num_arquivos * sizeof(int));
  int *visitados = (int *)malloc(num_arquivos * sizeof(int));
  
  if (comb_atual == NULL || visitados == NULL) {
    printf("Erro ao alocar memória.\n");
    exit(1);
  }
  
  // Chama a função para gerar combinações de arquivos nos pen drives
  gerarCombinacoes(tamanho_arquivos, num_arquivos, espaco_total / 2, visitados, 0);

  free(comb_atual);
  free(visitados);
}

// Função que analisa cada arquivo para retornar o espaço total utilizado
int verificarEspaco(int espaco_total, int num_arquivos, int tamanho_arquivos[]) {
  int soma = 0;

  // Calcula a soma dos tamanhos dos arquivos e verifica se algum arquivo é maior do que a metade do espaço disponível
  for (int i = 0; i < num_arquivos; i++) {
    soma += tamanho_arquivos[i];
    
    if (tamanho_arquivos[i] > espaco_total/2) {
      return 0;
    }

    if (soma >= espaco_total) {
      return 0;
    }
  }
  return 1;
}

// Main responsavel por realizar o código
int main() {
  FILE *arquivo;
  int num_testes, espaco_total, num_arquivos;

  // Abre o arquivo de entrada
  arquivo = fopen("backup.in", "r"); // Abrimos as informações do arquivo

  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return 1;
  }

  // Lê o número de testets do arquivo de entrada
  fscanf(arquivo, "%d", &num_testes);

  for (int i = 0; i < num_testes; i++) {
    // Lê o espaço total e o número de arquivos para o teste atual
    fscanf(arquivo, "%d %d", &espaco_total, &num_arquivos);

    // Cria um array para armazenar os tamanhos dos arquivos
    int tamanho_arquivos[num_arquivos];

    // Lê os tamanhos dos arquivos do arquivo de entrada
    for (int j = 0; j < num_arquivos; j++) {
      fscanf(arquivo, "%d", &tamanho_arquivos[j]);
    }

    // Verifica se é possível gravar todos os arquivos nos pen drives
    if (verificarEspaco(espaco_total, num_arquivos, tamanho_arquivos)) {
      printf("Teste %d:\n", i+1);
      printf("Espaço total: %d GB\n", espaco_total);
      printf("Número de arquivos: %d\n", num_arquivos);
      printf("Tamanho dos arquivos: ");

      // Imprime os tamanhos dos arquivos
      for (int j = 0; j < num_arquivos; j++) {
        printf("%d GB; ", tamanho_arquivos[j]);
      }

      printf("\n\n");

      // Chama a função para reorganizar os arquivos nos pen drives
      reorganizarArquivos(tamanho_arquivos, num_arquivos, espaco_total);
      
    }

    else {
      printf("Teste %d:\n", i+1);
      printf("Impossível gravar todos os arquivos nos pen drives.");
    }

    printf("\n\n");
  }

  // Fecha o arquivo de entrada
  fclose(arquivo);
  return 0;
}
