/****************************************************************************
** Meta object code from reading C++ file 'registerscreen.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../TaskManager/registerscreen.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'registerscreen.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.1. It"
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
struct qt_meta_stringdata_CLASSRegisterScreenENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSRegisterScreenENDCLASS = QtMocHelpers::stringData(
    "RegisterScreen",
    "moveToLoginClicked",
    "",
    "registerButtonClicked",
    "username",
    "password",
    "on_moveto_login_clicked",
    "on_btn_register_clicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSRegisterScreenENDCLASS_t {
    uint offsetsAndSizes[16];
    char stringdata0[15];
    char stringdata1[19];
    char stringdata2[1];
    char stringdata3[22];
    char stringdata4[9];
    char stringdata5[9];
    char stringdata6[24];
    char stringdata7[24];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSRegisterScreenENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSRegisterScreenENDCLASS_t qt_meta_stringdata_CLASSRegisterScreenENDCLASS = {
    {
        QT_MOC_LITERAL(0, 14),  // "RegisterScreen"
        QT_MOC_LITERAL(15, 18),  // "moveToLoginClicked"
        QT_MOC_LITERAL(34, 0),  // ""
        QT_MOC_LITERAL(35, 21),  // "registerButtonClicked"
        QT_MOC_LITERAL(57, 8),  // "username"
        QT_MOC_LITERAL(66, 8),  // "password"
        QT_MOC_LITERAL(75, 23),  // "on_moveto_login_clicked"
        QT_MOC_LITERAL(99, 23)   // "on_btn_register_clicked"
    },
    "RegisterScreen",
    "moveToLoginClicked",
    "",
    "registerButtonClicked",
    "username",
    "password",
    "on_moveto_login_clicked",
    "on_btn_register_clicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSRegisterScreenENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   38,    2, 0x06,    1 /* Public */,
       3,    2,   39,    2, 0x06,    2 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       6,    0,   44,    2, 0x08,    5 /* Private */,
       7,    0,   45,    2, 0x08,    6 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    4,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject RegisterScreen::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSRegisterScreenENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSRegisterScreenENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSRegisterScreenENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<RegisterScreen, std::true_type>,
        // method 'moveToLoginClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'registerButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'on_moveto_login_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btn_register_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void RegisterScreen::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RegisterScreen *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->moveToLoginClicked(); break;
        case 1: _t->registerButtonClicked((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 2: _t->on_moveto_login_clicked(); break;
        case 3: _t->on_btn_register_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (RegisterScreen::*)();
            if (_t _q_method = &RegisterScreen::moveToLoginClicked; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (RegisterScreen::*)(const QString & , const QString & );
            if (_t _q_method = &RegisterScreen::registerButtonClicked; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject *RegisterScreen::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RegisterScreen::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSRegisterScreenENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int RegisterScreen::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void RegisterScreen::moveToLoginClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void RegisterScreen::registerButtonClicked(const QString & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
