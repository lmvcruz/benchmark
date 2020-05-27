#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H

#include <vector>

#include "mark.h"

class Histogram {

private:
    int m_bins;
    double m_minv, m_maxv, m_binsize;
    std::vector<int> m_data;

public:
    Histogram();
    Histogram(int bins, double minV, double maxV);
    Histogram(const Histogram &that);
    ~Histogram();

    Histogram& operator=(const Histogram &that);

    void setRange(int bins, double minV, double maxV);
    double minRange();
    double maxRange();

    void set_size(int size);

    std::vector<int>& get_data();
    void set_data(std::vector<int> &data);

    // Este metodo devera ser mantido
    void AddData(double v);

    //TODO: remover o minV e maxV e usar o setRange
    void CreateBins(std::vector<double> &vec);

    int Distance(Histogram &that);
};


// Integer Descriptor class
class Descriptor {
protected:
    int m_bins;
    double m_minv, m_maxv;

public:
    Descriptor();
    virtual ~Descriptor();

    void setRange(int bins, double minV, double maxV);

    virtual Histogram Calculate(SampleMark &mark) = 0;
};


// Number particle descriptor
class QuantityDescriptor : public Descriptor{
public:
    QuantityDescriptor();

    Histogram Calculate(SampleMark &mark);
};

// Particle Distance Descriptor
class DistanceDescriptor : public Descriptor{
private:
    double m_maxDist;

public:
    DistanceDescriptor();

    Histogram Calculate(SampleMark &mark);

};

// Particle Angle descriptor
class AnchorAngleDescriptor: public Descriptor{
public:
    AnchorAngleDescriptor();
    ~AnchorAngleDescriptor();

    Histogram Calculate(SampleMark &mark);
};

// particle Neighbor Descriptor
class NeighborhoodDescriptor: public Descriptor{
private:
    double m_neigh;

public:
    NeighborhoodDescriptor(double neigh=2.0);
    ~NeighborhoodDescriptor();

    Histogram Calculate(SampleMark &mark);
};


#endif // DESCRIPTOR_H
