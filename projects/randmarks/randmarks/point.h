#ifndef POINT_H
#define POINT_H

#include <cmath>

#include "ctk/ctkexceptions.h"

template<class T>
class Point{
private:
    T x_, y_, z_;

public:
    Point(T x=0, T y=0, T z=0) {
        x_ = x;
        y_ = y;
        z_ = z;
    }

    Point(const Point &that) {
        x_ = that.x_;
        y_ = that.y_;
        z_ = that.z_;
    }

    virtual ~Point() {}

    Point& operator=(const Point &that) {
        x_ = that.x_;
        y_ = that.y_;
        z_ = that.z_;
        return *this;
    }

    bool operator==(const Point &that) {
        return (*this==that);
    }

    bool operator!=(const Point &that) {
        return !(*this==that);
    }

    void set(T x, T y, T z=0) {
        x_ = x;
        y_ = y;
        z_ = z;
    }

    void setX(T x) {
        x_ = x;
    }

    T getX() {
        return x_;
    }

    void setY(T y) {
        y_ = y;
    }

    T getY() {
        return y_;
    }

    void setZ(T z) {
        z_ = z;
    }

    int getZ() {
        return z_;
    }

    Point operator+(const Point &that) {
        return Point(x_+that.x_, y_+that.y_, z_+that.z_);
    }

    void operator+=(const Point &that) {
        x_ += that.x_;
        y_ += that.y_;
        z_ += that.z_;
    }

    Point operator+(T v) {
        return Point(x_ + v.x_, y_ + v.y_, z_ + v.z_);
    }

    void operator+=(T v) {
        x_ += v.x_;
        y_ += v.y_;
        z_ += v.z_;
    }

    Point operator-(const Point &that) {
        return Point(x_-that.x_, y_-that.y_, z_-that.z_);
    }

    void operator-=(const Point &that) {
        x_ -= that.x_;
        y_ -= that.y_;
        z_ -= that.z_;
    }

    Point operator-(T v) {
        return Point(x_ - v.x_, y_ - v.y_, z_ - v.z_);
    }

    void operator-=(T v) {
        x_ -= v.x_;
        y_ -= v.y_;
        z_ -= v.z_;
    }

    Point operator*(const Point &that) {
        return Point(x_*that.x_, y_*that.y_, z_*that.z_);
    }

    void operator*=(const Point &that) {
        x_ *= that.x_;
        y_ *= that.y_;
        z_ *= that.z_;
    }

    Point operator*(T v) {
        return Point(x_ * v.x_, y_ * v.y_, z_ * v.z_);
    }

    void operator*=(T v) {
        x_ *= v.x_;
        y_ *= v.y_;
        z_ *= v.z_;
    }

    Point operator/(const Point &that) {
        if((that.x_==0) || (that.y_==0) || (that.z_==0)) {
            throw division_per_zero();
        }
        return Point(x_/that.x_, y_/that.y_, z_/that.z_);
    }

    void operator/=(const Point &that) {
        if((that.x_==0) || (that.y_==0) || (that.z_==0)) {
            throw division_per_zero();
        }
        x_ /= that.x_;
        y_ /= that.y_;
        z_ /= that.z_;
    }

    Point operator/(T v) {
        if((v.x_==0) || (v.y_==0) || (v.z_==0)) {
            throw division_per_zero();
        }
        return Point(x_/v.x_, y_/v.y_, z_/v.z_);
    }

    void operator/=(T v) {
        if((v.x_==0) || (v.y_==0) || (v.z_==0)) {
            throw division_per_zero();
        }
        x_ /= v.x_;
        y_ /= v.y_;
        z_ /= v.z_;
    }

    int ManhattanLength() { // Mudar para ManhattanDistance()?
        int ml = std::fabs(x_) + std::fabs(x_) + std::fabs(x_);
        return static_cast<int>(ml);
    }

    double Norm() {
        return std::sqrt(x_*x_ + y_*y_ + z_*z_) ;
    }

    double inner(const Point &p) {       // produto interno
        return x_*p.x_ + y_*p.y_ + z_*p.z_;
    }

    Point outter(const Point &p){
        return Point(y_*p.z_ - z_*p.y_,
                     -1*(x_*p.z_ - z_*p.x_),
                     x_*p.y_ - y_*p.x_ );
    }

    // return não é uma função, por isso não precisa os parenteses ;)
    // exceto em um caso: return (logical_operation);
    // no caso em retornar um valor lógico que é calculado diretamente
    // os parênteses não são obrigatorios, mas aconselháveis ;)
    double Distance(const Point &p) {
        return std::sqrt( (x_-p.x_)*(x_-p.x_) + (y_-p.y_)*(y_-p.y_) + (z_-p.z_)*(z_-p.z_) );
    }

    double Angle(const Point &pa, const Point &pb) {
        double p_pa = Distance(pa);
        double p_pb = Distance(pb);
        double pa_pb = (pa-pb).Norm(); // std::sqrt( (pa.x_-pb.x_)*(pa.x_-pb.x_) + (pa.y_-pb.y_)*(pa.y_-pb.y_) + (pa.z_-pb.z_)*(pa.z_-pb.z_) );

        return std::acos((p_pa*p_pa + p_pb*p_pb + pa_pb*pa_pb)/(2*p_pa*p_pb));
    }

    Point normalize() {
        double n = Norm();
        return *this / n;
    }

    void SelfNormalize() {
        double n = Norm();
        *this /= n;
    }
};

typedef Point<int> PointI;
typedef Point<double> PointD;

#endif // POINT_H
