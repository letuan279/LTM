/****************************************************************************
** Meta object code from reading C++ file 'taskform.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../TaskManager/taskform.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'taskform.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSTaskFormENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSTaskFormENDCLASS = QtMocHelpers::stringData(
    "TaskForm",
    "handleAccept",
    "",
    "string",
    "name",
    "status",
    "start_date",
    "end_date",
    "comment",
    "id_assign",
    "handleReject",
    "on_buttonBox_accepted",
    "on_buttonBox_rejected"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSTaskFormENDCLASS_t {
    uint offsetsAndSizes[26];
    char stringdata0[9];
    char stringdata1[13];
    char stringdata2[1];
    char stringdata3[7];
    char stringdata4[5];
    char stringdata5[7];
    char stringdata6[11];
    char stringdata7[9];
    char stringdata8[8];
    char stringdata9[10];
    char stringdata10[13];
    char stringdata11[22];
    char stringdata12[22];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSTaskFormENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSTaskFormENDCLASS_t qt_meta_stringdata_CLASSTaskFormENDCLASS = {
    {
        QT_MOC_LITERAL(0, 8),  // "TaskForm"
        QT_MOC_LITERAL(9, 12),  // "handleAccept"
        QT_MOC_LITERAL(22, 0),  // ""
        QT_MOC_LITERAL(23, 6),  // "string"
        QT_MOC_LITERAL(30, 4),  // "name"
        QT_MOC_LITERAL(35, 6),  // "status"
        QT_MOC_LITERAL(42, 10),  // "start_date"
        QT_MOC_LITERAL(53, 8),  // "end_date"
        QT_MOC_LITERAL(62, 7),  // "comment"
        QT_MOC_LITERAL(70, 9),  // "id_assign"
        QT_MOC_LITERAL(80, 12),  // "handleReject"
        QT_MOC_LITERAL(93, 21),  // "on_buttonBox_accepted"
        QT_MOC_LITERAL(115, 21)   // "on_buttonBox_rejected"
    },
    "TaskForm",
    "handleAccept",
    "",
    "string",
    "name",
    "status",
    "start_date",
    "end_date",
    "comment",
    "id_assign",
    "handleReject",
    "on_buttonBox_accepted",
    "on_buttonBox_rejected"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSTaskFormENDCLASS[] = {

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
       1,    6,   38,    2, 0x06,    1 /* Public */,
      10,    0,   51,    2, 0x06,    8 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      11,    0,   52,    2, 0x08,    9 /* Private */,
      12,    0,   53,    2, 0x08,   10 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3,    4,    5,    6,    7,    8,    9,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject TaskForm::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSTaskFormENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSTaskFormENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSTaskFormENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<TaskForm, std::true_type>,
        // method 'handleAccept'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const string &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const string &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const string &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const string &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const string &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const string &, std::false_type>,
        // method 'handleReject'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_buttonBox_accepted'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_buttonBox_rejected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void TaskForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TaskForm *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->handleAccept((*reinterpret_cast< std::add_pointer_t<string>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<string>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<string>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<string>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<string>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<string>>(_a[6]))); break;
        case 1: _t->handleReject(); break;
        case 2: _t->on_buttonBox_accepted(); break;
        case 3: _t->on_buttonBox_rejected(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TaskForm::*)(const string & , const string & , const string & , const string & , const string & , const string & );
            if (_t _q_method = &TaskForm::handleAccept; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TaskForm::*)();
            if (_t _q_method = &TaskForm::handleReject; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject *TaskForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TaskForm::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSTaskFormENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int TaskForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void TaskForm::handleAccept(const string & _t1, const string & _t2, const string & _t3, const string & _t4, const string & _t5, const string & _t6)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t6))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TaskForm::handleReject()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
