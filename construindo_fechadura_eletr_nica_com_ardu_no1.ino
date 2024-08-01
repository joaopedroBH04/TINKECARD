    #include <Keypad.h>
    #include <Servo.h>

    Servo servo_Motor; 
    char* password = "1305"; 
    int position = 0; //VARIÁVEL PARA LEITURA DE POSIÇÃO DA TECLA PRESSIONADA
    const byte ROWS = 4; //NUMERO DE LINHAS DO TECLADO
    const byte COLS = 4; //NUMERO DE COLUNAS DO TECLADO
    char keys[ROWS][COLS] = { //DECLARAÇÃO DOS NUMEROS, LETRAS E CARACTERES DO TECLADO
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
    };

    byte rowPins[ROWS] = { 8, 7, 6, 9 }; // PINOS DE CONEXAO DAS LINHAS DO TECLADO
    byte colPins[COLS] = { 5, 4, 3, 2 }; //PINOS DE CONEXAO DAS COLUNAS DO TECLADO
    Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );//AS VARIAVEIS rowPins E colPins RECEBERÃO O VALOR DE LEITURA DOS PINOS DAS LINHAS E COLUNAS RESPECTIVAMENTE

    const int ledVermelho = 12; 
    const int ledVerde = 13;

    void setup(){
      pinMode(ledVermelho, OUTPUT); 
      pinMode(ledVerde, OUTPUT); 

      servo_Motor.attach(11); 
      setLocked(true); 
    }

    void loop(){
      char key = keypad.getKey(); //LEITURA DAS TECLAS PRESSIONADAS
      if (key == '*' || key == '#') { //SE A TECLA PRESSIONADA POR IGUAL A CARACTERE "*" OU "#", FAZ
          position = 0; //POSIÇÃO DE LEITURA DA TECLA PRESSIONADA INICIA EM 0
          setLocked(true); //FECHADURA TRANCADA
    }
    if (key == password[position]){ //SE A TECLA PRESSIONADA CORRESPONDER A SEQUÊNCIA DA SENHA, FAZ
          position ++;//PULA PARA A PRÓXIMA POSIÇÃO
    }
    if (position == 4){ // SE VARIÁVEL FOR IGUAL A 3 FAZ (QUANDO AS TECLAS PRESSIONADAS CHEGAREM A 3 POSIÇÕES, SIGNIFICA QUE A SENHA ESTÁ CORRETA)
          setLocked(false); //FECHADURA DESTRANCADA
    }
    delay(100);//INTERVALO DE 100 MILISSEGUNDOS
    }
    void setLocked(int locked){ //TRATANDO O ESTADO DA FECHADURA
    if (locked){ //SE FECHADURA TRANCADA, FAZ
        digitalWrite(ledVermelho, HIGH);
        digitalWrite(ledVerde, LOW);
        servo_Motor.write(0); //POSIÇÃO DO SERVO FICA EM 0º 
    }
    else{ 
        digitalWrite(ledVerde, HIGH);
        digitalWrite(ledVermelho, LOW);
        servo_Motor.write(90);// SERVO GIRA A 90º 
    }
    }