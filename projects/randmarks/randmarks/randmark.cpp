#include "randmark.h"

#include <iostream>

#include <QFile>
#include <QTextStream>
#include <QString>

#include "ctk/ctkexceptions.h"
#include "ctk/utils/filesys/filesystem.h"

//
// Histogram Class
//

/**
 * @brief Histogram::Histogram
 */
Histogram::Histogram()
{
    m_bins = 1;
    m_minv = 0;
    m_maxv = 1.0;
    m_binsize = (m_maxv - m_minv)/m_bins;
}

Histogram::Histogram(int bins, double minV, double maxV){
    m_bins = bins;
    m_data.resize(m_bins, 0);
    //
    m_minv = minV;
    m_maxv = maxV;
    m_binsize = (m_maxv - m_minv)/m_bins;
}

Histogram::Histogram(const Histogram &that)
{
    m_bins = that.m_bins;
    m_data = that.m_data;
    m_minv = that.m_minv;
    m_maxv = that.m_maxv;
    m_binsize = that.m_binsize;
}

Histogram::~Histogram(){
    m_data.clear();
}

Histogram &Histogram::operator=(const Histogram &that)
{
    m_bins = that.m_bins;
    m_data = that.m_data;
    m_minv = that.m_minv;
    m_maxv = that.m_maxv;
    m_binsize = that.m_binsize;
    return *this;
}

void Histogram::setRange(int bins, double minV, double maxV)
{
    m_bins = bins;
    m_data.resize(m_bins, 0);
    //
    m_minv = minV;
    m_maxv = maxV;
    m_binsize = (m_maxv - m_minv)/m_bins;
}

double Histogram::minRange()
{
    return m_minv;
}

double Histogram::maxRange()
{
    return m_maxv;
}

void Histogram::set_size(int size){
    m_bins = size;
    m_data.resize(m_bins, 0);
}

std::vector<int>& Histogram::get_data(){
    return this->m_data;
}

void Histogram::set_data(std::vector<int> &data){
    m_bins = data.size();
    m_data = data;
}

void Histogram::AddData(double v)
{
    if ((v<m_minv) || (m_maxv<v)) throw ctk::value_out_of_range();
    unsigned int idx = static_cast<unsigned int>((v-m_minv)/m_binsize);
    m_data[idx]++;
}

void Histogram::setBinValue(int b, int v)
{
    m_data[b] = v;
}

void Histogram::CreateBins(std::vector<double> &vec)
{
    for(auto &v: vec) AddData(v);
}

int Histogram::Distance(Histogram &that)
{
    int d = 0.0;
    std::vector<int>& thatdata = that.get_data();
    for (auto i=0; i<m_data.size(); i++) {
        d += std::abs(m_data[i] - thatdata[i]);
    }
    return d;
}

//
// Descriptor class
//

Descriptor::Descriptor(){

}

Descriptor::~Descriptor(){

}

void Descriptor::setRange(int bins, double minV, double maxV)
{
    m_bins = bins;
    m_minv = minV;
    m_maxv = maxV;
}

//
// QuantityDescriptor Class
//
QuantityDescriptor::QuantityDescriptor(){
}

Histogram QuantityDescriptor::Calculate(SampleMark &mark)
{
    Histogram hist;
    hist.setRange(m_bins, m_minv, m_maxv);
    // calculte number os particles
    hist.setBinValue(0, mark.CalculateMarkSize());
    return hist;
}


//
// AnchorAngleDescriptor
//

DistanceDescriptor::DistanceDescriptor(){
}

Histogram DistanceDescriptor::Calculate(SampleMark &mark)
{
    Histogram hist;
    hist.setRange(m_bins, m_minv, m_maxv);
    int size = mark.CalculateMarkSize();
    for(int i = 0; i < size - 1; i++){
        for(int j = (i+1); j < size; j++){
            hist.AddData( mark.ParticleDistance(i,j) );
        }
    }
    return hist;
}

//
// AnchorAngleDescriptor
//

AnchorAngleDescriptor::AnchorAngleDescriptor()
{

}

AnchorAngleDescriptor::~AnchorAngleDescriptor()
{

}

Histogram AnchorAngleDescriptor::Calculate(SampleMark &mark)
{

}

//
// NeighborhoodDescriptor Class
//

NeighborhoodDescriptor::NeighborhoodDescriptor(double neigh)
{
    m_neigh = neigh;
}

NeighborhoodDescriptor::~NeighborhoodDescriptor()
{
}

Histogram NeighborhoodDescriptor::Calculate(SampleMark &mark)
{
    Histogram hist;
    hist.setRange(m_bins, m_minv, m_maxv);
    int size = mark.CalculateMarkSize();
    for(int i = 0; i < size - 1; i++){
        for(int j = (i+1); j < size; j++){
            int N = mark.ParticleNeighbours(i, m_neigh);
            double nd = std::max( static_cast<double>(N),
                                  hist.maxRange() );
            hist.AddData(nd);
        }
    }
    return hist;
}


//
// SampleMark
//
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

//
// SetMark
//

SetMark::SetMark()
{

}

int SetMark::size()
{
    return m_marks.size();
}

void SetMark::addMark(SampleMark &m)
{
    m_marks.push_back(m);
    m_hists.push_back(Histogram());
}

SampleMark &SetMark::get(int idx)
{
    return m_marks[idx];
}

void SetMark::setHistogram(int idx, const Histogram &h)
{
    m_hists[idx] = h;
}

Histogram &SetMark::getHistogram(int idx)
{
    return m_hists[idx];
}

void SetMark::Open(QString filename)
{
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        m_marks.clear();
        int ssize;
        in >> ssize;
        for (int i=0; i<ssize; i++) {
            SampleMark m;
            std::vector<ctk::PointD> &data = m.get_data();
            int dsize;
            in >> dsize;
            data.resize(dsize);
            double x, y;
            for (auto j=0; j<dsize; j++) {
                in >> x >> y;
                data[j].set(x,y);
            }
            addMark(m);
        }
    }
    file.close();
}

void SetMark::Save(QString filename)
{
    QFile file(filename);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        int ssize = m_marks.size();
        out << ssize << "\n";
        for (int i=0; i<ssize; i++) {
            std::vector<ctk::PointD> &data = m_marks[i].get_data();
            int dsize = data.size();
            out << dsize << "\n";
            for (auto j=0; j<dsize; j++) {
                out << data[j].getX() << " " << data[j].getY() << "\n";
            }
        }
    }
    file.close();
}
