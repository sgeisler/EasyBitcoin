//
// Created by Sebastian on 24.05.2015.
//

#ifndef EASYBITCOIN_CONSTANTS_H
#define EASYBITCOIN_CONSTANTS_H

#define EC_PRIVATE_KEY_LENGTH 32
#define EC_PUBLIC_KEY_LENGTH 65
#define EC_COMPRESSED_PUBLIC_KEY_LENGTH 33

//OP codes
#define OP_FALSE        0x00
#define OP_PUSH_BEGIN   0x01
#define OP_PUSH_END     0x4b
#define OP_PUSHDATA1    0x4c
#define OP_PUSHDATA2    0x4d
#define OP_PUSHDATA4    0x4e
#define OP_1NEGATE      0x4f
#define OP_TRUE         0x51
#define OP_2            0x52
#define OP_16           0x60

#define OP_NOP          0x61
#define OP_IF           0x63
#define OP_NOTIF        0x64
#define OP_ELSE         0x67
#define OP_ENDIF        0x68
#define OP_VERIFY       0x69
#define OP_RETURN       0x6a

#define OP_TOALTSTACK   0x6b
#define OP_FROMALTSTACK 0x6c
#define OP_IFDUP        0x73
#define OP_DEPTH        0x74
#define OP_DROP         0x75
#define OP_DUP          0x76
#define OP_NIP          0x77
#define OP_OVER         0x78
#define OP_PICK         0x79
#define OP_ROLL         0x7a
#define OP_ROT          0x7b
#define OP_SWAP         0x7c
#define OP_TUCK         0x7d
#define OP_2DROP        0x6d
#define OP_2DUP         0x6e
#define OP_3DUP         0x6f
#define OP_2OVER        0x70
#define OP_2ROT         0x71
#define OP_2SWAP        0x72



#define OP_HASH160      0xa9
#define OP_EQUAL        0x87
#define OP_EQUALVERIFY  0x88
#define OP_CHECKSIG     0xac

#endif //EASYBITCOIN_CONSTANTS_H
