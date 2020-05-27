#ifndef MARK_H
#define MARK_H

#include <vector>

#include "ctk/ctkpoint.h"

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

#endif // MARK_H
