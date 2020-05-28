#ifndef RANDMARK_H
#define RANDMARK_H

#include <vector>

#include <QString>

#include "ctk/ctkpoint.h"

class SampleMark;

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

    void AddData(double v);
    void setBinValue(int b, int v);

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

// Sample mark class
class SampleMark{
private:
    std::vector<ctk::PointD> coords;

public:
    SampleMark();
    SampleMark(const SampleMark &that);
    virtual ~SampleMark();

    SampleMark& operator=(const SampleMark &that);

    void createUniformSampleMark(int qty,
                                 double xmin, double xmax,
                                 double ymin, double ymax,
                                 double zmin=0.0, double zmax=0.0);

    void addRandomTranslationNoise(float rate, float maxNoise);

    void addInsertionNoise(float rate, double xmin, double xmax,
                           double ymin, double ymax,
                           double zmin=0.0, double zmax=0.0);

    void addDeletionNoise(float rate);

    void set_data(std::vector<ctk::PointD> &p_coordinates);
    std::vector<ctk::PointD>& get_data();

    int CalculateMarkSize();
    double ParticleDistance(int p1, int p2);
    double ParticleDistance(ctk::PointD p1, ctk::PointD p2); // might not be needed
    double ParticleAngle(int p1, int p2, int p3);
    int ParticleNeighbours(int p, double ns);

private:
    double randFloat();
};


class SetMark {
private:
    std::vector<SampleMark> m_marks;
    std::vector<Histogram> m_hists;

public:
    SetMark();

    int size();

    void addMark(SampleMark &m);
    SampleMark &get(int idx);

    void setHistogram(int idx, const Histogram &h);
    Histogram &getHistogram(int idx);

    void Open(QString filename);
    void Save(QString filename);
};

#endif // RANDMARK_H
