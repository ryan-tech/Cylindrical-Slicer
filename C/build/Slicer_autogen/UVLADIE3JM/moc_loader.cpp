/****************************************************************************
** Meta object code from reading C++ file 'loader.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/parser.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'loader.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_STLParser_t {
    QByteArrayData data[13];
    char stringdata0[133];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_STLParser_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_STLParser_t qt_meta_stringdata_STLParser = {
    {
QT_MOC_LITERAL(0, 0, 9), // "STLParser"
QT_MOC_LITERAL(1, 10, 11), // "loaded_file"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 8), // "filename"
QT_MOC_LITERAL(4, 32, 8), // "got_mesh"
QT_MOC_LITERAL(5, 41, 5), // "Mesh*"
QT_MOC_LITERAL(6, 47, 1), // "m"
QT_MOC_LITERAL(7, 49, 1), // "b"
QT_MOC_LITERAL(8, 51, 9), // "is_reload"
QT_MOC_LITERAL(9, 61, 13), // "error_bad_stl"
QT_MOC_LITERAL(10, 75, 16), // "error_empty_mesh"
QT_MOC_LITERAL(11, 92, 21), // "warning_confusing_stl"
QT_MOC_LITERAL(12, 114, 18) // "error_missing_file"

    },
    "STLParser\0loaded_file\0\0filename\0"
    "got_mesh\0Mesh*\0m\0b\0is_reload\0error_bad_stl\0"
    "error_empty_mesh\0warning_confusing_stl\0"
    "error_missing_file"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_STLParser[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    3,   47,    2, 0x06 /* Public */,
       9,    0,   54,    2, 0x06 /* Public */,
      10,    0,   55,    2, 0x06 /* Public */,
      11,    0,   56,    2, 0x06 /* Public */,
      12,    0,   57,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 5, QMetaType::Bool,    6,    7,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void STLParser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        STLParser *_t = static_cast<STLParser *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->loaded_file((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->got_mesh((*reinterpret_cast< Mesh*(*)>(_a[1])),(*reinterpret_cast< Mesh*(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 2: _t->error_bad_stl(); break;
        case 3: _t->error_empty_mesh(); break;
        case 4: _t->warning_confusing_stl(); break;
        case 5: _t->error_missing_file(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (STLParser::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&STLParser::loaded_file)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (STLParser::*_t)(Mesh * , Mesh * , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&STLParser::got_mesh)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (STLParser::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&STLParser::error_bad_stl)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (STLParser::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&STLParser::error_empty_mesh)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (STLParser::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&STLParser::warning_confusing_stl)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (STLParser::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&STLParser::error_missing_file)) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject STLParser::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_STLParser.data,
      qt_meta_data_STLParser,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *STLParser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *STLParser::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_STLParser.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int STLParser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void STLParser::loaded_file(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void STLParser::got_mesh(Mesh * _t1, Mesh * _t2, bool _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void STLParser::error_bad_stl()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void STLParser::error_empty_mesh()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void STLParser::warning_confusing_stl()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void STLParser::error_missing_file()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
