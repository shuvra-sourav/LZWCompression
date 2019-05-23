#include <stdio.h>
#include <string.h>

#define codeword_max_size 4096

typedef struct {
    int code;
    char sequence[100];
}codeword;

int resultCode[255], resultLen= 0;
char resultWord[10000];


/*if the input string is found then code is returned, if not then -1 */
int findWord(char *input, codeword * dictionary){
    int i=0;
    for(i=0; i < codeword_max_size; i++){
        if(strcmp(input,dictionary[i].sequence) == 0){
            return dictionary[i].code;
        }
    }
    return -1;
}

void encode(char *input){
    codeword dictionaryEncode[codeword_max_size];
    for(int i=0; i<256; i++){
        dictionaryEncode[i].code = i;
        dictionaryEncode[i].sequence[0] = (char)i;
    }
    char w[255]="",wc[255]="";
    int dictsize = 256, length = strlen(input);
    resultLen=0;  //global variable
    for(int i=0; i<length;i++){
        strcpy(wc,w);
        int len = strlen(wc);
        wc[len] = input[i];
        wc[len+1] = '\0';
        int code = findWord(wc, dictionaryEncode);
        if(code != -1){
            strcpy(w,wc);
        } else {
            strcpy(dictionaryEncode[dictsize].sequence, wc);
            dictionaryEncode[dictsize].code =  dictsize;
            resultCode[resultLen] = findWord(w, dictionaryEncode);
            resultLen++;
            dictsize++;
            w[0] = input[i];
            w[1] = '\0';
        }
    }
    if(strcmp("",w) != 0){
        resultCode[resultLen]  = findWord(w, dictionaryEncode);
        resultLen++;
    }
}


char * findCode(int input,codeword * dictionary){
    int i=0;
    for(i=0; i<codeword_max_size; i++){
        if(input == dictionary[i].code){
            return dictionary[i].sequence;
        }
    }
    return "";
}

char * decode(int input[], int len){
    printf("%d",input[0]);
    codeword dictionaryDecode[codeword_max_size];
    for(int i=0; i<256; i++){
        dictionaryDecode[i].code = i;
        dictionaryDecode[i].sequence[0] = (char)i;
    }

    char result[10000],w[255],entry[255];
    int dictsize = 256;
    w[0]=(char)input[0];
    strcat(result,w);
    for (int i = 1; i < len; i++) {
        char temp[2];
        int code = input[i];
        char *sequence = findCode(code,dictionaryDecode);
        if(strcmp(sequence, "") != 0){
            strcpy(entry, sequence);
        } else if(code==dictsize){
            strcat(entry,w);
            temp[0]=w[0];   temp[1]='\0';
            strcat(entry,temp);
        }
        strcat(result,entry);
        strcat(dictionaryDecode[dictsize].sequence,w);
        temp[0]=entry[0];   temp[1]='\0';
        strcat(dictionaryDecode[dictsize].sequence,temp);
        dictsize++;
        strcpy(w, entry);
        if(strcmp(entry,"")==0) {
        }
    }

    return result;
}

int main() {

    char *s = "BABAABAAA";
    puts(s);
    encode(s);
    for(int j=0; j< resultLen; j++){
        printf("%d ",resultCode[j]);
    }
    return 0;
}
