#ifndef _COMMON_H_
#define _COMMON_H_

// template<class T>
// class Size2D_
// {
// public:
// 	Size2D_(){}
// 	Size2D_(const int x, const int y)
// 	{
// 		m_x = x;
// 		m_y = y;
// 	}
// 	~Size2D_(){}
// 
// 	Size2D_& operator -= (const double factor)
// 	{
// 		m_x = static_cast<T>(m_x-factor);
// 		m_y = static_cast<T>(m_y-factor);
// 		return *this;
// 	}
// 
// 	Size2D_& operator *= (const double factor)
// 	{
// 		m_x = static_cast<T>(m_x*factor);
// 		m_y = static_cast<T>(m_y*factor);
// 		return *this;
// 	}
// 
//     Size2D_& operator /= (const double factor)
//     {
//         m_x = static_cast<T>(m_x/factor);
//         m_y = static_cast<T>(m_y/factor);
//         return *this;
//     }
// 
// public:
// 	int m_x;
// 	int m_y;
// };
// typedef Size2D_<int> Size2D;
// typedef Size2D_<double> Size2Df;
// 
// 
// template<class T>
// class Size3D_
// {
// public:
//     Size3D_() {}
//     Size3D_(const int x, const int y, const int z)
//     {
//         m_x = x;
//         m_y = y;
//         m_z = z;
//     }
//     ~Size3D_() {}
// 
//     Size3D_& operator - (const double factor)
//     {
//         m_x = static_cast<T>(m_x - factor);
//         m_y = static_cast<T>(m_y - factor);
//         m_z = static_cast<T>(m_z - factor);
//         return *this;
//     }
// 
//     Size3D_& operator -= (const double factor)
//     {
//         m_x = static_cast<T>(m_x - factor);
//         m_y = static_cast<T>(m_y - factor);
//         m_z = static_cast<T>(m_z - factor);
//         return *this;
//     }
// 
//     Size3D_& operator *= (const double factor)
//     {
//         m_x = static_cast<T>(m_x*factor);
//         m_y = static_cast<T>(m_y*factor);
//         m_z = static_cast<T>(m_z*factor);
//         return *this;
//     }
// 
//     Size3D_& operator /= (const double factor)
//     {
//         m_x = static_cast<T>(m_x / factor);
//         m_y = static_cast<T>(m_y / factor);
//         m_z = static_cast<T>(m_z / factor);
//         return *this;
//     }
// 
// public:
//     int m_x;
//     int m_y;
//     int m_z;
// };
// typedef Size3D_<int> Size3D;
// typedef Size3D_<double> Size3Df;
// 
template<class T>
class Size3D_
{
public:
    Size3D_()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    Size3D_(T a, T b, T c)
    {
        x = a;
        y = b;
        z = c;
    }

    T Value()
    {
        return x*y*z;
    }

    bool operator==(const Size3D_<T>& nsize)
    {
        if (this->x == nsize.x &&
            this->y == nsize.y &&
            this->z == nsize.z)
        {
            return true;
        }
        else
            return false;
    }

    Size3D_<T>& operator=(const Size3D_<T>& nsize)
    {
        if (this == &nsize)
        {
            return *this;
        }
        this->x = nsize.x;
        this->y = nsize.y;
        this->z = nsize.z;
        return *this;
    }

    Size3D_<T> operator+(const Size3D_<T>& nsize)
    {
        Size3D_<T> tmp;
        tmp.x = this->x + nsize.x;
        tmp.y = this->y + nsize.y;
        tmp.z = this->z + nsize.z;
        return tmp;
    }

    Size3D_<T> operator-(const Size3D_<T>& nsize)
    {
        Size3D_<T> tmp;
        tmp.x = this->x - nsize.x;
        tmp.y = this->y - nsize.y;
        tmp.z = this->z - nsize.z;
        return tmp;
    }

    Size3D_<T> operator*(const Size3D_<T>& nsize)
    {
        Size3D_<T> tmp;
        tmp.x = this->x * nsize.x;
        tmp.y = this->y * nsize.y;
        tmp.z = this->z * nsize.z;
        return tmp;
    }

    Size3D_<T> operator/(const Size3D_<T>& nsize)
    {
        Size3D_<T> tmp;
        tmp.x = this->x / nsize.x;
        tmp.y = this->y / nsize.y;
        tmp.z = this->z / nsize.z;
        return tmp;
    }

    Size3D_<T>& operator+=(const Size3D_<T>& nsize)
    {
        this->x += nsize.x;
        this->y += nsize.y;
        this->z += nsize.z;
        return *this;
    }

    Size3D_<T>& operator-=(const Size3D_<T>& nsize)
    {
        this->x -= nsize.x;
        this->y -= nsize.y;
        this->z -= nsize.z;
        return *this;
    }

    Size3D_<T>& operator*=(const Size3D_<T>& nsize)
    {
        this->x *= nsize.x;
        this->y *= nsize.y;
        this->z *= nsize.z;
        return *this;
    }

    Size3D_<T>& operator/=(const Size3D_<T>& nsize)
    {
        this->x /= nsize.x;
        this->y /= nsize.y;
        this->z /= nsize.z;
        return *this;
    }

    Size3D_<T>& operator+(const double factor)
    {
        Size3D_<T> out;
        out.x = (T)((double)this->x + factor);
        out.y = (T)((double)this->y + factor);
        out.z = (T)((double)this->z + factor);
        return out;
    }

    Size3D_<T>& operator-(const double factor)
    {
        Size3D_<T> out;
        out.x = (T)((double)this->x - factor);
        out.y = (T)((double)this->y - factor);
        out.z = (T)((double)this->z - factor);
        return out;
    }

    Size3D_<T>& operator*(const double factor)
    {
        Size3D_<T> out;
        out.x = (T)((double)this->x * factor);
        out.y = (T)((double)this->y * factor);
        out.z = (T)((double)this->z * factor);
        return out;
    }

    Size3D_<T>& operator/(const double factor)
    {
        Size3D_<T> out;
        out.x = (T)((double)this->x / factor);
        out.y = (T)((double)this->y / factor);
        out.z = (T)((double)this->z / factor);
        return out;
    }

    Size3D_<T>& operator+=(const double factor)
    {
        this->x = (T)((double)this->x + factor);
        this->y = (T)((double)this->y + factor);
        this->z = (T)((double)this->z + factor);
        return *this;
    }

    Size3D_<T>& operator-=(const double factor)
    {
        this->x = (T)((double)this->x - factor);
        this->y = (T)((double)this->y - factor);
        this->z = (T)((double)this->z - factor);
        return *this;
    }

    Size3D_<T>& operator*=(const double factor)
    {
        this->x = (T)((double)this->x * factor);
        this->y = (T)((double)this->y * factor);
        this->z = (T)((double)this->z * factor);
        return *this;
    }

    Size3D_<T>& operator/=(const double factor)
    {
        this->x = (T)((double)this->x / factor);
        this->y = (T)((double)this->y / factor);
        this->z = (T)((double)this->z / factor);
        return *this;
    }

    bool Equal(const Size3D_<T>& nsize)
    {
        if (this->x != nsize.x ||
            this->y != nsize.y ||
            this->z != nsize.z)
        {
            return false;
        }

        return true;
    }

public:
    T x;
    T y;
    T z;
};
typedef Size3D_<int> Size3D;
typedef Size3D_<double> Size3Df;

template<class T>
class Size2D_
{
public:
    Size2D_()
    {
        x = 0;
        y = 0;
    }

    Size2D_(T a, T b)
    {
        x = a;
        y = b;
    }

    T Value()
    {
        return x*y;
    }
    bool operator==(const Size2D_<T>& nsize)
    {
        if (this->x == nsize.x &&
            this->y == nsize.y)
        {
            return true;
        }
        else
            return false;
    }

    Size2D_<T>& operator=(const Size2D_<T>& nsize)
    {
        if (this == &nsize)
        {
            return *this;
        }
        this->x = nsize.x;
        this->y = nsize.y;
        return *this;
    }

    Size2D_<T> operator+(const Size2D_<T>& nsize)
    {
        Size2D_<T> tmp;
        tmp.x = this->x + nsize.x;
        tmp.y = this->y + nsize.y;
        return tmp;
    }

    Size2D_<T> operator-(const Size2D_<T>& nsize)
    {
        Size2D_<T> tmp;
        tmp.x = this->x - nsize.x;
        tmp.y = this->y - nsize.y;
        return tmp;
    }

    Size2D_<T> operator*(Size2D_<T>& nsize)
    {
        Size2D_<T> tmp;
        tmp.x = this->x * nsize.x;
        tmp.y = this->y * nsize.y;
        return tmp;
    }

    Size2D_<T> operator/(const Size2D_<T>& nsize)
    {
        Size2D_<T> tmp;
        tmp.x = this->x / nsize.x;
        tmp.y = this->y / nsize.y;
        return tmp;
    }

    Size2D_<T>& operator+=(const Size2D_<T>& nsize)
    {
        this->x += nsize.x;
        this->y += nsize.y;
        return *this;
    }

    Size2D_<T>& operator-=(const Size2D_<T>& nsize)
    {
        this->x -= nsize.x;
        this->y -= nsize.y;
        return *this;
    }

    Size2D_<T>& operator*=(const Size2D_<T>& nsize)
    {
        this->x *= nsize.x;
        this->y *= nsize.y;
        return *this;
    }

    Size2D_<T>& operator/=(const Size2D_<T>& nsize)
    {
        this->x /= nsize.x;
        this->y /= nsize.y;
        return *this;
    }

    Size2D_<T>& operator+(const double factor)
    {
        Size2D_<T> out;
        out.x = (T)((double)this->x + factor);
        out.y = (T)((double)this->y + factor);
        return out;
    }

    Size2D_<T>& operator-(const double factor)
    {
        Size2D_<T> out;
        out.x = (T)((double)this->x - factor);
        out.y = (T)((double)this->y - factor);
        return out;
    }

    Size2D_<T>& operator*(const double factor)
    {
        Size2D_<T> out;
        out.x = (T)((double)this->x * factor);
        out.y = (T)((double)this->y * factor);
        return out;
    }

    Size2D_<T>& operator/(const double factor)
    {
        Size2D_<T> out;
        out.x = (T)((double)this->x / factor);
        out.y = (T)((double)this->y / factor);
        return out;
    }

    Size2D_<T>& operator+=(const double factor)
    {
        this->x = (T)((double)this->x + factor);
        this->y = (T)((double)this->y + factor);
        return *this;
    }

    Size2D_<T>& operator-=(const double factor)
    {
        this->x = (T)((double)this->x - factor);
        this->y = (T)((double)this->y - factor);
        return *this;
    }

    Size2D_<T>& operator*=(const double factor)
    {
        this->x = (T)((double)this->x * factor);
        this->y = (T)((double)this->y * factor);
        return *this;
    }

    Size2D_<T>& operator/=(const double factor)
    {
        this->x = (T)((double)this->x / factor);
        this->y = (T)((double)this->y / factor);
        return *this;
    }

public:
    T x;
    T y;
};
typedef Size2D_<int> Size2D;
typedef Size2D_<double> Size2Df;


class Coord
{
public:
    Coord() {}
    explicit Coord(const int x) { m_index.push_back(x); }
    explicit Coord(const int x, const int y) { m_index.push_back(x); m_index.push_back(y); }
    explicit Coord(const int x, const int y, const int z) { m_index.push_back(x); m_index.push_back(y); m_index.push_back(z); }
    explicit Coord(const std::vector<int>& coord) { m_index = coord; }
    ~Coord() {}

    int GetDimension()const { return static_cast<int>(m_index.size()); }
    void SetDimension(const int x) { m_index.resize(x); }

    int GetTotalSize()const
    {
        int n = m_index.at(0);
        for (size_t i = 1; i < m_index.size(); i++)
        {
            n *= m_index.at(i);
        }
        return n;
    }

    int GetValue(const int x)const { return m_index.at(x); }
    void SetValue(const int x, const int v) { m_index.at(x) = v; }
    void PushValue(const int v) { m_index.push_back(v); }
public:
    std::vector<int> m_index;
};
typedef Coord Dimen;

class Opts
{
public:
    double falpha;
    int batchsize;
    int numepochs;
};

#endif // !_COMMON_H_
