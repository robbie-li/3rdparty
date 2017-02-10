#ifndef UTILITY_MACRO_H_
#define UTILITY_MACRO_H_

#define SAFE_DELETE(p)        { if(nullptr != (p)) { delete (p);     (p) = nullptr; } }
#define SAFE_DELETE_ARRAY(p)  { if(nullptr != (p)) { delete[] (p);   (p) = nullptr; } }

#define DEFINE_PROPERTY(TYPE, NAME)                         \
protected: TYPE NAME ## _;                                    \
public: TYPE& get_ ## NAME() {return NAME ## _; }  \
public: const TYPE& get_ ## NAME() const {return NAME ## _; }  \
public: void set_ ## NAME(const TYPE &val) {NAME ## _ = val; }

#define DEFINE_QPROPERTY(TYPE, NAME)                        \
        Q_PROPERTY(TYPE NAME READ get_ ## NAME WRITE set_ ## NAME)    \
protected: TYPE NAME ## _;                                    \
public: TYPE& get_ ## NAME() {return NAME ## _; }  \
public: const TYPE& get_ ## NAME() const {return NAME ## _; }  \
public: void set_ ## NAME(const TYPE &val) {NAME ## _ = val; }

#define DEFINE_FULL_QPROPERTY(TYPE, NAME)                   \
        Q_PROPERTY(TYPE NAME READ get_ ## NAME WRITE set_ ## NAME NOTIFY NAME ## _changed) \
protected: TYPE NAME ## _;                                    \
public: TYPE& get_ ## NAME() {return NAME ## _; }  \
public: const TYPE& get_ ## NAME() const {return NAME ## _; }  \
public: void set_ ## NAME(const TYPE &val) {NAME ## _ = val; emit NAME ## _changed(val); }

#endif  // UTILITY_MACRO_H_
