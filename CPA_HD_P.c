//
// Created by pd on 19/10/2021.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <omp.h>
#define char_to_hex(c) ( (toupper((c)) >= 'A' && toupper((c)) <= 'F')? toupper((c)) - 'A' + 10 : (c) - '0')

unsigned char invSBOX[256] =
        {
                0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB,
                0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB,
                0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
                0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25,
                0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92,
                0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
                0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06,
                0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B,
                0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
                0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E,
                0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B,
                0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
                0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F,
                0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF,
                0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
                0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D
        };

int table_hamming[256] =
        {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
         1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
         1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
         2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
         1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
         2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
         2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
         3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8};


int main(int argc, char *argv[]){


    FILE *fp;
    char line[34];

    fp = fopen("demo_output.txt", "r");

    //Read cipher

    int cipher[2000][16];
    int j = 0;

    while(fgets(line, 34, fp) != NULL){
        for (int i = 0; i < 16; ++i){
            cipher[j][i] = 16*char_to_hex(line[2*i]) + char_to_hex(line[2*i + 1]);
        }
        j++;
    }

    //Read traces

    float *traces[2000];
    for (int i = 0; i < 2000; i++){
        traces[i] = (float *)malloc(29000*sizeof(float));
    }

    char order[5];
    int len;
    char file_name[20];
    char buffer[20];
    //File name processing
    printf("=========================Reading traces===================\n");
    for ( int k = 0; k < 2000; k++){
        strcpy(file_name, "curves/demo_");
        sprintf(order, "%d", k);
        len = 4 - strlen(order);

        for( int t = 0; t < len; t++){
            strcat(file_name, "0");
        }
        strcat(file_name, order);
        fp = fopen(file_name, "r");
        for(int i = 0; i < 29000; i++){
            fgets(buffer, 20, fp);
            traces[k][i] = atof(buffer);
        }
        fclose(fp);
    }
    freopen("CPA_parallel_log.txt", "w", stdout);
    printf("================Done reading=====================\n");
    int N = 2000;

    int v;
    int hw;
    int hw_arr[N];
    float trace_sum[29000];
    float trace_2_sum[29000];
    float tr;
    float weight_trace;
    int weight_sum;
    int weight_2_sum;
    double correlation;
    double max_correlation;
    int g;
    int max_g;
    int max_R;


    printf("precompute\n");
    for (int i = 0; i < 29000; ++i) {
        for (int k = 0; k < N; ++k) {
            tr = traces[k][i];
            trace_sum[i] += tr;
            trace_2_sum[i] += tr*tr;
        }
    }
    printf("precompute done\n");

    time_t s, e, S, E;
    S = clock();
    for (int key_th = 0; key_th < 16; ++key_th) {
        s = clock();
        printf("========================Guessing subkey no: %d===========================\n", key_th);
#pragma omp parallel shared(max_g, max_correlation, max_R, key_th) private(g, weight_sum, weight_2_sum, v, hw, hw_arr, tr, weight_trace, correlation)
        {

#pragma omp for

            for (g = 0; g < 256; ++g) {
                printf("Compute for key: %d from thread %d\n", g, omp_get_thread_num());
                if(key_th == 0){
                    for (int R = 0; R < 256; ++R) {
                        printf("Compute for key: %d with ref state; %d\n", g, R);
                        weight_sum = 0;
                        weight_2_sum = 0;
                        for (int i = 0; i < N; ++i) {
                            v = cipher[i][key_th]^g;
                            v = invSBOX[v];
                            v = v^R;
                            hw = table_hamming[v];
                            weight_sum += hw;
                            weight_2_sum += hw*hw;
                            hw_arr[i] = hw;
                        }
                        for (int k = 0; k < 29000; ++k) {
                            weight_trace = 0;
                            for (int i = 0; i < N; ++i){
                                tr = traces[i][k];
                                weight_trace += hw_arr[i]*tr;
                            }
                            correlation = sqrt((N*weight_2_sum - weight_sum*weight_sum)*(N*trace_2_sum[k] - trace_sum[k]*trace_sum[k]));
                            correlation = fabs((N*weight_trace - weight_sum*trace_sum[k])/correlation);

                            if(correlation > max_correlation){
                                printf("Temp max key: %02X with corr: %lf with ref state: %d of instance %d\n", g, correlation, R, k);
                                max_correlation = correlation;
                                max_g = g;
                                max_R = R;
                            }

                        }

                    }
                }
                else{
                    printf("Compute for key: %d with ref state; %d\n", g, max_R);
                    weight_sum = 0;
                    weight_2_sum = 0;
                    for (int i = 0; i < N; ++i) {
                        v = cipher[i][key_th] ^ g;
                        v = invSBOX[v];
                        v = v ^ max_R;
                        hw = table_hamming[v];
                        weight_sum += hw;
                        weight_2_sum += hw * hw;
                        hw_arr[i] = hw;
                    }
                    for (int k = 0; k < 29000; ++k) {
                        weight_trace = 0;
                        for (int i = 0; i < N; ++i){
                            tr = traces[i][k];
                            weight_trace += hw_arr[i]*tr;
                        }
                        correlation = sqrt((N*weight_2_sum - weight_sum*weight_sum)*(N*trace_2_sum[k] - trace_sum[k]*trace_sum[k]));
                        correlation = fabs((N*weight_trace - weight_sum*trace_sum[k])/correlation);

                        if(correlation > max_correlation){
                            printf("Temp max key: %02X with corr: %lf with ref state: %d of instance %d\n", g, correlation, max_R, k);
                            max_correlation = correlation;
                            max_g = g;
                        }

                    }

                }

            }
            printf("Guessed subkey: %02X correlation: %lf with ref state: %d\n", max_g, max_correlation, max_R);
        }
        e = clock();
        printf("Final guess for subkey no.%d is %02X correlation %lf, ref state: %d in time: %ld\n", key_th, max_g, max_correlation, max_R, (e-s)/CLOCKS_PER_SEC);
    }
    E = clock();
    printf("Total execution time for all subkeys: %ld\n", (E-S)/CLOCKS_PER_SEC);
    fclose(stdout);
    return 0;
}

