#ifndef MyPROPERTY_h
#define MyPROPERTY_h

namespace tnk {


#define PROPERTY(type, name) \
    Q_SIGNALS: \
    void name##Changed(); \
    public:                          \
    Q_PROPERTY(type name READ get_##name() WRITE set_##name NOTIFY name##Changed)  \
    type get_##name() const { return m_##name; } \
    void set_##name( type value) { m_##name = value; } \
    private: \
    type m_##name;

}

#endif // MyPROPERTY
