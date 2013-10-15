#include <iterator>

#include <algorithm>
#include <vector>

template <typename T>
struct Point {
    typedef std::vector<Point> List;
    T x_;
    T y_;
    Point(T x, T y):
        x_(x),
        y_(y)
    {

    }
    double distance(Point const & q)
    {
        return sqrt(pow(x_ - q.x_, 2) + pow(y_ - q.y_, 2));
    }
};

template <typename T>
struct PointPair {

    Point<T> first_;
    Point<T> second_;
    PointPair(Point<T> first, Point<T> second)
        :first_(first),
        second_(second)
    {

    }
    double distance()
    {
        return first_.distance(second_);
    }

};

template <typename T>
struct PointList 
{
    std::vector<Point<T>> ps_;

    PointList()
    {
    }
    PointList(std::initializer_list<Point<T>> ps):
        ps_(ps)
    {

    }

    PointPair<T> closest_split_pair(PointList Px, PointList Py, double S)
    {
        //auto x_bar = std::max(std::begin(Px), std::end(Px), [](Point<T> l, Point<T> r){ return l.x_ < r.x_;});

        return  PointPair<T>(Px[0], Py[0]);
    }

    Point<T> operator[](size_t const & idx)
    {
        return ps_[idx];
    }

    PointPair<T> closest_pair(PointList Px, PointList Py)
    {
        auto P = Px.size() > Py.size() ? Px : Py; 

        if(P.size() <= 3)
        {
            auto pair = PointPair<T>(P[0], P[1]);
            for(typename PointList::iterator ps = std::begin(P); ps != std::end(P); ++ps)
            {
                for(typename PointList::iterator qs = std::begin(P); qs != std::end(P); ++qs)
                {
                    auto tpair = PointPair<T>(*ps, *qs);
                    if(pair.distance() > tpair.distance())
                    {
                        std::swap(pair, tpair);
                    }

                }
            }
            return pair;
        }
        else
        {


            // Divide the list in half by size (the array is sorted so points in the
            // right half will be in the right half of the array.
            PointList Lx;
            PointList Ly;

            PointList Rx;
            PointList Ry;

            std::copy(std::begin(Px), std::begin(Px)+Px.size()/2, std::begin(Lx));
            std::copy(std::begin(Px)+(Px.size()/2)+1, std::end(Px), std::begin(Rx));

            std::copy(std::begin(Py), std::begin(Py)+Py.size()/2, std::begin(Ly));
            std::copy(std::begin(Py)+(Py.size()/2+1), std::end(Py), std::begin(Ry));

            auto p1 = closest_pair(Lx, Ly);
            auto p2 = closest_pair(Rx, Ry);

            double delta = std::min({p1.distance(), p2.distance()});

            auto p3 = closest_split_pair(Px, Py, delta);

            std::vector<PointPair<T>> fpairs{p1, p2, p3};

            return *(std::min_element(std::begin(fpairs), std::end(fpairs), [](PointPair<T> p, PointPair<T> q){ return p.distance() < q.distance();}));
        }

    }

    PointPair<T> closest_pair()
    {
        PointList Px;
        PointList Py;
        std::sort(std::begin(ps_), std::end(ps_), [](Point<T> p, Point<T> q){ return p.x_ < q.x_;});
        std::copy(std::begin(ps_), std::end(ps_), std::back_inserter(Px));

        std::sort(std::begin(ps_), std::end(ps_), [](Point<T> p, Point<T> q){ return p.y_ < p.y_;});
        std::copy(std::begin(Py), std::end(ps_), std::back_inserter(Py));

        return closest_pair(Px, Py);
    }

    typename std::vector<Point<T>>::iterator begin()
    {
        return std::begin(ps_);
    }
    
    typename std::vector<Point<T>>::iterator end()
    {
        return std::end(ps_);
    }

    size_t size()
    {
        return ps_.size();
    }

    typedef typename std::vector<Point<T>>::iterator iterator;
    typedef T value_type;

    void operator=(PointList const & ps):
        _ps(ps)
    {
        
    }
};


int main(int argc, const char *argv[])
{
    PointList<double> p{Point<double>(20,25), Point<double>(30, 25), Point<double>(30, 40), Point<double>(40, 32.5)};
    p.closest_pair();

    return 0;
}
