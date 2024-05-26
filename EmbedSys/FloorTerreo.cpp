#include <wiringPi.h>
#include <vector>
#include <unistd.h>
#include "Floors.hpp"

// Definições dos pinos
#define ENDERECO_01 22
#define ENDERECO_02 26
#define ENDERECO_03 19

#define SENSOR_DE_VAGA 18

#define SINAL_DE_LOTADO_FECHADO 27 

#define SENSOR_ABERTURA_CANCELA_ENTRADA 23
#define SENSOR_FECHAMENTO_CANCELA_ENTRADA 24

#define MOTOR_CANCELA_ENTRADA 10

#define SENSOR_ABERTURA_CANCELA_SAIDA 25
#define SENSOR_FECHAMENTO_CANCELA_SAIDA 12

#define MOTOR_CANCELA_SAIDA 17

void setup() {
    wiringPiSetupGpio();

    // Configurar os pinos como entrada ou saída
    pinMode(ENDERECO_01, OUTPUT);
    pinMode(ENDERECO_02, OUTPUT);
    pinMode(ENDERECO_03, OUTPUT);

    pinMode(SENSOR_DE_VAGA, INPUT);

    pinMode(SINAL_DE_LOTADO_FECHADO, OUTPUT);
    
    pinMode(SENSOR_ABERTURA_CANCELA_ENTRADA, INPUT);
    pinMode(SENSOR_FECHAMENTO_CANCELA_ENTRADA, INPUT);

    pinMode(MOTOR_CANCELA_ENTRADA, OUTPUT);
    digitalWrite(MOTOR_CANCELA_ENTRADA, LOW); 

    pinMode(SENSOR_ABERTURA_CANCELA_SAIDA, INPUT);
    pinMode(SENSOR_FECHAMENTO_CANCELA_SAIDA, INPUT);

    pinMode(MOTOR_CANCELA_SAIDA, OUTPUT);
    digitalWrite(MOTOR_CANCELA_SAIDA, LOW); 
}

// Função para ler o estado da vaga
bool ler_estado_vaga(int endereco) {
    // Configurar os bits de endereço
    digitalWrite(ENDERECO_01, (endereco & 0x01) ? HIGH : LOW);
    digitalWrite(ENDERECO_02, (endereco & 0x02) ? HIGH : LOW);
    digitalWrite(ENDERECO_03, (endereco & 0x04) ? HIGH : LOW);

    // Esperar 30ms
    usleep(30000);  

    // Ler o estado da vaga
    return digitalRead(SENSOR_DE_VAGA);
}

int floor_terreo(struct shared_data_client& sdc, std::mutex& mutex_floor) {
    setup();

    while (true) {
        
        //variaveis auxiliares
        int vagas_ocupadas = 0;
        std::vector<int> vagas = {0};
        
        // Verificar o sensor de abertura e fechamento da cancela de entrada
        bool abertura_cancela_entrada = digitalRead(SENSOR_ABERTURA_CANCELA_ENTRADA);
        bool fechamento_cancela_entrada = digitalRead(SENSOR_FECHAMENTO_CANCELA_ENTRADA);

        if (abertura_cancela_entrada) {
            digitalWrite(MOTOR_CANCELA_ENTRADA, HIGH);  // Acionar o motor
        }
        
        usleep(1000); // espera 1ms

        if (fechamento_cancela_entrada) {
            digitalWrite(MOTOR_CANCELA_ENTRADA, LOW);  // Desligar o motor
        }

        // Verificar o sensor de abertura e fechamento da cancela de saida
        bool abertura_cancela_saida = digitalRead(SENSOR_ABERTURA_CANCELA_SAIDA);
        bool abertura_cancela_saida = digitalRead(SENSOR_FECHAMENTO_CANCELA_SAIDA);

        if (abertura_cancela_saida) {
            digitalWrite(SENSOR_ABERTURA_CANCELA_SAIDA, HIGH);  // Acionar o motor
        }

        usleep(1000); // espera 1ms

        if (abertura_cancela_saida) {
            digitalWrite(SENSOR_FECHAMENTO_CANCELA_SAIDA, LOW);  // Desligar o motor
        }

        // Verificar o estado das 7 vagas
        for (int endereco = 0; endereco < 7; endereco++) {
            bool estado_vaga = ler_estado_vaga(endereco);
            if(estado_vaga){
                vagas_ocupadas++;
                vagas[endereco] = 1;
            }
        }

        if(vagas_ocupadas = 8 || read_signal_led(sdc) = true)
            digitalWrite(SINAL_DE_LOTADO_FECHADO, HIGH);  
        else          
            digitalWrite(SINAL_DE_LOTADO_FECHADO, LOW);

        {
            std::lock_guard<std::mutex> lock(mutex_floor);
            write_shared_data_client(sdc, "terreo", vagas_ocupadas, vagas, false, false, digitalRead(SINAL_DE_LOTADO_FECHADO));
        }

        delay(1000);  // Esperar 1 segundo antes de verificar novamente
    }

    return 0;
}
