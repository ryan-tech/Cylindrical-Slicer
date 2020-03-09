/****************************************************************************
** Meta object code from reading C++ file 'window.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/window.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Window_t {
    QByteArrayData data[26];
    char stringdata0[290];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Window_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Window_t qt_meta_stringdata_Window = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Window"
QT_MOC_LITERAL(1, 7, 7), // "on_open"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 8), // "on_about"
QT_MOC_LITERAL(4, 25, 10), // "on_bad_stl"
QT_MOC_LITERAL(5, 36, 13), // "on_empty_mesh"
QT_MOC_LITERAL(6, 50, 15), // "on_missing_file"
QT_MOC_LITERAL(7, 66, 16), // "on_confusing_stl"
QT_MOC_LITERAL(8, 83, 11), // "enable_open"
QT_MOC_LITERAL(9, 95, 12), // "disable_open"
QT_MOC_LITERAL(10, 108, 11), // "set_watched"
QT_MOC_LITERAL(11, 120, 8), // "filename"
QT_MOC_LITERAL(12, 129, 13), // "on_projection"
QT_MOC_LITERAL(13, 143, 8), // "QAction*"
QT_MOC_LITERAL(14, 152, 4), // "proj"
QT_MOC_LITERAL(15, 157, 11), // "on_drawMode"
QT_MOC_LITERAL(16, 169, 4), // "mode"
QT_MOC_LITERAL(17, 174, 17), // "on_watched_change"
QT_MOC_LITERAL(18, 192, 9), // "on_reload"
QT_MOC_LITERAL(19, 202, 23), // "on_autoreload_triggered"
QT_MOC_LITERAL(20, 226, 1), // "r"
QT_MOC_LITERAL(21, 228, 15), // "on_clear_recent"
QT_MOC_LITERAL(22, 244, 14), // "on_load_recent"
QT_MOC_LITERAL(23, 259, 1), // "a"
QT_MOC_LITERAL(24, 261, 9), // "on_loaded"
QT_MOC_LITERAL(25, 271, 18) // "on_save_screenshot"

    },
    "Window\0on_open\0\0on_about\0on_bad_stl\0"
    "on_empty_mesh\0on_missing_file\0"
    "on_confusing_stl\0enable_open\0disable_open\0"
    "set_watched\0filename\0on_projection\0"
    "QAction*\0proj\0on_drawMode\0mode\0"
    "on_watched_change\0on_reload\0"
    "on_autoreload_triggered\0r\0on_clear_recent\0"
    "on_load_recent\0a\0on_loaded\0"
    "on_save_screenshot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Window[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  104,    2, 0x0a /* Public */,
       3,    0,  105,    2, 0x0a /* Public */,
       4,    0,  106,    2, 0x0a /* Public */,
       5,    0,  107,    2, 0x0a /* Public */,
       6,    0,  108,    2, 0x0a /* Public */,
       7,    0,  109,    2, 0x0a /* Public */,
       8,    0,  110,    2, 0x0a /* Public */,
       9,    0,  111,    2, 0x0a /* Public */,
      10,    1,  112,    2, 0x0a /* Public */,
      12,    1,  115,    2, 0x08 /* Private */,
      15,    1,  118,    2, 0x08 /* Private */,
      17,    1,  121,    2, 0x08 /* Private */,
      18,    0,  124,    2, 0x08 /* Private */,
      19,    1,  125,    2, 0x08 /* Private */,
      21,    0,  128,    2, 0x08 /* Private */,
      22,    1,  129,    2, 0x08 /* Private */,
      24,    1,  132,    2, 0x08 /* Private */,
      25,    0,  135,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, 0x80000000 | 13,   16,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13,   23,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void,

       0        // eod
};

void Window::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Window *_t = static_cast<Window *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_open(); break;
        case 1: _t->on_about(); break;
        case 2: _t->on_bad_stl(); break;
        case 3: _t->on_empty_mesh(); break;
        case 4: _t->on_missing_file(); break;
        case 5: _t->on_confusing_stl(); break;
        case 6: _t->enable_open(); break;
        case 7: _t->disable_open(); break;
        case 8: _t->set_watched((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->on_projection((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 10: _t->on_drawMode((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 11: _t->on_watched_change((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: _t->on_reload(); break;
        case 13: _t->on_autoreload_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->on_clear_recent(); break;
        case 15: _t->on_load_recent((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 16: _t->on_loaded((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 17: _t->on_save_screenshot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        case 15:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        }
    }
}

const QMetaObject Window::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Window.data,
      qt_meta_data_Window,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Window::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Window::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Window.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Window::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
