#include"aes.h"

int mode, padding;
int wordLength;
int keyword;//密钥有多少个字长
int encryptTimes;//轮数
int beforeTimes;
int keybyte;
int forming;//1：字符串 2:十六进制 3:二进制 
//列混淆运算用到的乘2函数
AES::AES() {
    plen = clen = klen = 0;
}
unsigned char AES::xtime(unsigned char input) {    // x乘法('02'乘法)

    int temp;
    temp = input << 1;

    if (input & 0x80) {
        temp ^= 0x1b;
    }

    return temp;

}

//把4X4数组转回字符串
static void convertArrayToStr(int array[4][4], char* str) {
    int i, j;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            *str++ = (char)array[j][i];
}
//把4X4数组放进十六进制存放的字符串 
static void convertArrayToStr16(unsigned char chArray[], unsigned char B[4][4], int l) {
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            chArray[l] = B[j][i];
            l++;
        }
    }
}
//列混淆运算
void AES::mixcolumn(unsigned char input[][4]) {  //列混淆

    int i, j;
    unsigned char output[4][4];

    for (j = 0; j <= 3; j++)
        for (i = 0; i <= 3; i++)
            output[i][j] = xtime(input[i % 4][j]) //0x02乘法
            ^ (input[(i + 1) % 4][j] ^ xtime(input[(i + 1) % 4][j])) //0x03乘法
            ^ input[(i + 2) % 4][j]  //0x01乘法
            ^ input[(i + 3) % 4][j]; //0x01乘法

    for (i = 0; i <= 3; i++)
        for (j = 0; j <= 3; j++)
            input[i][j] = output[i][j];

}
//行移位

void AES::shiftrow(unsigned char B[][4]) {

    int i, temp;
    temp = B[1][0];

    for (i = 0; i <= 2; i++)
        B[1][i] = B[1][i + 1];
    B[1][3] = temp;

    for (i = 0; i <= 1; i++) {

        temp = B[2][i];
        B[2][i] = B[2][i + 2];
        B[2][i + 2] = temp;

    }

    temp = B[3][3];
    for (i = 3; i >= 1; i--)
        B[3][i] = B[3][i - 1];
    B[3][0] = temp;

}
//字节变换
void AES::bytesub(unsigned char S_BOX[][16], unsigned char B[][4]) {

    register int i, j;

    for (i = 0; i <= 3; i++)
        for (j = 0; j <= 3; j++)
            B[i][j] = S_BOX[B[i][j] / 16][B[i][j] % 16];

}
//逆行移位
void AES::invshiftrow(unsigned char B[][4]) {

    int i, temp;

    temp = B[1][3];

    for (i = 3; i >= 1; i--)
        B[1][i] = B[1][i - 1];
    B[1][0] = temp;

    for (i = 0; i <= 1; i++) {
        temp = B[2][i];
        B[2][i] = B[2][i + 2];
        B[2][i + 2] = temp;
    }

    temp = B[3][0];

    for (i = 0; i <= 2; i++)
        B[3][i] = B[3][i + 1];
    B[3][3] = temp;

}
//逆列混淆运算

void AES::invmixcolum(unsigned char input[][4]) {

    int i, j;
    unsigned char output[4][4];

    for (j = 0; j < 4; j++)
        for (i = 0; i < 4; i++)
            output[i][j] = (xtime(xtime(xtime(input[i % 4][j]))) ^ xtime(xtime(input[i % 4][j])) ^ xtime(input[i % 4][j])) //0x0E乘法
            ^ (xtime(xtime(xtime(input[(i + 1) % 4][j]))) ^ xtime(input[(i + 1) % 4][j]) ^ input[(i + 1) % 4][j]) //0x0B乘法
            ^ (xtime(xtime(xtime(input[(i + 2) % 4][j]))) ^ xtime(xtime(input[(i + 2) % 4][j])) ^ input[(i + 2) % 4][j]) //0x0D乘法
            ^ (xtime(xtime(xtime(input[(i + 3) % 4][j]))) ^ input[(i + 3) % 4][j]); //0x09乘法

    for (i = 0; i <= 3; i++)
        for (j = 0; j <= 3; j++)
            input[i][j] = output[i][j];

}

//逆字节变换
void AES::invbytesub(unsigned char N_S_BOX[][16], unsigned char B[][4]) {

    register int i, j;

    for (i = 0; i <= 3; i++)
        for (j = 0; j <= 3; j++)
            B[i][j] = N_S_BOX[B[i][j] / 16][B[i][j] % 16];

}

int AES::encrypt_cbc() {

    unsigned char e, B[4][4], iv[4][4];
    unsigned char keys[4][60];
    int i, j;
    int level, padLength;

    int cArray[4][4];
    int k, l;
    memset(cipher, 0, sizeof(cipher));
    plen = strlen(plain);

    padLength = 16 - plen % 16; //需要填充多少个字符 
    for (i = plen; i < padLength + plen; i++) {
        plain[i] = (char)padLength;
    }
    plen += padLength;
    plain[plen] = '\0';


    putchar('\n');

    setKey(S_BOX, keys);

    k = 0;
    printf("加密后的密文为(16进制):\n");
    for (l = 0; l < plen; l += 16) {

        k = l;
        for (i = 0; i <= 3; i++) {
            for (j = 0; j <= 3; j++) {
                B[j][i] = getIntFromChar(plain[k]);
                k++;
            }
        }
        if (l == 0) {
            for (i = 0; i < 4; i++) {
                for (j = 0; j < 4; j++) {
                    iv[i][j] = 0;
                }
            }

        }

        xorWithiv(iv, B); //和偏移向量进行异或 

        //轮密钥加 
        for (i = 0; i <= 3; i++)
            for (j = 0; j <= 3; j++) {
                B[i][j] ^= keys[i][j];
            }

        for (level = 1; level <= beforeTimes; level++) {    //1到9轮循环
            bytesub(S_BOX, B); //字节代换 
            shiftrow(B);  //行移位 
            mixcolumn(B);  //列混合 

            //这里似乎又是轮密钥加 
            for (i = 0; i <= 3; i++)
                for (j = 0; j <= 3; j++)
                    B[i][j] ^= keys[i][level * 4 + j];
        }

        bytesub(S_BOX, B);               //第10轮循环
        shiftrow(B);

        for (i = 0; i <= 3; i++)
            for (j = 0; j <= 3; j++) {
                B[i][j] ^= keys[i][wordLength - 4 + j];
                cArray[i][j] = (int)B[i][j];
            }

        convertArrayToStr(cArray, cipher + l);

        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                iv[i][j] = B[i][j];
            }
        }
        for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++)
            {
                printf("%x ", B[j][i]);
            }
    }
    cipher[plen] = '\0';
    clen = plen;
    return 0;
}
int AES::decrypt_cbc() {

    unsigned char B[4][4], iv[4][4], bef[4][4];
    unsigned char keys[4][60];
    int temp, i, j;
    int level;

    char plain[MAXLEN];
    int cArray[4][4];
    unsigned char chArray[MAXLEN];
    int  l, k, padLength;

    memset(plain, 0, sizeof(plain));
    //keyexpansion(S_BOX, keys);
    setKey(S_BOX, keys);

    for (l = 0; l < clen; l += 16) {
        k = l;
        for (i = 0; i <= 3; i++) {
            for (j = 0; j <= 3; j++) {
                B[j][i] = getIntFromChar(cipher[k]);
                bef[j][i] = B[j][i];
                k++;
            }
        }

        if (l == 0) {
            for (i = 0; i < 4; i++) {
                for (j = 0; j < 4; j++) {
                    iv[i][j] = 0;
                }
            }
        }

        for (i = 0; i <= 3; i++)
            for (j = 0; j <= 3; j++)
                B[i][j] ^= keys[i][j + wordLength - 4];

        for (level = 1; level <= beforeTimes; level++) {

            invshiftrow(B);
            invbytesub(N_S_BOX, B);

            for (i = 0; i <= 3; i++)
                for (j = 0; j <= 3; j++)
                    B[i][j] ^= keys[i][wordLength - 4 - level * 4 + j];

            invmixcolum(B);
        }

        invshiftrow(B);
        invbytesub(N_S_BOX, B);

        for (i = 0; i <= 3; i++)
            for (j = 0; j <= 3; j++) {
                B[i][j] ^= keys[i][j];
            }

        xorWithiv(iv, B);

        for (i = 0; i <= 3; i++) {
            for (j = 0; j <= 3; j++) {
                iv[i][j] = bef[i][j];
                cArray[i][j] = (int)B[i][j];
            }
        }

        convertArrayToStr(cArray, plain + l);
    }


    padLength = (int)plain[clen - 1];
    plain[clen - padLength] = '\0';

    printf("%s", plain);
    putchar('\n');

    return 0;

}


void AES::setKeyLength(int length)
{
    keybyte = length >> 3;//密钥的字节数量
    keyword = keybyte >> 2;//已经有了多少字

    encryptTimes = keyword + 6;
    beforeTimes = encryptTimes - 1;
    wordLength = (encryptTimes + 1) << 2;//总字数，
}
void AES::setKey(unsigned char S_BOX[][16], unsigned char keys[][60]) {
    int k, i, j;
    unsigned char temp[4];
    setKeyLength(128);
    //if (mode == 1 || mode == 4) {
    //    printf("请输入16位长度密钥:\n");
    //    setKeyLength(128);
    //}

    //if (mode == 2 || mode == 5) {
    //    printf("请输入24位长度密钥:\n");
    //    setKeyLength(192);
    //}

    //if (mode == 3 || mode == 6) {
    //    printf("请输入32位长度密钥:\n");
    //    setKeyLength(256);
    //}
    convertBigInttoStr(AES_k, aes_key);

    klen = strlen(aes_key);
    for (i = klen; i < keybyte; i++) {
        aes_key[i] = 0;
    }
    aes_key[klen] = '\0';

    k = 0;
    for (i = 0; i < keyword; i++)
        for (j = 0; j <= 3; j++) {
            keys[j][i] = getIntFromChar(aes_key[k]);
            k++;
        }

    for (i = keyword; i < wordLength; i++) { //后40个word
        if (i % keyword != 0) {//不是4的倍数，word[i] = word[i-4]^word[i-1]
            for (j = 0; j < 4; j++) {
                temp[j] = keys[j][i - 1];
            }

            for (j = 0; j < 4; j++) {
                if (i % keyword == 4 && keyword > 6) {
                    temp[j] = S_BOX[temp[j] / 16][temp[j] % 16];
                }
                keys[j][i] = keys[j][i - keyword] ^ temp[j];
            }
        }

        else {//4的倍数，word[i] = word[i-4]^T(word[i-1]),T代表字节左移一位，S盒字节代换，根据轮数与轮常量进行异或
            for (j = 0; j < 4; j++) {
                temp[j] = keys[j][i - 1];
            }
            for (j = 0; j < 4; j++) {
                temp[j] = keys[(j + 1) % 4][i - 1];
                temp[j] = S_BOX[temp[j] / 16][temp[j] % 16];
                temp[j] = temp[j] ^ rcon[(i / keyword - 1)][j];
                keys[j][i] = keys[j][i - keyword] ^ temp[j];
            }

        }
    }
}
//和偏移向量进行异或
void AES::xorWithiv(unsigned char iv[4][4], unsigned char B[4][4]) {
    for (int i = 0; i <= 3; i++) {
        for (int j = 0; j <= 3; j++) {
            B[i][j] ^= iv[i][j];
        }
    }
}