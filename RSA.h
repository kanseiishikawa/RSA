#ifndef RSA_H
#define RSA_H

class RSA
{
 public:
    struct code_key
    {
        long int public_key_1;
        long int public_key_2;
        long int secret_key;
    };

    code_key key_generate( long int security_value );
    long int powmod( long int msg, long int exp, long int mod );//暗号化と復号を冪剰余を用いて行う
    //msgは暗号化か復号化したいもの
    //暗号化 exp = public_key1, mod = public_key2
    //復号 exp = secret_key, mod = public_key2

 private:
    long int prime_number_seach( long int standard );//初期の素数を生成する
    long int extEuqlid( long int a, long int b );//拡張ユーグリッド互除法を用いて秘密鍵を生成する
    long int lcm( long int x, long int y );//最大公約数を求める
    long int gcd( long int x, long int y );//最小公倍数を求める


};
#endif
