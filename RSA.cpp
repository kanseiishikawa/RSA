#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include <cmath>
#include <numeric>

struct code_key
{
    int64_t public_key_1;
    int64_t public_key_2;
    int64_t secret_key;
};

code_key key_generate( int64_t security_value );
int64_t powmod( int64_t msg, int64_t exp, int64_t mod );//暗号化と復号を冪剰余を用いて行う
//msgは暗号化か復号化したいもの
//暗号化 exp = public_key1, mod = public_key2
//復号 exp = secret_key, mod = public_key2
int64_t prime_number_seach( int64_t standard );//初期の素数を生成する
int64_t extEuqlid( int64_t a, int64_t b );//拡張ユーグリッド互除法を用いて秘密鍵を生成する
int64_t lcm( int64_t x, int64_t y );//最大公約数を求める
int64_t gcd( int64_t x, int64_t y );//最小公倍数を求める

int main()
{
    code_key ck = key_generate( 10000 );
    int64_t a = 1000;
    int64_t c = powmod( a, ck.public_key_1, ck.public_key_2 );
    int64_t m = powmod( c, ck.secret_key, ck.public_key_2 );
    std::cout<< "公開鍵1 " << ck.public_key_1 <<"\n";
    std::cout<< "公開鍵2 " << ck.public_key_2 <<"\n";
    std::cout<< "秘密鍵 " << ck.secret_key <<"\n";
    std::cout<< "メッセージ " << a <<"\n";
    std::cout<< "暗号化 " << c <<"\n";
    std::cout<< "復号 " << m <<"\n";
}

//公開鍵と秘密鍵の生成を行う
code_key key_generate( int64_t security_value )
{
    std::srand( time(NULL) );
    code_key ck;
    int64_t prime_number1 = prime_number_seach( ( rand() % security_value ) + security_value );
    int64_t prime_number2 = prime_number_seach( ( rand() % security_value ) + security_value );

    ck.public_key_1 = 65537;
    ck.public_key_2 = prime_number1 * prime_number2;
    
    int64_t L = lcm( prime_number1 - 1, prime_number2 - 1 );
    
    ck.secret_key = extEuqlid( ck.public_key_1 , L);
    
    return ck;
}

int64_t powmod( int64_t msg, int64_t exp, int64_t mod )
{
    int64_t result = 1;

    while( exp > 0 )
    {
        if( ( exp & 1 ) == 1 )
        {
            result = ( result * msg ) % mod;
        }

        exp >>= 1;
        msg = ( msg * msg ) % mod;
    }

    return result;
}

//拡張ユーグリッド互除法
int64_t extEuqlid( int64_t a, int64_t b )
{
    int64_t x1 = 0, y1 = 1, r1 = b;
    int64_t x2 = 1, y2 = 0, r2 = a;

    int64_t d;

    while( true )
    {
        
        int64_t q = r1 / r2;
        int64_t r = r1 % r2;
        int64_t x = x1 - x2 * q;
        int64_t y = y1 - y2 * q;

        if( r == 0 )
        {
            d = x2;
            break;
        }

        x1 = x2; y1 = y2; r1 = r2;
        x2 =  x; y2 =  y; r2 =  r;
    }

    while( d <= 0 )
    {
        d += b;
    }
  
    return d;
}

int64_t prime_number_seach( int64_t standard )
{
    bool discover = false;
    standard = abs( standard );
    
    while( !discover )
    {
        bool check = true;
        
        if( standard % 2 != 0 )
        {
            for( int64_t i = 3; i < sqrt( standard ); i += 2)
            {
                if( standard % i == 0 )
                {
                    check = false;
                    break;
                }
            }

            if( check )
            {
                discover = true;
            }
        }

        if( !discover )
        {
            standard += 1;
        }
    }

    return standard;
}

int64_t gcd( int64_t x, int64_t y )
{
    int64_t min = ( x < y ) ? x : y;
    int64_t max = ( x < y ) ? y : x;
    
    while( 1 )
    {
        int64_t mod = max % min;
        
        if( mod == 0 )
        {
            return min;
        }

        max = min;
        min = mod;
    }
    
    return 1;
}

int64_t lcm( int64_t x, int64_t y )
{
    return ( x * y ) / gcd( x, y );
}




