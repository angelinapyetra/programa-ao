#include <stdio.h>
#include <string.h>
#include <unistd.h>  


typedef struct {
    char destinatario[50];
    char conteudo[160];
} Mensagem;


typedef struct {
    char nome[50];
    char telefone[15];
} Contato;


typedef struct {
    char destinatario[50];
    int duracao;  
} Chamada;


void imprimiMenu(){
    printf("Aperte 1 para ver nível de bateria\n");
    printf("Aperte 2 para ver mensagens\n");
    printf("Aperte 3 para ver histórico de ligação\n");
    printf("Aperte 4 para ver agenda\n");
    printf("Aperte 5 para ver créditos\n");
    printf("Aperte 6 para ver operadora\n");
}


void imprimiBateria(int bateria){
    printf("Bateria: %d%%\n", bateria);
    printf("Duração de mais %d horas.\n", bateria / 20);
    printf("Aperte 0 para voltar ao menu inicial.\n");
}


void imprimiMensagens(Mensagem mensagens[], int num_mensagens){
    printf("Mensagens recebidas:\n");
    for (int i = 0; i < num_mensagens; i++) {
        printf("De: %s\n", mensagens[i].destinatario);
        printf("Conteúdo: %s\n", mensagens[i].conteudo);
        printf("----------------------------\n");
    }
    printf("Aperte 0 para voltar ao menu inicial.\n");
}


void imprimiLigacao(Chamada chamadas[], int num_chamadas){
    printf("Histórico de chamadas:\n");
    for (int i = 0; i < num_chamadas; i++) {
        printf("Para: %s\n", chamadas[i].destinatario);
        printf("Duração: %d segundos\n", chamadas[i].duracao);
        printf("----------------------------\n");
    }
    printf("Aperte 0 para voltar ao menu inicial.\n");
}


void imprimiAgenda(Contato agenda[], int num_contatos){
    printf("Agenda de contatos:\n");
    for (int i = 0; i < num_contatos; i++) {
        printf("Nome: %s\n", agenda[i].nome);
        printf("Telefone: %s\n", agenda[i].telefone);
        printf("----------------------------\n");
    }
    printf("Aperte 0 para voltar ao menu inicial.\n");
}


void imprimiCreditos(int creditos){
    printf("%d créditos restantes.\n", creditos);
    printf("Podem ser feitas %d ligações e enviadas %d mensagens.\n", creditos / 2, creditos);
    printf("Aperte 0 para voltar ao menu inicial.\n");
}


void imprimiOperadora(){
    printf("Operadora: Claro\n");
    printf("Aperte 0 para voltar ao menu inicial.\n");
}


void realizarLigacao(Contato agenda[], int *creditos, Chamada chamadas[], int *num_chamadas, int *bateria, int num_contatos){
    if (*creditos < 2) {
        printf("Créditos insuficientes para realizar uma ligação.\n");
        return;
    }


    printf("Escolha o contato para realizar a ligação:\n");
    for (int i = 0; i < num_contatos; i++) {
        printf("%d. %s - %s\n", i + 1, agenda[i].nome, agenda[i].telefone);
    }


    int opcao;
    printf("Escolha o número do contato: ");
    scanf("%d", &opcao);


    if (opcao < 1 || opcao > num_contatos) {
        printf("Contato inválido.\n");
        return;
    }


    *creditos -= 2;
    strcpy(chamadas[*num_chamadas].destinatario, agenda[opcao - 1].nome);
    chamadas[*num_chamadas].duracao = 5;
    (*num_chamadas)++;


    printf("Ligando para %s... (Duração: 5 segundos)\n", agenda[opcao - 1].nome);
    sleep(5);  
    *bateria -= 1;  
    printf("Ligação concluída!\n");
}


void enviarMensagem(Mensagem mensagens[], int *num_mensagens, int *creditos){
    if (*creditos < 1) {
        printf("Créditos insuficientes para enviar uma mensagem.\n");
        return;
    }


    char destinatario[50], conteudo[160];
    printf("Digite o destinatário da mensagem: ");
    getchar();  
    fgets(destinatario, sizeof(destinatario), stdin);
    destinatario[strcspn(destinatario, "\n")] = 0;  


    printf("Digite o conteúdo da mensagem: ");
    fgets(conteudo, sizeof(conteudo), stdin);
    conteudo[strcspn(conteudo, "\n")] = 0;


    *creditos -= 1;
    strcpy(mensagens[*num_mensagens].destinatario, destinatario);
    strcpy(mensagens[*num_mensagens].conteudo, conteudo);
    (*num_mensagens)++;


    printf("Mensagem enviada para %s: %s\n", destinatario, conteudo);
}


int main(){
    int opcao = -1;
    int opcao2 = -1;
    int bateria = 100;
    int creditos = 10;
    int num_mensagens = 0;
    int num_chamadas = 0;
    int num_contatos = 0;


    Mensagem mensagens[10];
    Chamada chamadas[10];
    Contato agenda[10];


    strcpy(agenda[num_contatos].nome, "João");
    strcpy(agenda[num_contatos].telefone, "987654321");
    num_contatos++;


    strcpy(agenda[num_contatos].nome, "Maria");
    strcpy(agenda[num_contatos].telefone, "912345678");
    num_contatos++;


    while(opcao != 0){
        imprimiMenu();
        scanf("%d", &opcao);
        if(opcao == 1){
            imprimiBateria(bateria);
            scanf("%d", &opcao2);
        } else if(opcao == 2){
            imprimiMensagens(mensagens, num_mensagens);
            scanf("%d", &opcao2);
        } else if(opcao == 3){
            imprimiLigacao(chamadas, num_chamadas);
            scanf("%d", &opcao2);
        } else if(opcao == 4){
            imprimiAgenda(agenda, num_contatos);
            scanf("%d", &opcao2);
        } else if(opcao == 5){
            imprimiCreditos(creditos);
            scanf("%d", &opcao2);
        } else if(opcao == 6){
            imprimiOperadora();
            scanf("%d", &opcao2);
        }


        if (bateria > 0) {
            bateria--;  
        }


        if (creditos == 0) {
            printf("Você ficou sem créditos!\n");
            break;
        }
    }
    return 0;
}


