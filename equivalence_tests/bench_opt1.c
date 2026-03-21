/* bench_opt1.c — Speed benchmark for Option 1 (hand-crafted C) */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "shufflenet_v2.h"
#ifdef __APPLE__
#include <mach/mach_time.h>
static double get_ms(void) {
    static double s=0;
    if(s==0){mach_timebase_info_data_t i;mach_timebase_info(&i);s=(double)i.numer/i.denom/1e6;}
    return mach_absolute_time()*s;
}
#endif

#define TRIALS 7
#define ITERS 100
#define WARMUP 10

static int dcmp(const void*a,const void*b){double d=*(double*)a-*(double*)b;return(d>0)-(d<0);}

int main(void) {
    float *in = calloc(150528, sizeof(float));
    float out[1000];
    srand(42);
    for(int i=0;i<150528;i++) in[i]=((float)rand()/RAND_MAX-0.5f)*2.0f;

    ShuffleNetV2 *model = sn2_create_model();
    if (!model) { printf("Failed to create model\n"); return 1; }

    if (sn2_load_weights(model, "option1_handcrafted_c/weights.bin") != 0)
        if (sn2_load_weights(model, "../option1_handcrafted_c/weights.bin") != 0)
            if (sn2_load_weights(model, "weights.bin") != 0) {
                printf("ERROR: Cannot find weights.bin\n"); return 1;
            }

    SN2Workspace ws;
    sn2_workspace_init(&ws, NULL, 0);  /* auto-allocate */

    printf("Option 1 (Hand-Crafted C): %d trials x %d iters (+%d warmup)\n", TRIALS, ITERS, WARMUP);
    for(int w=0;w<WARMUP;w++) sn2_forward(model, in, out, &ws);

    double all[TRIALS*ITERS]; int idx=0;
    double tmeans[TRIALS];
    for(int t=0;t<TRIALS;t++){
        double times[ITERS],sum=0;
        for(int i=0;i<ITERS;i++){
            double t0=get_ms();
            sn2_forward(model, in, out, &ws);
            times[i]=get_ms()-t0;
            sum+=times[i];
        }
        tmeans[t]=sum/ITERS;
        qsort(times,ITERS,8,dcmp);
        printf("  Trial %d: mean=%.2f min=%.2f median=%.2f max=%.2f ms\n",
            t+1,tmeans[t],times[0],times[ITERS/2],times[ITERS-1]);
        for(int i=0;i<ITERS;i++) all[idx++]=times[i];
    }
    qsort(all,idx,8,dcmp);
    double s=0,s2=0; for(int i=0;i<idx;i++){s+=all[i];s2+=all[i]*all[i];}
    double mean=s/idx, std_dev=sqrt(s2/idx-mean*mean);
    printf("\nRESULT: mean=%.2f std=%.2f median=%.2f min=%.2f max=%.2f ms (%d measurements)\n",
        mean,std_dev,all[idx/2],all[0],all[idx-1],idx);
    printf("Throughput: %.1f inferences/sec\n",1000.0/mean);
    double ts=0,ts2=0; for(int t=0;t<TRIALS;t++){ts+=tmeans[t];ts2+=tmeans[t]*tmeans[t];}
    printf("Trial means: %.2f +/- %.2f ms\n",ts/TRIALS,sqrt(ts2/TRIALS-(ts/TRIALS)*(ts/TRIALS)));

    int top=0;for(int i=1;i<1000;i++)if(out[i]>out[top])top=i;
    printf("Sanity: top1=class %d (%.3f)\n",top,out[top]);

    sn2_workspace_free(&ws);
    sn2_destroy_model(model);
    free(in);
    return 0;
}
