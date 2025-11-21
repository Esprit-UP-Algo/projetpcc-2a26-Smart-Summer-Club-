/****************************************************************************
** Meta object code from reading C++ file 'emailpanel.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../emailpanel.h"
#include <QtGui/qtextcursor.h>
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'emailpanel.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSEmailPanelENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSEmailPanelENDCLASS = QtMocHelpers::stringData(
    "EmailPanel",
    "onMemberSelectionChanged",
    "",
    "onTemplateChanged",
    "onMessageTextChanged",
    "onSendClicked",
    "onScheduleClicked",
    "onPreviewClicked",
    "onSelectAllMembers",
    "checked",
    "onFilterChanged",
    "onSearchTextChanged",
    "onCreateTemplateClicked",
    "onTestAPIClicked"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSEmailPanelENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   80,    2, 0x08,    1 /* Private */,
       3,    0,   81,    2, 0x08,    2 /* Private */,
       4,    0,   82,    2, 0x08,    3 /* Private */,
       5,    0,   83,    2, 0x08,    4 /* Private */,
       6,    0,   84,    2, 0x08,    5 /* Private */,
       7,    0,   85,    2, 0x08,    6 /* Private */,
       8,    1,   86,    2, 0x08,    7 /* Private */,
      10,    0,   89,    2, 0x08,    9 /* Private */,
      11,    0,   90,    2, 0x08,   10 /* Private */,
      12,    0,   91,    2, 0x08,   11 /* Private */,
      13,    0,   92,    2, 0x08,   12 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject EmailPanel::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSEmailPanelENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSEmailPanelENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSEmailPanelENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<EmailPanel, std::true_type>,
        // method 'onMemberSelectionChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onTemplateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onMessageTextChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onSendClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onScheduleClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onPreviewClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onSelectAllMembers'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'onFilterChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onSearchTextChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onCreateTemplateClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onTestAPIClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void EmailPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<EmailPanel *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onMemberSelectionChanged(); break;
        case 1: _t->onTemplateChanged(); break;
        case 2: _t->onMessageTextChanged(); break;
        case 3: _t->onSendClicked(); break;
        case 4: _t->onScheduleClicked(); break;
        case 5: _t->onPreviewClicked(); break;
        case 6: _t->onSelectAllMembers((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 7: _t->onFilterChanged(); break;
        case 8: _t->onSearchTextChanged(); break;
        case 9: _t->onCreateTemplateClicked(); break;
        case 10: _t->onTestAPIClicked(); break;
        default: ;
        }
    }
}

const QMetaObject *EmailPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EmailPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSEmailPanelENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int EmailPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
