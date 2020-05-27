#include "descriptor.h"

#include <iostream>

#include "ctk/ctkexceptions.h"

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
    // FIX_IT: inicializar o maxrange de forma apropriada (generica)
}

Histogram QuantityDescriptor::Calculate(SampleMark &mark)
{
    Histogram hist;
    hist.setRange(m_bins, m_minv, m_maxv);
    // calculte number os particles
    double qty = std::min(static_cast<double>(mark.CalculateMarkSize()),
                          hist.maxRange() );
    hist.AddData(qty);
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
