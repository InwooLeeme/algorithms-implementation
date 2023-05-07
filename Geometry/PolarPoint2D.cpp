struct Point2D{
    double x, y;
    Point2D(double x, double y): x(x), y(y){};
    static Point2D from_polar(double r, double theta) {
        return {r * cos(theta), r * sin(theta)};
    }
    Point2D to_polar() const {
        double r = sqrt(x * x + y * y);
        double theta = ::atan2(y, x); if(theta < 0) theta += numbers::pi * 2; 
        return {r, theta};
    }
    static Point2D from(int i, double x, double y){
        switch (i) {
            case 1: return {x, y};
            case 2: return from_polar(x, y);
        }
    }
    Point2D to(int i) {
        switch (i) {
            case 1: return *this;
            case 2: return to_polar();
        }
    } friend ostream& operator<<(ostream& f, const Point2D& a){
        return f << a.x << ' ' << a.y ;
    }
};
