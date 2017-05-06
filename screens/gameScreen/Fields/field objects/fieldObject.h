#ifndef FIELDOBJECT_H
#define FIELDOBJECT_H


class fieldObject
{
    public:
        fieldObject();
        virtual ~fieldObject();
        virtual void draw()=0;
    protected:
    private:
};

#endif // FIELDOBJECT_H
