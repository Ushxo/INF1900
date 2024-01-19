#include <avr/io.h> 
#define F_CPU 8000000
#include <util/delay.h>

const int ROUGE = 0x01;
const int VERT = 0x02;
const int PRESSED = 0x04;
const int MODE_SORTIE = 0xff;
const int ETEINT = 0x00;

void probleme1(){
    DDRB = MODE_SORTIE; // Le port B est en mode sortie
    enum State : int{INIT, S1, S2, S3}; // États INIT, S1, S2, S3
    State state = INIT; // État initial
    bool previousStateIsPressed = false;

    for(;;){ // Loop infinie
        if(PIND & PRESSED){
            _delay_ms(10); // Debounce
            previousStateIsPressed = true;
        }
        else if(previousStateIsPressed){
            // Ici, le bouton vient d'être relâché
            previousStateIsPressed = false;
            switch(state){
                case INIT: state = S1; break;
                case S1: state = S2; break;
                case S2: state = S3; break;
                case S3: 
                    PORTB = VERT; // Allumer en vert
                    _delay_ms(2000); // Attendre 2 secondes
                    PORTB = ETEINT; // Éteindre la DEL
                    state = INIT; // Revenir à l'état initial
                    break;
            }
        }
    }    
}

int main(){
    probleme1();
    return 0;
}


