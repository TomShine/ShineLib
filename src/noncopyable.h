#ifndef NONCOPYABLE_H
#define NONCOPYABLE_H

namespace shine {

class noncopyable
{
protected:
    noncopyable() {}
    virtual ~noncopyable() {}

private:
    noncopyable(const noncopyable&);
    noncopyable& operator=(const noncopyable&);
};

}

#endif // NONCOPYABLE_H
