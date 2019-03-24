#ifndef RSA_H
#define RSA_H

class RSA
{
 public:
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

 private:
    int64_t prime_number_seach( int64_t standard );//初期の素数を生成する
    int64_t extEuqlid( int64_t a, int64_t b );//拡張ユーグリッド互除法を用いて秘密鍵を生成する
    int64_t lcm( int64_t x, int64_t y );//最大公約数を求める
    int64_t gcd( int64_t x, int64_t y );//最小公倍数を求める


};
#endif
