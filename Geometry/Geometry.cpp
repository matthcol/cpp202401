#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <array>
#include <functional>
#include <memory>
#include <iterator>
#include <format>
#include <algorithm>
#include <random>
#include <numeric>
#include <tuple>

#include "Point.h"
#include "display.h"
#include "PointT.h"

void playWithPoints() {
    Point p0; // default constructor
    Point pA("A", 3.5, 4.75);
    Point pB("B", 7.5, 1.75);
    std::cout << p0.toString() << std::endl;
    std::cout << pA.toString() << std::endl;
    Form& f = pA;
    std::cout << f.toString() << std::endl; 
    std::cout << f << std::endl;
    std::cout << pA << std::endl;
    std::cout << "Distance A-B: "
        << pA.distance(pB)
        << " or " << pB.distance(pA)
        << std::endl;
    for (auto& p : { p0, pA, pB }) {
        std::cout << "before translate: " << p << std::endl;
    }
    std::vector<Point> points{ p0, pA, pB }; // vector contains copies
    for (auto& p : points) {
        p.translate(1, -1);
        std::cout << "after translate (in vector): " << p << std::endl;
    }
    for (auto& p : { p0, pA, pB }) {
        std::cout << "after translate (p0, pA, pB): " << p << std::endl;
    }
    std::vector<std::reference_wrapper<Point>> points2{ p0, pA, pB }; // vector contains copies
    for (auto p : points2) {
        p.get().translate(1, -1);
        std::cout << "after translate (in vector by reference): " << p << std::endl;
    }
    for (Point& p : points2) {
        p.translate(1, -1);
        std::cout << "after translate (in vector by reference): " << p << std::endl;
    }
}

void playWithMemoryAdresses() {
    // direct mode: point in the Stack
    Point ptA("A", 3.5, 12.75);
    // indirect mode: point in the Heap
    Point* ptB_ptr = new Point("B", 23.5, 67.25); 
    // pointer on stack object
    Point* point_ptr = &ptA; 
    // smart pointer: point int the Heap
    std::shared_ptr<Point> ptC_ptr(new Point("C", 98.25, 632.5));
    std::shared_ptr<Point> ptD_ptr = std::make_shared<Point>("D", 76.25, 501.5);

    // references
    Point& point1 = ptA;
    Point& point2 = *ptB_ptr;
    Point*& point2_ptr = ptB_ptr;
    std::cout << point1.x() << " "
        << point2_ptr->x() << " "
        << std::endl;
    
    // print local variable adresses
    std::cout << "ptA: @=" << &ptA << std::endl;
    std::cout << "ptB_ptr: @=" << &ptB_ptr << std::endl;


    // use points
    std::cout << ptA << std::endl;
    std::cout << *ptB_ptr 
        << " (@=" << ptB_ptr << ")" 
        << std::endl;

    delete ptB_ptr; // disalloc Point in the Heap
} // Point A unstack + Points C,D desalloc with smart pointer destructor (counter=0)


void playWithContainerDoubles() {
    std::vector<double> temperatures{ -1.4, 12.3, 8.5, 6.4, 8.4, 8.2, 12.3 };
    // iterate by copy
    for (double t : temperatures) {
        std::cout << t << " ";
    }
    std::cout << std::endl;

    std::vector<double> temperatureSample(temperatures.begin(), temperatures.begin()+3);
    for (double t : temperatureSample) {
        std::cout << t << " ";
    }
    std::cout << std::endl;

    std::set<double> temperatureSortedSet(temperatures.cbegin(), temperatures.cend());
    for (double t : temperatureSortedSet) {
        std::cout << t << " ";
    }
    std::cout << std::endl;
    temperatureSortedSet.insert(9.9);
    temperatureSortedSet.insert({ -5.0, -3.0, 5.4 });
    for (double t : temperatureSortedSet) {
        std::cout << t << " ";
    }
    std::cout << std::endl;

    // smart function on iterators: next, advance, prev, distance, ...
    auto first = temperatureSortedSet.cbegin();
    auto last = std::next(first, 3); // 3x ++ on a copy of first
    std::list<double> temperatureList(first, last);
    for (double t : temperatureList) {
        std::cout << t << " ";
    }
    std::cout << std::endl;

    double threshold = 3.0;
    std::copy_if(
        temperatureSortedSet.cbegin(),
        temperatureSortedSet.cend(),
        std::ostream_iterator<double>(std::cout, ", "),
        [threshold](auto t) { return t < threshold; }
    );
}

void mapReduce() {
    // generate random numbers with a Gauss distribution
    std::random_device rd{};
    std::mt19937 gen{ rd() };

    // values near the mean are the most likely
    // standard deviation affects the dispersion of generated values from the mean
    std::normal_distribution d{ 25.0, 4.0 };

    // draw a sample from the normal distribution and round it to an integer
    auto random_double = [&d, &gen] { return d(gen); };

    double tempRandom = random_double();
    std::cout << "1 random temperature: " << tempRandom << std::endl;

    size_t size = 1000000;
    // create vector de size elements with random_double function
    std::vector<double> temperatures(size); 
    // temperatures.capacity/size = size, 
    std::cout << "Check vector size: " << temperatures.size() << std::endl;
    std::generate(temperatures.begin(), temperatures.end(), random_double);

    auto display_iterator = std::ostream_iterator<double>(std::cout, ", ");
    // print 10 first and 10 last values
    std::copy_n(temperatures.cbegin(), 10, display_iterator);
    std::cout << " ... ";
    std::copy_n(temperatures.cend()-10, 10, display_iterator);
    std::cout << std::endl;

    // print temperatures >= threshold (ex: 40)
    double threshold = 40.0;
    auto value_greater_threshold = [threshold](auto v) {return v >= threshold; };
    std::copy_if(
        temperatures.cbegin(),
        temperatures.cend(),
        display_iterator,
        value_greater_threshold
    );

    // store filtered data in a container 
    // - temperatures > threshold (ex: 40)
    // - res: sorted vector, then set
    std::vector<double> filteredTemperatureVector;
    std::set<double> filteredTemperatureSet;
    std::copy_if(
        temperatures.cbegin(),
        temperatures.cend(),
        std::back_inserter(filteredTemperatureVector), 
        value_greater_threshold
    );
    std::sort(filteredTemperatureVector.begin(), filteredTemperatureVector.end());
    std::copy_if(
        temperatures.cbegin(),
        temperatures.cend(),
        std::inserter(filteredTemperatureSet, filteredTemperatureSet.begin()),
        value_greater_threshold
    );

    // print results
    std::cout << std::endl << std::endl << "Vector (filtered) [" 
        << filteredTemperatureVector.size() << "]: ";
    std::copy(filteredTemperatureVector.begin(), filteredTemperatureVector.end(), display_iterator);

    std::cout << std::endl << std::endl << "Set (filtered) ["
        << filteredTemperatureSet.size() << "]: ";
    std::copy(filteredTemperatureSet.begin(), filteredTemperatureSet.end(), display_iterator);
    std::cout << std::endl;

    // compute: min, max, mean, sum, count
    // minmax => pair<it,it>
    auto min_max = std::minmax_element(
        temperatures.cbegin(),
        temperatures.cend()
    );
    double min = *min_max.first;
    double max = *min_max.second;
    double sum = std::accumulate(
        temperatures.cbegin(),
        temperatures.cend(),
        0.0
    );
    size_t count = temperatures.size();
    double mean = sum / count;
    std::cout << "min=" << min
        << "; max=" << max
        << "; count=" << count
        << "; sum=" << sum
        << "; mean=" << mean
        << std::endl;
    
    // 
    std::tuple<double, double, double, size_t> min_max_sum_count{-5.5, 42.3, 20000.23, 300};
    auto [min2, max2, sum2, count2] = min_max_sum_count;
    std::cout << std::get<0>(min_max_sum_count) << std::endl;
    std::cout << "min=" << min2
        << "; max=" << max2
        << "; count=" << count2
        << "; sum=" << sum2
        << std::endl;

    auto reduce_min_max_sum_count = [](
        std::tuple<double, double, double, size_t> min_max_sum_count_temp, 
        double t) 
    {
        auto [min_temp, max_temp, sum_temp, count_temp] = min_max_sum_count_temp;
        return std::tuple<double, double, double, size_t>{
            std::min(t, min_temp),
            std::max(t, max_temp),
            t + sum_temp,
            count_temp + 1
        };
    };
    auto [min3, max3, sum3, count3] = std::accumulate(
        temperatures.cbegin(),
        temperatures.cend(),
        std::tuple<double, double, double, size_t>{
            std::numeric_limits<double>::infinity(), // min
            -std::numeric_limits<double>::infinity(), // max
            0.0,        // sum
            0           // count
        },
        reduce_min_max_sum_count
    );
    std::cout << "min=" << min3
        << "; max=" << max3
        << "; count=" << count3
        << "; sum=" << sum3
        << std::endl;

}

void demo_cpp20_formatting() {
    std::tuple<double, double, double, size_t> min_max_sum_count{ -5.5, 42.3, 20000.23, 300 };
    auto [min, max, sum, count] = min_max_sum_count;
    std::cout 
        << std::format("min={} ; max={} ; sum={:.3f}; count={}", min, max, sum, count)
        << std::endl;
}

void mapReduce_cpp20_ranges() {
    // NB: range is a concept: a range has start position and a sentinel to en iteration
    // 
    // generate random numbers with a Gauss distribution
    std::random_device rd{};
    std::mt19937 gen{ rd() };

    // values near the mean are the most likely
    // standard deviation affects the dispersion of generated values from the mean
    std::normal_distribution d{ 25.0, 4.0 };

    // draw a sample from the normal distribution and round it to an integer
    auto random_double = [&d, &gen] { return d(gen); };

    double tempRandom = random_double();
    std::cout << "1 random temperature: " << tempRandom << std::endl;

    size_t size = 1000000;
    // create vector de size elements with random_double function
    std::vector<double> temperatures(size);
    // temperatures.capacity/size = size, 
    std::cout << "Check vector size: " << temperatures.size() << std::endl;
    std::ranges::generate(temperatures, random_double);

    auto display_iterator = std::ostream_iterator<double>(std::cout, ", ");
    // print 10 first and 10 last values
    std::ranges::copy_n(temperatures.cbegin(), 10, display_iterator);
    std::cout << " ... ";
    std::ranges::copy_n(temperatures.cend() - 10, 10, display_iterator);
    std::cout << std::endl;

    // print temperatures >= threshold (ex: 40)
    double threshold = 40.0;
    auto value_greater_threshold = [threshold](auto v) {return v >= threshold; };
    std::ranges::copy_if(
        temperatures,
        display_iterator,
        value_greater_threshold
    );

    // store filtered data in a container 
    // - temperatures > threshold (ex: 40)
    // - res: sorted vector, then set
    std::vector<double> filteredTemperatureVector;
    std::set<double> filteredTemperatureSet;
    std::ranges::copy_if(
        temperatures,
        std::back_inserter(filteredTemperatureVector),
        value_greater_threshold
    );
    std::sort(filteredTemperatureVector.begin(), filteredTemperatureVector.end());
    std::copy_if(
        temperatures.cbegin(),
        temperatures.cend(),
        std::inserter(filteredTemperatureSet, filteredTemperatureSet.begin()),
        value_greater_threshold
    );

    // print results
    std::cout << std::endl << std::endl << "Vector (filtered) ["
        << filteredTemperatureVector.size() << "]: ";
    std::copy(filteredTemperatureVector.begin(), filteredTemperatureVector.end(), display_iterator);

    std::cout << std::endl << std::endl << "Set (filtered) ["
        << filteredTemperatureSet.size() << "]: ";
    std::copy(filteredTemperatureSet.begin(), filteredTemperatureSet.end(), display_iterator);
    std::cout << std::endl;

    // compute: min, max, mean, sum, count
    // minmax => pair<it,it>
    auto min_max = std::minmax_element(
        temperatures.cbegin(),
        temperatures.cend()
    );
    double min = *min_max.first;
    double max = *min_max.second;
    double sum = std::accumulate(
        temperatures.cbegin(),
        temperatures.cend(),
        0.0
    );
    size_t count = temperatures.size();
    double mean = sum / count;
    std::cout << "min=" << min
        << "; max=" << max
        << "; count=" << count
        << "; sum=" << sum
        << "; mean=" << mean
        << std::endl;

    // 
    std::tuple<double, double, double, size_t> min_max_sum_count{ -5.5, 42.3, 20000.23, 300 };
    auto [min2, max2, sum2, count2] = min_max_sum_count;
    std::cout << std::get<0>(min_max_sum_count) << std::endl;
    std::cout << "min=" << min2
        << "; max=" << max2
        << "; count=" << count2
        << "; sum=" << sum2
        << std::endl;

    auto reduce_min_max_sum_count = [](
        std::tuple<double, double, double, size_t> min_max_sum_count_temp,
        double t)
        {
            auto [min_temp, max_temp, sum_temp, count_temp] = min_max_sum_count_temp;
            return std::tuple<double, double, double, size_t>{
                std::min(t, min_temp),
                    std::max(t, max_temp),
                    t + sum_temp,
                    count_temp + 1
            };
        };
    auto [min3, max3, sum3, count3] = std::accumulate(
        temperatures.cbegin(),
        temperatures.cend(),
        std::tuple<double, double, double, size_t>{
        std::numeric_limits<double>::infinity(), // min
            -std::numeric_limits<double>::infinity(), // max
            0.0,        // sum
            0           // count
    },
        reduce_min_max_sum_count
    );
    std::cout << "min=" << min3
        << "; max=" << max3
        << "; count=" << count3
        << "; sum=" << sum3
        << std::endl;

}

void compare_points_cpp20() {
    // <=> three way comparison operator (starship operator)
    // 3 ordering class: strong_ordering, weak_ordering, partial_ordering
    // strong,weak: 3 results => less, equivalent, greater
    // partial: 4 results => less, equivalent, greater, unordered
    // Implication: strong => weak => partial
    // Result => bool helpers: is_eq, is_neq, is_lt, is_lteq, is_gt, is_gteq
    // weak: can have both true is_eq(a <=> b) and a != b
    std::vector<Point> points{
        Point("A", 1.5, 5.4),
        Point("B", -1.5, 5.4),
        Point("C", 10.5, 5.4),
        Point("D", 1.5, 2.4),
        Point("A", 1.5, 5.4),
    };

    Point partialPoint("W", std::nan("1"), 3);

    std::cout << std::boolalpha
        << " | < " << (points[0] < points[1])
        << " | <= " << (points[0] <= points[4])
        << " | == " << (points[0] == points[4])
        << " | unordered " << ((points[0] <=> partialPoint) == std::partial_ordering::unordered)
        << std::endl;

    std::ranges::sort(points);
    std::ranges::copy(points, std::ostream_iterator<const Point&>(std::cout, ", "));
    std::cout << std::endl;
}

void playWithRhsPoint(
    Point&& point // rhs
) 
{
    Point pt(point); // move rhs into a lhs
    std::cout << "Point moved here: " << pt << std::endl;
}


void moveDemo() {
    // * * * * * * * * * * * * * * * * * * * *
    // & & & & & & & & & & & & & & & & & & & &
    // && && && && && && && && && && && && && &&
    int y = (3 + 4) / 7;
    int x = y + 3;

    Point p("A", 1.5, 3.5); // Point lhs
    std::vector<Point> points{
        Point("B", 1.5, 5.4),  // Point rhs
        Point("C", -1.5, 5.4)  // // Point rhs
    };
    points.push_back(p); // add lhs by ref (&)
    points.push_back(Point("D", -1.5, 5.4)); // add rhs (&&)
    playWithRhsPoint(Point("D", -1.5, 5.4));
    playWithRhsPoint(std::move(p)); // convert lhs in rhs
    // do not use p anymore !!
    // std::cout << "After move: " << p << std::endl;
}

void demoArray() {
    std::array<double, 4> temperatures{ 12.5, 34.4,-12.0, 2.4 };
    std::array<Point, 2> points{
        Point("B", 1.5, 5.4),
        Point("C", -1.5, 5.4)
    };
    std::array<Point*, 2> points2{
        new Point("B", 1.5, 5.4),
        new Point("C", -1.5, 5.4)
    };
    // following templateusage does not compile:
    //std::array<Point&, 2> points3{
    //   points[0],
    //   points[1]
    //};
    std::array<std::reference_wrapper<Point>, 2> points3{
       points[0],
       points[1]
    };
    for (auto temperature : temperatures) { // foreach C++11
        std::cout << "\t-" << temperature << std::endl;
    }
    for (size_t i = 0; i < temperatures.size(); i++) { // for C
        auto temperature = temperatures[i];
        std::cout << "\t*" << temperature << std::endl;
    }

    // display(temperatures.cbegin(), temperatures.cend()); // OK for InputIy, KO for T
    display<double>(temperatures.cbegin(), temperatures.cend()); // T=double
    display<double, std::array<double,4>::const_iterator>(temperatures.cbegin(), temperatures.cend());

    display<Point>(points.cbegin(), points.cend());
    display<Point*>(points2.cbegin(), points2.cend());
    display<std::reference_wrapper<Point>>(points3.cbegin(), points3.cend());

    display(points2.cbegin(), points2.cend(), [](Point* point_pt) {return *point_pt; });
    
    // display x coord of each point in points
    display(points.cbegin(), points.cend(), [](const Point& point) {return point.x(); });
    display(points.cbegin(), points.cend(), [](auto& point) {return point.x(); });
    // display x coord of each point in points2
    display(points2.cbegin(), points2.cend(), [](auto point_ptr) {return point_ptr->x(); });
}

void playWithGenericPoints() {
    PointT<double> pointD("A", 3.4, 4.5);
    PointT<float> pointF("B", 3.4f, 4.5f);
    PointT<int> pointI("C", 3, 4);
    PointT<int> pointI2("D", 7, 7);
    PointT<int> pointI3;
    PointT<double> pointD2;
    std::cout << "point with double coords: " << pointD.toString() << std::endl
        << "point with float coords: " << pointF.toString() << std::endl
        << "point with int coords: " << pointI.toString() << std::endl;
    std::vector<Form*> points{ &pointD, &pointF, &pointI, &pointI2, &pointI3, &pointD2 };
    for (auto point_ptr : points) {
        point_ptr->translate(1.4, -1.3);
        std::cout << point_ptr->toString() << " ; ";
    }
    std::cout << std::endl;
    double d = pointI.distance(pointI2);
    std::cout << "distance: " << d << std::endl;

    double d2 = pointI.distance(pointF);
    std::cout << "distance: " << d2 << std::endl;

}

int main()
{
    // playWithPoints();
    // playWithMemoryAdresses();
    // playWithContainerDoubles();
    // mapReduce();
    // demo_cpp20_formatting();
    // mapReduce_cpp20_ranges();
    // compare_points_cpp20();
    // moveDemo();
    // demoArray();
    playWithGenericPoints();
    return 0;
}
