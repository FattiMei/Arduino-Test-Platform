typedef union{
    unsigned char raw;

    struct{
        unsigned char C : 1;
        unsigned char Z : 1;
        unsigned char N : 1;
        unsigned char V : 1;
        unsigned char S : 1;
        unsigned char H : 1;
        unsigned char T : 1;
        unsigned char I : 1;
    };
} SREG_t;

typedef union{
    unsigned char raw;

    struct{
        unsigned char B0 : 1;
        unsigned char B1: 1;
        unsigned char B2 : 1;
        unsigned char B3 : 1;
        unsigned char B4 : 1;
        unsigned char B5 : 1;
        unsigned char B6 : 1;
        unsigned char B7 : 1;
    };
} PORTB_t;

typedef union{
    unsigned char raw;

    struct{
        unsigned char B0 : 1;
        unsigned char B1: 1;
        unsigned char B2 : 1;
        unsigned char B3 : 1;
        unsigned char B4 : 1;
        unsigned char B5 : 1;
        unsigned char B6 : 1;
        unsigned char B7 : 1;
    };
} DDRB_t;

typedef union{
    unsigned char raw;

    struct{
        unsigned char B0 : 1;
        unsigned char B1: 1;
        unsigned char B2 : 1;
        unsigned char B3 : 1;
        unsigned char B4 : 1;
        unsigned char B5 : 1;
        unsigned char B6 : 1;
        unsigned char B7 : 1;
    };
} PINB_t;

typedef union{
    unsigned char raw;

    struct{
        unsigned char C0 : 1;
        unsigned char C1: 1;
        unsigned char C2 : 1;
        unsigned char C3 : 1;
        unsigned char C4 : 1;
        unsigned char C5 : 1;
        unsigned char C6 : 1;
        unsigned char C7 : 1;
    };
} PORTC_t;

typedef union{
    unsigned char raw;

    struct{
        unsigned char C0 : 1;
        unsigned char C1: 1;
        unsigned char C2 : 1;
        unsigned char C3 : 1;
        unsigned char C4 : 1;
        unsigned char C5 : 1;
        unsigned char C6 : 1;
        unsigned char C7 : 1;
    };
} DDRC_t;

typedef union{
    unsigned char raw;

    struct{
        unsigned char C0 : 1;
        unsigned char C1: 1;
        unsigned char C2 : 1;
        unsigned char C3 : 1;
        unsigned char C4 : 1;
        unsigned char C5 : 1;
        unsigned char C6 : 1;
        unsigned char C7 : 1;
    };
} PINC_t;

typedef union{
    unsigned char raw;

    struct{
        unsigned char D0 : 1;
        unsigned char D1: 1;
        unsigned char D2 : 1;
        unsigned char D3 : 1;
        unsigned char D4 : 1;
        unsigned char D5 : 1;
        unsigned char D6 : 1;
        unsigned char D7 : 1;
    };
} PORTD_t;

typedef union{
    unsigned char raw;

    struct{
        unsigned char D0 : 1;
        unsigned char D1: 1;
        unsigned char D2 : 1;
        unsigned char D3 : 1;
        unsigned char D4 : 1;
        unsigned char D5 : 1;
        unsigned char D6 : 1;
        unsigned char D7 : 1;
    };
} DDRD_t;
typedef union{
    unsigned char raw;

    struct{
        unsigned char D0 : 1;
        unsigned char D1: 1;
        unsigned char D2 : 1;
        unsigned char D3 : 1;
        unsigned char D4 : 1;
        unsigned char D5 : 1;
        unsigned char D6 : 1;
        unsigned char D7 : 1;
    };
} PIND_t;

PORTB_t PORTB;
DDRB_t DDRB;
PINB_t PINB;

PORTC_t PORTC;
DDRC_t DDRC;
PINC_t PINC;

PORTD_t PORTD;
DDRD_t DDRD;
PIND_t PIND;
