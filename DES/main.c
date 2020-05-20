//
//  main.c
//  DES
//
//

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>

int PC_1[7][8] = {
    {57, 49, 41, 33, 25, 17, 9, 1},
    {58, 50, 42, 34, 26, 18, 10, 2},
    {59, 51, 43, 35, 27, 19, 11, 3},
    {60, 52, 44, 36, 63, 55, 47, 39},
    {31, 23, 15, 7, 62, 54, 46, 38},
    {30, 22, 14, 6, 61, 53, 45, 37},
    {29, 21, 13, 5, 28, 20, 12, 4}
};

int PC_2[8][6] = {
    {14, 17, 11, 24, 1, 5},
    {3, 28, 15, 6, 21, 10},
    {23, 19, 12, 4, 26, 8},
    {16, 7, 27, 20, 13, 2},
    {41, 52, 31, 37, 47, 55},
    {30, 40, 51, 45, 33, 48},
    {44, 49, 39, 56, 34, 53},
    {46, 42, 50, 36, 29, 32}
};

int InitialPermutationTable[8][8] = {
    {58, 50, 42, 34, 26, 28, 10, 2},
    {60, 52, 44, 36, 28, 20, 12, 4},
    {62, 54, 46, 38, 30, 22, 14, 6},
    {64, 56, 48, 40, 32, 24, 16, 8},
    {57, 49, 41, 33, 25, 17, 9, 1},
    {59, 51, 43, 35, 27, 19, 11, 3},
    {61, 53, 45, 37, 29, 21, 13, 5},
    {63, 55, 47, 39, 31, 23, 15, 7}
};

int ETable[8][6] = {
    {32, 1, 2, 3, 4, 5},
    {4, 5, 6, 7, 8, 9},
    {8, 9, 10, 11, 12, 13},
    {12, 13, 14, 15, 16, 17},
    {16, 17, 18, 19, 20, 21},
    {20, 21, 22, 23, 24, 25},
    {24, 25, 26, 27, 28, 29},
    {28, 29, 30, 31, 32, 1}
};

int S1[4][16] = {
    {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
    {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
    {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
    {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
};

int S2[4][16] = {
    {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
    {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
    {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
    {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
};

int S3[4][16] = {
    {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
    {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
    {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
    {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}
};

int S4[4][16] = {
    {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
    {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
    {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
    {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}
};

int S5[4][16] = {
    {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
    {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
    {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
    {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3},
};

int S6[4][16] = {
    {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
    {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
    {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
    {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
};

int S7[4][16] = {
    {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
    {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
    {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
    {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}
};

int S8[4][16] = {
    {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
    {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
    {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
    {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}
};

int P[8][4] = {
    {16, 7, 20, 21},
    {29, 12, 28, 17},
    {1, 18, 31, 10},
    {5, 18, 31, 10},
    {2, 8, 24, 14},
    {32, 27, 3, 9},
    {19, 13, 30, 6},
    {22, 11, 4, 25}
};

void print(char *c, char *mozi, int len) {
    int i, c_len;
    c_len = strlen(c);
    printf("%s:", c);
    for (i = 0; i < 20 - c_len; i++) {
        printf(" ");
    }
    for (i = 0; i < 10 - len; i++) {
        printf(" ");
    }
    for (i = 0; i < len; i++) {
        printf("%d", mozi[i]);
    }
    printf("\n");
}

void PC1(char *inputKey, char *permutedChoiceLeft, char *permutedChoiceRight){
    int i, j;
    char permutedChoice[56];
    
    for(i=0;i < 7;i++){
        for(j = 0;j < 8;j++){
            permutedChoice[8 * i + j] = inputKey[PC_1[i][j] - 1];
        }
    }
    print("PC1", permutedChoice, 56);
    for(i=0;i<56;i++){
        if(i < 28){
            permutedChoiceLeft[i] = permutedChoice[i];
        }else{
            permutedChoiceRight[i - 28] = permutedChoice[i];
        }
    }
    print("PC1 Left", permutedChoiceLeft, 28);
    print("PC1 Right", permutedChoiceRight, 28);
}

void PC2(int number, char *inputLeft, char *inputRight, char *outputLeft, char *outputRight, char *subKeyGenerate){
    int i, j;
    char mozi[56];
    // 1,2,9,16番目で1シフト(i=0から始まるためそれぞれ-1にする)
    if(number == 0 || number == 1 || number == 8 || number == 15){
        outputLeft[27] = inputLeft[0];
        outputRight[27] = inputRight[0];
        for(i=0;i<27;i++){
            outputLeft[i] = inputLeft[i+1];
            outputRight[i] = inputRight[i+1];
        }
    }else{
        outputLeft[26] = inputLeft[0];
        outputRight[26] = inputRight[0];
        outputLeft[27] = inputLeft[1];
        outputRight[27] = inputRight[1];
        for(i=0;i<26;i++){
            outputLeft[i] = inputLeft[i+2];
            outputRight[i] = inputRight[i+2];
        }
    }
    for(i=0;i<28;i++){
        mozi[i] = inputLeft[i];
        mozi[i + 28] = inputRight[i];
    }
    for(i=0;i<8;i++){
        for(j=0;j<6;j++){
            subKeyGenerate[6 * i + j] = mozi[PC_2[i][j] - 1];
        }
    }
    print("outputLeft", outputLeft, 28);
    print("outputRight", outputRight, 28);
    print("outputPC2", mozi, 56);
    print("subKeyGenerate", subKeyGenerate, 48);
}

void ExpansionPermutation(char *ipRight, char *expansionPermutation){
    int i, j;
    for(i=0;i<8;i++){
        for(j=0;j<6;j++){
            expansionPermutation[6 * i + j] = ipRight[ETable[i][j] - 1];
        }
    }
}


// 初期転置(IP:Initial Permutation)
void InitialPermutation(char *plainText, char *ipLeft, char *ipRight) {
    int i, j;
    char ip[64];
    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            ip[6 * i + j] = plainText[ETable[i][j] - 1];
        }
    }
    for(i = 0; i < 32; i++){
        ipLeft[i] = ip[i];
        ipRight[i] = ip[i + 32];
    }
}

// 2進数から10進数へ変換
void binaryDemical(char *mozi, int *suti){
    suti[0] = mozi[0] * 2 + mozi[1];
    suti[1] = mozi[0] * 8 + mozi[1] * 4 + mozi[2] * 2 + mozi[3];
}

// 初期配置の反対の操作(IP-1)
void InitialPermutationInverse(char *l3, char * r3, char *ipInverse) {
    ipInverse[0] = l3[3];
    ipInverse[1] = l3[0];
    ipInverse[2] = l3[2];
    ipInverse[3] = r3[0];
    ipInverse[4] = r3[2];
    ipInverse[5] = l3[1];
    ipInverse[6] = r3[3];
    ipInverse[7] = r3[1];
}

void function_S(char *outputExpansionPermutation, char *outputS){
    int i, suti[2];
    char moziS[6];
    for(i=0;i<8;i++){
        moziS[0] = outputExpansionPermutation[i*6];
        moziS[1] = outputExpansionPermutation[i*6+1];
        moziS[2] = outputExpansionPermutation[i*6+2];
        moziS[3] = outputExpansionPermutation[i*6+3];
        moziS[4] = outputExpansionPermutation[i*6+4];
        moziS[5] = outputExpansionPermutation[i*6+5];
        binaryDemical(moziS, suti);
        
        switch (i) {
            case 0:
                outputS[0] = S1[suti[0]][suti[1]];
                break;
            case 1:
                outputS[1] = S2[suti[0]][suti[1]];
                break;
            case 2:
                outputS[2] = S3[suti[0]][suti[1]];
                break;
            case 3:
                outputS[3] = S4[suti[0]][suti[1]];
                break;
            case 4:
                outputS[4] = S5[suti[0]][suti[1]];
                break;
            case 5:
                outputS[5] = S6[suti[0]][suti[1]];
            default:
                break;
        }
        
    }
}

void proccessingP(char *input, char *output){
    int i, j;
    for(i = 0;i < 8;i++){
        for(j=0;j< 4;j++){
            output[4 * i + j] = input[P[i][j] - 1];
        }
    }
}

// 関数F
void function_f(char *key, char *ipRight) {
    int i;
    char outputExpansionPermutation[48];
    char outputP[32], outputS[6];

    // 拡大転置 (E/P:Expansion Permutation)
    ExpansionPermutation(ipRight, outputExpansionPermutation);
    print("拡大転置(E/P)", outputExpansionPermutation, 8);
    // XORする
    for (i = 0; i < 48; i++) {
        outputExpansionPermutation[i] = outputExpansionPermutation[i] ^ key[i];
    }
    print("XOR", outputExpansionPermutation, 48);
    function_S(outputExpansionPermutation, outputS);
    proccessingP(outputS, outputP);
}

// XOR関数
void xor(char *sbox_output, char *l, char *output) {
    int i;

    for (i = 0; i < 4; i++) {
        output[i] = sbox_output[i] ^ l[i];
    }
}

int main(int argc, const char * argv[]) {
    int i, k, password;
    char key[64];
    char ipLeft[32], ipRight[32];
    char plainText[64];
    char permutedChoice1Left[28], permutedChoice1Right[28];
    char permutedChoice2Left[28], permutedChoice2Right[28];
    char outputPC2[48];
    
    password = 16;
    
    for (i = 63; 0 <= i; i--) {
        key[i] = password % 2;
        password = password / 2;
    }
    print("key", key, 64);
    PC1(key, permutedChoice1Left, permutedChoice1Right);
    InitialPermutation(plainText, ipLeft, ipRight);
    /*
    for(k = 0;k < 16;k++){
        PC2(0, permutedChoice1Left, permutedChoice1Right, permutedChoice2Left, permutedChoice2Right, outputPC2);
        
    }
    */
    return 0;
}
