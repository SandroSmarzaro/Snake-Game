#include <stdio.h> // padrão de input e output
#include <time.h> //para randomizar o item
#include <windows.h> // pro COORD, sleep
#include <conio.h> //pro getch e kbhit
#include <ctype.h> //para o tolower
#include <string.h> //para os processos com o usuário

int player[20][2], movement,end_player, end_player2, score, speed=100, colune_player, line_player; //varialveis globalais do jogador 
int  item, colune_item, line_item, command, Time=0, option=7, x=7, y, comparison, comparison2, comparison3, save=0; //variavéis globais do jogo em geral
char user[20]="user", typed_user[20], typed_user2[20], password[20]="password", typed_password[20], typed_password2[20], mode[7]="Normal", mode1[7]="Easy", mode2[7]="Normal", mode3[7]="Hard";
char h1_user[20]="user", h2_user[20]="user",h3_user[20]="User", h1_mode[7]="Normal", h2_mode[7]="Normal", h3_mode[7]="Normal";
int  highscore1=0, highscore2=0, highscore3=0;

void coordinate(int colune,int line);

void edge();

void menu();

void move_menu();

void erase_menu();

void running();

void difficulty_menu();

void login_menu();

void user_menu();

void sound_effect(int frequency);

void start_player();

void draw_player();

void update_player();

int move_player();

int draw_item();

void highscore_menu();

void data_highscore();

void collision();

void game_over();

int new_game();

void continue_game();

int main (){
    
    SetConsoleTitle("Centipide Game");          //nomeado a janela com o game
    srand(time(NULL));                          //randomizando com a data da maquina
    start_player();
    edge();                                     
    login_menu();
    menu();
    running();

    coordinate(15,11);                          //se todas operações foram feitas, dar a mensagem de game fechado
    printf("You left the game.");

    return 0;
}

void coordinate(int colune,int line){
    
    COORD coord; //atribuindo as cordenadas a struct
    coord.X = colune;
    coord.Y = line;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord); //colocar o cursor na coordenada
}

void edge(){

    for(int count=0;count<47;count++){  
        
        if(count<24){
            
            coordinate(0,count);   //barra da esquerda
            printf("%c",186);
        
            coordinate(46,count); //barra da direita 
            printf("%c",186);
        }
        
        coordinate(count,0);   //barra do topo
        printf("%c",205);
        coordinate(count,24);  //barra de baixo
        printf("%c",205);
    }
}

void menu(){

    coordinate(16,3);
    printf("Centipide Game");
    coordinate(19,7);
    printf("New Game");
    coordinate(19,9);
    printf("Continue");
    coordinate(18,11);
    printf("Difficulty");
    coordinate(18,13);
    printf("Highscore");
    coordinate(21,15);
    printf("User");
    coordinate(21,17);
    printf("Exit");

    coordinate(59,2);
    printf("Move up: W");
    coordinate(59,4);
    printf("Move down: S");
    coordinate(59,6);
    printf("Confirm: Enter");
}

void move_menu(){

    do{  
        command=0;                              //resetando a variavél

        if(kbhit())                             //pegando o teclado sem parar o programa
            command=getch();
            
        if(tolower(command)=='s'){              //caso da seta para baixo
            coordinate(15,x);                   //no cursor atual apaga a seta
            printf(" ");
            coordinate(15,x+2);                 //move o cursor para baixo
            printf("%c",16);
            x=x+2;                              //atualizando a variavél
            sound_effect(1500);
        }
     
        if(tolower(command)=='w'){              //caso da seta para cima
            coordinate(15,x);                   //no cursor atual apaga a seta
            printf(" ");
            coordinate(15,x-2);                 //move o  cursor para cima
            printf("%c",16);                    
            x=x-2;
            sound_effect(1500);                 
        }
    }while(command!=13);                        //caso não de enter
    option=x;                                   //salvar a line como a opção escolhida
    erase_menu();                               //fecha o menu
}

void erase_menu(){

  system("cls");           //apaga toda tela
  edge();                  //refaz as bordas
}

void running(){
    do{
        move_menu();
    }while(command!=13);                    //se movimenta no menu enquanto não apertar enter

    do{
        
        if(option==7){                      //se for selecionado novo jogo
            new_game();
        }
        else if(option==9){                 //se for selecionado continuar
            continue_game();
        }
        else if(option==11){                //se for selecionado dificuldade
            difficulty_menu();
        }
        else if(option==13){                //se for selecionado records
            highscore_menu();
        }
        else if(option==15){                //se for selecionado usuário
            user_menu();
        }
        else if(option==17){                //se for selecionado para sair
            return 0;
        }
        
    }while(command != 13);
}

void difficulty_menu(){
    
    erase_menu();
    coordinate(16,3);
    printf("Centipide Game");
    coordinate(19,7);
    printf("Easy");
    coordinate(19,9);
    printf("Normal");
    coordinate(19,11);
    printf("Hard");

    move_menu();

    switch(option){

        case 7:
            speed=125; //caso seja selecionado fácil, o game roda mais lento
            for(int count=0; count<7; count++){
                mode[count]=mode1[count];   //atulizando o modo com a dificuldade correspondente 
            }
            break;
        
        case 9:
            speed=100;  //dificuldade padrão com tempo de resposta normal
            for(int count=0; count<7; count++){
                mode[count]=mode2[count];   //atulizando o modo com a dificuldade correspondente 
            }
            break;
        
        case 11:
            speed=25;  //caso seja selecionado dificil o game tem o tempo de resposta e exewcução mais rápido
            for(int count=0; count<7; count++){
                mode[count]=mode3[count];
            }
            break;
    }
    erase_menu();
    menu();
    running();
}

void login_menu(){
    
    erase_menu();

    coordinate(59,2);
    printf("Default user: user");
    coordinate(59,4);
    printf("Default password: password");
    coordinate(59,6);
    printf("Confirm: Enter");

    do{
        coordinate(16,3);
        printf("Centipide Game");
        coordinate(13,7);
        printf("Enter your username:");
        coordinate(19,9);
        scanf("%s", typed_user);
        comparison=strcmp(user, typed_user);    //comparando o usuário padrão com o digitado
        
        if(comparison!=0){                      //se for diferente pedir para repetir
            coordinate(19,9);
            printf("                     ");
            coordinate(10,11);
            printf("Incorrect user! Type again.");
            sound_effect(500);
        }
    }while(comparison!=0);                      //enquanto o resultado for diferente ele pede para digitar
    sound_effect(2200);
    erase_menu();
    do{
        coordinate(16,3);
        printf("Centipide Game");
        coordinate(13,7);
        printf("Enter your password:");
        coordinate(19,9);
        scanf("%s", typed_password);
        comparison=strcmp(password, typed_password);    //comparando a senha padrão com a digitada

        if(comparison!=0){
            coordinate(19,9);
            printf("                     ");
            coordinate(10,11);
            printf("Incorrect password! Type again.");
            sound_effect(500);
        }
    }while(comparison!=0);
    sound_effect(2200);
    erase_menu();
}

void user_menu(){

    erase_menu();
    do{
        coordinate(16,3);
        printf("Centipide Game");
        coordinate(12,7);
        printf("Enter your new username:");
        coordinate(19,9);
        scanf("%s", typed_user);
        erase_menu();
        coordinate(16,3);
        printf("Centipide Game");
        coordinate(12,7);
        printf("Confirm your new user");
        coordinate(19,9);
        scanf("%s", typed_user2);
        
        comparison=strcmp(typed_user, typed_user2); //comparando com os dois usuarios novos digitados
        comparison2=strcmp(user,typed_user);        //comparando o usuario novo com o padrão
        comparison3=strcmp(user,typed_user2);
        
        if(comparison!=0){                          //se os usuários novos forem diferentes entre si repete
            coordinate(19,9);
            printf("                     ");
            coordinate(12,11);
            printf("Different users, retype");
            sound_effect(500);
        }
        else if(comparison2==0 || comparison3==0){   //se o usuario novo for igual o padrão repetir
            coordinate(19,9);
            printf("                     ");
            coordinate(4,13);
            printf("The new user is the same as the old one");
            sound_effect(500);
            comparison=1;
        } 
    }while(comparison!=0);
    sound_effect(2200);
    erase_menu();
    
    do{
        coordinate(16,3);
        printf("Centipide Game");
        coordinate(12,7);
        printf("Enter your password:");
        coordinate(19,9);
        scanf("%s", typed_password);
        erase_menu();
        coordinate(16,3);
        printf("Centipide Game");
        coordinate(12,7);
        printf("Confirm your new password");
        coordinate(19,9);
        scanf("%s", typed_password2);

        comparison=strcmp(typed_password, typed_password2);
        comparison2=strcmp(password,typed_password);
        comparison3=strcmp(password,typed_password2);

        if(comparison!=0){
            coordinate(19,9);
            printf("                     ");
            coordinate(12,11);
            printf("Different passwords, retype");
            sound_effect(500);
        }
        else if(comparison2==0 || comparison3==0){
            coordinate(19,9);
            printf("                     ");
            coordinate(2,13);
            printf("The new password is the same as the old one");
            sound_effect(500);
            comparison=1;
        } 
    }while(comparison!=0);
    sound_effect(2200);
    for(int count=0; count<20; count++){      //atribuindo os valores do novo usuário e senha
        user[count]=typed_user[count];
        password[count]=typed_password[count];
    }
    erase_menu();
    login_menu();
    menu();
    running();
}

void sound_effect(int frequency){
    Beep(frequency,150); //frequencia depois duração
}

void start_player(){

    for(int count=0; count<20; count++){   //coloca as coordenada do jogador na variável
        player[count][0]=count+5;  
        player[count][1]=10;
    }
}

void draw_player(){
    
    end_player=player[0][0];                            //recebendo da parte final do jogador
    end_player2=player[0][1];     
    
    for(int count=0; count<20; count++){ 
        
        coordinate(player[count][0], player[count][1]); //colocando o cursor no jogador
        printf("%c",72);                                //fazendo o print do jogador
    }

    coordinate(player[19][0], player[19][1]);           //colocando o cursor no ínico da print do jogador
    printf("%c", 111);    

    coordinate(end_player, end_player2);                //colocando o cursor no fim da print do jogador
    printf(" ");                                        //deixa vazio o ultimo print do jogador 

    collision();
    
    coordinate(59,2); 
    printf("Score: %d",score);                          //print das informações
    coordinate(59,4);
    printf("Move up: W");
    coordinate(59,6);
    printf("Move down: S");
    coordinate(59,8);
    printf("Move left: A");
    coordinate(59,10);
    printf("Move right: D");
    coordinate(59,12);
    printf("Exit: Esc");
    Time++;                                            //incrementador do relógio
    
    if(Time > 75){                                     //se o item demorar demais no mesmo lugar

        coordinate(colune_item,line_item);             //cursor no item
        printf(" ");                                   //apaga o item
        item=0;                                        //reseta a pocição do item     
        sound_effect(1500);                            //efeito de mudança
    }
}

void update_player(){
    
    for(int count=0; count<19; count++){ 

        player[count][0] = player[count+1][0]; //move os prints do jogador para trás
        player[count][1] = player[count+1][1];
    }
}

int move_player(){
    
    for(int count=0; count<20; count++){
        
        command=0;                              //resetando a variável
        
        if(kbhit()){                             //pegando o teclado sem parar o programa
            command=getch();
            
        }    
        if(command==27){                         //saindo do jogo quando pressiondado Esc
            command=0; 
            erase_menu();
            menu();
            running();
            return 0;
        }
        if(save==1){                            //caso a colisão no próprio jogador aconteça
            game_over();
        } 

        if(tolower(command)=='d'){                  
            if(movement==2)sound_effect(500);    //se for percorrer por dentro do print do jogador avisar
            else movement=0;                    //caso da seta tecla d
        }
            
        if(tolower(command)=='s'){                   
            if(movement==3)sound_effect(500);
            else movement=1;                    //caso da seta tecla s
        }
            
        if(tolower(command)=='a'){                   
            if(movement==0)sound_effect(500);
            else movement=2;                    //caso da seta tecla a
        }
            
        if(tolower(command)=='w'){    
            if(movement==1)sound_effect(500);  
            else movement=3;                    //caso da seta tecla w
        }
    }

    switch(movement){
        case 0:
            
            if(player[19][0] < 45){     //até o jogador chegar no limite direito
                update_player();        //movimentos do print do jogador para tras
                player[19][0]++;        //movimento para direita
            }
            else{
                update_player();
                player[19][0]=player[19][0]-44; //caso o jogador passe do limite da direita é direcionado paro inico da esquerda
            }            
            break;
        
        case 1:
            
            if(player[19][1] < 23){     //até o jogador chegar no limite de baixo
                update_player();        
                player[19][1]++;        //movimento para baixo
            }
            else{
                update_player();
                player[19][1]=player[19][1]-22; //caso o jogador passe do limite de baixo, ir para o inicio de cima
            }
               
            break;
        
        case 2:
            
            if(player[19][0] > 1){      //até o jogador chegar no limite da esquerda
                update_player();        
                player[19][0]--;        //movimento para esquerda;
            }
            else{
                update_player();
                player[19][0]=player[19][0]+44; //caso o jogador passe do limite da esquerda, ir para o final da direita
            }
            break;
        
        case 3:

            if(player[19][1] > 1){      //até o jogador chegar no limite da barras superior
                update_player();        
                player[19][1]--;        //movimento para cima
            }
            else{
                update_player();
                player[19][1]=player[19][1]+22; //caso o jogador passe do limite de cima, ir para o final do de baixo
            }
            break;
    }
    
    if(player[19][0]==colune_item && player[19][1]==line_item){ //caso o print do jogador colide com o do item
        item=0;
        score++;
        sound_effect(2200);
    }
    
    return 0;
}

int draw_item(){
    int reset=0;
    
    if(item==0)Time=0;                            //reseta o tempo quando reseta o item
    if(item==1)return 0;                         //se já estiver item, não criar outro
    
    do{
        colune_item= rand()%44+1;                         //coordenadas do item
        line_item= rand()%21+1;                          
        
        for(int count=0; count<20; count++){    //se a coordenada do item for igual o print do jogador
            if(colune_item==player[count][0]){
                if(line_item==player[count][1]){
                    colune_item=22;
                    line_item=11;
                }
            }                          
        }
    
    }while(reset!=0);

    coordinate(colune_item,line_item);           //cursor na coordenada no item
    printf("%c",79);                            //printa o item
    item=1;                                     //item existente
}

void highscore_menu(){
    command=0;
    erase_menu();
    coordinate(16,3);
    printf("Centipide Game");
    coordinate(7,7);
    printf("User          Mode          Score");
    coordinate(7,11);
    printf("%s          %s          %d", h1_user, h1_mode, highscore1);
    coordinate(7,13);
    printf("%s          %s          %d", h2_user, h2_mode, highscore2);
    coordinate(7,15);
    printf("%s          %s          %d", h3_user, h3_mode, highscore3);
    coordinate(59,2);
    printf("Exit: Enter");
   
    do{
        if(kbhit())
            command=getch();
    }while(command!=13);
    
    erase_menu();
    menu();
    running();
}

void collision(){

    for(int count=0; count<19; count++){ //salvando as corrdenadas do jogador para verificar se são iguais
        colune_player=player[count][0]; 
        line_player=player[count][1];
        
        if(colune_player==player[19][0]){ //caso seja igual a parte incial do jogador, a colisão aconteceu
            if(line_player==player[19][1]){
                save=1;
            }
        }
    }
}

void game_over(){
    save=0;
    erase_menu();
    coordinate(18,7);                          
    printf("GAME OVER");
    coordinate(13,9);                          
    printf("Score %d in %s mode ", score, mode);
    do{
        if(kbhit())
            command=getch();
    }while(command!=13);
    start_player();
    item=1;
    
    if(score>highscore1){
        y=1;
        data_highscore(); 
    }else if(score>highscore2){
        y=2;
        data_highscore();
    }
    else if(score>highscore3){
        y=2;
        data_highscore();
    }
    score=0;
    erase_menu();
    menu();
    running();
}

void data_highscore(){

    switch(y){
        
        case 1:                                         //caso suge um novo maior recorde
            for(int count=0; count<20; count++){        //trocando o segundo recorde com o terceiro
                h3_user[count]=h2_user[count];
                if(count<7){
                    h3_mode[count]=h2_mode[count];
                }
            }
            highscore3=highscore2;
            
            for(int count=0; count<20; count++){        //trocando o primeiro recorde com o segundo
                h2_user[count]=h1_user[count];
                if(count<7){
                    h2_mode[count]=h1_mode[count];
                }
            }
            highscore2=highscore1;
            
            for(int count=0; count<20; count++){        //atribuindo o novo recorde ao primeiro
                h1_user[count]=user[count];
                if(count<7){
                    h1_mode[count]=mode[count];
                }
            }
            highscore1=score;

            break;

        case 2:                                         //caso surge um segundo melhor recorde
            for(int count=0; count<20; count++){        //trocando o segundo recorde com o terceiro
                h3_user[count]=h2_user[count];
                if(count<7){
                    h3_mode[count]=h2_mode[count];
                }
            }
            highscore3=highscore2;

            for(int count=0; count<20; count++){        //atribuindo o novo segundo melhor recorde
                h2_user[count]=user[count];
                if(count<7){
                    h2_mode[count]=mode[count];
                }
            }

            highscore2=score;
            break;

        case 3:
            
            for(int count=0; count<20; count++){        //atribuindo o novo segundo melhor recorde
                h3_user[count]=user[count];
                if(count<7){
                    h3_mode[count]=mode[count];
                }
            }
            highscore3=score;

            break;
    }
}

int new_game(){
    
    start_player();
    item=0;
    score=0;
    do{
        draw_player();
        move_player();
        draw_item();
        Sleep(speed);//velocidade do jogador
    }while(command!=27);
    return 0;
}

void continue_game(){
    
    item=0;
    do{
        draw_player();
        move_player();
        draw_item();
        Sleep(speed);
    }while(command!=27);
    
}