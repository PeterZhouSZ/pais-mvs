#ifndef __PAIS_PSO_SOLVER_H__
#define __PAIS_PSO_SOLVER_H__

#include <vector>
#include <algorithm>
#include <time.h>

// include openMP
#include <omp.h>

#include "particle.h"

using namespace std;
using namespace PAIS;

namespace PAIS {
	// container for local best
	struct LocalParticle {
		// distance from pbest to current position 
		double dist; 
		// pbest holder
		const Particle *p;
	};

	class PsoSolver {
	private:
		// sorter for using Local Best
        static bool sortLocalParticle (const LocalParticle &i, const LocalParticle &j);

		// dimension of problem space
		int dim;

		// number of iteration
        int iteration;

		// max number of iteration
        int maxIteration;

		// number of particle
		int particleNum;

		// DispersionIDX and VelocityIDX convergence threshold
        double convergenceThreshold;

		// particle container
		vector<Particle> particles;

		// upper and lower range
        double *rangeL;
        double *rangeU;
        double *rangeInter; // rangeU - rangeL
		
		// global best
        const double *gBest;
        double gBestFitness;
        int    gBestIteration;

		// velocity weight
        double iw; // inertia weight  (Basic-PSO)
        double pw; // pBest weight    (Basic-PSO)
        double gw; // gBest weight    (Basic-PSO)
		double lw; // lBest weight    (GLN-PSO)
		double nw; // nBest weight    (GLN-PSO)
	
		// local best K nearest neighbor (GLN-PSO)
		int localK;

		// flag for using GLN-PSO
		bool enableGLNPSO;

		// fitness function
        double (*getFitness)(const Particle &p, void *obj);
		// bundled object for fitness function
		void *obj;

		// set random seed to current time and thread
		void setRandomSeed() const;
		// return uniform random number [0, 1]
        inline double random();

		// PSO convergence index
		double getDispersionIDX() const;
		double getVelocityIDX()   const;

		// set initial particle position and velocity
		void initParticles();

		// set initial particle fitness
		void initFitness();

		// update particle fitness
		void updateFitness();

		// move particle
		void moveParticles();

		// update gbest
		void updateGbest();

		const double* getLocalBest(const int idx) const;

		void setNearNeighborBest(const int idx);
	public:
		PsoSolver(const int dim, 
			      const double *rangeL, const double *rangeU, 
				  double (*getFitness)(const Particle &p, void *obj) = NULL, 
				  void *obj = NULL,
				  int maxIteration = 1000, int particleNum = 30,
				  double convergenceThreshold = 0.01, 
				  double iw = 0.8, double pw = 1.2, double gw = 1.5, double lw = 1.0, double nw = 1.0,
				  int localK = 5);

        ~PsoSolver(void);

		bool setParticle(const double *pos, const double *vec = NULL, const int idx = 0);
		void run(const bool enableGLNPSO = false, const double minIw = 0.4);

		int           getDimension()      const { return dim; }
		int           getParticleNum()    const { return particleNum; }
        int           getMaxIteration()   const { return maxIteration; }
        double        getInertiaWeight()  const { return iw; }
        double        getPbestWeight()    const { return pw; }
        double        getGbestWeight()    const { return gw; }
		double        getLbestWeight()    const { return lw; }
		double        getNbestWeight()    const { return nw; }
        const double* getGbest()          const { return gBest; }
        const double* getRangeL()         const { return rangeL; }
        const double* getRangeU()         const { return rangeU; }
		double        getGbestFitness()   const { return gBestFitness; }
        int           getGbestIteration() const { return gBestIteration; }
		int           getIteration()      const { return iteration; }
	};
};

#endif