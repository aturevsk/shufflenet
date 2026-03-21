#!/bin/bash
# run_c_benchmark.sh — Compile and run 7x100 C speed benchmark for Options 2 and 4
# (Using 100 iters per trial instead of 1000 since each inference takes ~50ms)
set -e
cd "$(dirname "$0")/.."
MATLAB_INC="/Applications/MATLAB_R2026a.app/extern/include"

cat > /tmp/bench_shufflenet.c << 'CEOF'
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#ifdef __APPLE__
#include <mach/mach_time.h>
static double get_ms(void) {
    static double s=0;
    if(s==0){mach_timebase_info_data_t i;mach_timebase_info(&i);s=(double)i.numer/i.denom/1e6;}
    return mach_absolute_time()*s;
}
#else
#include <time.h>
static double get_ms(void){struct timespec t;clock_gettime(CLOCK_MONOTONIC,&t);return t.tv_sec*1000.0+t.tv_nsec/1e6;}
#endif

#if OPT==2
#include "mInvoke_shufflenet.h"
#include "mInvoke_shufflenet_initialize.h"
#include "mInvoke_shufflenet_terminate.h"
#define INIT() mInvoke_shufflenet_initialize()
#define RUN(i,o) mInvoke_shufflenet(i,o)
#define DONE() mInvoke_shufflenet_terminate()
#elif OPT==4
#include "predict_shufflenet_onnx.h"
#include "predict_shufflenet_onnx_initialize.h"
#include "predict_shufflenet_onnx_terminate.h"
#define INIT() predict_shufflenet_onnx_initialize()
#define RUN(i,o) predict_shufflenet_onnx(i,o)
#define DONE() predict_shufflenet_onnx_terminate()
#endif

#define TRIALS 7
#define ITERS 100
#define WARMUP 10

static int dcmp(const void*a,const void*b){double d=*(double*)a-*(double*)b;return(d>0)-(d<0);}

int main(void){
    float *in=calloc(150528,4); float out[1000];
    srand(42); for(int i=0;i<150528;i++) in[i]=((float)rand()/RAND_MAX-0.5f)*2.0f;
    INIT();
    printf("Option %d: %d trials x %d iters (+%d warmup)\n",OPT,TRIALS,ITERS,WARMUP);
    for(int w=0;w<WARMUP;w++) RUN(in,out);
    double all[TRIALS*ITERS]; int idx=0;
    double tmeans[TRIALS];
    for(int t=0;t<TRIALS;t++){
        double times[ITERS],sum=0;
        for(int i=0;i<ITERS;i++){double t0=get_ms();RUN(in,out);times[i]=get_ms()-t0;sum+=times[i];}
        tmeans[t]=sum/ITERS;
        qsort(times,ITERS,8,dcmp);
        printf("  Trial %d: mean=%.2f std=%.2f min=%.2f median=%.2f max=%.2f ms\n",
            t+1,tmeans[t],0.0,times[0],times[ITERS/2],times[ITERS-1]);
        for(int i=0;i<ITERS;i++) all[idx++]=times[i];
    }
    qsort(all,TRIALS*ITERS,8,dcmp);
    double s=0,s2=0; for(int i=0;i<idx;i++){s+=all[i];s2+=all[i]*all[i];}
    double mean=s/idx, std=sqrt(s2/idx-mean*mean);
    printf("\nRESULT: mean=%.2f std=%.2f median=%.2f min=%.2f max=%.2f ms (%d measurements)\n",
        mean,std,all[idx/2],all[0],all[idx-1],idx);
    printf("Throughput: %.1f inferences/sec\n",1000.0/mean);
    // Trial-level stats
    double ts=0,ts2=0; for(int t=0;t<TRIALS;t++){ts+=tmeans[t];ts2+=tmeans[t]*tmeans[t];}
    printf("Trial means: %.2f +/- %.2f ms\n",ts/TRIALS,sqrt(ts2/TRIALS-(ts/TRIALS)*(ts/TRIALS)));
    int top=0;for(int i=1;i<1000;i++)if(out[i]>out[top])top=i;
    printf("Sanity: top1=class %d (%.3f)\n",top,out[top]);
    DONE(); free(in);
    return 0;
}
CEOF

echo "=== Compiling Option 2 ==="
gcc -O3 -std=c99 -ffast-math -o /tmp/bench2 /tmp/bench_shufflenet.c \
    option2_pytorch_coder/embeddedOutputDir/mInvoke_shufflenet.c \
    option2_pytorch_coder/embeddedOutputDir/mInvoke_shufflenet_initialize.c \
    option2_pytorch_coder/embeddedOutputDir/mInvoke_shufflenet_terminate.c \
    option2_pytorch_coder/embeddedOutputDir/mInvoke_shufflenet_data.c \
    -lm -Ioption2_pytorch_coder/embeddedOutputDir -I"$MATLAB_INC" -DOPT=2

echo "=== Compiling Option 4 ==="
gcc -O3 -std=c99 -ffast-math -o /tmp/bench4 /tmp/bench_shufflenet.c \
    option4_onnx_import/embeddedDir/predict_shufflenet_onnx.c \
    option4_onnx_import/embeddedDir/callPredict.c \
    option4_onnx_import/embeddedDir/conv2dDirectOptimizedColMajor.c \
    option4_onnx_import/embeddedDir/mean.c \
    option4_onnx_import/embeddedDir/permute.c \
    option4_onnx_import/embeddedDir/predict_shufflenet_onnx_initialize.c \
    option4_onnx_import/embeddedDir/predict_shufflenet_onnx_terminate.c \
    option4_onnx_import/embeddedDir/predict_shufflenet_onnx_rtwutil.c \
    option4_onnx_import/embeddedDir/Shape_To_SliceLayer1000.c \
    option4_onnx_import/embeddedDir/Shape_To_SliceLayer1004.c \
    option4_onnx_import/embeddedDir/Shape_To_SliceLayer1012.c \
    -lm -Ioption4_onnx_import/embeddedDir -I"$MATLAB_INC" -DOPT=4

echo ""
echo "=== Running Option 2 (7x100) ==="
cd option2_pytorch_coder && /tmp/bench2 && cd ..

echo ""
echo "=== Running Option 4 (7x100) ==="
cd option4_onnx_import && /tmp/bench4 && cd ..

echo ""
echo "=== Binary sizes ==="
ls -lh /tmp/bench2 /tmp/bench4
