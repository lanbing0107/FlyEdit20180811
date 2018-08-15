/****************************************************************************
** Meta object code from reading C++ file 'flyedit.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../flyedit.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'flyedit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FlyEdit_t {
    QByteArrayData data[11];
    char stringdata0[140];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FlyEdit_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FlyEdit_t qt_meta_stringdata_FlyEdit = {
    {
QT_MOC_LITERAL(0, 0, 7), // "FlyEdit"
QT_MOC_LITERAL(1, 8, 8), // "onSubmit"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 7), // "onReMod"
QT_MOC_LITERAL(4, 26, 8), // "onInsRow"
QT_MOC_LITERAL(5, 35, 9), // "onDeleRow"
QT_MOC_LITERAL(6, 45, 17), // "paraSelectAndShow"
QT_MOC_LITERAL(7, 63, 13), // "onImportExcel"
QT_MOC_LITERAL(8, 77, 15), // "onExportToExcel"
QT_MOC_LITERAL(9, 93, 21), // "setParaSelectsAndPlot"
QT_MOC_LITERAL(10, 115, 24) // "mouseDoubleToRescaleAxes"

    },
    "FlyEdit\0onSubmit\0\0onReMod\0onInsRow\0"
    "onDeleRow\0paraSelectAndShow\0onImportExcel\0"
    "onExportToExcel\0setParaSelectsAndPlot\0"
    "mouseDoubleToRescaleAxes"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FlyEdit[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x08 /* Private */,
       3,    0,   60,    2, 0x08 /* Private */,
       4,    0,   61,    2, 0x08 /* Private */,
       5,    0,   62,    2, 0x08 /* Private */,
       6,    0,   63,    2, 0x08 /* Private */,
       7,    0,   64,    2, 0x08 /* Private */,
       8,    0,   65,    2, 0x08 /* Private */,
       9,    0,   66,    2, 0x08 /* Private */,
      10,    0,   67,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void FlyEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FlyEdit *_t = static_cast<FlyEdit *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onSubmit(); break;
        case 1: _t->onReMod(); break;
        case 2: _t->onInsRow(); break;
        case 3: _t->onDeleRow(); break;
        case 4: _t->paraSelectAndShow(); break;
        case 5: _t->onImportExcel(); break;
        case 6: _t->onExportToExcel(); break;
        case 7: _t->setParaSelectsAndPlot(); break;
        case 8: _t->mouseDoubleToRescaleAxes(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject FlyEdit::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_FlyEdit.data,
      qt_meta_data_FlyEdit,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FlyEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FlyEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FlyEdit.stringdata0))
        return static_cast<void*>(const_cast< FlyEdit*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int FlyEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
