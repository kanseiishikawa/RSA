#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include <cmath>
#include <numeric>
#include "RSA.h"

int main()
{
    RSA rsa;
    RSA::code_key ck = rsa.key_generate( 10000 );
    int64_t a = 1000;
    int64_t c = rsa.powmod( a, ck.public_key_1, ck.public_key_2 );
    int64_t m = rsa.powmod( c, ck.secret_key, ck.public_key_2 );
    std::cout<< "公開鍵1 " << ck.public_key_1 <<"\n";
    std::cout<< "公開鍵2 " << ck.public_key_2 <<"\n";
    std::cout<< "秘密鍵 " << ck.secret_key <<"\n";
    std::cout<< "メッセージ " << a <<"\n";
    std::cout<< "暗号化 " << c <<"\n";
    std::cout<< "復号 " << m <<"\n";
}

