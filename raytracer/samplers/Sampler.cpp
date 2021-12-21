#include "Sampler.hpp"
#include <algorithm>
#include <random>

Sampler::Sampler(){
    camera_ptr = NULL;
    viewplane_ptr = NULL;
    count = 0;
}

Sampler::Sampler(int num_samples_) : num_samples(num_samples_), count(0) {
}

Sampler::Sampler(Camera *c_ptr, ViewPlane *v_ptr){
    camera_ptr = c_ptr;
    viewplane_ptr = v_ptr;
    count = 0;
}

void Sampler::set_num_sets(int ns){
    num_sets = ns;
    count = 0;
}

std::vector<Ray> Sampler::get_rays(int px, int py) const{
    std::vector<Ray> r;
    return r;
}

void Sampler::set_num_samples(int nsm) {
    num_samples = nsm;
}

int Sampler::get_num_samples() {
    return num_samples;
}

void Sampler::setup_shuffled_indices(){
    shuffled_indices.reserve(num_samples * num_sets);
    std::vector<int> indices;

    std::random_device rd;
    std::mt19937 g(rd());

    for (int i = 0; i < num_samples; i++){
        indices.push_back(i);
    }

    for (int j = 0; j < num_sets; j++){
        std::shuffle(indices.begin(), indices.end(), g);
        
        for (int k = 0; k < num_samples; k++)
            shuffled_indices.push_back(indices[k]);
    }
}

Point3D Sampler::sample_hemisphere(){
    if (count % num_samples == 0){
        jump = (rand() % num_sets) * num_samples;
    }

    return hemisphere_samples[jump + shuffled_indices[jump + count++ % num_samples]];
}

void Sampler::map_samples_to_hemisphere(const double exp){

    int size = samples.size();
	hemisphere_samples.reserve(num_samples * num_sets);
		
	for (int j = 0; j < size; j++) {
		double cos_phi = cos(2.0 * PI * samples[j].x);
		double sin_phi = sin(2.0 * PI * samples[j].x);	
		double cos_theta = pow((1.0 - samples[j].y), 1.0 / (exp + 1.0));
		double sin_theta = sqrt (1.0 - cos_theta * cos_theta);
		double pu = sin_theta * cos_phi;
		double pv = sin_theta * sin_phi;
		double pw = cos_theta;
		hemisphere_samples.push_back(Point3D(pu, pv, pw)); 
	}
}

