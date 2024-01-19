/*
 * Nom:Sami Madani (2294008) et Jazia Benhadjeba (2301759)
 * Groupe: 05
 * TP2 PB1
 * Descrption du programme:
 * Identifications mat/rielles: Entree : Bouton-poussoir(D2), Sortie: DEL

        TABLEAU D'ETAT PROBLEME 1
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

constexpr int PRESSED = (1 << PIND2);
constexpr int OFF &= ~((1 << PINB0) | (1 << PINB1));
constexpr int DEBOUNCE_DELAY_MS = 10;
constexpr int LIGHTOFF_DELAY_MS = 2000;

void greenLight(){
    PORTB &= ~(1 << PB1);
    PORTB |= (1 << PB0);
}

bool debounce(){
    if(PIND & PRESSED){
            _delay_ms(DEBOUNCE_DELAY_MS); // Debounce
            return (PIND & PRESSED);
    }
        return false;
}

void pb1(){
    DDRB |= (1 << PIND2);
    enum class State : int{INIT, P_R1, P_R2, P_R3}; // P_R = Press_Release
    State state = State::INIT;
    bool isPressed = false;

    while (true) {
        isPressed = debounce();
            switch(state) {
                case State::INIT:
                    state = State::P_R1;
                    break;
                case State::P_R1:
                    state = State::P_R2;
                    break;
                case State::P_R2:
                    state = State::P_R3;
                    break;
                case State::P_R3:
                    PORTB = greenLight();
                    _delay_ms(LIGHTOFF_DELAY_MS);
                    PORTB = OFF;
                    state = State::INIT;
                    break;
            }
        }
    }


int main(){
    pb1();
    return 0;
}