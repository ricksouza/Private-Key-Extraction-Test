/*
 * main.cpp
 *
 *  Created on: Aug 12, 2013
 *      Author: rick
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pbc/pbc.h>

void open_file(long lSize, size_t result, FILE* f_share1, char** c_share1) {

	fseek(f_share1, 0, SEEK_END);
	lSize = ftell(f_share1);
	rewind(f_share1);
	// allocate memory to contain the whole file:
	*c_share1 = (char*) (malloc(sizeof(char) * lSize));
	if (*c_share1 == NULL) {
		fputs("Memory error", stderr);
		exit(2);
	}
	// copy the file into the share_buffer:
	result = fread(*c_share1, 1, lSize, f_share1);
	if (result != lSize) {
		fputs("Reading error", stderr);
		exit(3);
	}
	/* the whole file is now loaded in the memory share_buffer. */
	// terminate
	fclose(f_share1);
}

int main(){

	FILE *f_share1;
	FILE *f_share2;
	FILE *f_share3;
	FILE *f_share4;
	FILE *f_private_key1;
	FILE *f_private_key2;
	FILE *f_private_key3;
	FILE *f_private_key4;
	FILE *f_public_key1;
	FILE *f_public_key2;
	FILE *f_public_key3;
	FILE *f_public_key4;
	FILE *f_pairing;

	long lSize1;
	long lSize2;
	long lSize3;
	long lSize4;
	long lSize5;

	char *c_share1;
	char *c_share2;
	char *c_share3;
	char *c_share4;
	char *c_private_key1;
	char *c_private_key2;
	char *c_private_key3;
	char *c_private_key4;
	char *c_public_key1;
	char *c_public_key2;
	char *c_public_key3;
	char *c_public_key4;

	char *c_pairing;

	size_t result;

	printf("Começou \n");

	f_share1 = fopen("shares/share1", "r");
	f_share2 = fopen("shares/share2", "r");
	f_share3 = fopen("shares/share3", "r");
	f_share4 = fopen("shares/share4", "r");
	f_private_key1 = fopen("keys/keys1", "r");
	f_private_key2 = fopen("keys/keys2", "r");
	f_private_key3 = fopen("keys/keys3", "r");
	f_private_key4 = fopen("keys/keys4", "r");
	f_public_key1 = fopen("keys/pub1", "r");
	f_public_key2 = fopen("keys/pub2", "r");
	f_public_key3 = fopen("keys/pub3", "r");
	f_public_key4 = fopen("keys/pub4", "r");
	f_pairing = fopen("pairing.param", "r");

	open_file(lSize1, result, f_share1, &c_share1);
	open_file(lSize2, result, f_share2, &c_share2);
	open_file(lSize3, result, f_share3, &c_share3);
	open_file(lSize4, result, f_share4, &c_share4);
	open_file(lSize1, result, f_private_key1, &c_private_key1);
	open_file(lSize2, result, f_private_key2, &c_private_key2);
	open_file(lSize3, result, f_private_key3, &c_private_key3);
	open_file(lSize4, result, f_private_key4, &c_private_key4);
	open_file(lSize1, result, f_public_key1, &c_public_key1);
	open_file(lSize2, result, f_public_key2, &c_public_key2);
	open_file(lSize3, result, f_public_key3, &c_public_key3);
	open_file(lSize4, result, f_public_key4, &c_public_key4);
	open_file(lSize5, result, f_pairing, &c_pairing);

	char *tokenId1;
	char *tokenId2;
	char *tokenId3;
	char *tokenId4;

	tokenId1 = strtok(c_share1, ":");
	tokenId2 = strtok(c_share2, ":");
	tokenId3 = strtok(c_share3, ":");
	tokenId4 = strtok(c_share4, ":");

	element_ptr indices[4];
	element_ptr coeffs[4];
	//vector <G1> shares;

	pairing_t pairing;

	pairing_init_set_buf(pairing, c_pairing, result);

//	indices.push_back(Zr(e, tokenId1));
//	indices.push_back(Zr(e, tokenId2));
//	indices.push_back(Zr(e, tokenId3));
//	indices.push_back(Zr(e, tokenId4));

	element_t Did1;
	element_t Did2;
	element_t Did3;
	element_t Did4;
	element_t Ppub1;
	element_t Ppub2;
	element_t Ppub3;
	element_t Ppub4;
	element_t num;
	element_t den;
	element_t ind1;
	element_t ind2;
	element_t ind3;
	element_t ind4;
	element_t alpha;
	element_t temp1;
	element_t temp2;
	element_t temp3;
	element_t priv_key;
	element_t public_key;

	element_init_G1(Did1, pairing);
	element_init_G1(Did2, pairing);
	element_init_G1(Did3, pairing);
	element_init_G1(Did4, pairing);
	element_init_G1(Ppub1, pairing);
	element_init_G1(Ppub2, pairing);
	element_init_G1(Ppub3, pairing);
	element_init_G1(Ppub4, pairing);
	element_init_G1(priv_key, pairing);
	element_init_G1(public_key, pairing);
	element_init_G1(temp2, pairing);
	element_init_G1(temp3, pairing);

	element_init_Zr(num, pairing);
	element_init_Zr(den, pairing);

	element_init_Zr(ind1, pairing);
	element_set_si(ind1, (signed long int)tokenId1);

	element_init_Zr(ind2, pairing);
	element_set_si(ind2, (signed long int)tokenId2);

	element_init_Zr(ind3, pairing);
	element_set_si(ind3, (signed long int)tokenId3);

	element_init_Zr(ind4, pairing);
	element_set_si(ind4, (signed long int)tokenId4);

	element_init_Zr(temp1, pairing);
	element_init_Zr(alpha, pairing);

	indices[0] = ind1;
	indices[1] = ind2;
	indices[2] = ind3;
	indices[3] = ind4;

	element_set_str(Did1, c_private_key1, 10);
	element_set_str(Did2, c_private_key2, 10);
	element_set_str(Did3, c_private_key3, 10);
	element_set_str(Did4, c_private_key4, 10);

	element_set_str(Ppub1, c_public_key1, 10);
	element_set_str(Ppub2, c_public_key2, 10);
	element_set_str(Ppub3, c_public_key3, 10);
	element_set_str(Ppub4, c_public_key4, 10);


	int i = 0;
	int j = 0;

	for(i =0; i < 4; i++){
		element_set1(num);
		element_set1(den);
		element_set1(temp1);
		element_set1(alpha);
		for(j = 0; j < 4; j++){
			if(j == i)	continue;
			//element_sub(num, indices[j], alpha);
			//element_mul(num, num, temp1);

			element_sub(den, indices[j], indices[i]);
			//element_div(temp1, indices[j], temp1);
			element_div(num, indices[j], den);
			element_mul(temp1, temp1, num);
		}
		//element_div(temp1, num, den);
		coeffs[i] = temp1;
	}


	element_set0(priv_key);
	element_set0(public_key);

	//element_pow_zn(temp2, Did1, coeffs[0]);
	//element_pow_zn(temp3, Ppub1, coeffs[0]);

	element_mul(temp2, Did1, coeffs[0]);
	element_mul(temp3, Ppub1, coeffs[0]);

	element_add(priv_key, priv_key, temp2);
	element_add(public_key, public_key, temp3);

	//element_mul(priv_key, priv_key, temp2);
	//element_mul(public_key, public_key, temp3);

	//element_pow_zn(temp2, Did2, coeffs[1]);
	//element_pow_zn(temp3, Ppub2, coeffs[1]);

	element_mul(temp2, Did2, coeffs[1]);
	element_mul(temp3, Ppub2, coeffs[1]);

	element_add(priv_key, priv_key, temp2);
	element_add(public_key, public_key, temp3);

	//element_mul(priv_key, priv_key, temp2);
	//element_mul(public_key, public_key, temp3);

	element_mul(temp2, Did3, coeffs[2]);
	element_mul(temp3, Ppub3, coeffs[2]);

	//element_pow_zn(temp2, Did3, coeffs[2]);
	//element_pow_zn(temp3, Ppub3, coeffs[2]);

	element_add(priv_key, priv_key, temp2);
	element_add(public_key, public_key, temp3);

	//element_mul(priv_key, priv_key, temp2);
	//element_mul(public_key, public_key, temp3);

	//element_pow_zn(temp2, Did4, coeffs[3]);
	element_mul(temp2, Did4, coeffs[3]);
	element_mul(temp3, Ppub4, coeffs[3]);

//	element_mul(priv_key, priv_key, temp2);
//	element_mul(public_key, public_key, temp3);

	element_add(priv_key, priv_key, temp2);
	element_add(public_key, public_key, temp3);

	//Zr alpha(e,(long)0);
	//vector<Zr> coeffs = lagrange_coeffs(indices, alpha);
	//G1 user_private_key = lagrange_apply(coeffs, shares);

	FILE *f_priv_key;
	FILE *f_pub_key;

	f_priv_key = fopen("priv_key1", "w");
	f_pub_key = fopen("pub_key1", "w");

	element_out_str(f_priv_key, 10, priv_key);
	element_out_str(f_pub_key, 10, public_key);

	fclose(f_priv_key);
	fclose(f_pub_key);

	printf("Terminou \n");

	return 0;
}
