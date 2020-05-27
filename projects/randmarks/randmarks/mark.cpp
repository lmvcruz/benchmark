#include "mark.h"

#include <vector>
#include <cmath>

// Sample Mark
SampleMark::SampleMark(){}

SampleMark::SampleMark(const SampleMark &that)
{
    coords = that.coords;
}

SampleMark::~SampleMark(){}

SampleMark &SampleMark::operator=(const SampleMark &that)
{
    coords = that.coords;
    return *this;
}

void SampleMark::createUniformSampleMark(int qty, double xmin, double xmax, double ymin, double ymax, double zmin, double zmax)
{
    coords.resize(qty);
    for(int i=0; i<qty; i++) {
        // valor random entre xmin e xmax, ymin e ymax

        double x = randFloat()*(xmax - xmin) + xmin;
        double y = randFloat()*(ymax - ymin) + ymin;
        double z = randFloat()*(zmax - zmin) + zmin;
        coords[i].set(x,y,z);
    }
}

// em rate% das samples adicionar um valor [-maxNoise; maxNoise];
void SampleMark::addRandomTranslationNoise(float rate, float maxNoise) {
    //TODO: despoletar exceção se rate<0 or rate >1
    int qty = static_cast<int>(rate*coords.size());
    int cs = coords.size();
    for(int i = 0; i < qty; i++){
        double x = randFloat()*maxNoise*2.0 - maxNoise;
        double y = randFloat()*maxNoise*2.0 - maxNoise;
        double z = randFloat()*maxNoise*2.0 - maxNoise;
        coords[rand()%cs] += ctk::PointD(x,y,z);
    }}

// adcionar particulas aleatorias
void SampleMark::addInsertionNoise(float rate,
                             double xmin, double xmax,
                             double ymin, double ymax,
                             double zmin, double zmax) {
    int qty = static_cast<int>(rate*coords.size());
    int size = coords.size();
    coords.reserve(size+qty);
    for(int i = 0; i < qty; i++){
        double x = randFloat()*(xmax - xmin) + xmin;
        double y = randFloat()*(ymax - ymin) + ymin;
        double z = randFloat()*(zmax - zmin) + zmin;
        coords.push_back(ctk::PointD(x,y,z));
    }
}

// escolher rate% de indices para serem removidos
void SampleMark::addDeletionNoise(float rate) {
    int qty = static_cast<int>(rate*coords.size());
    for(int i = 0; i < qty; i++){
        int idx = rand()%coords.size();
        coords.erase(coords.begin()+idx);
    }
}

void SampleMark::set_data(std::vector<ctk::PointD> &p_coordinates){
    this->coords.clear();
    this->coords.resize(p_coordinates.size());
    for(unsigned int i=0; i<p_coordinates.size(); i++)
        this->coords[i] = p_coordinates[i];
    return;
}

std::vector<ctk::PointD> &SampleMark::get_data(){
    return this->coords;
}

int SampleMark::CalculateMarkSize()
{
    return this->coords.size();
}

double SampleMark::ParticleDistance(int p1, int p2)
{
    double xx = this->coords[p1].getX() - this->coords[p2].getX();
    double yy = this->coords[p1].getY() - this->coords[p2].getY();
    double d = std::sqrt( xx*xx + yy*yy);

    return d;
}

double SampleMark::ParticleDistance(ctk::PointD p1, ctk::PointD p2) // might not be needed
{
    double xx = p1.getX() - p2.getY();
    double yy = p1.getX() - p2.getY();
    double d = std::sqrt(xx*xx + yy*yy);

    return d;
}

double SampleMark::ParticleAngle(int p1, int p2, int p3)
{
    double d_12 = ParticleDistance(p1, p2);
    double d_13 = ParticleDistance(p1, p3);
    double d_23 = ParticleDistance(p2, p3);

    double angle = std::acos( (d_12*d_12 + d_13*d_13 - d_23*d_23) / (2*d_12*d_13) );

    return(angle);
}

int SampleMark::ParticleNeighbours(int p, double ns) // ns is neighborhood size, in distance
{
    int cnt = 0;
    for(auto i = 0; i < CalculateMarkSize(); i++){ // np: neighbour points
            if(ParticleDistance(p, i) < ns)
                cnt++;
    }
    return(cnt);
}

double SampleMark::randFloat() {
    return static_cast<double>(rand())/static_cast<double>(INT_MAX);
}
