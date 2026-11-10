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

    // Vetor que guarda o estados das teclas
    bool teclas /*lista de interruptores*/[ALLEGRO_KEY_MAX] = {false}; /*numero total de teclas*/
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
    // driver do mouse
    if (!al_install_mouse())
    {
        printf("Falha em reconhecer o mouse \n");
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

    if (!display /*Verifica se a janela falhou*/)
    {
        printf("Erro ao exibir display");
        return -1;
    }
    // Fila onde o allegro coloca o que aconteceu
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();

    // um relogio que libera um aviso 60 vezes por segundo
    ALLEGRO_TIMER *timer /*Variavel ponteiro que guarda o relogio na mermoria*/ = al_create_timer(1.0 / 60.0) /*cria o cronometro e o intervalo*/;

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
    // fila de eventos mouse
    al_register_event_source(
        event_queue,
        al_get_mouse_event_source());
    // fila de evento do timer
    al_register_event_source(
        event_queue,                     // guarda o evento
        al_get_timer_event_source(timer) // liga e avis o evento
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

        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            printf("Clique em X: %d, Y: %d\n",
                   event.mouse.x,
                   event.mouse.y);
            // se o evento detectar um clique mandara mensagem no terminal
            if (event.mouse.x >= jogador.x &&
                event.mouse.x <= jogador.x + jogador.width &&
                event.mouse.y >= jogador.y &&
                event.mouse.y <= jogador.y + jogador.height)
            {
                printf("Clicou no jogador!\n");
            }
        }

        // criar movimento do jogador
        if (event.type /*que tipo de acontecimento acabou de ocorrer*/ == ALLEGRO_EVENT_KEY_DOWN) // verifica qual tecla foi apertada
        {
            teclas[event.keyboard.keycode] = true; // é verdadeiro que a tecla esta pressionada
        }
        if (event.type == ALLEGRO_EVENT_KEY_UP) /*Verifica o evento de soltar a tecla*/
        {
            teclas[event.keyboard.keycode] = false; // muda para false fazendo assim o movimento parar
        }
        // mover pelo timer
        if (event.type == ALLEGRO_EVENT_TIMER) // aviso o evento
        {
            if (teclas[ALLEGRO_KEY_RIGHT])
            {
                jogador.x += 5; // direita

                // for (int i = 0; i < 2; i++)
                // {
                //     if (colisao(jogador, obstaculo[i]))
                //     {
                //         jogador.x -= 5; // 5-5=0
                //     }
                // }
            }
            if (teclas[ALLEGRO_KEY_LEFT])
            {
                jogador.x -= 5; // esquerda

                // for (int i = 0; i < 2; i++)
                // {
                //     if (colisao(jogador, obstaculo[i]))
                //     {
                //         jogador.x +=5; // -5+5=0
                //     }
                // }
            }
            if (teclas[ALLEGRO_KEY_UP])
            {
                jogador.y -= 5; // baixo
                // for (int i = 0; i < 2; i++)
                // {
                //     if (colisao(jogador, obstaculo[i]))
                //     {
                //         jogador.y += 5; // -5+5=0
                //     }
                // }
            }

            if (teclas[ALLEGRO_KEY_DOWN])
            {
                jogador.y += 5; // cima
                //     for (int i = 0; i < 2; i++)
                //     {
                //         if (colisao(jogador, obstaculo[i]))
                //         {
                //             jogador.y -= 5; // 5-5=0
                //         }
                //     }
                // }
            }

            // limpa tela
            al_clear_to_color(al_map_rgb(0, 0, 0)); // tirar o rastro limpando a cada quadro

            // Aparecer desenho na tela, desenha retangulo
            al_draw_filled_rectangle(
                jogador.x,
                jogador.y,
                jogador.x + jogador.width,
                jogador.y + jogador.height,
                jogador.color);
            al_flip_display(); // faz o desenho aparecer na tela
        }
    }
}