#include <stdio.h>// padrão de input e output
#include <windows.h>// pro COORD e cursor
#include <time.h>//para randomizar o item
#include <conio.h> //pro getch, kbhit

int player[20][2], score=0, end_player, end_player2, speed=100; //varialvél global do jogador 
int fdp=0, value_time=70, item, line_item, colune_item, command, movement; //variavéis globais do jogo em geral

void coordinate(int colune,int line); 

void menu();

void draw_player();

int draw_item();

void update_player();

int move_player();

void sound_effect(int frequency);

int main(){

    srand(time(NULL));
    
    for(int count=0; count<47; count++){

        if(count<24){
        
            coordinate(0,count); //barra da esquerda
            printf("%c", 178);

            coordinate(46,count); //barra da direita 
            printf("%c", 178);                   
        }

        coordinate(count,0); //barra do topo
        printf("%c", 178);

        coordinate(count,24); //barra de baixo
        printf("%c", 178);
    }

    for(int count=0; count<20; count++){ //coloca a posiçao da lacraia no vetor
        
        player[count][0]=count+5;   
        player[count][1]=10;   
    }
    do{
        draw_player();
        move_player();
        draw_item();
        sleep(speed); //velocidade da cobra
    
    }while(command!=27);

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

    for(int count=0; count<20; count++){

        coordinate(player[count][0],player[count][1]);//colocando o cursor no jogador
        printf("%c", 72);
    }

    coordinate(player[19][0], player[19][1]); //colocando o ínico do imagem do jogador
    printf("%c", 60);

    coordinate(end_player,end_player2); //colocando o cursor no fim da imagem do jogador
    printf(" ");//apagando a ultima imagem da lacraia

    coordinate(59,3); //colocando informações
    printf("Score:  %d", score);
    coordinate(59,5);
    printf("Exit:   Esc");

    fdp++;
    if(fdp>value_time){

        item=0; //reseta o item
        coordinate(colune_item, line_item); //indo até o item
        printf(" "); //deletando o item
        sound_effect(1500); //efeito do reset da maça
    }
}

int draw_item(){

    int repeat=0;
    
    if(item==0){
        fdp=0; //zerando o tempo com o reset do item
    }

    if(item==1){
        return 0; //não resetar o item caso já tenha
    }
    
    do{

        colune_item= rand()%45+1; //coluna do item
        line_item= rand()%22+1; //linha do item

        for(int count=0; count<20; count++){ //deixando o item não ser o jogador

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

void update_player(){

    for( int count=0; count<19; count++){

        player[count][0]=player[count+1][0]; //move a imagem do jogador 
        player[count][1]=player[count+1][1];
    }
}

int move_player(){

    for(int count=0; count<20; count++){

        command=0;
        
        if(kbhit()) //pegando o teclado sem parar o programa
            command=getch(); //lendo essa tecla e guardadndo 

        if(command==27) //se for digitado Esc, sair do jogo
            return 0;

        if(command==87){ //pegar a tecla w igual o para cima
            if(movement==3) sound_effect(500); //aviso sonoro se tentar andar na imagem do jogador
            else movement==0; //caso relacionado a essa tecla
        }

        if(command==65){ //tecla a como esquerda
            if(movement==2)sound_effect(500);
            else movement==1;
        }

        if(command=68){ //tecla d como direita
            if(movement==1) sound_effect(500);
            else movement=2;
        }

        if(command=83){//tecla s como baixo
            if(movement==0) sound_effect(500);
            else movement=3;
        }
    }

    switch(movement){

        case 0:
            if(player[19][1]>1){
                update_player();
                player[19][1]--;
            }
            break;

        case 1:
            if(player[19][0]>1){
                update_player();
                player[19][0]--;
            }
            break;

        case 2:
            if(player[19][0]<45){
                update_player();
                player[19][0]++;
            }
            break;

        case 3:
            if(player[19][1]<23){
                update_player();
                player[19][1]++;
            }
            break;
    }
    if(player[19][0]==colune_item && player[19][1]==line_item){ //se a imagem do player colodir com a imagem do item  

        item=0; //reset item
        score++; //aumenta a pontução
        sound_effect(2200); //efeito sonoro
    }

}

void sound_effect(int frequency){

    Beep(frequency, 150); //frequencia depois duração

}