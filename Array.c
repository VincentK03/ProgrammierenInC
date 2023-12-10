#include <stdio.h>
#include <string.h>
#include <stdint.h> //fuer uintptr_t
#include <stdlib.h> //fuer strtol()
#define VT100_FETT "\033[1m"
#define VT100_OFF "\033[0m"

// Compilerschalter: -Wall -fsanitize=address

typedef enum
{
    DUMP_8,
    DUMP_16,
    DUMP_32,
    DUMP_8A,
    DUMP_16A,
    DUMP_32A,
} DUMP_MODE;
int dump(void *start, size_t len, int width, DUMP_MODE mode);

int32_t mat1[4][5] = {{10, 20, 30, 40},
                      {11, 22, 33, 44},
                      {01, 02, 03, 04}};
int32_t mat2[4][5] = {{[2] = 3}, {[0 ... 2] = 2}, {[1] = 7, 8}, [1][2] = 1, [3][1] = -1, [3][1 ... 2] = -2};

// Aufgabe 1)
// Erstellen sie einen Zeiger auf ein zweidimensionales Array, welchen
//   z.B. eines der beiden obigen Array zugeweisen werden kann (mat3=mat1;)
#if 1
int32_t (*mat3)[5] = mat1; // bei eindimensionalen arrays kann die klammer weg
#endif
// Aufgabe 2) Matrix Initialisierung
// mat1 und mat2 werden mit der Definition initialisiert. Erklären sie für
//    beide Initialisierungen, welche Initialisierungswerte welche Arrayelemente
//    initialisiert
/*
mat1 4 Zeilen und 5 Spalten
+--+--+--+--+--+
|10|20|30|40|0 |
|11|22|33|44|0 |
|01|02|03|04|0 |
|0 |0 |0 |0 |0 |
+--+--+--+--+--+

mat2 4 Zeilen und 5 Spalten ??????
+--+--+--+--+--+
|0 |0 |3 |0 |0 |
|2 |2 |1 |0 |0 |
|0 |7 |8 |0 |0 |
|0 |-2|-2|0 |0 |
+--+--+--+--+--+
*/
// Aufgabe 3a) Matrix mit beliebiger Dimension als Call by Reference übergeben
// Erstellen sie eine Funktion, welche den Inhalt einer Matrix ausgibt.
//    Die darzustellende Matrix wird als Call By Reference übergeben. Die Dimension
//    der Matrix wird ebenfalls übergeben, so dass diese Funktion Matrizen
//    beliebiger Dimension darstellen kann.
//    Vervollständigen sie den Code im main() zum Aufruf dieser Funktion
// Aufruf/Test der Funktionalität bspw. über:
//>>debugr [mat1|mat2|mat3] dim1 dim2
//>>debugr mat1 4 5
//>>debugr mat1 4 4
//>>debugr mat1 5 4
//>>debugr mat2 1 20
#if 1
void debugr(int32_t *arr, int zeile, int spalte)
{
    if (arr == NULL)
    {
        printf("Array nicht definiert!\n");
    }
    else
    {
        printf("Matrix:\n");
        for (int i = 0; i < zeile; i++)
        {
            for (int j = 0; j < spalte; j++)
            {
                printf("%d\t", arr[i * spalte + j]);
            }
            printf("\n");
        }
    }
}
#endif
// Aufgabe 3b) Matrizen mit fester Dimension als Call by Reference über- und zurückgeben
// Erstellen sie eine Funktion, welche zwei Matrizen subtrahiert und die
//    resultierende Matrix als Rückgabeparameter an den Aufrufer zurückgibt.
//    Benutzend sie bei der Datentypdefinition für den minuend und den subtrahend
//    jeweils ein andere Schreibweise!
//    Vervollständigen sie den Code im main() zum Aufruf dieser Funktion
// Aufruf/Test der Funktionalität bspw. über
//>>sub [mat1|mat2|mat3] [mat1|mat2|mat3]
//>>sub mat1 mat2
//>>sub mat1 mat1
#if 0
___ sub( ___ minuend ___  , ___ subtrahend ___)
{
if(!minuend || !subtrahend) {
    printf("minuend oder subtrahend nicht definiert\n");
    return NULL;
}
___  diff ___ =malloc( ___ );  
return diff;
}
#endif

// Aufgabe 4a) Matrix per Call By Value übergeben
// Erstellen sie eine Funktion, welche den Inhalt einer Matrix ausgibt
//    Die darzustellende Matrix wird als Call By Value übergeben. Die
//    Dimension ist fix [4][5].
//    Vervollständigen sie den Code im main() zum Aufruf dieser Funktion
// Aufruf/Test der Funktionalität bspw. mittels
//>>debugv [mat1|mat2|mat3]
#if 1
// Erstellen sie einen Alias eines Datentyps zur Nutzung für diese Call By Value Aufgaben
typedef struct
    cbv_t
{
    int arr[4][5]
} cbv_t;

void debugv(cbv_t mat)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            printf("%3d ", mat.arr[i * 4 + j]);
        }
        printf("\n");
    }
    printf("\n");
}
#endif(
// Aufgabe 4b) Matrix per Call By Value zurückgeben
// Erstellen sie eine Funktion, welche eine Matrix fixer Größe [4][5]
//    erstellt, die einzelnen Elemente mittels matr[zeile][spale]=zeile*100+spalte;
//    initialisiert und diese als Call by Value zurückgibt
//    Vervollständigen sie den Code im main() zum Aufruf dieser Funktion
// Aufruf/Test der Funktionalität bspw. mittels
//>>allocv [mat1|mat2|mat3]
#if 0
cbv_t allocv(void)
{
}
#endif

// Aufgabe 5) Speicherbedarf
// Wieviel Bytes werden beim Aufruf der Funktion vom Caller (hier main())
//   an den Callee (hier debugr(), sub(), debugv(), allocv())
//   vom Caller an den Callee übergeben und vom Callee an den Caller zurückgegeben

// Aufgabe 6) Speicherorganisation
// Geben sie in die Standardeingabe 'dump mat1' zur Ausgabe des Speicherabbildes
//   der Matrix1 ein. Kopieren sie diesen Speicherdump hier in den Sourcecode
//   und ordnen sie die Speicherinhalte den einzelnen Array-Elemente zu.
// Entfernen sie zur Darstellung des Speicherdump den Compilerschalter -fsanitize=address

const char help[] = "\n"
                    "dump   mat1|mat2                 - Speicherdump einer Matrix\n"
                    "debugr mat1|mat2|mat3 dim1 dim2  - Formatierte Ausgabe der Matrix\n"
                    "sub    mat1|mag2 mat1|mat2       - Subtraktion mat3=1.Operand-2.Operand\n"
                    "allocv mat1|mat2|mat3            - Array Initialisieren\n"
                    "debugv mat1|mat2|mat3            - Formatierte Ausgabe der Matrix\n"
                    "help                             - Führt alle Operationen auf.\n"
                    "quit                             - Beendet das Programm.\n";

int main(int argc, char const *argv[])
{
    printf("File:"__FILE__
           " erstellt am "__DATE__
           " um "__TIME__
           " gestartet\n");
    printf(help);
    while (1)
    {
        fflush(stdout);
        char input[100];
        if (fgets(input, sizeof input, stdin) == NULL)
        {
            break;
        }
        char *arg1 = strtok(input, " \n\r");
        char *arg2 = strtok(NULL, " \n\r");
        char *arg3 = strtok(NULL, " \n\r");
        char *arg4 = strtok(NULL, " \n\r");
        if (arg1 == NULL)
        {
            continue;
        }
#if 0
    else if((strcmp(arg1,"debugr")==0) && (arg2!=NULL) && (arg3!=NULL) && (arg4!=NULL)) {
        int zeilen= (int)strtol(arg3,NULL,0);
        int spalten=(int)strtol(arg4,NULL,0);
        if(strcmp(arg2,"mat1")==0) 
            debugr(*mat1,zeilen,spalten);
        else if(strcmp(arg2,"mat2")==0)
            debugr(*mat2,zeilen,spalten);
        else if(strcmp(arg2,"mat3")==0)
            debugr(*mat3,zeilen,spalten);
        else
            printf("Invalid Matrix\n");       
    }
#endif
#if 0
    else if((strcmp(arg1,"sub")==0) && (arg2!=NULL) && (arg3!=NULL)) {
        ______   minuend  _____;
        ______   subtrahend _____;
        minuend = strcmp(arg2,"mat1")==0 ? mat1 : 
                    (strcmp(arg2,"mat2")==0 ? mat2 : NULL);
        subtrahend = strcmp(arg3,"mat1")==0 ? mat1 : 
                    (strcmp(arg3,"mat2")==0 ? mat2 : NULL);
        if((minuend!=NULL) && (subtrahend!=NULL)) {
            if(mat3!=NULL)
                free(mat3);
            mat3=sub(minuend,subtrahend);
        }
        else
            printf("Invalid Argument\n");                    
    }
#endif
#if 0
    else if((strcmp(arg1,"allocv")==0) && (arg2!=NULL)) {
        cbv_t mat=allocv();
        if(strcmp(arg2,"mat1")==0) 
                _______  // mat1 <- mat
        if(strcmp(arg2,"mat2")==0) 
                _______  // mat2 <- mat
    }
#endif
#if 1
        else if ((strcmp(arg1, "debugv") == 0) && (arg2 != NULL))
        {
            struct cbv_t mat;
            if (strcmp(arg2, "mat1") == 0)
                mat = (struct cbv_t){mat1}; // mat <- mat1
            if (strcmp(arg2, "mat2") == 0)
                mat = (struct cbv_t){mat2}; // mat <- mat2
            if (strcmp(arg2, "mat3") == 0)
                mat = (struct cbv_t){mat2}; // mat <- mat3
            debugv(mat);
        }
#endif
        else if ((strcmp(arg1, "dump") == 0) && (arg2 != NULL))
        {
            if (strcmp(arg2, "mat1") == 0)
                dump(mat1, sizeof(mat1), 16, DUMP_8);
            if (strcmp(arg2, "mat2") == 0)
                dump(mat2, sizeof(mat2), 16, DUMP_8);
        }
        else if (strcmp(arg1, "help") == 0)
        {
            printf(help);
        }
        else if (strcmp(arg1, "quit") == 0)
        {
            break;
        }
        else
        {
            printf("%s \n", arg1);
            printf("unbekanntes Kommando\n");
        }
    }
    return 0;
}

/*---------------------------------------------------------------------------------------------*/
static char *dump_str[] = {
    "8-Bit",
    "16-Bit",
    "32-Bit",
    "8-Bit",
    "16-Bit",
    "32-Bit",
};
// Bei Nutzung dieser Funktion darf der Compiler-Schalter -fsanitze=address nicht genutzt werden
int dump(void *start, size_t len, int width, DUMP_MODE mode)
{
    { // Sanitizer Aktivierung feststellen
        int var1;
        int var2 = 0x55;
        int var3 = 0xaa;
        (void)var1;
        void *ptr2 = &var2;
        void *ptr3 = &var3;
        if (((ptr2 > ptr3) && ((size_t)ptr2 - (size_t)ptr3 != sizeof(int))) ||
            ((ptr2 < ptr3) && ((size_t)ptr3 - (size_t)ptr2 != sizeof(int))))
        {
            return printf("Für Speicherdump Compilerschalter -fsanitize=address rausnehmen!\n");
            return -1;
        }
    }
    void *ptr;
    uintptr_t size;
    switch (mode)
    {
    case DUMP_8:
    case DUMP_8A:
        size = 0x01;
        break;
    case DUMP_16:
    case DUMP_16A:
        size = 0x02;
        break;
    case DUMP_32:
    case DUMP_32A:
        size = 0x04;
        break;
    default:
        fprintf(stderr, "Illegal Mode\n");
        return -1;
    }
    ptr = (void *)((uintptr_t)start & ~(size - 1));
    printf(VT100_FETT "Speicherdump: %10p .. %10p Mode=%s " VT100_OFF,
           start, (void *)((char *)start + len - 1), dump_str[mode]);
    while ((char *)ptr < (char *)start + len)
    {
        printf("\n%#0*zx:", (int)sizeof(void *) * 2, (uintptr_t)ptr);
        for (int lauf = 0; lauf < width; lauf++)
        {
            switch (mode)
            {
            case DUMP_8:
            case DUMP_8A:
                printf(" %02x", *(((unsigned char *)ptr) + lauf) & 0xFF);
                break;
            case DUMP_16:
            case DUMP_16A:
                printf(" %04x", *(((unsigned short *)ptr) + lauf) & 0xFFFF);
                break;
            case DUMP_32:
            case DUMP_32A:
                printf(" %08x", *(((unsigned int *)ptr) + lauf));
                break;
            }
        }
        if ((mode == DUMP_8A) || (mode == DUMP_16A) || (mode == DUMP_32A))
        {
            printf(" - ");
            for (int lauf = 0; lauf < (width * size); lauf++)
            {
                switch (mode)
                {
                case DUMP_8A:
                case DUMP_16A:
                case DUMP_32A:
                {
                    char ch = *(((unsigned char *)ptr) + lauf) & 0xFF;
                    printf("%c", ch < 0x20 ? '.' : ch);
                    break;
                }
                case DUMP_8:
                case DUMP_16:
                case DUMP_32:
                    break;
                }
            }
        }
        ptr = (char *)ptr + (width * size);
    }
    printf("\n");
    return 0;
}
