#ifndef POINT_HPP
#define POINT_HPP

namespace tcodtutorial
{
    struct Point
    {
        int x_, y_;
    };

    inline bool operator==(const Point& a, const Point& b)
    {
        return(a.x_ == b.x_ && a.y_ == b.y_);
    }
}

#endif
