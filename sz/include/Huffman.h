/**
 *  @file Huffman.h
 *  @author Sheng Di
 *  @date Aug., 2016
 *  @brief Header file for the exponential segment constructor.
 *  (C) 2016 by Mathematics and Computer Science (MCS), Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
 */

#ifndef _Huffman_H
#define _Huffman_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h> 
//Note: when changing the following settings, intvCapacity in sz.h should be changed as well.
//#define allNodes 131072
//#define stateNum 65536

typedef struct node_t {
	struct node_t *left, *right;
	size_t freq;
	char t; //in_node:0; otherwise:1
	unsigned int c;
} *node;

extern int stateNum;
extern int allNodes;

//for multi-thread version (in the future), these global variables must be carefully handled
//e.g., share by passing addresses instead. 
//extern struct node_t pool[allNodes];
extern struct node_t* pool;
extern node *qqq, *qq;
extern int n_nodes, qend; //n_nodes is for compression
extern unsigned long **code;
extern unsigned char *cout;
extern int n_inode; //n_inode is for decompression

node new_node(size_t freq, unsigned int c, node a, node b);
node new_node2(unsigned int c, unsigned char t);
void qinsert(node n);
node qremove();
void build_code(node n, int len, unsigned long out1, unsigned long out2);
void init(int *s, size_t length);
void encode(int *s, size_t length, unsigned char *out, size_t *outSize);
void decode(unsigned char *s, size_t targetLength, node t, int *out);
void pad_tree_uchar(unsigned char* L, unsigned char* R, unsigned int* C, unsigned char* t, unsigned int i, node root);
void pad_tree_ushort(unsigned short* L, unsigned short* R, unsigned int* C, unsigned char* t, unsigned int i, node root);
void pad_tree_uint(unsigned int* L, unsigned int* R, unsigned int* C, unsigned char* t, unsigned int i, node root);
unsigned int convert_HuffTree_to_bytes_anyStates(int nodeCount, unsigned char** out);
void unpad_tree_uchar(unsigned char* L, unsigned char* R, unsigned int* C, unsigned char *t, unsigned int i, node root);
void unpad_tree_ushort(unsigned short* L, unsigned short* R, unsigned int* C, unsigned char* t, unsigned int i, node root);
void unpad_tree_uint(unsigned int* L, unsigned int* R, unsigned int* C, unsigned char* t, unsigned int i, node root);
node reconstruct_HuffTree_from_bytes_anyStates(unsigned char* bytes, int nodeCount);
void encode_withTree(int *s, size_t length, unsigned char **out, size_t *outSize);
void decode_withTree(unsigned char *s, size_t targetLength, int *out);
void SZ_ReleaseHuffman();

#ifdef __cplusplus
}
#endif

#endif
