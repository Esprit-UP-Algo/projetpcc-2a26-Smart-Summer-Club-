/****************************************************************************
** Meta object code from reading C++ file 'employee.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../employee.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'employee.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSEmployeeENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSEmployeeENDCLASS = QtMocHelpers::stringData(
    "Employee",
    "onSearchEmployees",
    "",
    "onUploadPhoto",
    "onConfirmAdd",
    "onConfirmUpdate",
    "onConfirmDelete",
    "clearEmployeeForm",
    "onEditEmployeeByCin",
    "cin",
    "onDeleteEmployeeByCin",
    "onEditEmployee",
    "row",
    "onDeleteEmployee",
    "onSortEmployees",
    "onExportEmployees",
    "onFilterByDepartment",
    "onFilterByStatus"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSEmployeeENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   98,    2, 0x0a,    1 /* Public */,
       3,    0,   99,    2, 0x0a,    2 /* Public */,
       4,    0,  100,    2, 0x0a,    3 /* Public */,
       5,    0,  101,    2, 0x0a,    4 /* Public */,
       6,    0,  102,    2, 0x0a,    5 /* Public */,
       7,    0,  103,    2, 0x0a,    6 /* Public */,
       8,    1,  104,    2, 0x0a,    7 /* Public */,
      10,    1,  107,    2, 0x0a,    9 /* Public */,
      11,    1,  110,    2, 0x0a,   11 /* Public */,
      13,    1,  113,    2, 0x0a,   13 /* Public */,
      14,    0,  116,    2, 0x0a,   15 /* Public */,
      15,    0,  117,    2, 0x0a,   16 /* Public */,
      16,    0,  118,    2, 0x0a,   17 /* Public */,
      17,    0,  119,    2, 0x0a,   18 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject Employee::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSEmployeeENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSEmployeeENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSEmployeeENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Employee, std::true_type>,
        // method 'onSearchEmployees'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onUploadPhoto'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onConfirmAdd'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onConfirmUpdate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onConfirmDelete'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'clearEmployeeForm'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onEditEmployeeByCin'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'onDeleteEmployeeByCin'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'onEditEmployee'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onDeleteEmployee'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onSortEmployees'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onExportEmployees'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onFilterByDepartment'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onFilterByStatus'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void Employee::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Employee *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onSearchEmployees(); break;
        case 1: _t->onUploadPhoto(); break;
        case 2: _t->onConfirmAdd(); break;
        case 3: _t->onConfirmUpdate(); break;
        case 4: _t->onConfirmDelete(); break;
        case 5: _t->clearEmployeeForm(); break;
        case 6: _t->onEditEmployeeByCin((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->onDeleteEmployeeByCin((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 8: _t->onEditEmployee((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 9: _t->onDeleteEmployee((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 10: _t->onSortEmployees(); break;
        case 11: _t->onExportEmployees(); break;
        case 12: _t->onFilterByDepartment(); break;
        case 13: _t->onFilterByStatus(); break;
        default: ;
        }
    }
}

const QMetaObject *Employee::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Employee::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSEmployeeENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Employee::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
