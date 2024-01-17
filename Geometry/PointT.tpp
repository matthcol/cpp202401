#include <format>

template<class T>
PointT<T>::PointT() : Form(), m_x(T()), m_y(T()) {

}

template<class T>
PointT<T>::PointT(const std::string& name, T x, T y): Form(name), m_x(x), m_y(y) {

}

template<class T>
void PointT<T>::setX(T x) {
	m_x = x;
}

template<class T>
T PointT<T>::x() const {
	return m_x;
}

template<class T>
void PointT<T>::setY(T y) {
	m_y = y;
}

template<class T>
T PointT<T>::y() const {
	return m_y;
}

template<class T>
std::string PointT<T>::toString() const {
	return std::format("{0}({1}, {2})", name(), m_x, m_y);
}

template<class T>
void PointT<T>::translate(double deltaX, double deltaY) {
	m_x += static_cast<T>(deltaX);
	m_y += static_cast<T>(deltaY);
}

template<class T>
double PointT<T>::distance(const PointT<T>& other) const {
	double deltaX = m_x - other.m_x; // need operator- on type T and conversion to type double
	double deltaY = m_y - other.m_y;
	return hypot(deltaX, deltaY);
}