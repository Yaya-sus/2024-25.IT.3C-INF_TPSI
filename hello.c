#include <stdio.h> 
#include <string.h>

// porte logiche
int NOT(int a) { return 1 - a;}
int AND(int a, int b) { return (a*b);}
int OR(int a, int b) { return (a+b)-(a*b);}
int XOR(int a, int b) { return (a+b) - 2*(a*b);}
int OR3(int a, int b, int c) { return OR(OR(a,b),c);}
int OR4(int a, int b, int c, int d) { return OR(OR3(a,b,c),d);}
int OR5(int a, int b, int c, int d, int e) { return OR(OR4(a,b,c,d),e);}
int NOR(int a, int b){ return NOT((a+b)-(a*b));}
int NOR3(int a, int b, int c){ return NOT(OR3(a,b,c));}
int NOR4(int a, int b, int c, int d){ return NOT(OR4(a,b,c,d));}
int AND3(int a, int b, int c) { return a*b*c;}
int AND4(int a, int b, int c, int d) { return a*b*c*d;}
int AND5(int a, int b, int c, int d, int e) {return a*b*c*d*e;}
int NAND(int a, int b){ return NOT(a*b);}
int NAND3(int a, int b, int c){ return NOT(a*b*c);}
int NAND4(int a, int b, int c, int d){ return NOT(a*b*c*d);}
int NAND5(int a, int b, int c, int d, int e){ return NOT(a*b*c*d*e);}
int XOR3(int a, int b, int c) { return XOR(XOR(a, b), c);}
int XOR4(int a, int b, int c, int d) { return XOR(XOR(a, b), XOR(c, d)); }
int XOR5(int a, int b, int c, int d, int e) { return XOR(XOR4(a, b, c, d), e); }


//alu e registri + collegamento con input
void ALU(int Cn, int M, int A0, int B0, int A1, int B1, int A2, int B2, int A3, int B3, int S0, int S1, int S2, int S3, int* nm, int* f0, int* f1, int* f2, int* f3, int* ab, int *x, int* cn4, int* y)
{
// Calcolo parte 1
int z = NOR3(AND(NOT(B0),S1),AND(S0,B0),A0);
int z1 = NOR(AND3(A0,NOT(B0),S2),AND3(B0,A0,S3));

int z2 = NOR3(AND(NOT(B1),S1),AND(S0,B1),A1);
int z3 = NOR(AND3(A1,NOT(B1),S2),AND3(B1,A1,S3));

int z4 = NOR3(AND(NOT(B2),S1),AND(S0,B2),A2);
int z5 = NOR(AND3(A2,NOT(B2),S2),AND3(B2,A2,S3));

int z6 = NOR3(AND(NOT(B3),S1),AND(S0,B3),A3);
int z7 = NOR(AND3(A3,NOT(B3),S2),AND3(B3,A3,S3));

// Calcolo parte 2
*nm = NOT(M);
*f0 = XOR(NAND(*nm,Cn),XOR(z1,z2));
*f1 = XOR(NOR(AND(*nm,z),AND3(*nm,Cn,z1)),XOR(z2,z3));
*f2 = XOR(NOR3(AND(z2,*nm),AND3(*nm,z,z3),AND4(*nm,z3,z1,Cn)),XOR(z4,z5));
*f3 = XOR(OR4(AND(*nm,z4),AND3(*nm,z2,z5),AND4(*nm,z,z5,z3),AND5(*nm,z5,z3,z1,Cn)),XOR(z6,z7));
*ab = AND4(*f0,*f1,*f2,*f3);
*x = NAND4(z1,z3,z5,z7);
*cn4 = OR(NOT(NAND5(Cn,z1,z3,z5,z7)),NOT(NOR4(AND4(z,z3,z5,z7),AND3(z2,z5,z7),AND(z4,z7),z6)));
*y = NOR4(AND4(z,z3,z5,z7),AND3(z2,z5,z7),AND(z4,z7),z6);

}

void REGISTRO(int i0, int i1, int i2, int i3, int i4 , int i5, int i6, int i7, int* o0, int* o1, int* o2, int* o3, int* o4, int* o5, int* o6, int* o7){
    int reset = 0;

    //Reset
    *o0 = AND(i0, NOT(reset));
    *o1 = AND(i1, NOT(reset));
    *o2 = AND(i2, NOT(reset));
    *o3 = AND(i3, NOT(reset));
    *o4 = AND(i4, NOT(reset));
    *o5 = AND(i5, NOT(reset));
    *o6 = AND(i6, NOT(reset));
    *o7 = AND(i7, NOT(reset));
       
    //Visualizzazione numeri memorizzati
    printf("Dato memorizzato: o0 = %d\n", *o0);
    printf("Dato memorizzato: o1 = %d\n", *o1);
    printf("Dato memorizzato: o2 = %d\n", *o2);
    printf("Dato memorizzato: o3 = %d\n", *o3);
    printf("Dato memorizzato: o4 = %d\n", *o4);
    printf("Dato memorizzato: o5 = %d\n", *o5);
    printf("Dato memorizzato: o6 = %d\n", *o6);
    printf("Dato memorizzato: o7 = %d\n", *o7);
    
    // Scelte utente
    while (1) {
        int s;
        printf("Scelte disponibili:\n");
        printf("1 - Reset\n");
        printf("2 - Sovrascrivi con nuove variabili\n");
        printf("3 - Termina\n");
        printf("Scegliere cosa fare:");
        scanf("%d", &s);

        if (s == 1) {
            // Caclolo reset
            i0 = 0;
            i1 = 0;
            i2 = 0;
            i3 = 0;
            i4 = 0;
            i5 = 0;
            i6 = 0;
            i7 = 0;
            reset = 1;
            
            *o0 = AND(i0, NOT(reset));
            *o1 = AND(i1, NOT(reset));
            *o2 = AND(i2, NOT(reset));
            *o3 = AND(i3, NOT(reset));
            *o4 = AND(i4, NOT(reset));
            *o5 = AND(i5, NOT(reset));
            *o6 = AND(i6, NOT(reset));
            *o7 = AND(i7, NOT(reset));
            
            printf("Reset effettuato o0 = %d\n", *o0);
            printf("Reset effettuato o1 = %d\n", *o1); 
            printf("Reset effettuato o2 = %d\n", *o2); 
            printf("Reset effettuato o3 = %d\n", *o3);
            printf("Reset effettuato o4 = %d\n", *o4); 
            printf("Reset effettuato o5 = %d\n", *o5);
            printf("Reset effettuato o6 = %d\n", *o6);
            printf("Reset effettuato o7 = %d\n", *o7);
    } 
    else if (s == 2) {
    //Nuove variabili
    printf("Inserisci nuova variabile (0 o 1): ");
           
    scanf("%d", &i0);
    scanf("%d", &i1);
    scanf("%d", &i2);    
    scanf("%d", &i3);    
    scanf("%d", &i4);    
    scanf("%d", &i5);    
    scanf("%d", &i6);   
    scanf("%d", &i7);    
     
    //Memorizzazione variabiki
    
    *o0 = AND(i0, NOT(reset));
        
    *o1 = AND(i1, NOT(reset));

    *o2 = AND(i2, NOT(reset));
            
    *o3 = AND(i3, NOT(reset));
            
    *o4 = AND(i4, NOT(reset));
        
    *o5 = AND(i5, NOT(reset));
            
    *o6 = AND(i6, NOT(reset));
            
    *o7 = AND(i7, NOT(reset));
    
    //Visualizazzione memorizzazione
    printf("Numero memorizzato: o0 = %d\n", *o0);
    printf("Numero memorizzato: o1 = %d\n", *o1);
    printf("Numero memorizzato: o2 = %d\n", *o2);
    printf("Numero memorizzato: o3 = %d\n", *o3);
    printf("Numero memorizzato: o4 = %d\n", *o4);
    printf("Numero memorizzato: o5 = %d\n", *o5);
    printf("Numero memorizzato: o6 = %d\n", *o6);
    printf("Numero memorizzato: o7 = %d\n", *o7);
    } 
    else if (s == 3) {
    printf("Fine registro\n");
    break;
    } 
    else {
    printf("Scelta non valida, riprova\n");
        }
    }
}

void LETTURA(char* reg, int indiceREG, int ValoreReg[8]) {
    
    for (int b = 0; b < 8; b++) {
        int r = indiceREG + b;
        
        if (reg[r] == '0' || reg[r] == '1') {
            ValoreReg[b] = reg[r] - '0';
        } else {
            ValoreReg[b] = 0; 
        }
    }
}



// decimale -> binario
void inverti(char* Abin) {

    int lunghezza = strlen(Abin);
    int i, j;
    char rif;
    for (i = 0, j = lunghezza - 1; i < j; i++, j--) {
        rif = Abin[i]; //0
        Abin[i] = Abin[j]; //9
        Abin[j] = rif;
    }
}

void BIN(int A, char* Abin) {
    
    // Gestione del caso 0
    if (A == 0) {
        strcpy(Abin, "0");
        return;
    }

    int i = 0;
    int Arif = A;

    // Estrae i bit e li inserisce nel buffer (in ordine inverso)
    while (Arif > 0){
        if(Arif % 2 == 0){Abin[i] = '0' ;}
        else{Abin[i]= '1' ;}
        
        Arif /= 2;
        i++;
    }
    
    Abin[i] = '\0';

    // Inverte la stringa per avere l'ordine corretto dei bit
    inverti(Abin);
}





int main() {


int A, B;
    // Un int è tipicamente 32 bit, quindi servono 32 caratteri per il binario + 1 per il '\0'.
    char numA[32 + 1];
    char numB[32 + 1];

    printf("Inserisci 2 numeri decimali non negativi: ");
    scanf("%d", &A);
    scanf("%d", &B);

    // Chiama la funzione per convertire e riempire il buffer
    
    BIN(A, numA);
    BIN(B, numB);

    printf("Il numero %d in binario: %s\n", A, numA);
    printf("Il numero %d in binario: %s\n", B, numB);


//Dichiarazione variabili
    int lunghezza;
    int InRegA[4][8]; 
    int OutRegA[4][8];

    int InRegB[4][8]; 
    int OutRegB[4][8];


    lunghezza = strlen(numA);

    printf("Numero inserito: %s (numero di bit %d)\n", numA, lunghezza);
    if(lunghezza > 32){ 
        printf("valore A causa overflow\n");
        return 0;
    }



    lunghezza = strlen(numB);

    printf("Numero inserito: %s (numero di bit %d)\n", numB, lunghezza);
    if(lunghezza > 32){ 
        printf("valore B causa overflow\n");
        return 0;
    }





//Memorizzazione nel registro A e B
    for (int r = 0; r < 4; r++) { 
        LETTURA(numA, r * 8, InRegA[r]);

printf("Inizializzazione e Interazione con Registro %d\n", r);
        REGISTRO(InRegA[r][0], InRegA[r][1], InRegA[r][2], InRegA[r][3],
                 InRegA[r][4], InRegA[r][5], InRegA[r][6], InRegA[r][7],
                 &OutRegA[r][0], &OutRegA[r][1], &OutRegA[r][2], &OutRegA[r][3],
                 &OutRegA[r][4], &OutRegA[r][5], &OutRegA[r][6], &OutRegA[r][7]);


        LETTURA(numB, r * 8, InRegB[r]);

printf("Inizializzazione e Interazione con Registro %d\n", r);
        REGISTRO(InRegB[r][0], InRegB[r][1], InRegB[r][2], InRegB[r][3],
                 InRegB[r][4], InRegB[r][5], InRegB[r][6], InRegB[r][7],
                 &OutRegB[r][0], &OutRegB[r][1], &OutRegB[r][2], &OutRegB[r][3],
                 &OutRegB[r][4], &OutRegB[r][5], &OutRegB[r][6], &OutRegB[r][7]);

    }


//Visualizzazione risultato
    printf("Stato finale del registro A:\n");
    for (int r = 0; r < 4; r++){
        printf("Registro %d: ", r);
        for (int b = 0; b < 8; b++) {
            printf("%d", OutRegA[r][b]);
        }
        printf("\n");
    }

        printf("Stato finale del registro B:\n");
    for (int r = 0; r < 4; r++){
        printf("Registro %d: ", r);
        for (int b = 0; b < 8; b++) {
            printf("%d", OutRegB[r][b]);
        }
        printf("\n");
    }


    //sezione calcolo

ALU();
ALU();
ALU();
ALU();
ALU();
ALU();
ALU();
ALU();



    printf("\nProgramma terminato\n");
    return 0;
} 


