#include "MultiJittered.hpp"
#include <math.h>

MultiJittered::MultiJittered(): Sampler(){
}

MultiJittered::MultiJittered(int num_samples) : Sampler(num_samples){
}

MultiJittered::MultiJittered(const MultiJittered& other): Sampler(other) {
}

MultiJittered &MultiJittered::operator=(const MultiJittered &rhs){
    Sampler::operator=(rhs);
    return *this;
}

void MultiJittered::generate_samples(){
    int n = (int) sqrt((double) num_samples);
    double cell_width =  1.0 /(double)num_samples;

    Point3D fill_point;
    for (int i=0; i < num_samples * num_sets; i++)
        samples.push_back(fill_point);
    
    for (int i=0; i < num_sets; i++){
        for (int j=0; j < n; j++){
            for (int k=0; k < n; k++){
                int a = rand() % (n-1) + k;
                samples[j * n + k + i * num_samples].x = (j * n + k) * cell_width + static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
                samples[j * n + a + i * num_samples].y = (k * n + j) * cell_width + static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
            }
        }
    }

    for (int i=0; i < num_sets; i++){
        for (int j=0; j < n; j++){
            for (int k=0; k < n; k++){
                int a = rand() % (n-1) + k;
                double t = samples[j * n + k + i * num_samples].x;
                samples[j * n + k + i * num_samples].x = samples[j * n + a + i * num_samples].x;
                samples[j * n + a + i * num_samples].x = t;
            }
        }
    }

    for (int i=0; i < num_sets; i++){
        for (int j=0; j < n; j++){
            for (int k=0; k < n; k++){
                int a = rand() % (n-1) + k;
                double t = samples[k * n + j + i * num_samples].y;
                samples[k * n + j + i * num_samples].y = samples[a * n + j + i * num_samples].y;
                samples[a * n + j + i * num_samples].y = t;
            }
        }
    }

}
