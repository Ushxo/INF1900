#include <avr/io.h> 
#define F_CPU 8000000
#include <util/delay.h>

const int ROUGE = 0x01;
const int VERT = 0x02;
const int PRESSED = 0x04;
const int MODE_SORTIE = 0xff;
const int ETEINT = 0x00;
bool currentStateIsPressed = false;

void CheckIfPressed(){
    if(PIND & PRESSED){ 
        _delay_ms(10); // Debounce
        if(PIND & PRESSED){
            currentStateIsPressed = true;
        }
    }
    else
        currentStateIsPressed = false;
}

void probleme2(){
    DDRB = MODE_SORTIE;
    enum State : int{S0, S1, S2, S3, S4, S5, S6};
    State state = S0; // État initial
    
    for(;;){
        CheckIfPressed();
        switch(state){
            case S0: // Rouge initial
                PORTB = ROUGE;
                if (currentStateIsPressed)
                    state = S1;
                break;
            case S1: // Ambre (bouton-poussoir pesé)
                while (currentStateIsPressed){
                    PORTB = ROUGE;
                    _delay_ms(4);
                    PORTB = VERT;
                    _delay_ms(4);
                    CheckIfPressed();
                }
                state = S2;
                break;
            case S2: // Vert (bouton-poussoir relâché)
                PORTB = VERT;
                if (!currentStateIsPressed)
                    state = S3;
                break;
            case S3: // Rouge (bouton-poussoir pesé à nouveau)
                PORTB = ROUGE;
                if (currentStateIsPressed)
                    state = S4;
                break;
            case S4: // Éteint (bouton-poussoir relâché à nouveau)
                PORTB = ETEINT;
                if (!currentStateIsPressed)
                    state = S5;
                break;
            case S5: // Vert (bouton-poussoir pesé encore)
                PORTB = VERT;
                if (currentStateIsPressed)
                    state = S6;
                break;
            case S6: // Rouge (bouton-poussoir relâché encore)
                PORTB = ROUGE;
                state = S0;
                break;
        }
    }
}

int main(){
    probleme2();
    return 0;
}
