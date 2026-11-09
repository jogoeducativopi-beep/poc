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
    if(!al_init_primitives_addon){
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

}