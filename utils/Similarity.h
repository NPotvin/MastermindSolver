#ifndef MASTERMINDSOLVER_SIMILARITY_H
#define MASTERMINDSOLVER_SIMILARITY_H


class Similarity {
private:

    unsigned _perfect;
    unsigned _colorOnly;

public:

    Similarity() : _perfect(0), _colorOnly(0) {};
    explicit Similarity(unsigned p, unsigned co) : _perfect(p), _colorOnly(co) {}
    Similarity(const Similarity& other) = default;

    const unsigned& getPerfect() const {return _perfect;}
    const unsigned& getColorOnly() const {return _colorOnly;}
};

#endif //MASTERMINDSOLVER_SIMILARITY_H
