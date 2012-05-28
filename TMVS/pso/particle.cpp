#include "particle.h"

using namespace PAIS;

Particle::Particle() {
    dim        = 0;
    pBest      = 0;
    pos        = 0;
    vec        = 0;
    score      = 1.7976931348623158e+308;
    pBestScore = 1.7976931348623158e+308;
}

Particle::Particle(int dim) {
    this->dim  = dim;
    pBest      = new double [dim];
    pos        = new double [dim];
    vec        = new double [dim];
    score      = 1.7976931348623158e+308;
    pBestScore = 1.7976931348623158e+308;

    for (int i = 0; i < dim; i++) {
        pBest[i] = 0;
        pos[i]   = 0;
        vec[i]   = 0;
    }
}

Particle::Particle(const Particle &p) {
    dim        = p.dim;
    pBest      = new double [p.dim];
    pos        = new double [p.dim];
    vec        = new double [p.dim];
    score      = p.score;
    pBestScore = p.pBestScore;

    for (int i = 0; i < dim; i++) {
        pBest[i] = p.pBest[i];
        pos[i]   = p.pos[i];
        vec[i]   = p.vec[i];
    }
}

Particle& Particle::operator=(const Particle &p){

    if (dim != p.dim) {
        dim = p.dim;
        if (pBest) delete [] pBest;
        if (pos)   delete [] pos;
        if (vec)   delete [] vec;
        pBest = new double [dim];
        pos   = new double [dim];
        vec   = new double [dim];
    }
            
    for (int i = 0; i < dim; i++) {
        pBest[i] = p.pBest[i];
        pos[i]   = p.pos[i];
        vec[i]   = p.vec[i];
    }

    return *this;
}

Particle::~Particle(void) {
    if (pBest) {
        delete [] pBest;
        pBest = 0;
    }
    if (pos) {
        delete [] pos;
        pos = 0;
    }
    if (vec) {
        delete [] vec;
        vec = 0;
    }
}