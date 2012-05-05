#pragma once

#include <math.h>
#include <float.h>

using namespace std;

namespace geom {

    class Vector2D
    {
    public:
        Vector2D(float X = 0, float Y = 0)
        {
            x = X;
            y = Y;
        };
        ~Vector2D() {} ;

        float x, y;

        Vector2D operator*(float scalar) const
        {
            return Vector2D(x * scalar, y * scalar);
        }


        Vector2D operator+(const Vector2D &vect) const
        {
            return Vector2D(x + vect.x, y + vect.y);
        }

        Vector2D operator-(const Vector2D &vect) const
        {
            return Vector2D(x - vect.x, y - vect.y);
        }

        void rotate(float angle)
        {
            float xt = (x * cosf(angle)) - (y * sinf(angle));
            float yt = (y * cosf(angle)) + (x * sinf(angle));
            x = xt;
            y = yt;
        }

        float crossproduct(const Vector2D &vect2) const
        {
            return (this->x * vect2.y) - (this->y * vect2.x);
        }

        float magnitude()
        {
            return sqrtf(x * x +y * y);
        }

        void normalise()
        {
            float mag = sqrtf(x* x + y * y);
            this->x = x / mag;
            this->y = y / mag;
        }

        // return dot product
        float dotproduct(const Vector2D &vect) const
        {
            return (x * vect.x) + (y * vect.y);
        }
    };

    struct Line {
        Vector2D p1;
        Vector2D p2;
    };

    // Assumes horizontal directrix;
    struct Parabola {
        Vector2D focus;
        int directrix;
    };



    Line perpendicularBisector(Line line) {
        float BISECTOR_SCALE = 1;
        float dy = line.p2.y - line.p1.y;
        float dx = line.p2.x - line.p1.x;


        // Horizontal line
        if (dy == 0) {
            return {{-10000.0f, line.p1.y}, {10000.0f, line.p1.y}};

        // Vertical line
        }else if (dx == 0) {
            return {{line.p1.x, -10000.0f}, {line.p1.x, 10000.0f}};
        }else {

            Vector2D midpoint = {line.p1.x + (dx / 2), line.p1.y + (dy / 2)};

            Vector2D p1 = {midpoint.x - dx * BISECTOR_SCALE, midpoint.y + dy * BISECTOR_SCALE};
            Vector2D p2 = {midpoint.x + dx * BISECTOR_SCALE, midpoint.y - dy * BISECTOR_SCALE};



            return {p1, p2};
        }
    }

    // Based on http://local.wasp.uwa.edu.au/~pbourke/geometry/lineline2d/
    bool intersect(Line a, Line b, Vector2D& out) {
        float x1 = a.p1.x;
        float x2 = a.p2.x;
        float x3 = b.p1.x;
        float x4 = b.p2.x;
        float y1 = a.p1.y;
        float y2 = a.p2.y;
        float y3 = b.p1.y;
        float y4 = b.p2.y;


        float uwDenominator =
            ((y4 - y3) * (x2 - x1)) - ((x4 - x3) * (y2 - y1));

        float uNumerator =
            ((x4 - x3) * (y1 - y3)) - ((y4 - y3) * (x1 - x3));

        float wNumerator =
            ((x2 - x1) * (y1 - y3)) - ((y2 - y1) * (x1 - x3));

        // Lines are paralell or coincident
        if(uwDenominator == 0.0f)
        {
            return false;
        }

        float u = uNumerator / uwDenominator;
        float w = wNumerator / uwDenominator;


        //if(u >= 0.0f && u <= 1.0f && w >= 0.0f && w <= 1.0f)
        {
            // Get the intersection point.
            float x = x1 + (u * (x2 - x1));
            float y = y1 + (w * (y2 - y1));
            out.x = x;
            out.y = y;

            return true;
        }

        // Lines intersect, but not within the given segments
        return false;
    }

    Vector2D pointOnParabola(Parabola parabola, int tx) {
        float txf = static_cast<float>(tx);
        float dxf = static_cast<float>(parabola.directrix);
        Vector2D T = {txf, dxf};
        Line FT = {parabola.focus, T};
        Line bisectorFT = perpendicularBisector(FT);
        Line perpToDirectrixAtT = {{txf, 1000.0f}, {txf, 0.0f}};
        Vector2D P;
        intersect(perpToDirectrixAtT, bisectorFT, P);
        printf("%f, %f\n", P.x, P.y);

        return P;
    }
}
