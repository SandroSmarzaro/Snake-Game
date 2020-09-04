#include <stdio.h>// padrão de input e output
#include <windows.h>// pro COORD e cursor
#include <time.h>//para randomizar o item
#include <conio.h>

void coordinate(int colune,int line); 

void menu();

void draw_player();

int draw_item();

void sound_effect(int frequency);

int player[10][2], score=0, end_player, end_player2; //varialvél global do jogador 
int Time=0, value_time=70, item, line_item, colune_item; //variavéis globais do jogo em geral

int main(){

    srand(time(NULL));
    
    for(int count=0; count<50; count++){

        if(count<25){
        
            coordinate(0,count); //barra da esquerda
            printf("%c", 178);

            coordinate(49,count); //barra da direita 
            printf("%c", 178);                   
        }

        coordinate(count,0); //barra do topo
        printf("%c", 178);

        coordinate(count,25); //barra de baixo
        printf("%c", 178);
    }

    for(int count=0; count<10; count++){ //coloca a posiçao da lacraia no vetor
        
        player[count][0]=count+5;   
        player[count][1]=10;   
    }

    draw_player();
    draw_item();

    return 0;
}

void coordinate(int colune,int line){

    COORD coord; //atribuindo as cordenadas a struct
    coord.X = colune;
    coord.Y= line;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);// movimenta cursor
}

void draw_player(){
                                
    end_player= player[0][0]; //recebendo da parte final do jogador
    end_player2= player[0][1];

    for(int count=0; count<10; count++){

        coordinate(player[count][0],player[count][1]);//colocando o cursor no jogador
        printf("%c", 72);
    }

    coordinate(player[9][0], player[9][1]); //colocando o ínico do imagem do jogador
    printf("%c", 60);

    coordinate(end_player,end_player2); //colocando o cursor no fim da imagem do jogador
    printf(" ");//apagando a ultima imagem da lacraia

    coordinate(59,3); //colocando informações
    printf("Score:  %d", score);
    coordinate(59,5);
    printf("Exit:   Esc");

    Time++;
    if(Time>value_time){

        item=0; //reseta o item
        coordinate(colune_item, line_item); //indo até o item
        printf(" "); //deletando o item
        sound_effect(1500); //efeito do reset da maça
    }
}

int draw_item(){

    int repeat=0;
    
    if(item==0){
        Time=0; //zerando o tempo com o reset do item
    }

    if(item==1){
        return 0; //não resetar o item caso já tenha
    }
    
    do{

        colune_item= rand()%45+1; //coluna do item
        line_item= rand()%23+1; //linha do item

        for(int count=0; count<10; count++){ //deixando o item não ser o jogador

            if(colune_item==player[count][0] && line_item==player[count][1]){
                repeat=1;
            }
        }

    }while(repeat!=0);

    coordinate(colune_item, line_item); //imagem do item
    printf("%c", 79);
    item=1; //informando que já tem item

    return 0;
}

void sound_effect(int frequency){

    Beep(frequency, 150); //frequencia depois duração

}