#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include <cmath>
#include <numeric>
#include "RSA.h"

//公開鍵と秘密鍵の生成を行う
RSA::code_key
RSA::key_generate( long int security_value )
{
    std::srand( time(NULL) );
    code_key ck;
    long int prime_number1 = prime_number_seach( ( rand() % security_value ) + security_value );
    long int prime_number2 = prime_number_seach( ( rand() % security_value ) + security_value );
    std::cout<< "素数1 " << prime_number1 <<"\n";
    std::cout<< "素数2 " << prime_number2 <<"\n";
    ck.public_key_1 = 65537;
    ck.public_key_2 = prime_number1 * prime_number2;
    
    long int L = lcm( prime_number1 - 1, prime_number2 - 1 );
    
    ck.secret_key = extEuqlid( ck.public_key_1 , L);
    
    return ck;
}

long int
RSA::powmod( long int msg, long int exp, long int mod )
{
    long int result = 1;
    
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
long int
RSA::extEuqlid( long int a, long int b )
{
    long int x1 = 0, y1 = 1, r1 = b;
    long int x2 = 1, y2 = 0, r2 = a;

    long int d;

    while( true )
    {
        
        long int q = r1 / r2;
        long int r = r1 % r2;
        long int x = x1 - x2 * q;
        long int y = y1 - y2 * q;

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

long int
RSA::prime_number_seach( long int standard )
{
    bool discover = false;
    standard = abs( standard );
    
    while( !discover )
    {
        bool check = true;
        
        if( standard % 2 != 0 )
        {
            for( long int i = 3; i < sqrt( standard ); i += 2)
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

long int
RSA::gcd( long int x, long int y )
{
    long int min = ( x < y ) ? x : y;
    long int max = ( x < y ) ? y : x;
    
    while( 1 )
    {
        long int mod = max % min;
        
        if( mod == 0 )
        {
            return min;
        }

        max = min;
        min = mod;
    }
    
    return 1;
}

long int
RSA::lcm( long int x, long int y )
{
    return ( x * y ) / gcd( x, y );
}




