#pragma once 

#include "Sampler.hpp"

class MultiJittered : public Sampler {
    public:
        MultiJittered();

        MultiJittered(int num_samples);

        MultiJittered(const MultiJittered &);

        MultiJittered &operator=(const MultiJittered &);

        ~MultiJittered() = default;

    private:
        virtual void generate_samples();
};