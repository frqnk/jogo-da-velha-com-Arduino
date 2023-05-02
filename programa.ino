#define BOTOES A5
const byte LED[2][9] = {{4,8,12,2,6,10,0,A4,A2},{5,9,13,3,7,11,1,A3,A1}};
byte jogadasAnteriores[9], leituraAnterior, passo, posicao[3];
bool identificador;

void setup() {
    randomSeed(analogRead(A0));
    for(byte n1 = 0; n1 < 2; n1++) {
        for(byte n2 = 0; n2 < 9; n2++) {
            pinMode(LED[n1][n2], OUTPUT);
        }
    }
}

void loop() {
    byte leitura = round(analogRead(BOTOES)*9.00/1023);
    if(leitura && leitura != leituraAnterior) {
        for(byte n = 0; n < passo || n == 0; n++) {
            if(leitura == jogadasAnteriores[n]) break;
            else if(n == passo-1 || !passo) {
                if(passo % 2 == 0) {
                    if(passo == 0) identificador = random(2);
                    digitalWrite(LED[identificador][leitura-1], 1);
                    jogadasAnteriores[passo] = leitura;
                    if(passo >= 4) ChecarVitoria(identificador);
                }
                else {
                    digitalWrite(LED[!identificador][leitura-1], 1);
                    jogadasAnteriores[passo] = leitura;
                    if(passo >= 5) ChecarVitoria(!identificador);
                }
                if(passo >= 8) {
                    for(byte n1 = 0; n1 < 2; n1++) {
                        for(byte n2 = 0; n2 < 9; n2++) {
                            digitalWrite(LED[n1][n2], 0);
                        }
                    }
                    passo = 0;
                }
                else passo++;
            }
        }
    }
    leituraAnterior = leitura;
}

void ChecarVitoria(bool id) {
    for(byte n = 0; n < 8 && !(passo > 8); n++) {
        switch(n) {
            case 0:
                DefinirSequencia(0,1,2);
                break;
            case 1:
                DefinirSequencia(3,4,5);
                break;
            case 2:
                DefinirSequencia(6,7,8);
                break;
            case 3:
                DefinirSequencia(0,3,6);
                break;
            case 4:
                DefinirSequencia(1,4,7);
                break;
            case 5:
                DefinirSequencia(2,5,8);
                break;
            case 6:
                DefinirSequencia(0,4,8);
                break;
            case 7:
                DefinirSequencia(2,4,6);
                break;
        }
        if(digitalRead(LED[id][posicao[0]]) && digitalRead(LED[id][posicao[1]]) && digitalRead(LED[id][posicao[2]])) {
            for(byte n1 = 0; n1 < 7; n1++) {
                for(byte n2 = 0; n2 < 3; n2++) {
                        digitalWrite(LED[id][posicao[n2]], !digitalRead(LED[id][posicao[n2]]));
                }
                delay(333);
            }
            passo = 10;
        }
    }
}

void DefinirSequencia(byte m0, byte m1, byte m2) {
    posicao[0] = m0;
    posicao[1] = m1;
    posicao[2] = m2;
}