# ProgrammierenInC

#include <stdio.h>
#include <string.h>
#include <stdint.h>   //fuer uintptr_t

#define VT100_FETT    "\033[1m"
#define VT100_OFF     "\033[0m"

//Compilerschalter: keine
typedef enum {DUMP_8, DUMP_16, DUMP_32, 
              DUMP_8A,DUMP_16A,DUMP_32A,} DUMP_MODE;
int dump(void *start, size_t len, int width, DUMP_MODE mode);
void print_memory_region(void *stack_start);

typedef  struct  {int  x,y,z;}  xyz_t;
typedef  union   {int  a;short  b;char  c;}  abc_t; 
//Bitte als globale Variablen belassen
int     vari1=0x01234567;    
short   vars1=0x1122;
short   vars2=0x3344;
char    varc1='a';
char    varc2=49;
char    varc3=50;
char    varc4='\a';
int     vari2='a' + ('b'<<24);
char    varc5a[16]="abcdefghijklmno";
xyz_t   varxyz={-2, 3,-4};
abc_t   varabc={.c=5};
unsigned int   *ptri   =(unsigned int   *)0x0001;
unsigned short *ptrs   =(unsigned short *)(15<<24);
unsigned char  *ptrc   =(unsigned char  *)(0x101<<16);
xyz_t  *ptrxyz =(xyz_t *)-4;
abc_t  *ptrabc =(abc_t *)-5;

void  func_value(int   vari) {
         vari=7;
}
void  func_reference(unsigned int  *ptrlok) {
        *ptrlok=7;
}
void  func_ptrptr(unsigned int  **pptri) {
        *pptri=(unsigned int*)&vari2;
}
void func_return(void) {
        unsigned int   lokale=4711;
        ptri=&lokale;
}
void dump_variablen(void)
{
    printf("----------------------------------------\n"
           "vari1=%08x    vari2=%08x\n"
           "vars1=%04hx        vars2=%04hx\n"
           "varc1=%02hhx varc2=%02hhx varc3=%02hhx varc4=%02hhx\n"
           "Varc5[0..15] =%02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx\n"
           "varxyz.x=%08x varxyz.y=%08x varxyz.z=%08x\n"
           "varabc.a=%08x varabc.b=%04hx     varabc.c=%02hhx\n",
           vari1,vari2,vars1,vars2,varc1,varc2,varc3,varc4,
           varc5a[0],varc5a[1],varc5a[ 2],varc5a[ 3],varc5a[ 4],varc5a[ 5],varc5a[ 6],varc5a[ 7],
           varc5a[8],varc5a[9],varc5a[10],varc5a[11],varc5a[12],varc5a[13],varc5a[14],varc5a[15],
           varxyz.x,varxyz.y,varxyz.z,
           varabc.a,varabc.b,varabc.c);
}

int  main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    print_memory_region(&argc);


//1) Nachfolgende Funktion stellt den Speicherbereich rund um die oben
//   definierten globalen Variablen dar. Fügen sie den DUMP-Ausdruck 
//   hier in den Kommentarbereich ein und kommentieren sie, welche
//   Inhalte/Bytes zu welchen Variablen gehören
/*
pointer unabhängig vom von Datenty 4 oder g Byte groß, 
Variablen alle nacheinander angelegt und liegen somit im Speicher alle hintereinander 
Speicherdump:   0x404040 ..   0x404097 Mode=8-Bit 
0x00000000404040: 67 45 23 01 22 11 44 33 - gE#.".D3    int vari1 -> 4Byte : 67 45 23 01, short vars1 -> 2 Byte : 22 11,short vars2 -> 2 Byte : 44 33  
0x00000000404048: 61 31 32 07 61 00 00 62 - a12.a..b    char varc1 -> 1 Byte : 61, char varc2 -> 1 Byte : 31; char varc3 -> 1 Byte : 32, char varc4 -> 1 Byte : 07, int vari2 -> 4Byte : 61 00 00 62
0x00000000404050: 61 62 63 64 65 66 67 68 - abcdefgh    char varc5a[16] -> 16 Byte : 61 62 63 64 65 66 67 68 69 6a 6b 6c 6d 6e 6f 00
0x00000000404058: 69 6a 6b 6c 6d 6e 6f 00 - ijklmno.
0x00000000404060: fe ff ff ff 03 00 00 00 - ........    xyz_t varxyz -> 12 Byte : fe ff ff ff 03 00 00 00 fc ff ff ff
0x00000000404068: fc ff ff ff 05 00 00 00 - ........    abc_t   varabc -> Union so groß wie das größte element, hier int -> 4 Byte : 05 00 00 00
0x00000000404070: 01 00 00 00 00 00 00 00 - ........    unsigned int *ptri -> 8Byte (64 Bit System) : 01 00 00 00 00 00 00 00
0x00000000404078: 00 00 00 0f 00 00 00 00 - ........    unsigned short *ptrs -> 8Byte : 00 00 00 0f 00 00 00 00
0x00000000404080: 00 00 01 01 00 00 00 00 - ........    unsigned char  *ptrc -> 8Byte : 00 00 01 01 00 00 00 00
0x00000000404088: fc ff ff ff ff ff ff ff - ........    xyz_t  *ptrxyz -> 8 Byte : fc ff ff ff ff ff ff ff
0x00000000404090: fb ff ff ff ff ff ff ff - ........    abc_t  *ptrabc -> 8 Byte : fb ff ff ff ff ff ff ff
*/
dump(&vari1,(char *)&ptrabc-(char *)&vari1+sizeof(ptrabc),8,DUMP_8A);
//   start          länge                   breite 
//2) Führen sie nachfolgende Befehle im Block aus 
//   Überlegen sie sich vor Ausführung auf Basis des Speicherdumps
//   aus der vorherigen Aufgabe die dargestellten Werte für die 
//   Dereferenzierung
//   Erklären sie für die makierten Zeilen, wie sich der Wert der 
//   Pointervariablen zusammensetzt und woher der Inhalt
//   bei der Dereferenzierung stammt
#if 0
  printf("Adresse von vari1:%p\n",(void *)&vari1);
  ptrc= (unsigned char  *)& vari1;     printf("%02hhx\n",*ptrc);  
  ptrc=((unsigned char  *)& vari1)+1;  printf("%02hhx\n",*ptrc);  
  ptrc=((unsigned char  *)& vari1)+2;  printf("%02hhx\n",*ptrc);  //<<<<
  ptrc=((unsigned char  *)& vari1)+3;  printf("%02hhx\n",*ptrc);  
  ptrc=((unsigned char  *)& vari1)+4;  printf("%02hhx\n",*ptrc);  
  ptrc=((unsigned char  *)& vari1)+5;  printf("%02hhx\n",*ptrc); 
  ptrc=((unsigned char  *)& vari1)+6;  printf("%02hhx\n",*ptrc); 
  ptrc=((unsigned char  *)& vari1)+7;  printf("%02hhx\n",*ptrc); 
  ptrc=((unsigned char  *)& vari1)+8;  printf("%02hhx\n",*ptrc); 
  ptrc=((unsigned char  *)& vari1)+9;  printf("%02hhx\n",*ptrc); 
  ptrc=((unsigned char  *)& vari1)+10; printf("%02hhx\n",*ptrc); 
  ptrc=((unsigned char  *)& vari1)+11; printf("%02hhx\n",*ptrc);  
#elif 0
  printf("Adresse von vari1:%p\n",(void *)&vari1);
  ptrs= (unsigned short *)& vari1;    printf("%04hx\n",*ptrs);    
  ptrs=((unsigned short *)& vari1)+2; printf("%04hx\n",*ptrs);
  ptrs=((unsigned short *)& vari1)+3; printf("%04hx\n",*ptrs); //<<<< 
  ptrs=((unsigned short *)& vari1)+4; printf("%04hx\n",*ptrs); 
  ptrs=((unsigned short *)& vari1)+5; printf("%04hx\n",*ptrs); 
#elif 0
  printf("Adresse von vari1:%p\n",(void *)&vari1);
  ptri=(unsigned int *)&vari1;    printf("%08x\n",*ptri);   
  ptri=(unsigned int *)&vari1+1;  printf("%08x\n",*ptri);  //<<<<
  ptri=(unsigned int *)&vari1+2;  printf("%08x\n",*ptri);  
#endif

//3) Führen sie nachfolgende Zeilen einzeln durch. 
//   Erklären sie, wie sich der Wert der Pointervariablen zusammensetzt und 
//   welche Adresse in der Tat dereferenziert wird.
//   Als Hilfestellung nutzen sie die 'Liste der Prioritäten'
//   https://de.wikibooks.org/wiki/C-Programmierung:_Liste_der_Operatoren_nach_Priorit%C3%A4t
//   Einige der Dereferenzierung schlagen fehl. Begründen sie, warum diese fehl schlagen
#if 0
                                       fprintf(stderr,"1) %02hhx\n",*ptrc);
  ptrc=(unsigned char *)0x100;         fprintf(stderr,"2) %02hhx\n",*ptrc);      
  ptrc=(unsigned char *)&vari1;        fprintf(stderr,"3) %02hhx\n",*ptrc);     
  ptrc=(unsigned char *)&vari1+1;      fprintf(stderr,"4) %02hhx\n",*ptrc);   
  ptrc=(unsigned char *)(&vari1+1);    fprintf(stderr,"5) %02hhx\n",*ptrc);   
  ptrc=(unsigned char *)&vari1;        fprintf(stderr,"6) %02hhx\n",*ptrc+1);  
  ptrc=(unsigned char *)&vari1;        fprintf(stderr,"7) %02hhx\n",*(ptrc+1)); 
  ptrc=(unsigned char *)(&vari1-100);  fprintf(stderr,"8) %02hhx\n",*ptrc);   
  ptrc=(unsigned char *)(&vari1+4096); fprintf(stderr,"9) %02hhx\n",*ptrc); 
#endif
 
//4) Lassen sie sich die Inhalte der Variablen vari1..varc4 vor und nach  
//   der Ausführung folgender Anweisungen ausgeben 
//   Begründen sie die Änderungen, die hier stattfinden
#if 0
  dump_variablen();
  ptrxyz=(xyz_t  *)& vari1;
  ptrxyz->x=0x01234567;   
  ptrxyz->y=0x00020002; 
  ptrxyz->z=0x01020403;   
  dump_variablen();
#endif

//5) Wie  müssten  die  Variablen   vars2.. varc5a  initialisiert  werden,  
//   damit  nachfolgende  Bedingung  erfüllt ist
#if 0
  ptrxyz=(xyz_t*)& vars2;
  if((ptrxyz->x==1)  &&  (ptrxyz->y==-1)  &&  (ptrxyz->z==0x48495051))
        printf("True");
#endif

//6) Erklären sie, wie der dargestellte Speicherdump 'zustandekommt'
#if 0
  varabc.a=0x11111111;
  varabc.b=0x22222222;
  varabc.c=0x33333333;
  dump(&varabc,4,4,DUMP_8);
#endif

//7) Welche  Auswirkung  hat  der  Aufruf  der  einzelnen  Funktionen  auf  
//   die  zuvor  initialisierten globalen Variable/Pointer?
#if 0
  unsigned int vari1=1;
  func_value(vari1);   
#elif 0
  unsigned int vari1=1;
  func_reference(&vari1);  
#elif 0
  unsigned int vari1=1;
  ptri=& vari1;
  func_reference(ptri);    
#elif 0
  ptri=(unsigned int *)&vari1;
  func_ptrptr(&ptri);              
#endif

//8) Erklären sie, warum bei den beiden printf Ausgabe unterschiedliche
//   Werte ausgegeben werden, obwohl ptri nur einmal gesetzt wird!
#if 0
  unsigned int lok=0;
  func_return();
  lok=*ptri;
  fprintf(stderr,"1.Lauf Value=%u\n",lok);  
  func_value(1111);
  lok=*ptri;
  fprintf(stderr,"2.Lauf Value=%u\n",lok); 
#endif

//9) Erklären sie anhand des Speicherdumps die Ausgabe nachfolgender printf Anweisung
#if 0
  printf("'%s'\n",&varc1);
#endif 
fprintf(stderr,"Main erfolgreich durchgelaufen");
return 0;
}

/*------------------------------------------------------------------*/
/*   Hilfsroutinen                                                  */
/*------------------------------------------------------------------*/
static const char *dump_str[]={"8-Bit","16-Bit","32-Bit",
                  "8-Bit","16-Bit","32-Bit",};
//Bei Nutzung dieser Funktion darf der Compiler-Schalter -fsanitze=address nicht genutzt werden
int dump(void *start, size_t len, int width, DUMP_MODE mode)
{
    {   //Sanitizer Aktivierung feststellen
        int var1;
        int var2=0x55;
        int var3=0xaa;
        (void)var1;
        void *ptr2=&var2;
        void *ptr3=&var3;
        if(((ptr2>ptr3) && ((size_t)ptr2-(size_t)ptr3!=sizeof(int))) ||
           ((ptr2<ptr3) && ((size_t)ptr3-(size_t)ptr2!=sizeof(int)))) {
            return printf("Für Speicherdump Compilerschalter -fsanitize=address rausnehmen!\n");
            return -1;
           }
    }
    void *ptr;
    uintptr_t size;
    switch(mode) {
        case DUMP_8: 
        case DUMP_8A:
            size=0x01;
            break;
        case DUMP_16:
        case DUMP_16A: 
            size=0x02;
            break;
        case DUMP_32:
        case DUMP_32A:
            size=0x04;
            break;
        default:
            fprintf(stderr,"Illegal Mode\n");
            return -1;
    }
    ptr=(void *)((uintptr_t)start & ~(size-1));
    printf(VT100_FETT "Speicherdump: %10p .. %10p Mode=%s " VT100_OFF ,
            start,(void *)((char *)start+len-1),dump_str[mode]);
    while((char *)ptr<(char *)start+len) {
        printf("\n%#0*zx:",(int)sizeof(void *)*2,(uintptr_t)ptr);
        for(int lauf=0;lauf<width;lauf++) {
            switch(mode) {
                case DUMP_8:
                case DUMP_8A:
                    printf(" %02x",*(((unsigned char *)ptr)+lauf)&0xFF);
                    break;
                case DUMP_16:
                case DUMP_16A: 
                    printf(" %04x",*(((unsigned short *)ptr)+lauf)&0xFFFF);
                    break;
                case DUMP_32:
                case DUMP_32A:
                    printf(" %08x",*(((unsigned int *)ptr)+lauf));
                    break;
            }
        }
        if((mode==DUMP_8A) || (mode==DUMP_16A) || (mode==DUMP_32A)) {
            printf(" - ");
            for(int lauf=0;lauf<(width*size);lauf++) {
                switch(mode) {
                    case DUMP_8A:
                    case DUMP_16A:
                    case DUMP_32A: {
                        char ch=*(((unsigned char *)ptr)+lauf)&0xFF;
                        printf("%c",ch<0x20?'.':ch);
                        break;
                    }
                    case DUMP_8:
                    case DUMP_16:
                    case DUMP_32:
                        break;
                }
            }
        }
        ptr=(char *)ptr + (width*size);
    }
    printf("\n");
    return 0;
}
/*---------------------------------------------------------------------------------------------*/
void print_memory_region(void *stack_start)
{
#if 1 // Bitte auf 0 setzen, wenn in diesem Bereich ein Compilerfelher entstehen sollte
      // Sollte unter Linux lauffähig sein. Andere System unbekannt
    //Durch das LinkerScript-File definierte Variablen, welche
    //an den Start und das Ende von Speicherbereichen gesetzt wird
    extern char __data_start;
    extern char _edata;
    extern char __bss_start;
    extern char _end;
    printf(VT100_FETT "Vom Prozess u.A. genutzte Speicherbereiche\n" VT100_OFF
           "Global-Init Data:    %p..%p  (Page)%#zx..%#zx\n"
           "Global-NonInit Data: %p..%p  (Page)%#zx..%#zx\n"
           "Stack:               %p..??\n\n",
           (void *)&__data_start,(void *)&_edata,
           (uintptr_t)&__data_start&~4095,(uintptr_t)&_edata|4095,
           (void *)&__bss_start,(void *)&_end,
           (uintptr_t)&__bss_start&~4095,(uintptr_t)&_end|4095,
           (void *) ((uintptr_t)stack_start&~4095));
#endif           
}
