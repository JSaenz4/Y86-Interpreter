/* Created by Jesse Saenz in April 2013 for Dr. Peterson's Spring 2013 CS 429 class */

#include <stdio.h>
#include <stdlib.h>

//do your typedefs here

//here's nibbles
#define HI_NIBBLE(b) (((b)>>4)&0x0F)
#define LO_NIBBLE(b) ((b)&0x0F)

//here;s the getbytes function
int getbytes2(int a,int b,int c,int d);
void inittable(void);
void readob(char* f);
unsigned int gmem4(unsigned int myint);
int nex2(FILE *f);
unsigned char gmem(unsigned int myint);
void smem(unsigned int myint,unsigned char val);
void screwed_up(const char*message);
//ADDRESSES
unsigned int liladd=0xFFFFFFFF;
unsigned int laradd=0x0;
//ADDRESSES

//FIRST MEM
unsigned char **mem1[1024]={NULL};




    

//initialize
char* otablename[256];
//it


int main (int argc, char** argv) 
{
    argc--, argv++;
//check the args
    int i=0;

    while((argc>0)&&(**argv=='-'))
        {
            argc--, argv++;
        }

    readob(argv[0]);
    //read these in
    unsigned char* buffer=malloc(laradd+1);
    unsigned char* memory=malloc(laradd+1);
    //init my buffers
    inittable();
    {
        
        for(i=liladd;i<=laradd;i++)
            {
                unsigned char f=gmem(i);
                unsigned int s=gmem4(i);
                buffer[i]=f;
            }
    }

    //printf("\n\n\n");

    /*for(i=0;i<100;i++)
    {
        printf("%02X %X %X\n", buffer[i], HI_NIBBLE(buffer[i]), LO_NIBBLE(buffer[i]));
    }*/



    
    int eax=0; //0
    int ecx=0; //1
    int edx=0; //2
    int ebx=0; //3
    int esp=0; //4
    int ebp=0; //5
    int esi=0; //6
    int edi=0; //7
    //nothing            //8

    int cf=0;
    int zf=0;
    int sf=0;
    int of=0;
    
    int memindex;
    i=0;
    //i=0x46;
    //while((otablename[buffer[i]]!="invalid")&&(otablename[buffer[i]]!="halt"))
    while(1)
    {
        if(otablename[buffer[i]]=="halt")
        {
            printf("0x%08X: halt\n\n", i);
            exit(0);
        }
        else if(otablename[buffer[i]]=="invalid")
        {
            printf("0x%08X: 0x%02X -- invalid opcode\n\n", i, buffer[i]);
            exit(1);
        }
        else if(otablename[buffer[i]]=="nop")
        {
            printf("0x%08X: nop\n", i);
            i++;
        }
        else if(otablename[buffer[i]]=="rrmovl")
        {
            printf("0x%08X: rrmovl ", i);
            if(HI_NIBBLE(buffer[i+1])==0x0)
                printf("%%EAX, ");
            else if(HI_NIBBLE(buffer[i+1])==0x1)
                printf("%%ECX, ");
            else if(HI_NIBBLE(buffer[i+1])==0x2)
                printf("%%EDX, ");
            else if(HI_NIBBLE(buffer[i+1])==0x3)
                printf("%%EBX, ");
            else if(HI_NIBBLE(buffer[i+1])==0x4)
                printf("%%ESP, ");
            else if(HI_NIBBLE(buffer[i+1])==0x5)
                printf("%%EBP, ");
            else if(HI_NIBBLE(buffer[i+1])==0x6)
                printf("%%ESI, ");
            else if(HI_NIBBLE(buffer[i+1])==0x7)
                printf("%%EDI, ");
            if(LO_NIBBLE(buffer[i+1])==0x0)
                printf("%%EAX       ");
            else if(LO_NIBBLE(buffer[i+1])==0x1)
                printf("%%ECX       ");
            else if(LO_NIBBLE(buffer[i+1])==0x2)
                printf("%%EDX       ");
            else if(LO_NIBBLE(buffer[i+1])==0x3)
                printf("%%EBX       ");
            else if(LO_NIBBLE(buffer[i+1])==0x4)
                printf("%%ESP       ");
            else if(LO_NIBBLE(buffer[i+1])==0x5)
                printf("%%EBP       ");
            else if(LO_NIBBLE(buffer[i+1])==0x6)
                printf("%%ESI       ");
            else if(LO_NIBBLE(buffer[i+1])==0x7)
                printf("%%EDI       ");

            int newval;

            if(HI_NIBBLE(buffer[i+1])==0x0)
                {printf("(%%EAX -> 0x%08X, ", eax); newval=eax;}
            else if(HI_NIBBLE(buffer[i+1])==0x1)
                {printf("(%%ECX -> 0x%08X, ", ecx); newval=ecx;}
            else if(HI_NIBBLE(buffer[i+1])==0x2)
                {printf("(%%EDX -> 0x%08X, ", edx); newval=edx;}
            else if(HI_NIBBLE(buffer[i+1])==0x3)
                {printf("(%%EBX -> 0x%08X, ", ebx); newval=ebx;}
            else if(HI_NIBBLE(buffer[i+1])==0x4)
                {printf("(%%ESP -> 0x%08X, ", esp); newval=esp;}
            else if(HI_NIBBLE(buffer[i+1])==0x5)
                {printf("(%%EBP -> 0x%08X, ", ebp); newval=ebp;}
            else if(HI_NIBBLE(buffer[i+1])==0x6)
                {printf("(%%ESI -> 0x%08X, ", esi); newval=esi;}
            else if(HI_NIBBLE(buffer[i+1])==0x7)
                {printf("(%%EDI -> 0x%08X, ", edi); newval=edi;}
            if(LO_NIBBLE(buffer[i+1])==0x0)
                {printf("0x%08X -> %%EAX)\n", newval); eax=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x1)
                {printf("0x%08X -> %%ECX)\n", newval); ecx=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x2)
                {printf("0x%08X -> %%EDX)\n", newval); edx=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x3)
                {printf("0x%08X -> %%EBX)\n", newval); ebx=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x4)
                {printf("0x%08X -> %%ESP)\n", newval); esp=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x5)
                {printf("0x%08X -> %%EBP)\n", newval); ebp=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x6)
                {printf("0x%08X -> %%ESI)\n", newval); esi=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x7)
                {printf("0x%08X -> %%EDI)\n", newval); edi=newval;}

            i+=2;
        }
        else if(otablename[buffer[i]]=="irmovl")
        {
            unsigned int addr = gmem4(i+2);
            printf("0x%08X: irmovl 0x%08X, ", i, addr);
            if(LO_NIBBLE(buffer[i+1])==0x0)
                {printf("%%EAX       (0x%08X -> %%EAX)\n", addr); eax=addr;}
            else if(LO_NIBBLE(buffer[i+1])==0x1)
                {printf("%%ECX       (0x%08X -> %%ECX)\n", addr); ecx=addr;}
            else if(LO_NIBBLE(buffer[i+1])==0x2)
                {printf("%%EDX       (0x%08X -> %%EDX)\n", addr); edx=addr;}
            else if(LO_NIBBLE(buffer[i+1])==0x3)
                {printf("%%EBX       (0x%08X -> %%EBX)\n", addr); ebx=addr;}
            else if(LO_NIBBLE(buffer[i+1])==0x4)
                {printf("%%ESP       (0x%08X -> %%ESP)\n", addr); esp=addr;}
            else if(LO_NIBBLE(buffer[i+1])==0x5)
                {printf("%%EBP       (0x%08X -> %%EBP)\n", addr); ebp=addr;}
            else if(LO_NIBBLE(buffer[i+1])==0x6)
                {printf("%%ESI       (0x%08X -> %%ESI)\n", addr); esi=addr;}
            else if(LO_NIBBLE(buffer[i+1])==0x7)
                {printf("%%EDI       (0x%08X -> %%EDI)\n", addr); edi=addr;}
            i+=6;
        }
        else if(otablename[buffer[i]]=="rmmovl")
        {
            int firstval;
            unsigned int disp = gmem4(i+2);
            printf("0x%08X: rmmovl ", i);
            if(HI_NIBBLE(buffer[i+1])==0x0)
                {printf("%%EAX, ");}
            else if(HI_NIBBLE(buffer[i+1])==0x1)
                {printf("%%ECX, ");}
            else if(HI_NIBBLE(buffer[i+1])==0x2)
                {printf("%%EDX, ");}
            else if(HI_NIBBLE(buffer[i+1])==0x3)
                {printf("%%EBX, ");}
            else if(HI_NIBBLE(buffer[i+1])==0x4)
                {printf("%%ESP, ");}
            else if(HI_NIBBLE(buffer[i+1])==0x5)
                {printf("%%EBP, ");}
            else if(HI_NIBBLE(buffer[i+1])==0x6)
                {printf("%%ESI, ");}
            else if(HI_NIBBLE(buffer[i+1])==0x7)
                {printf("%%EDI, ");}
            if(LO_NIBBLE(buffer[i+1])==0x0)
                {printf("0x%08X(%%EAX)       (%%EAX -> 0x%08X, ", disp, eax); firstval=eax;}
            else if(LO_NIBBLE(buffer[i+1])==0x1)
                {printf("0x%08X(%%ECX)       (%%ECX -> 0x%08X, ", disp, ecx); firstval=ecx;}
            else if(LO_NIBBLE(buffer[i+1])==0x2)
                {printf("0x%08X(%%EDX)       (%%EDX -> 0x%08X, ", disp, edx); firstval=edx;}
            else if(LO_NIBBLE(buffer[i+1])==0x3)
                {printf("0x%08X(%%EBX)       (%%EBX -> 0x%08X, ", disp, ebx); firstval=ebx;}
            else if(LO_NIBBLE(buffer[i+1])==0x4)
                {printf("0x%08X(%%ESP)       (%%ESP -> 0x%08X, ", disp, esp); firstval=esp;}
            else if(LO_NIBBLE(buffer[i+1])==0x5)
                {printf("0x%08X(%%EBP)       (%%EBP -> 0x%08X, ", disp, ebp); firstval=ebp;}
            else if(LO_NIBBLE(buffer[i+1])==0x6)
                {printf("0x%08X(%%ESI)       (%%ESI -> 0x%08X, ", disp, esi); firstval=esi;}
            else if(LO_NIBBLE(buffer[i+1])==0x7)
                {printf("0x%08X(%%EDI)       (%%EDI -> 0x%08X, ", disp, edi); firstval=edi;}

            if(HI_NIBBLE(buffer[i+1])==0x0)
                {printf("%%EAX -> 0x%08X, 0x%08X -> [0x%08X]\n", eax, eax, firstval+disp); 
                buffer[firstval+disp]=eax & 0xff;
            buffer[firstval+disp+1]=eax >> 8 & 0xff;
            buffer[firstval+disp+2]=eax >> 16 & 0xff;
            buffer[firstval+disp+3]=eax >> 24 & 0xff;} //buffer[firstval+disp]=eax;}
            else if(HI_NIBBLE(buffer[i+1])==0x1)
                {printf("%%ECX -> 0x%08X, 0x%08X -> [0x%08X]\n", ecx, ecx, firstval+disp); buffer[firstval+disp]=ecx & 0xff;
            buffer[firstval+disp+1]=ecx >> 8 & 0xff;
            buffer[firstval+disp+2]=ecx >> 16 & 0xff;
            buffer[firstval+disp+3]=ecx >> 24 & 0xff;} //buffer[firstval+disp]=ecx;}
            else if(HI_NIBBLE(buffer[i+1])==0x2)
                {printf("%%EDX -> 0x%08X, 0x%08X -> [0x%08X]\n", edx, edx, firstval+disp); buffer[firstval+disp]=edx & 0xff;
            buffer[firstval+disp+1]=edx >> 8 & 0xff;
            buffer[firstval+disp+2]=edx >> 16 & 0xff;
            buffer[firstval+disp+3]=edx >> 24 & 0xff;} //buffer[firstval+disp]=edx;}
            else if(HI_NIBBLE(buffer[i+1])==0x3)
                {printf("%%EBX -> 0x%08X, 0x%08X -> [0x%08X]\n", ebx, ebx, firstval+disp); buffer[firstval+disp]=ebx & 0xff;
            buffer[firstval+disp+1]=ebx >> 8 & 0xff;
            buffer[firstval+disp+2]=ebx >> 16 & 0xff;
            buffer[firstval+disp+3]=ebx >> 24 & 0xff;} //buffer[firstval+disp]=ebx;}
            else if(HI_NIBBLE(buffer[i+1])==0x4)
                {printf("%%ESP -> 0x%08X, 0x%08X -> [0x%08X]\n", esp, esp, firstval+disp); buffer[firstval+disp]=esp & 0xff;
            buffer[firstval+disp+1]=esp >> 8 & 0xff;
            buffer[firstval+disp+2]=esp >> 16 & 0xff;
            buffer[firstval+disp+3]=esp >> 24 & 0xff;} //buffer[firstval+disp]=esp;}
            else if(HI_NIBBLE(buffer[i+1])==0x5)
                {printf("%%EBP -> 0x%08X, 0x%08X -> [0x%08X]\n", ebp, ebp, firstval+disp); buffer[firstval+disp]=ebp & 0xff;
            buffer[firstval+disp+1]=ebp >> 8 & 0xff;
            buffer[firstval+disp+2]=ebp >> 16 & 0xff;
            buffer[firstval+disp+3]=ebp >> 24 & 0xff;} //buffer[firstval+disp]=ebp;}
            else if(HI_NIBBLE(buffer[i+1])==0x6)
                {printf("%%ESI -> 0x%08X, 0x%08X -> [0x%08X]\n", esi, esi, firstval+disp); buffer[firstval+disp]=esi & 0xff;
            buffer[firstval+disp+1]=esi >> 8 & 0xff;
            buffer[firstval+disp+2]=esi >> 16 & 0xff;
            buffer[firstval+disp+3]=esi >> 24 & 0xff;} //buffer[firstval+disp]=esi;}
            else if(HI_NIBBLE(buffer[i+1])==0x7)
                {printf("%%EDI -> 0x%08X, 0x%08X -> [0x%08X]\n", edi, edi, firstval+disp); buffer[firstval+disp]=edi & 0xff;
            buffer[firstval+disp+1]=edi >> 8 & 0xff;
            buffer[firstval+disp+2]=edi >> 16 & 0xff;
            buffer[firstval+disp+3]=edi >> 24 & 0xff;} //buffer[firstval+disp]=edi;}

            i+=6;
        }

        else if(otablename[buffer[i]]=="mrmovl")
        {
            int myregister;
            int firstval;
            unsigned int disp = gmem4(i+2);
            printf("0x%08X: mrmovl ", i);

            if(LO_NIBBLE(buffer[i+1])==0x0)
                {printf("0x%08X(%%EAX), ", disp); firstval=eax;}
            else if(LO_NIBBLE(buffer[i+1])==0x1)
                {printf("0x%08X(%%ECX), ", disp); firstval=ecx;}
            else if(LO_NIBBLE(buffer[i+1])==0x2)
                {printf("0x%08X(%%EDX), ", disp); firstval=edx;}
            else if(LO_NIBBLE(buffer[i+1])==0x3)
                {printf("0x%08X(%%EBX), ", disp); firstval=ebx;}
            else if(LO_NIBBLE(buffer[i+1])==0x4)
                {printf("0x%08X(%%ESP), ", disp); firstval=esp;}
            else if(LO_NIBBLE(buffer[i+1])==0x5)
                {printf("0x%08X(%%EBP), ", disp); firstval=ebp;}
            else if(LO_NIBBLE(buffer[i+1])==0x6)
                {printf("0x%08X(%%ESI), ", disp); firstval=esi;}
            else if(LO_NIBBLE(buffer[i+1])==0x7)
                {printf("0x%08X(%%EDI), ", disp); firstval=edi;}
            if(HI_NIBBLE(buffer[i+1])==0x0)
                {printf("%%EAX       ");}
            else if(HI_NIBBLE(buffer[i+1])==0x1)
                {printf("%%ECX       ");}
            else if(HI_NIBBLE(buffer[i+1])==0x2)
                {printf("%%EDX       ");}
            else if(HI_NIBBLE(buffer[i+1])==0x3)
                {printf("%%EBX       ");}
            else if(HI_NIBBLE(buffer[i+1])==0x4)
                {printf("%%ESP       ");}
            else if(HI_NIBBLE(buffer[i+1])==0x5)
                {printf("%%EBP       ");}
            else if(HI_NIBBLE(buffer[i+1])==0x6)
                {printf("%%ESI       ");}
            else if(HI_NIBBLE(buffer[i+1])==0x7)
                {printf("%%EDI       ");}
            

            if(LO_NIBBLE(buffer[i+1])==0x0)
                printf("(%%EAX -> 0x%08X, [0x%08X] -> ", eax, myregister=eax+disp);
            else if(LO_NIBBLE(buffer[i+1])==0x1)
                printf("(%%ECX -> 0x%08X, [0x%08X] -> ", ecx, myregister=ecx+disp);
            else if(LO_NIBBLE(buffer[i+1])==0x2)
                printf("(%%EDX -> 0x%08X, [0x%08X] -> ", edx, myregister=edx+disp);
            else if(LO_NIBBLE(buffer[i+1])==0x3)
                printf("(%%EBX -> 0x%08X, [0x%08X] -> ", ebx, myregister=ebx+disp);
            else if(LO_NIBBLE(buffer[i+1])==0x4)
                printf("(%%ESP -> 0x%08X, [0x%08X] -> ", esp, myregister=esp+disp);
            else if(LO_NIBBLE(buffer[i+1])==0x5)
                printf("(%%EBP -> 0x%08X, [0x%08X] -> ", ebp, myregister=ebp+disp);
            else if(LO_NIBBLE(buffer[i+1])==0x6)
                printf("(%%ESI -> 0x%08X, [0x%08X] -> ", esi, myregister=esi+disp);
            else if(LO_NIBBLE(buffer[i+1])==0x7)
                printf("(%%EDI -> 0x%08X, [0x%08X] -> ", edi, myregister=edi+disp);
            if(HI_NIBBLE(buffer[i+1])==0x0)
                {eax=getbytes2(buffer[myregister+3], buffer[myregister+2], buffer[myregister+1], buffer[myregister]); printf("0x%08X, 0x%08X -> %%EAX)\n", eax, eax);}
            else if(HI_NIBBLE(buffer[i+1])==0x1)
                {ecx=getbytes2(buffer[myregister+3], buffer[myregister+2], buffer[myregister+1], buffer[myregister]); printf("0x%08X, 0x%08X -> %%ECX)\n", ecx, ecx);}
            else if(HI_NIBBLE(buffer[i+1])==0x2)
                {edx=getbytes2(buffer[myregister+3], buffer[myregister+2], buffer[myregister+1], buffer[myregister]); printf("0x%08X, 0x%08X -> %%EDX)\n", edx, edx);}
            else if(HI_NIBBLE(buffer[i+1])==0x3)
                {ebx=getbytes2(buffer[myregister+3], buffer[myregister+2], buffer[myregister+1], buffer[myregister]); printf("0x%08X, 0x%08X -> %%EBX)\n", ebx, ebx);}
            else if(HI_NIBBLE(buffer[i+1])==0x4)
                {esp=getbytes2(buffer[myregister+3], buffer[myregister+2], buffer[myregister+1], buffer[myregister]); printf("0x%08X, 0x%08X -> %%ESP)\n", esp, esp);}
            else if(HI_NIBBLE(buffer[i+1])==0x5)
                {ebp=getbytes2(buffer[myregister+3], buffer[myregister+2], buffer[myregister+1], buffer[myregister]); printf("0x%08X, 0x%08X -> %%EBP)\n", ebp, ebp);}
            else if(HI_NIBBLE(buffer[i+1])==0x6)
                {esi=getbytes2(buffer[myregister+3], buffer[myregister+2], buffer[myregister+1], buffer[myregister]); printf("0x%08X, 0x%08X -> %%ESI)\n", esi, esi);}
            else if(HI_NIBBLE(buffer[i+1])==0x7)
                {edi=getbytes2(buffer[myregister+3], buffer[myregister+2], buffer[myregister+1], buffer[myregister]); printf("0x%08X, 0x%08X -> %%EDI)\n", edi, edi);}

            i+=6;
        }

        else if(otablename[buffer[i]]=="addl")
        {   
            int firstval;
            int result;
            printf("0x%08X: addl ", i);
            if(HI_NIBBLE(buffer[i+1])==0x0)
                {printf("%%EAX, ");}
            else if(HI_NIBBLE(buffer[i+1])==0x1)
                {printf("%%ECX, ");}
            else if(HI_NIBBLE(buffer[i+1])==0x2)
                {printf("%%EDX, ");}
            else if(HI_NIBBLE(buffer[i+1])==0x3)
                {printf("%%EBX, ");}
            else if(HI_NIBBLE(buffer[i+1])==0x4)
                {printf("%%ESP, ");}
            else if(HI_NIBBLE(buffer[i+1])==0x5)
                {printf("%%EBP, ");}
            else if(HI_NIBBLE(buffer[i+1])==0x6)
                {printf("%%ESI, ");}
            else if(HI_NIBBLE(buffer[i+1])==0x7)
                {printf("%%EDI, ");}
            if(LO_NIBBLE(buffer[i+1])==0x0)
                {printf("%%EAX       ");}
            else if(LO_NIBBLE(buffer[i+1])==0x1)
                {printf("%%ECX       ");}
            else if(LO_NIBBLE(buffer[i+1])==0x2)
                {printf("%%EDX       ");}
            else if(LO_NIBBLE(buffer[i+1])==0x3)
                {printf("%%EBX       ");}
            else if(LO_NIBBLE(buffer[i+1])==0x4)
                {printf("%%ESP       ");}
            else if(LO_NIBBLE(buffer[i+1])==0x5)
                {printf("%%EBP       ");}
            else if(LO_NIBBLE(buffer[i+1])==0x6)
                {printf("%%ESI       ");}
            else if(LO_NIBBLE(buffer[i+1])==0x7)
                {printf("%%EDI       ");}
            if(HI_NIBBLE(buffer[i+1])==0x0)
                {printf("(%%EAX -> 0x%08X, ", eax); firstval=eax;} //buffer[firstval+disp]=eax;}
            else if(HI_NIBBLE(buffer[i+1])==0x1)
                {printf("(%%ECX -> 0x%08X, ", ecx); firstval=ecx;} //buffer[firstval+disp]=ecx;}
            else if(HI_NIBBLE(buffer[i+1])==0x2)
                {printf("(%%EDX -> 0x%08X, ", edx); firstval=edx;} //buffer[firstval+disp]=edx;}
            else if(HI_NIBBLE(buffer[i+1])==0x3)
                {printf("(%%EBX -> 0x%08X, ", ebx); firstval=ebx;} //buffer[firstval+disp]=ebx;}
            else if(HI_NIBBLE(buffer[i+1])==0x4)
                {printf("(%%ESP -> 0x%08X, ", esp); firstval=esp;} //buffer[firstval+disp]=esp;}
            else if(HI_NIBBLE(buffer[i+1])==0x5)
                {printf("(%%EBP -> 0x%08X, ", ebp); firstval=ebp;} //buffer[firstval+disp]=ebp;}
            else if(HI_NIBBLE(buffer[i+1])==0x6)
                {printf("(%%ESI -> 0x%08X, ", esi); firstval=esi;} //buffer[firstval+disp]=esi;}
            else if(HI_NIBBLE(buffer[i+1])==0x7)
                {printf("(%%EDI -> 0x%08X, ", edi); firstval=edi;} //buffer[firstval+disp]=edi;}
            if(LO_NIBBLE(buffer[i+1])==0x0)
                {printf("%%EAX -> 0x%08X, 0x%08X -> %%EAX, ", eax, result=eax+firstval); eax=result;
                if((unsigned)result<(unsigned)firstval) cf=1; else cf=0;
                if(result==0) {zf=1; printf("Z");} else {printf("."); zf=0;}
                if(result<0) {sf=1; printf("S");} else {printf("."); sf=0;}
                if((firstval<0==eax<0)&&(result<0!=firstval<0)) {of=1; printf("O");} else {printf("."); of=0;}}
            else if(LO_NIBBLE(buffer[i+1])==0x1)
                {printf("%%ECX -> 0x%08X, 0x%08X -> %%ECX, ", ecx, result=ecx+firstval); ecx=result;
                if((unsigned)result<(unsigned)firstval) cf=1; else cf=0;
                if(result==0) {zf=1; printf("Z");} else {printf("."); zf=0;}
                if(result<0) {sf=1; printf("S");} else {printf("."); sf=0;}
                if((firstval<0==ecx<0)&&(result<0!=firstval<0)) {of=1; printf("O");} else {printf("."); of=0;}}
            else if(LO_NIBBLE(buffer[i+1])==0x2)
                {printf("%%EDX -> 0x%08X, 0x%08X -> %%EDX, ", edx, result=edx+firstval); edx=result;
                if((unsigned)result<(unsigned)firstval) cf=1; else cf=0;
                if(result==0) {zf=1; printf("Z");} else {printf("."); zf=0;}
                if(result<0) {sf=1; printf("S");} else {printf("."); sf=0;}
                if((firstval<0==edx<0)&&(result<0!=firstval<0)) {of=1; printf("O");} else {printf("."); of=0;}}
            else if(LO_NIBBLE(buffer[i+1])==0x3)
                {printf("%%EBX -> 0x%08X, 0x%08X -> %%EBX, ", ebx, result=ebx+firstval); ebx=result;
                if((unsigned)result<(unsigned)firstval) cf=1; else cf=0;
                if(result==0) {zf=1; printf("Z");} else {printf("."); zf=0;}
                if(result<0) {sf=1; printf("S");} else {printf("."); sf=0;}
                if((firstval<0==ebx<0)&&(result<0!=firstval<0)) {of=1; printf("O");} else {printf("."); of=0;}}
            else if(LO_NIBBLE(buffer[i+1])==0x4)
                {printf("%%ESP -> 0x%08X, 0x%08X -> %%ESP, ", esp, result=esp+firstval); esp=result;
                if((unsigned)result<(unsigned)firstval) cf=1; else cf=0;
                if(result==0) {zf=1; printf("Z");} else {printf("."); zf=0;}
                if(result<0) {sf=1; printf("S");} else {printf("."); sf=0;}
                if((firstval<0==esp<0)&&(result<0!=firstval<0)) {of=1; printf("O");} else {printf("."); of=0;}}
            else if(LO_NIBBLE(buffer[i+1])==0x5)
                {printf("%%EBP -> 0x%08X, 0x%08X -> %%EBP, ", ebp, result=ebp+firstval); ebp=result;
                if((unsigned)result<(unsigned)firstval) cf=1; else cf=0;
                if(result==0) {zf=1; printf("Z");} else {printf("."); zf=0;}
                if(result<0) {sf=1; printf("S");} else {printf("."); sf=0;}
                if((firstval<0==ebp<0)&&(result<0!=firstval<0)) {of=1; printf("O");} else {printf("."); of=0;}}
            else if(LO_NIBBLE(buffer[i+1])==0x6)
                {printf("%%ESI -> 0x%08X, 0x%08X -> %%ESI, ", esi, result=esi+firstval); esi=result;
                if((unsigned)result<(unsigned)firstval) cf=1; else cf=0;
                if(result==0) {zf=1; printf("Z");} else {printf("."); zf=0;}
                if(result<0) {sf=1; printf("S");} else {printf("."); sf=0;}
                if((firstval<0==esi<0)&&(result<0!=firstval<0)) {of=1; printf("O");} else {printf("."); of=0;}}
            else if(LO_NIBBLE(buffer[i+1])==0x7)
                {printf("%%EDI -> 0x%08X, 0x%08X -> %%EDI, ", edi, result=edi+firstval); edi=result;
                if((unsigned)result<(unsigned)firstval) cf=1; else cf=0;
                if(result==0) {zf=1; printf("Z");} else {printf("."); zf=0;}
                if(result<0) {sf=1; printf("S");} else {printf("."); sf=0;}
                if((firstval<0==edi<0)&&(result<0!=firstval<0)) {of=1; printf("O");} else {printf("."); of=0;}}

            printf(" -> CC)\n");

            i+=2;

        }

        else if(otablename[buffer[i]]=="subl")
        {   
            int firstval;
            int result;
            printf("0x%08X: subl ", i);
            if(HI_NIBBLE(buffer[i+1])==0x0)
                {printf("%%EAX, ");}
            else if(HI_NIBBLE(buffer[i+1])==0x1)
                {printf("%%ECX, ");}
            else if(HI_NIBBLE(buffer[i+1])==0x2)
                {printf("%%EDX, ");}
            else if(HI_NIBBLE(buffer[i+1])==0x3)
                {printf("%%EBX, ");}
            else if(HI_NIBBLE(buffer[i+1])==0x4)
                {printf("%%ESP, ");}
            else if(HI_NIBBLE(buffer[i+1])==0x5)
                {printf("%%EBP, ");}
            else if(HI_NIBBLE(buffer[i+1])==0x6)
                {printf("%%ESI, ");}
            else if(HI_NIBBLE(buffer[i+1])==0x7)
                {printf("%%EDI, ");}
            if(LO_NIBBLE(buffer[i+1])==0x0)
                {printf("%%EAX       ");}
            else if(LO_NIBBLE(buffer[i+1])==0x1)
                {printf("%%ECX       ");}
            else if(LO_NIBBLE(buffer[i+1])==0x2)
                {printf("%%EDX       ");}
            else if(LO_NIBBLE(buffer[i+1])==0x3)
                {printf("%%EBX       ");}
            else if(LO_NIBBLE(buffer[i+1])==0x4)
                {printf("%%ESP       ");}
            else if(LO_NIBBLE(buffer[i+1])==0x5)
                {printf("%%EBP       ");}
            else if(LO_NIBBLE(buffer[i+1])==0x6)
                {printf("%%ESI       ");}
            else if(LO_NIBBLE(buffer[i+1])==0x7)
                {printf("%%EDI       ");}
            if(HI_NIBBLE(buffer[i+1])==0x0)
                {printf("(%%EAX -> 0x%08X, ", eax); firstval=eax;} //buffer[firstval+disp]=eax;}
            else if(HI_NIBBLE(buffer[i+1])==0x1)
                {printf("(%%ECX -> 0x%08X, ", ecx); firstval=ecx;} //buffer[firstval+disp]=ecx;}
            else if(HI_NIBBLE(buffer[i+1])==0x2)
                {printf("(%%EDX -> 0x%08X, ", edx); firstval=edx;} //buffer[firstval+disp]=edx;}
            else if(HI_NIBBLE(buffer[i+1])==0x3)
                {printf("(%%EBX -> 0x%08X, ", ebx); firstval=ebx;} //buffer[firstval+disp]=ebx;}
            else if(HI_NIBBLE(buffer[i+1])==0x4)
                {printf("(%%ESP -> 0x%08X, ", esp); firstval=esp;} //buffer[firstval+disp]=esp;}
            else if(HI_NIBBLE(buffer[i+1])==0x5)
                {printf("(%%EBP -> 0x%08X, ", ebp); firstval=ebp;} //buffer[firstval+disp]=ebp;}
            else if(HI_NIBBLE(buffer[i+1])==0x6)
                {printf("(%%ESI -> 0x%08X, ", esi); firstval=esi;} //buffer[firstval+disp]=esi;}
            else if(HI_NIBBLE(buffer[i+1])==0x7)
                {printf("(%%EDI -> 0x%08X, ", edi); firstval=edi;} //buffer[firstval+disp]=edi;}
            if(LO_NIBBLE(buffer[i+1])==0x0)
                {printf("%%EAX -> 0x%08X, 0x%08X -> %%EAX, ", eax, result=eax+(-1*firstval)); eax=result;
                if((unsigned)result<(unsigned)firstval) cf=1; else cf=0;
                if(result==0) {zf=1; printf("Z");} else {printf("."); zf=0;}
                if(result<0) {sf=1; printf("S");} else {printf("."); sf=0;}
                if((firstval<0==eax<0)&&(result<0!=firstval<0)) {of=1; printf("O");} else {printf("."); of=0;}}
            else if(LO_NIBBLE(buffer[i+1])==0x1)
                {printf("%%ECX -> 0x%08X, 0x%08X -> %%ECX, ", ecx, result=ecx+(-1*firstval)); ecx=result;
                if((unsigned)result<(unsigned)firstval) cf=1; else cf=0;
                if(result==0) {zf=1; printf("Z");} else {printf("."); zf=0;}
                if(result<0) {sf=1; printf("S");} else {printf("."); sf=0;}
                if((firstval<0==ecx<0)&&(result<0!=firstval<0)) {of=1; printf("O");} else {printf("."); of=0;}}
            else if(LO_NIBBLE(buffer[i+1])==0x2)
                {printf("%%EDX -> 0x%08X, 0x%08X -> %%EDX, ", edx, result=edx+(-1*firstval)); edx=result;
                if((unsigned)result<(unsigned)firstval) cf=1; else cf=0;
                if(result==0) {zf=1; printf("Z");} else {printf("."); zf=0;}
                if(result<0) {sf=1; printf("S");} else {printf("."); sf=0;}
                if((firstval<0==edx<0)&&(result<0!=firstval<0)) {of=1; printf("O");} else {printf("."); of=0;}}
            else if(LO_NIBBLE(buffer[i+1])==0x3)
                {printf("%%EBX -> 0x%08X, 0x%08X -> %%EBX, ", ebx, result=ebx+(-1*firstval)); ebx=result;
                if((unsigned)result<(unsigned)firstval) cf=1; else cf=0;
                if(result==0) {zf=1; printf("Z");} else {printf("."); zf=0;}
                if(result<0) {sf=1; printf("S");} else {printf("."); sf=0;}
                if((firstval<0==ebx<0)&&(result<0!=firstval<0)) {of=1; printf("O");} else {printf("."); of=0;}}
            else if(LO_NIBBLE(buffer[i+1])==0x4)
                {printf("%%ESP -> 0x%08X, 0x%08X -> %%ESP, ", esp, result=esp+(-1*firstval)); esp=result;
                if((unsigned)result<(unsigned)firstval) cf=1; else cf=0;
                if(result==0) {zf=1; printf("Z");} else {printf("."); zf=0;}
                if(result<0) {sf=1; printf("S");} else {printf("."); sf=0;}
                if((firstval<0==esp<0)&&(result<0!=firstval<0)) {of=1; printf("O");} else {printf("."); of=0;}}
            else if(LO_NIBBLE(buffer[i+1])==0x5)
                {printf("%%EBP -> 0x%08X, 0x%08X -> %%EBP, ", ebp, result=ebp+(-1*firstval)); ebp=result;
                if((unsigned)result<(unsigned)firstval) cf=1; else cf=0;
                if(result==0) {zf=1; printf("Z");} else {printf("."); zf=0;}
                if(result<0) {sf=1; printf("S");} else {printf("."); sf=0;}
                if((firstval<0==ebp<0)&&(result<0!=firstval<0)) {of=1; printf("O");} else {printf("."); of=0;}}
            else if(LO_NIBBLE(buffer[i+1])==0x6)
                {printf("%%ESI -> 0x%08X, 0x%08X -> %%ESI, ", esi, result=esi+(-1*firstval)); esi=result;
                if((unsigned)result<(unsigned)firstval) cf=1; else cf=0;
                if(result==0) {zf=1; printf("Z");} else {printf("."); zf=0;}
                if(result<0) {sf=1; printf("S");} else {printf("."); sf=0;}
                if((firstval<0==esi<0)&&(result<0!=firstval<0)) {of=1; printf("O");} else {printf("."); of=0;}}
            else if(LO_NIBBLE(buffer[i+1])==0x7)
                {printf("%%EDI -> 0x%08X, 0x%08X -> %%EDI, ", edi, result=edi+(-1*firstval)); edi=result;
                if((unsigned)result<(unsigned)firstval) cf=1; else cf=0;
                if(result==0) {zf=1; printf("Z");} else {printf("."); zf=0;}
                if(result<0) {sf=1; printf("S");} else {printf("."); sf=0;}
                if((firstval<0==edi<0)&&(result<0!=firstval<0)) {of=1; printf("O");} else {printf("."); of=0;}}

            printf(" -> CC)\n");

            i+=2;

        }

        else if(otablename[buffer[i]]=="andl")
        {   
            int val;
            if(HI_NIBBLE(buffer[i+1])==0x0)
                {printf("0x%08X: andl %%EAX, %%EAX       (%%EAX -> 0x%08X, %%EAX -> 0x%08X, 0x%08X -> %%EAX, ", i, eax, eax, eax); val=eax;}
            else if(HI_NIBBLE(buffer[i+1])==0x1)
                {printf("0x%08X: andl %%ECX, %%ECX       (%%ECX -> 0x%08X, %%ECX -> 0x%08X, 0x%08X -> %%ECX, ", i, ecx, ecx, ecx); val=ecx;}
            else if(HI_NIBBLE(buffer[i+1])==0x2)
                {printf("0x%08X: andl %%EDX, %%EDX       (%%EDX -> 0x%08X, %%EDX -> 0x%08X, 0x%08X -> %%EDX, ", i, edx, edx, edx); val=edx;}
            else if(HI_NIBBLE(buffer[i+1])==0x3)
                {printf("0x%08X: andl %%EBX, %%EBX       (%%EBX -> 0x%08X, %%EBX -> 0x%08X, 0x%08X -> %%EBX, ", i, ebx, ebx, ebx); val=ebx;}
            else if(HI_NIBBLE(buffer[i+1])==0x4)
                {printf("0x%08X: andl %%ESP, %%ESP       (%%ESP -> 0x%08X, %%ESP -> 0x%08X, 0x%08X -> %%ESP, ", i, esp, esp, esp); val=esp;}
            else if(HI_NIBBLE(buffer[i+1])==0x5)
                {printf("0x%08X: andl %%EBP, %%EBP       (%%EBP -> 0x%08X, %%EBP -> 0x%08X, 0x%08X -> %%EBP, ", i, ebp, ebp, ebp); val=ebp;}
            else if(HI_NIBBLE(buffer[i+1])==0x6)
                {printf("0x%08X: andl %%ESI, %%ESI       (%%ESI -> 0x%08X, %%ESI -> 0x%08X, 0x%08X -> %%ESI, ", i, esi, esi, esi); val=esi;}
            else if(HI_NIBBLE(buffer[i+1])==0x7)
                {printf("0x%08X: andl %%EDI, %%EDI       (%%EDI -> 0x%08X, %%EDI -> 0x%08X, 0x%08X -> %%EDI, ", i, edi, edi, edi); val=edi;}

            if(val==0)
            {
                zf=1;
                printf("Z");
            }
            else
            {
                zf=0;
                printf(".");
            }
            if(val<0)
            {
                sf=1;
                printf("S");
            }
            else
            {
                sf=0;
                printf(".");
            }
            if((val<0==val<0)&&(val<0!=val<0))
            {
                of=1;
                printf("O");
            }
            else
            {
                of=0;
                printf(".");
            }

            printf(" -> CC)\n");
            i+=2;
            
        }

        else if(otablename[buffer[i]]=="xorl")
        {
            int val;
            if(HI_NIBBLE(buffer[i+1])==0x0)
                {printf("0x%08X: xorl %%EAX, %%EAX       (%%EAX -> 0x%08X, %%EAX -> 0x%08X, 0x00000000 -> %%EAX, ", i, eax, eax); eax=0;}
            else if(HI_NIBBLE(buffer[i+1])==0x1)
                {printf("0x%08X: xorl %%ECX, %%ECX       (%%ECX -> 0x%08X, %%ECX -> 0x%08X, 0x00000000 -> %%ECX, ", i, ecx, ecx); ecx=0;}
            else if(HI_NIBBLE(buffer[i+1])==0x2)
                {printf("0x%08X: xorl %%EDX, %%EDX       (%%EDX -> 0x%08X, %%EDX -> 0x%08X, 0x00000000 -> %%EDX, ", i, edx, edx); edx=0;}
            else if(HI_NIBBLE(buffer[i+1])==0x3)
                {printf("0x%08X: xorl %%EBX, %%EBX       (%%EBX -> 0x%08X, %%EBX -> 0x%08X, 0x00000000 -> %%EBX, ", i, ebx, ebx); ebx=0;}
            else if(HI_NIBBLE(buffer[i+1])==0x4)
                {printf("0x%08X: xorl %%ESP, %%ESP       (%%ESP -> 0x%08X, %%ESP -> 0x%08X, 0x00000000 -> %%ESP, ", i, esp, esp); esp=0;}
            else if(HI_NIBBLE(buffer[i+1])==0x5)
                {printf("0x%08X: xorl %%EBP, %%EBP       (%%EBP -> 0x%08X, %%EBP -> 0x%08X, 0x00000000 -> %%EBP, ", i, ebp, ebp); ebp=0;}
            else if(HI_NIBBLE(buffer[i+1])==0x6)
                {printf("0x%08X: xorl %%ESI, %%ESI       (%%ESI -> 0x%08X, %%ESI -> 0x%08X, 0x00000000 -> %%ESI, ", i, esi, esi); esi=0;}
            else if(HI_NIBBLE(buffer[i+1])==0x7)
                {printf("0x%08X: xorl %%EDI, %%EDI       (%%EDI -> 0x%08X, %%EDI -> 0x%08X, 0x00000000 -> %%EDI, ", i, edi, edi); edi=0;}

            printf("Z.. -> CC)\n");
            zf=1;
            sf=0;
            of=0;
            i+=2;
        }

        else if(otablename[buffer[i]]=="jmp")
        {
            unsigned int addr = gmem4(i+1);
            printf("0x%08X: jmp 0x%08X       (0x%08X -> PC)\n", i, addr, addr);
            i=addr;
        }

        else if(otablename[buffer[i]]=="jle")
        {
            unsigned int addr = gmem4(i+1);
            printf("0x%08X: jle 0x%08X       (ZF -> %d, SF -> %d, OF -> %d, ", i, addr, zf, sf, of);
            if((sf^of)|zf) //if(sf==1)
            {
                printf("0x%08X -> PC)\n", addr);
                i=addr;
            }
            else
            {
                printf("no jump)\n");
                i+=5;
            }
        }

        else if(otablename[buffer[i]]=="jl")
        {
            unsigned int addr = gmem4(i+1);
            printf("0x%08X: jl 0x%08X       (ZF -> %d, SF -> %d, OF -> %d, ", i, addr, zf, sf, of);
            if(sf^of) //if(sf!=of)
            {
                printf("0x%08X -> PC)\n", addr);
                i=addr;
            }
            else
            {
                printf("no jump)\n");
                i+=5;
            }
        }

        else if(otablename[buffer[i]]=="je")
        {
            unsigned int addr = gmem4(i+1);
            printf("0x%08X: je 0x%08X       (ZF -> %d, ", i, addr, zf);
            if(zf==1)
            {
                printf("0x%08X -> PC)\n", addr);
                i=addr;
            }
            else
            {
                printf("no jump)\n");
                i+=5;
            }
        }

        else if(otablename[buffer[i]]=="jne")
        {
            unsigned int addr = gmem4(i+1);
            printf("0x%08X: jne 0x%08X       (ZF -> %d, ", i, addr, zf);
            if(zf==0)
            {
                printf("0x%08X -> PC)\n", addr);
                i=addr;
            }
            else
            {
                printf("no jump)\n");
                i+=5;
            }
        }

        else if(otablename[buffer[i]]=="jge")
        {
            unsigned int addr = gmem4(i+1);
            printf("0x%08X: jge 0x%08X       (ZF -> %d, SF -> %d, OF -> %d, ", i, addr, zf, sf, of);
            if(!(sf^of)) //if(sf==0)
            {
                printf("0x%08X -> PC)\n", addr);
                i=addr;
            }
            else
            {
                printf("no jump)\n");
                i+=5;
            }
        }

        else if(otablename[buffer[i]]=="jg")
        {
            unsigned int addr = gmem4(i+1);
            printf("0x%08X: jg 0x%08X       (ZF -> %d, SF -> %d, OF -> %d, ", i, addr, zf, sf, of);
            if((!(sf^of))&(!(zf))) //if(zf!=of) //CHANGED FROM (zf==0) START TROUBLESHOOTING HERE
            {
                printf("0x%08X -> PC)\n", addr);
                i=addr;
            }
            else
            {
                printf("no jump)\n");
                i+=5;
            }
        }

        else if(otablename[buffer[i]]=="cmovle")
        {
            printf("0x%08X: cmovle ", i);
            if(HI_NIBBLE(buffer[i+1])==0x0)
                printf("%%EAX, ");
            else if(HI_NIBBLE(buffer[i+1])==0x1)
                printf("%%ECX, ");
            else if(HI_NIBBLE(buffer[i+1])==0x2)
                printf("%%EDX, ");
            else if(HI_NIBBLE(buffer[i+1])==0x3)
                printf("%%EBX, ");
            else if(HI_NIBBLE(buffer[i+1])==0x4)
                printf("%%ESP, ");
            else if(HI_NIBBLE(buffer[i+1])==0x5)
                printf("%%EBP, ");
            else if(HI_NIBBLE(buffer[i+1])==0x6)
                printf("%%ESI, ");
            else if(HI_NIBBLE(buffer[i+1])==0x7)
                printf("%%EDI, ");
            if(LO_NIBBLE(buffer[i+1])==0x0)
                printf("%%EAX       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);
            else if(LO_NIBBLE(buffer[i+1])==0x1)
                printf("%%ECX       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);
            else if(LO_NIBBLE(buffer[i+1])==0x2)
                printf("%%EDX       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);
            else if(LO_NIBBLE(buffer[i+1])==0x3)
                printf("%%EBX       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);
            else if(LO_NIBBLE(buffer[i+1])==0x4)
                printf("%%ESP       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);
            else if(LO_NIBBLE(buffer[i+1])==0x5)
                printf("%%EBP       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);
            else if(LO_NIBBLE(buffer[i+1])==0x6)
                printf("%%ESI       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);
            else if(LO_NIBBLE(buffer[i+1])==0x7)
                printf("%%EDI       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);

            int newval;

            if((sf^of)|zf)
            {
            if(HI_NIBBLE(buffer[i+1])==0x0)
                {printf("%%EAX -> 0x%08X, ", eax); newval=eax;}
            else if(HI_NIBBLE(buffer[i+1])==0x1)
                {printf("%%ECX -> 0x%08X, ", ecx); newval=ecx;}
            else if(HI_NIBBLE(buffer[i+1])==0x2)
                {printf("%%EDX -> 0x%08X, ", edx); newval=edx;}
            else if(HI_NIBBLE(buffer[i+1])==0x3)
                {printf("%%EBX -> 0x%08X, ", ebx); newval=ebx;}
            else if(HI_NIBBLE(buffer[i+1])==0x4)
                {printf("%%ESP -> 0x%08X, ", esp); newval=esp;}
            else if(HI_NIBBLE(buffer[i+1])==0x5)
                {printf("%%EBP -> 0x%08X, ", ebp); newval=ebp;}
            else if(HI_NIBBLE(buffer[i+1])==0x6)
                {printf("%%ESI -> 0x%08X, ", esi); newval=esi;}
            else if(HI_NIBBLE(buffer[i+1])==0x7)
                {printf("%%EDI -> 0x%08X, ", edi); newval=edi;}
            if(LO_NIBBLE(buffer[i+1])==0x0)
                {printf("0x%08X -> %%EAX)\n", newval); eax=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x1)
                {printf("0x%08X -> %%ECX)\n", newval); ecx=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x2)
                {printf("0x%08X -> %%EDX)\n", newval); edx=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x3)
                {printf("0x%08X -> %%EBX)\n", newval); ebx=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x4)
                {printf("0x%08X -> %%ESP)\n", newval); esp=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x5)
                {printf("0x%08X -> %%EBP)\n", newval); ebp=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x6)
                {printf("0x%08X -> %%ESI)\n", newval); esi=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x7)
                {printf("0x%08X -> %%EDI)\n", newval); edi=newval;}
            }
            else
            {
                printf("no jump)\n");
            }

            i+=2;
        }

        else if(otablename[buffer[i]]=="cmovl")
        {
            printf("0x%08X: cmovl ", i);
            if(HI_NIBBLE(buffer[i+1])==0x0)
                printf("%%EAX, ");
            else if(HI_NIBBLE(buffer[i+1])==0x1)
                printf("%%ECX, ");
            else if(HI_NIBBLE(buffer[i+1])==0x2)
                printf("%%EDX, ");
            else if(HI_NIBBLE(buffer[i+1])==0x3)
                printf("%%EBX, ");
            else if(HI_NIBBLE(buffer[i+1])==0x4)
                printf("%%ESP, ");
            else if(HI_NIBBLE(buffer[i+1])==0x5)
                printf("%%EBP, ");
            else if(HI_NIBBLE(buffer[i+1])==0x6)
                printf("%%ESI, ");
            else if(HI_NIBBLE(buffer[i+1])==0x7)
                printf("%%EDI, ");
            if(LO_NIBBLE(buffer[i+1])==0x0)
                printf("%%EAX       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);
            else if(LO_NIBBLE(buffer[i+1])==0x1)
                printf("%%ECX       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);
            else if(LO_NIBBLE(buffer[i+1])==0x2)
                printf("%%EDX       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);
            else if(LO_NIBBLE(buffer[i+1])==0x3)
                printf("%%EBX       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);
            else if(LO_NIBBLE(buffer[i+1])==0x4)
                printf("%%ESP       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);
            else if(LO_NIBBLE(buffer[i+1])==0x5)
                printf("%%EBP       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);
            else if(LO_NIBBLE(buffer[i+1])==0x6)
                printf("%%ESI       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);
            else if(LO_NIBBLE(buffer[i+1])==0x7)
                printf("%%EDI       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);

            int newval;

            if(sf^of)
            {
            if(HI_NIBBLE(buffer[i+1])==0x0)
                {printf("%%EAX -> 0x%08X, ", eax); newval=eax;}
            else if(HI_NIBBLE(buffer[i+1])==0x1)
                {printf("%%ECX -> 0x%08X, ", ecx); newval=ecx;}
            else if(HI_NIBBLE(buffer[i+1])==0x2)
                {printf("%%EDX -> 0x%08X, ", edx); newval=edx;}
            else if(HI_NIBBLE(buffer[i+1])==0x3)
                {printf("%%EBX -> 0x%08X, ", ebx); newval=ebx;}
            else if(HI_NIBBLE(buffer[i+1])==0x4)
                {printf("%%ESP -> 0x%08X, ", esp); newval=esp;}
            else if(HI_NIBBLE(buffer[i+1])==0x5)
                {printf("%%EBP -> 0x%08X, ", ebp); newval=ebp;}
            else if(HI_NIBBLE(buffer[i+1])==0x6)
                {printf("%%ESI -> 0x%08X, ", esi); newval=esi;}
            else if(HI_NIBBLE(buffer[i+1])==0x7)
                {printf("%%EDI -> 0x%08X, ", edi); newval=edi;}
            if(LO_NIBBLE(buffer[i+1])==0x0)
                {printf("0x%08X -> %%EAX)\n", newval); eax=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x1)
                {printf("0x%08X -> %%ECX)\n", newval); ecx=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x2)
                {printf("0x%08X -> %%EDX)\n", newval); edx=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x3)
                {printf("0x%08X -> %%EBX)\n", newval); ebx=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x4)
                {printf("0x%08X -> %%ESP)\n", newval); esp=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x5)
                {printf("0x%08X -> %%EBP)\n", newval); ebp=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x6)
                {printf("0x%08X -> %%ESI)\n", newval); esi=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x7)
                {printf("0x%08X -> %%EDI)\n", newval); edi=newval;}
            }
            else
            {
                printf("no jump)\n");
            }

            i+=2;
        }

        else if(otablename[buffer[i]]=="cmove")
        {
            printf("0x%08X: cmove ", i);
            if(HI_NIBBLE(buffer[i+1])==0x0)
                printf("%%EAX, ");
            else if(HI_NIBBLE(buffer[i+1])==0x1)
                printf("%%ECX, ");
            else if(HI_NIBBLE(buffer[i+1])==0x2)
                printf("%%EDX, ");
            else if(HI_NIBBLE(buffer[i+1])==0x3)
                printf("%%EBX, ");
            else if(HI_NIBBLE(buffer[i+1])==0x4)
                printf("%%ESP, ");
            else if(HI_NIBBLE(buffer[i+1])==0x5)
                printf("%%EBP, ");
            else if(HI_NIBBLE(buffer[i+1])==0x6)
                printf("%%ESI, ");
            else if(HI_NIBBLE(buffer[i+1])==0x7)
                printf("%%EDI, ");
            if(LO_NIBBLE(buffer[i+1])==0x0)
                printf("%%EAX       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);
            else if(LO_NIBBLE(buffer[i+1])==0x1)
                printf("%%ECX       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);
            else if(LO_NIBBLE(buffer[i+1])==0x2)
                printf("%%EDX       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);
            else if(LO_NIBBLE(buffer[i+1])==0x3)
                printf("%%EBX       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);
            else if(LO_NIBBLE(buffer[i+1])==0x4)
                printf("%%ESP       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);
            else if(LO_NIBBLE(buffer[i+1])==0x5)
                printf("%%EBP       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);
            else if(LO_NIBBLE(buffer[i+1])==0x6)
                printf("%%ESI       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);
            else if(LO_NIBBLE(buffer[i+1])==0x7)
                printf("%%EDI       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);

            int newval;

            if(zf==1)
            {
            if(HI_NIBBLE(buffer[i+1])==0x0)
                {printf("%%EAX -> 0x%08X, ", eax); newval=eax;}
            else if(HI_NIBBLE(buffer[i+1])==0x1)
                {printf("%%ECX -> 0x%08X, ", ecx); newval=ecx;}
            else if(HI_NIBBLE(buffer[i+1])==0x2)
                {printf("%%EDX -> 0x%08X, ", edx); newval=edx;}
            else if(HI_NIBBLE(buffer[i+1])==0x3)
                {printf("%%EBX -> 0x%08X, ", ebx); newval=ebx;}
            else if(HI_NIBBLE(buffer[i+1])==0x4)
                {printf("%%ESP -> 0x%08X, ", esp); newval=esp;}
            else if(HI_NIBBLE(buffer[i+1])==0x5)
                {printf("%%EBP -> 0x%08X, ", ebp); newval=ebp;}
            else if(HI_NIBBLE(buffer[i+1])==0x6)
                {printf("%%ESI -> 0x%08X, ", esi); newval=esi;}
            else if(HI_NIBBLE(buffer[i+1])==0x7)
                {printf("%%EDI -> 0x%08X, ", edi); newval=edi;}
            if(LO_NIBBLE(buffer[i+1])==0x0)
                {printf("0x%08X -> %%EAX)\n", newval); eax=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x1)
                {printf("0x%08X -> %%ECX)\n", newval); ecx=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x2)
                {printf("0x%08X -> %%EDX)\n", newval); edx=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x3)
                {printf("0x%08X -> %%EBX)\n", newval); ebx=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x4)
                {printf("0x%08X -> %%ESP)\n", newval); esp=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x5)
                {printf("0x%08X -> %%EBP)\n", newval); ebp=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x6)
                {printf("0x%08X -> %%ESI)\n", newval); esi=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x7)
                {printf("0x%08X -> %%EDI)\n", newval); edi=newval;}
            }
            else
            {
                printf("no jump)\n");
            }

            i+=2;
        }

        else if(otablename[buffer[i]]=="cmovne")
        {
            printf("0x%08X: cmovne ", i);
            if(HI_NIBBLE(buffer[i+1])==0x0)
                printf("%%EAX, ");
            else if(HI_NIBBLE(buffer[i+1])==0x1)
                printf("%%ECX, ");
            else if(HI_NIBBLE(buffer[i+1])==0x2)
                printf("%%EDX, ");
            else if(HI_NIBBLE(buffer[i+1])==0x3)
                printf("%%EBX, ");
            else if(HI_NIBBLE(buffer[i+1])==0x4)
                printf("%%ESP, ");
            else if(HI_NIBBLE(buffer[i+1])==0x5)
                printf("%%EBP, ");
            else if(HI_NIBBLE(buffer[i+1])==0x6)
                printf("%%ESI, ");
            else if(HI_NIBBLE(buffer[i+1])==0x7)
                printf("%%EDI, ");
            if(LO_NIBBLE(buffer[i+1])==0x0)
                printf("%%EAX       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);
            else if(LO_NIBBLE(buffer[i+1])==0x1)
                printf("%%ECX       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);
            else if(LO_NIBBLE(buffer[i+1])==0x2)
                printf("%%EDX       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);
            else if(LO_NIBBLE(buffer[i+1])==0x3)
                printf("%%EBX       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);
            else if(LO_NIBBLE(buffer[i+1])==0x4)
                printf("%%ESP       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);
            else if(LO_NIBBLE(buffer[i+1])==0x5)
                printf("%%EBP       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);
            else if(LO_NIBBLE(buffer[i+1])==0x6)
                printf("%%ESI       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);
            else if(LO_NIBBLE(buffer[i+1])==0x7)
                printf("%%EDI       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);

            int newval;

            if(zf==0)
            {
            if(HI_NIBBLE(buffer[i+1])==0x0)
                {printf("%%EAX -> 0x%08X, ", eax); newval=eax;}
            else if(HI_NIBBLE(buffer[i+1])==0x1)
                {printf("%%ECX -> 0x%08X, ", ecx); newval=ecx;}
            else if(HI_NIBBLE(buffer[i+1])==0x2)
                {printf("%%EDX -> 0x%08X, ", edx); newval=edx;}
            else if(HI_NIBBLE(buffer[i+1])==0x3)
                {printf("%%EBX -> 0x%08X, ", ebx); newval=ebx;}
            else if(HI_NIBBLE(buffer[i+1])==0x4)
                {printf("%%ESP -> 0x%08X, ", esp); newval=esp;}
            else if(HI_NIBBLE(buffer[i+1])==0x5)
                {printf("%%EBP -> 0x%08X, ", ebp); newval=ebp;}
            else if(HI_NIBBLE(buffer[i+1])==0x6)
                {printf("%%ESI -> 0x%08X, ", esi); newval=esi;}
            else if(HI_NIBBLE(buffer[i+1])==0x7)
                {printf("%%EDI -> 0x%08X, ", edi); newval=edi;}
            if(LO_NIBBLE(buffer[i+1])==0x0)
                {printf("0x%08X -> %%EAX)\n", newval); eax=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x1)
                {printf("0x%08X -> %%ECX)\n", newval); ecx=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x2)
                {printf("0x%08X -> %%EDX)\n", newval); edx=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x3)
                {printf("0x%08X -> %%EBX)\n", newval); ebx=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x4)
                {printf("0x%08X -> %%ESP)\n", newval); esp=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x5)
                {printf("0x%08X -> %%EBP)\n", newval); ebp=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x6)
                {printf("0x%08X -> %%ESI)\n", newval); esi=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x7)
                {printf("0x%08X -> %%EDI)\n", newval); edi=newval;}
            }
            else
            {
                printf("no jump)\n");
            }

            i+=2;
        }

        else if(otablename[buffer[i]]=="cmovge")
        {
            printf("0x%08X: cmovge ", i);
            if(HI_NIBBLE(buffer[i+1])==0x0)
                printf("%%EAX, ");
            else if(HI_NIBBLE(buffer[i+1])==0x1)
                printf("%%ECX, ");
            else if(HI_NIBBLE(buffer[i+1])==0x2)
                printf("%%EDX, ");
            else if(HI_NIBBLE(buffer[i+1])==0x3)
                printf("%%EBX, ");
            else if(HI_NIBBLE(buffer[i+1])==0x4)
                printf("%%ESP, ");
            else if(HI_NIBBLE(buffer[i+1])==0x5)
                printf("%%EBP, ");
            else if(HI_NIBBLE(buffer[i+1])==0x6)
                printf("%%ESI, ");
            else if(HI_NIBBLE(buffer[i+1])==0x7)
                printf("%%EDI, ");
            if(LO_NIBBLE(buffer[i+1])==0x0)
                printf("%%EAX       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);
            else if(LO_NIBBLE(buffer[i+1])==0x1)
                printf("%%ECX       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);
            else if(LO_NIBBLE(buffer[i+1])==0x2)
                printf("%%EDX       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);
            else if(LO_NIBBLE(buffer[i+1])==0x3)
                printf("%%EBX       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);
            else if(LO_NIBBLE(buffer[i+1])==0x4)
                printf("%%ESP       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);
            else if(LO_NIBBLE(buffer[i+1])==0x5)
                printf("%%EBP       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);
            else if(LO_NIBBLE(buffer[i+1])==0x6)
                printf("%%ESI       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);
            else if(LO_NIBBLE(buffer[i+1])==0x7)
                printf("%%EDI       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);

            int newval;

            if(!(sf^of))
            {
            if(HI_NIBBLE(buffer[i+1])==0x0)
                {printf("%%EAX -> 0x%08X, ", eax); newval=eax;}
            else if(HI_NIBBLE(buffer[i+1])==0x1)
                {printf("%%ECX -> 0x%08X, ", ecx); newval=ecx;}
            else if(HI_NIBBLE(buffer[i+1])==0x2)
                {printf("%%EDX -> 0x%08X, ", edx); newval=edx;}
            else if(HI_NIBBLE(buffer[i+1])==0x3)
                {printf("%%EBX -> 0x%08X, ", ebx); newval=ebx;}
            else if(HI_NIBBLE(buffer[i+1])==0x4)
                {printf("%%ESP -> 0x%08X, ", esp); newval=esp;}
            else if(HI_NIBBLE(buffer[i+1])==0x5)
                {printf("%%EBP -> 0x%08X, ", ebp); newval=ebp;}
            else if(HI_NIBBLE(buffer[i+1])==0x6)
                {printf("%%ESI -> 0x%08X, ", esi); newval=esi;}
            else if(HI_NIBBLE(buffer[i+1])==0x7)
                {printf("%%EDI -> 0x%08X, ", edi); newval=edi;}
            if(LO_NIBBLE(buffer[i+1])==0x0)
                {printf("0x%08X -> %%EAX)\n", newval); eax=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x1)
                {printf("0x%08X -> %%ECX)\n", newval); ecx=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x2)
                {printf("0x%08X -> %%EDX)\n", newval); edx=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x3)
                {printf("0x%08X -> %%EBX)\n", newval); ebx=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x4)
                {printf("0x%08X -> %%ESP)\n", newval); esp=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x5)
                {printf("0x%08X -> %%EBP)\n", newval); ebp=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x6)
                {printf("0x%08X -> %%ESI)\n", newval); esi=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x7)
                {printf("0x%08X -> %%EDI)\n", newval); edi=newval;}
            }
            else
            {
                printf("no jump)\n");
            }

            i+=2;
        }

        else if(otablename[buffer[i]]=="cmovg")
        {
            printf("0x%08X: cmovg ", i);
            if(HI_NIBBLE(buffer[i+1])==0x0)
                printf("%%EAX, ");
            else if(HI_NIBBLE(buffer[i+1])==0x1)
                printf("%%ECX, ");
            else if(HI_NIBBLE(buffer[i+1])==0x2)
                printf("%%EDX, ");
            else if(HI_NIBBLE(buffer[i+1])==0x3)
                printf("%%EBX, ");
            else if(HI_NIBBLE(buffer[i+1])==0x4)
                printf("%%ESP, ");
            else if(HI_NIBBLE(buffer[i+1])==0x5)
                printf("%%EBP, ");
            else if(HI_NIBBLE(buffer[i+1])==0x6)
                printf("%%ESI, ");
            else if(HI_NIBBLE(buffer[i+1])==0x7)
                printf("%%EDI, ");
            if(LO_NIBBLE(buffer[i+1])==0x0)
                printf("%%EAX       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);
            else if(LO_NIBBLE(buffer[i+1])==0x1)
                printf("%%ECX       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);
            else if(LO_NIBBLE(buffer[i+1])==0x2)
                printf("%%EDX       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);
            else if(LO_NIBBLE(buffer[i+1])==0x3)
                printf("%%EBX       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);
            else if(LO_NIBBLE(buffer[i+1])==0x4)
                printf("%%ESP       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);
            else if(LO_NIBBLE(buffer[i+1])==0x5)
                printf("%%EBP       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);
            else if(LO_NIBBLE(buffer[i+1])==0x6)
                printf("%%ESI       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);
            else if(LO_NIBBLE(buffer[i+1])==0x7)
                printf("%%EDI       (ZF -> %d, SF -> %d, OF -> %d, ", zf, sf, of);

            int newval;

            if((!(sf^of))&(!(zf)))
            {
            if(HI_NIBBLE(buffer[i+1])==0x0)
                {printf("%%EAX -> 0x%08X, ", eax); newval=eax;}
            else if(HI_NIBBLE(buffer[i+1])==0x1)
                {printf("%%ECX -> 0x%08X, ", ecx); newval=ecx;}
            else if(HI_NIBBLE(buffer[i+1])==0x2)
                {printf("%%EDX -> 0x%08X, ", edx); newval=edx;}
            else if(HI_NIBBLE(buffer[i+1])==0x3)
                {printf("%%EBX -> 0x%08X, ", ebx); newval=ebx;}
            else if(HI_NIBBLE(buffer[i+1])==0x4)
                {printf("%%ESP -> 0x%08X, ", esp); newval=esp;}
            else if(HI_NIBBLE(buffer[i+1])==0x5)
                {printf("%%EBP -> 0x%08X, ", ebp); newval=ebp;}
            else if(HI_NIBBLE(buffer[i+1])==0x6)
                {printf("%%ESI -> 0x%08X, ", esi); newval=esi;}
            else if(HI_NIBBLE(buffer[i+1])==0x7)
                {printf("%%EDI -> 0x%08X, ", edi); newval=edi;}
            if(LO_NIBBLE(buffer[i+1])==0x0)
                {printf("0x%08X -> %%EAX)\n", newval); eax=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x1)
                {printf("0x%08X -> %%ECX)\n", newval); ecx=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x2)
                {printf("0x%08X -> %%EDX)\n", newval); edx=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x3)
                {printf("0x%08X -> %%EBX)\n", newval); ebx=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x4)
                {printf("0x%08X -> %%ESP)\n", newval); esp=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x5)
                {printf("0x%08X -> %%EBP)\n", newval); ebp=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x6)
                {printf("0x%08X -> %%ESI)\n", newval); esi=newval;}
            else if(LO_NIBBLE(buffer[i+1])==0x7)
                {printf("0x%08X -> %%EDI)\n", newval); edi=newval;}
            }
            else
            {
                printf("no jump)\n");
            }

            i+=2;
        }

        else if(otablename[buffer[i]]=="call")
        {
            unsigned int addr = gmem4(i+1);
            memindex=esp-0x4;
            buffer[memindex]=i+5;

            printf("0x%08X: call 0x%08X       (%%ESP -> 0x%08X, 0x%08X -> [0x%08X], 0x%08X -> ESP, 0x%08X -> PC)\n", i, addr, esp, i+5, memindex, memindex, addr);
            esp=memindex;

            i=addr;
        }

        else if(otablename[buffer[i]]=="ret")
        {
            
            printf("0x%08X: ret       (%%ESP -> 0x%08X, [0x%08X] -> 0x%08X, 0x%08X -> ESP, 0x%08X -> PC)\n", i, esp, esp, getbytes2(buffer[esp+3], buffer[esp+2], buffer[esp+1], buffer[esp]), esp+4, getbytes2(buffer[esp+3], buffer[esp+2], buffer[esp+1], buffer[esp]));
            i=getbytes2(buffer[esp+3], buffer[esp+2], buffer[esp+1], buffer[esp]);
            esp+=0x4;
        }
    
	else if(otablename[buffer[i]]=="pushl")
        {
            printf("0x%08X: pushl ", i);
            if(HI_NIBBLE(buffer[i+1])==0x0)
	    { 
	      //printf("\n\n\neax: %08X\n", eax);
	      memindex=esp-4;
	      //printf("memindex: %08X\n", memindex);
	      buffer[memindex]=eax & 0xff;
          buffer[memindex+1]=eax >> 8 & 0xff;
          buffer[memindex+2]=eax >> 16 & 0xff;
          buffer[memindex+3]=eax >> 24 & 0xff;
	      //printf("buffer[memindex]: %08X\n", buffer[memindex]);
	      printf("%%EAX,       (%%EAX -> 0x%08X, %%ESP -> 0x%08X, 0x%08X -> [0x%08X], 0x%08X -> %%ESP)\n", eax, esp, eax, memindex, memindex);
	      esp=memindex;
	      //printf("esp: %08X\n\n\n", esp);
	      
	    }
            else if(HI_NIBBLE(buffer[i+1])==0x1)
	    { 
	      memindex=esp-4;
	      buffer[memindex]=eax & 0xff;
          buffer[memindex+1]=eax >> 8 & 0xff;
          buffer[memindex+2]=eax >> 16 & 0xff;
          buffer[memindex+3]=eax >> 24 & 0xff;
	      printf("%%ECX,       (%%ECX -> 0x%08X, %%ESP -> 0x%08X, 0x%08X -> [0x%08X], 0x%08X -> %%ESP)\n", ecx, esp, ecx, memindex, memindex);
	      esp=memindex;
	    }
            else if(HI_NIBBLE(buffer[i+1])==0x2)
	    { 
	      memindex=esp-4;
	      buffer[memindex]=edx & 0xff;
          buffer[memindex+1]=edx >> 8 & 0xff;
          buffer[memindex+2]=edx >> 16 & 0xff;
          buffer[memindex+3]=edx >> 24 & 0xff;
	      printf("%%EDX,       (%%EDX -> 0x%08X, %%ESP -> 0x%08X, 0x%08X -> [0x%08X], 0x%08X -> %%ESP)\n", edx, esp, edx, memindex, memindex);
	      esp=memindex;
	    }
            else if(HI_NIBBLE(buffer[i+1])==0x3)
	    { 
	      memindex=esp-4;
	      buffer[memindex]=ebx & 0xff;
          buffer[memindex+1]=ebx >> 8 & 0xff;
          buffer[memindex+2]=ebx >> 16 & 0xff;
          buffer[memindex+3]=ebx >> 24 & 0xff;
	      printf("%%EBX,       (%%EBP -> 0x%08X, %%ESP -> 0x%08X, 0x%08X -> [0x%08X], 0x%08X -> %%ESP)\n", ebx, esp, ebx, memindex, memindex);
	      esp=memindex;
	    }
            else if(HI_NIBBLE(buffer[i+1])==0x4)
	    { 
	      memindex=esp-4;
	      buffer[memindex]=esp & 0xff;
          buffer[memindex+1]=esp >> 8 & 0xff;
          buffer[memindex+2]=esp >> 16 & 0xff;
          buffer[memindex+3]=esp >> 24 & 0xff;
	      printf("%%ESP,       (%%ESP -> 0x%08X, %%ESP -> 0x%08X, 0x%08X -> [0x%08X], 0x%08X -> %%ESP)\n", esp, esp, esp, memindex, memindex);
	      esp=memindex;
	    }
            else if(HI_NIBBLE(buffer[i+1])==0x5)
	    { 
	      memindex=esp-4;
	      buffer[memindex]=ebp & 0xff;
          buffer[memindex+1]=ebp >> 8 & 0xff;
          buffer[memindex+2]=ebp >> 16 & 0xff;
          buffer[memindex+3]=ebp >> 24 & 0xff;
	      printf("%%EBP,       (%%EBP -> 0x%08X, %%ESP -> 0x%08X, 0x%08X -> [0x%08X], 0x%08X -> %%ESP)\n", ebp, esp, ebp, memindex, memindex);
	      esp=memindex;
	    }
            else if(HI_NIBBLE(buffer[i+1])==0x6)
	    { 
	      memindex=esp-4;
	      buffer[memindex]=esi & 0xff;
          buffer[memindex+1]=esi >> 8 & 0xff;
          buffer[memindex+2]=esi >> 16 & 0xff;
          buffer[memindex+3]=esi >> 24 & 0xff;
	      printf("%%ESI,       (%%ESI -> 0x%08X, %%ESP -> 0x%08X, 0x%08X -> [0x%08X], 0x%08X -> %%ESP)\n", esi, esp, esi, memindex, memindex);
	      esp=memindex;
	    }
            else if(HI_NIBBLE(buffer[i+1])==0x7)
	    { 
	      memindex=esp-4;
	      buffer[memindex]=edi & 0xff;
          buffer[memindex+1]=edi >> 8 & 0xff;
          buffer[memindex+2]=edi >> 16 & 0xff;
          buffer[memindex+3]=edi >> 24 & 0xff;
	      printf("%%EDI,       (%%EDI -> 0x%08X, %%ESP -> 0x%08X, 0x%08X -> [0x%08X], 0x%08X -> %%ESP)\n", edi, esp, edi, memindex, memindex);
	      esp=memindex;
	    }
	    i+=2;
        }
        
        else if(otablename[buffer[i]]=="popl")
        {
	   printf("0x%08X: popl ", i);
            if(HI_NIBBLE(buffer[i+1])==0x0)
	    { 
	      printf("%%EAX,       (%%ESP -> 0x%08X, [0x%08X] -> 0x%08X, 0x%08X -> %%ESP, 0x%08X -> %%EAX)\n", esp, esp, getbytes2(buffer[esp+3], buffer[esp+2], buffer[esp+1], buffer[esp]), esp+4, getbytes2(buffer[esp+3], buffer[esp+2], buffer[esp+1], buffer[esp]));
	      
	      eax=getbytes2(buffer[esp+3], buffer[esp+2], buffer[esp+1], buffer[esp]);
          esp+=4;
	    }
            else if(HI_NIBBLE(buffer[i+1])==0x1)
	    { 
	      printf("%%ECX,       (%%ESP -> 0x%08X, [0x%08X] -> 0x%08X, 0x%08X -> %%ESP, 0x%08X -> %%ECX)\n", esp, esp, getbytes2(buffer[esp+3], buffer[esp+2], buffer[esp+1], buffer[esp]), esp+4, getbytes2(buffer[esp+3], buffer[esp+2], buffer[esp+1], buffer[esp]));
	      
	      ecx=getbytes2(buffer[esp+3], buffer[esp+2], buffer[esp+1], buffer[esp]);
          esp+=4;
	    }
            else if(HI_NIBBLE(buffer[i+1])==0x2)
	    { 
	      printf("%%EDX,       (%%ESP -> 0x%08X, [0x%08X] -> 0x%08X, 0x%08X -> %%ESP, 0x%08X -> %%EDX)\n", esp, esp, getbytes2(buffer[esp+3], buffer[esp+2], buffer[esp+1], buffer[esp]), esp+4, getbytes2(buffer[esp+3], buffer[esp+2], buffer[esp+1], buffer[esp]));
	      
	      edx=getbytes2(buffer[esp+3], buffer[esp+2], buffer[esp+1], buffer[esp]);
          esp+=4;
	    }
            else if(HI_NIBBLE(buffer[i+1])==0x3)
	    { 
	      printf("%%EBX,       (%%ESP -> 0x%08X, [0x%08X] -> 0x%08X, 0x%08X -> %%ESP, 0x%08X -> %%EBX)\n", esp, esp, getbytes2(buffer[esp+3], buffer[esp+2], buffer[esp+1], buffer[esp]), esp+4, getbytes2(buffer[esp+3], buffer[esp+2], buffer[esp+1], buffer[esp]));
	      
	      ebx=getbytes2(buffer[esp+3], buffer[esp+2], buffer[esp+1], buffer[esp]);
          esp+=4;
	    }
            else if(HI_NIBBLE(buffer[i+1])==0x4)
	    { 
	      printf("%%ESP,       (%%ESP -> 0x%08X, [0x%08X] -> 0x%08X, 0x%08X -> %%ESP, 0x%08X -> %%ESP)\n", esp, esp, getbytes2(buffer[esp+3], buffer[esp+2], buffer[esp+1], buffer[esp]), esp+4, getbytes2(buffer[esp+3], buffer[esp+2], buffer[esp+1], buffer[esp]));
	      
	      esp=getbytes2(buffer[esp+3], buffer[esp+2], buffer[esp+1], buffer[esp]);
          esp+=4;
	    }
            else if(HI_NIBBLE(buffer[i+1])==0x5)
	    { 
	      printf("%%EBP,       (%%ESP -> 0x%08X, [0x%08X] -> 0x%08X, 0x%08X -> %%ESP, 0x%08X -> %%EBP)\n", esp, esp, getbytes2(buffer[esp+3], buffer[esp+2], buffer[esp+1], buffer[esp]), esp+4, getbytes2(buffer[esp+3], buffer[esp+2], buffer[esp+1], buffer[esp]));
	      
	      ebp=getbytes2(buffer[esp+3], buffer[esp+2], buffer[esp+1], buffer[esp]);
          esp+=4;
	    }
            else if(HI_NIBBLE(buffer[i+1])==0x6)
	    { 
	      printf("%%ESI,       (%%ESP -> 0x%08X, [0x%08X] -> 0x%08X, 0x%08X -> %%ESP, 0x%08X -> %%ESI)\n", esp, esp, getbytes2(buffer[esp+3], buffer[esp+2], buffer[esp+1], buffer[esp]), esp+4, getbytes2(buffer[esp+3], buffer[esp+2], buffer[esp+1], buffer[esp]));
	      
	      esi=getbytes2(buffer[esp+3], buffer[esp+2], buffer[esp+1], buffer[esp]);
          esp+=4;
	    }
            else if(HI_NIBBLE(buffer[i+1])==0x7)
	    { 

	      printf("%%EDI,       (%%ESP -> 0x%08X, [0x%08X] -> 0x%08X, 0x%08X -> %%ESP, 0x%08X -> %%EDI)\n", esp, esp, getbytes2(buffer[esp+3], buffer[esp+2], buffer[esp+1], buffer[esp]), esp+4, getbytes2(buffer[esp+3], buffer[esp+2], buffer[esp+1], buffer[esp]));
	      
	      edi=getbytes2(buffer[esp+3], buffer[esp+2], buffer[esp+1], buffer[esp]);
          esp+=4;
	    }
	    i+=2;
	}

    }


    //USE LARGEST ADDRESS +1
    //USE LARGEST ADDRESS +1, i, eax, eax, eax
    //USE LARGEST ADDRESS +1
    //USE LARGEST ADDRESS +1
    //USE LARGEST ADDRESS +1
    //USE LARGEST ADDRESS +1
    //USE LARGEST ADDRESS +1
    //USE LARGEST ADDRESS +1
    //USE LARGEST ADDRESS +1
    //USE LARGEST ADDRESS +1
    free(buffer);
    free(memory);

    exit(0);
}

int getbytes2(int a, int b, int c, int d)
{
  int c1=a;
  int c2=b;
  int c3=c;
  int c4=d;
  int first=c1*256+c2;
  int second=c3*256+c4;
  //printf("H %x\n", first);
  //printf("O %x\n", second);
  if((c1!=EOF)&&(c2!=EOF)&&(c3!=EOF)&&(c4!=EOF))
    return (first*65536+second);
  else
    return -1;
}

void inittable(void)
{
    int i;
    for(i=0;i<256;i++)
        otablename[i]="invalid";

    otablename[0x00]="halt";//initializing
    otablename[0x10]="nop";
    otablename[0x30]="irmovl";
    otablename[0x40]="rmmovl";//initializing
    otablename[0x50]="mrmovl";
    otablename[0x80]="call";
    otablename[0x90]="ret";
    otablename[0xA0]="pushl";
    otablename[0xB0]="popl";//initializing
    otablename[0x20]="rrmovl";
    otablename[0x21]="cmovle";
    otablename[0x22]="cmovl";//initializing
    otablename[0x23]="cmove";
    otablename[0x24]="cmovne";
    otablename[0x25]="cmovge";
    otablename[0x26]="cmovg";//initializing
    otablename[0x60]="addl";
    otablename[0x61]="subl";
    otablename[0x62]="andl";//initializing
    otablename[0x63]="xorl";
    otablename[0x70]="jmp";//initializing
    otablename[0x71]="jle";
    otablename[0x72]="jl";
    otablename[0x73]="je";
    otablename[0x74]="jne";
    otablename[0x75]="jge";//initializing
    otablename[0x76]="jg";
}

//read ea object
void readob(char* f)
{
    unsigned int laddress;

    FILE* filep=fopen (f, "rb"); //open
    if(filep==NULL) 
        screwed_up("This is not a Y86 object file"); //not file
    
    int m=nex2(filep); //getm
    if(m!=0x7962)
        {
            screwed_up("This is not a Y86 object file"); //not file
        }

    while((laddress=nex2(filep))!=-1)
        {
            int size;
            
            if(laddress==-2)
                screwed_up("This Y86 object file is corrupted"); //corrupt
            size=nex2(filep);
            if(size<0)
                screwed_up("This Y86 object file is corrupted"); //corrupt
            while(size>0)
                {
                    int c=fgetc(filep);
                    if (c==EOF)
                        screwed_up("This Y86 object file is corrupted"); //corrupt
                    smem(laddress,c);
                    laddress+=1;
                    size-=1;
                    //increment!
                }
        }

}

////HEERERERERER
unsigned int gmem4(unsigned int myint)
{
    unsigned int value=0;
    int i;

    for(i=3;i>=0;i--)
        {
            //DO EACH VAL
            unsigned char val=gmem(myint+i); //NOW TO MAKE IT HEX
            value=(value<<8)|val;
        }
    return(value); //RETURN VAL
}
//GET THE NEXT 2 BYTES
int nex2(FILE *f)
{
    int a1, a2;

    a1=fgetc(f);
    if(a1==EOF) return(-1);
    a2=fgetc(f);
    if(a2==EOF) return(-2);
    return((a1<<8)|a2);
}

//GETMEM MAN
unsigned char gmem(unsigned int myint)
{
    unsigned char val=0;
    int tbit=(myint>>22)&0x3FF; //FOR TBITS
    unsigned char** mem2=mem1[tbit];
    if(mem2!=NULL)
        {
            //FOR MIDDLE BITS
            int mbit=(myint>>12)&0x3FF;
            unsigned char* mem3=mem2[mbit];
            if(mem3!=NULL)
                {
                    //FOR BOTTOM BITS
                    int bbit=myint&0xFFF;
                    val=mem3[bbit];
                }
        }
    return(val); //RETURN DAT VAL

}

//HERE'S WHERE I SCAN MEM
void smem(unsigned int myint,unsigned char val)
{
    //INITIALIZE TBIT
    int tbit=(myint>>22)&0x3FF;
    //MAKE TBIT IN HEX
    unsigned char **mem2=mem1[tbit];
    if(mem2==NULL)
        { 
            //TOP BITS
            mem1[tbit]=(unsigned char**)malloc(1035*sizeof(unsigned char*));
            mem2=mem1[tbit];
            if(mem2==NULL) //ERROR
                screwed_up("No more memory in mem2");
        }
    
    int mbit=(myint>>12)&0x3FF;
    unsigned char* mem3=mem2[mbit];
    if(mem3==NULL)
        {
            //MIDDLE BITS
            mem2[mbit]=(unsigned char*)malloc(4123*sizeof(unsigned char));
            mem3=mem2[mbit];
            if(mem3==NULL) //ERROR
                screwed_up("No more memory in mem3");
        }
        //NOW DO BBIT
    int bbit=myint&0xFFF;
    mem3[bbit]=val;

    if(myint<liladd)
        {
            //DO THE LITTLEADDRESS
            liladd=myint;
        }
    
    if(myint>laradd)
        {
            //DO THE LARGEADDRESS
            laradd=myint;
        }
}

//ERRORS
void screwed_up(const char*message)
{
    //PRINT ERROR
    fprintf(stderr,"%s.\nUsage: ./a.out or ./.a.exe myY86object.yb",message);

    //EXIT W/ ERROR
    exit(1);
}