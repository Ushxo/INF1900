/*
 * Nom:Sami Madani (2294008) et Jazia Benhadjeba (2301759)
 * Groupe: 05
 * TP2 PB2
 * Descrption du programme:
 * Identifications mat/rielles: Entree : Bouton-poussoir(D2), Sortie: DEL

        TABLEAU D'ETAT PROBLEME 2 (A MODIFIER)
 CURRENT STATE || ENTREE || NEXT STATE || SORTIE
 -----------------------------------------------
      INIT     ||   0    ||    INIT    || ETEINT
      INIT     ||   1    ||     S0     || ETEINT
       S0      ||   0    ||     S0     || ETEINT
       S0      ||   1    ||     S1     || ETEINT
       S1      ||   0    ||     S1     || ETEINT
       S1      ||   1    ||     S2     || ETEINT
       S2      ||   0    ||     S2     || ETEINT
       S2      ||   1    ||     S3     || ETEINT
       S3      ||   0    ||     S3     || ETEINT
       S3      ||   1    ||     S4     || ETEINT
       S4      ||   0    ||     S4     || ETEINT
       S4      ||   1    ||    INIT    || VERT

 */

#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

const int PRESSED = 0x04;
const int MODE_SORTIE = 0xff;
const int ETEINT = 0x00;
bool isPressed = false;

bool checkIfPressed(){
    if(PIND & PRESSED){
        _delay_ms(10); // Debounce
        return (PIND & PRESSED);
    }
        return false;
    }

void greenLight(){
    PORTB &= ~(1 << PB1);
    PORTB |= (1 << PB0);
}

void redLight(){
    PORTB &= ~(1 << PB0);
    PORTB |= (1 << PB1);
}

void pb2(){
    DDRB = MODE_SORTIE;
    enum class State : int{S0, S1, S2, S3, S4, S5};
    State state = State::S0; // État initial
    bool isPressed = false;

    while (true) {
        isPressed = checkIfPressed();
        switch(state) {
            case State::S0: // Rouge initial
                PORTB = redLight();
                break;
            case State::S1: // Ambre (bouton-poussoir pesé)
                PORTB = redLight();
                _delay_ms(4);
                PORTB = greenLight();
                _delay_ms(4);
                break;
            case State::S2: // Vert (bouton-poussoir relâché)
                PORTB = greenLight();
                break;
            case State::S3: // Rouge (bouton-poussoir pesé à nouveau)
                PORTB = redLight();
                break;
            case State::S4: // Éteint (bouton-poussoir relâché à nouveau)
                PORTB = ETEINT;
                break;
            case State::S5: // Vert (bouton-poussoir pesé encore)
                PORTB = VERT;
                break;
        }

        switch(state){
            case State::S0: // Rouge initial
                if (isPressed)
                    state = State::S1;
                break;
            case State::S1: // Ambre (bouton-poussoir pesé)
                if (!isPressed)
                    state = State::S2;
                break;
            case State::S2: // Vert (bouton-poussoir relâché)
                if (isPressed)
                    state = State::S3;
                break;
            case State::S3: // Rouge (bouton-poussoir pesé à nouveau)
                if (!isPressed)
                    state = State::S4;
                break;
            case State::S4: // Éteint (bouton-poussoir relâché à nouveau)
                if (isPressed)
                    state = State::S5;
                break;
            case State::S5: // Vert (bouton-poussoir pesé encore)
                if (!isPressed)
                    state = State::S0;
                break;
        }
    }
}

int main(){
    pb2();
    return 0;
}