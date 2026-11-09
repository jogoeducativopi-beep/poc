#include <stdio.h>
#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

// estrutura do retangulo
typedef struct /*Permite juntar varias informações dentro de uma unica coisa*/
{
    // molde do retangulo, quando criar um retangulo, ele vai guardar posição, tamanho e cor
    float x;             // posição horizontal
    float y;             // posição vertical
    float width;         // largura
    float height;        // altura
    ALLEGRO_COLOR color; // cor
} Retangulo;             // nome do molde;

int main()
{
    // Inicializar o Allegro
    if (/*"Liga o Allegro"*/ !al_init())
    {
        printf("Erro ao inicializar o Allegro. \n");
        return -1;
    }
    // Inicializa o Teclado
    if (/*Reconhecer o Teclado*/ !al_install_keyboard())
    {
        printf("Falha em Reconhecer o Teclado. \n");
        return -1;
    }
    // Pacote para desenhas formas geométricas
    if (!al_init_primitives_addon())
    {
        printf("Erro em Inicializar as primitivas");
        return -1;
    }
    // Cria o Display
    ALLEGRO_DISPLAY *display = al_create_display(800, 600);

    Retangulo jogador = {
        100,
        100,
        50,
        50,
        al_map_rgb(255, 0, 0)};
    
    Retangulo obstaculo = {
        300,
        400,
        100,
        50,
        al_map_rgb(0,255,0)
    };
        if (!display /*Verifica se a janela falhou*/)
    {
        printf("Erro ao exibir display");
        return -1;
    }
    // Fila onde o allegro coloca o que aconteceu
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();

    // um relogio que libera um aviso 60 vezes por segundo
    ALLEGRO_TIMER * timer /*Variavel ponteiro que guarda o relogio na mermoria*/ = al_create_timer(1.0 / 60.0) /*cria o cronometro e o intervalo*/;

    // O display vai enviar eventos para a fila
    al_register_event_source(                                     /*Conecta o gerador de eventos a uma fila de eventos*/
                             event_queue,                         /*estrutura que guarda a ordem*/
                             al_get_display_event_source(display) /*pega o canal de avisos da janela display*/
                             // quando acontecer um evento nessa janela, coloque o evento na event_queue
    );

    // Teclado a fila de eventos
    al_register_event_source(
        event_queue,                   // guarda o evento
        al_get_keyboard_event_source() // liga o teclado
    );
    //fila de evento do timer
    al_register_event_source(
        event_queue,  //guarda o evento
        al_get_timer_event_source(timer) //liga e avis o evento
    );

    // Inicia o timer
    al_start_timer(timer);

    // Enquanto for verdadeiro , o programa continua
    bool /*dado boleano guarda verdadeiro ou falso*/ running /*chave geral do loop*/ = true;

    while (running) /*enquanto running for verdadeiro mantem o loop ativo*/
    {
        ALLEGRO_EVENT event; /*cria uma variavel event anota os detalher que acabou de acontecer */

        // pausar o programa ate que algo aconteça e retirar o acontecimento da fila para ler
        al_wait_for_event(event_queue, &event /*&passa o endereço de memoria da variavel*/);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            running = false;
            // se o evento do display fechar o running da falso e interrope o evento
        }

        // criar movimento do jogador
        if (event.type /*que tipo de acontecimento acabou de ocorrer*/ == ALLEGRO_EVENT_KEY_DOWN) // verifica qual tecla foi apertada
        {
            if (event.keyboard.keycode /*campo que guarda o codigo exato da tecla que foi apertada*/ == ALLEGRO_KEY_RIGHT /*representa a tecla da direita*/)
            {                   // verifica se a tecla apertada foi a ->
                jogador.x += 5; // adicionar 5 no x, anda mais a direita
            }
            if (event.keyboard.keycode /*campo que guarda o codigo exato da tecla que foi apertada*/ == ALLEGRO_KEY_LEFT /*representa a tecla da esquerda*/)
            {                   // verifica se a tecla apertada foi a <-
                jogador.x -= 5; // adicionar 5 no y, anda mais a esquerda
            }
            if (event.keyboard.keycode /*campo que guarda o codigo exato da tecla que foi apertada*/ == ALLEGRO_KEY_DOWN /*representa a tecla da esquerda*/)
            {                   // verifica se a tecla apertada foi a <-
                jogador.y += 5; // adicionar 5 no y, anda mais a esquerda
            }
            if (event.keyboard.keycode /*campo que guarda o codigo exato da tecla que foi apertada*/ == ALLEGRO_KEY_UP /*representa a tecla da esquerda*/)
            {                   // verifica se a tecla apertada foi a <-
                jogador.y -= 5; // adicionar 5 no y, anda mais a esquerda
            }
        }

        //limpa tela
        al_clear_to_color(al_map_rgb(0,0,0)); //tirar o rastro limpando a cada quadro

        // Aparecer desenho na tela, desenha retangulo
        al_draw_filled_rectangle(
            jogador.x,
            jogador.y,
            jogador.x + jogador.width,
            jogador.y + jogador.height,
            jogador.color);

        al_draw_filled_rectangle(
            obstaculo.x,
            obstaculo.y,
            obstaculo.x + obstaculo.width,
            obstaculo.y + obstaculo.height,
            obstaculo.color
        );
        al_flip_display(); // faz o desenho aparecer na tela
    }

    // apaga a fila e fecha a janela
    al_destroy_event_queue(event_queue); // apagar a fila de evntos na memoria ram quando o jogo termina
    al_destroy_display(display);         // fecha a janela do jogo e libera memoria da placa video e ram
    return 0;
    // 1- Declara o Ponteiro e cria a fila na memoria; 2- registra as fontes, quais aparelhos vai mandar aviso para a fila
    // 3- Ler os eventos do loop, no while tira o proximo aviso da fila e analisa; 4-Destruir, ao terminar o jogo libera memoria
}