#include <stdio.h>
#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

int main(){
    //Inicializar o Allegro
    if(/*"Liga o Allegro"*/!al_init()){
        printf("Erro ao inicializar o Allegro. \n");
        return -1;
    }
    //Inicializa o Teclado
    if(/*Reconhecer o Teclado*/!al_install_keyboard()){
        printf("Falha em Reconhecer o Teclado. \n");
        return -1;
    }
    //Pacote para desenhas formas geométricas
    if(!al_init_primitives_addon()){
        printf("Erro em Inicializar as primitivas");
        return -1;
    }
    // Cria o Display
    ALLEGRO_DISPLAY * display = al_create_display(800,600);
    if (!display /*Verifica se a janela falhou*/)
    {
        printf("Erro ao exibir display");
        return -1;
    }
    //Fila onde o allegro coloca o que aconteceu
    ALLEGRO_EVENT_QUEUE*event_queue = al_create_event_queue();
    //O display vai enviar eventos para a fila
    al_register_event_source(/*Conecta o gerador de eventos a uma fila de eventos*/
        event_queue, /*estrutura que guarda a ordem*/
        al_get_display_event_source(display) /*pega o canal de avisos da janela display*/
    // quando acontecer um evento nessa janela, coloque o evento na event_queue
    );
    //Enquanto for verdadeiro , o programa continua
    bool /*dado boleano guarda verdadeiro ou falso*/ running /*chave geral do loop*/ = true;

    while (running) /*enquanto running for verdadeiro mantem o loop ativo*/
    {
        ALLEGRO_EVENT event; /*cria uma variavel event anota os detalher que acabou de acontecer */
        
        //pausar o programa ate que algo aconteça e retirar o acontecimento da fila para ler
        al_wait_for_event(event_queue, &event /*&passa o endereço de memoria da variavel*/);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            running = false;
            // se o evento do display fechar o running da falso e interrope o evento
        }

    }
    
    //apaga a fila e fecha a janela
    al_destroy_event_queue(event_queue);//apagar a fila de evntos na memoria ram quando o jogo termina
    al_destroy_display(display); //fecha a janela do jogo e libera memoria da placa video e ram
    return 0;
    // 1- Declara o Ponteiro e cria a fila na memoria; 2- registra as fontes, quais aparelhos vai mandar aviso para a fila
    // 3- Ler os eventos do loop, no while tira o proximo aviso da fila e analisa; 4-Destruir, ao terminar o jogo libera memoria 
}