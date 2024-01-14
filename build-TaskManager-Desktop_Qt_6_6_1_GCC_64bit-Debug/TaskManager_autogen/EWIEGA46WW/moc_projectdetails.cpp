/****************************************************************************
** Meta object code from reading C++ file 'projectdetails.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../TaskManager/projectdetails.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'projectdetails.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSProjectDetailsENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSProjectDetailsENDCLASS = QtMocHelpers::stringData(
    "ProjectDetails",
    "widgetShown",
    "",
    "widgetChanged",
    "index",
    "doubleClick",
    "id",
    "closeApp",
    "on_project_stackwidget_currentChanged",
    "arg1",
    "on_task_table_doubleClicked",
    "QModelIndex"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSProjectDetailsENDCLASS_t {
    uint offsetsAndSizes[24];
    char stringdata0[15];
    char stringdata1[12];
    char stringdata2[1];
    char stringdata3[14];
    char stringdata4[6];
    char stringdata5[12];
    char stringdata6[3];
    char stringdata7[9];
    char stringdata8[38];
    char stringdata9[5];
    char stringdata10[28];
    char stringdata11[12];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSProjectDetailsENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSProjectDetailsENDCLASS_t qt_meta_stringdata_CLASSProjectDetailsENDCLASS = {
    {
        QT_MOC_LITERAL(0, 14),  // "ProjectDetails"
        QT_MOC_LITERAL(15, 11),  // "widgetShown"
        QT_MOC_LITERAL(27, 0),  // ""
        QT_MOC_LITERAL(28, 13),  // "widgetChanged"
        QT_MOC_LITERAL(42, 5),  // "index"
        QT_MOC_LITERAL(48, 11),  // "doubleClick"
        QT_MOC_LITERAL(60, 2),  // "id"
        QT_MOC_LITERAL(63, 8),  // "closeApp"
        QT_MOC_LITERAL(72, 37),  // "on_project_stackwidget_curren..."
        QT_MOC_LITERAL(110, 4),  // "arg1"
        QT_MOC_LITERAL(115, 27),  // "on_task_table_doubleClicked"
        QT_MOC_LITERAL(143, 11)   // "QModelIndex"
    },
    "ProjectDetails",
    "widgetShown",
    "",
    "widgetChanged",
    "index",
    "doubleClick",
    "id",
    "closeApp",
    "on_project_stackwidget_currentChanged",
    "arg1",
    "on_task_table_doubleClicked",
    "QModelIndex"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSProjectDetailsENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x06,    1 /* Public */,
       3,    1,   51,    2, 0x06,    2 /* Public */,
       5,    1,   54,    2, 0x06,    4 /* Public */,
       7,    0,   57,    2, 0x06,    6 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       8,    1,   58,    2, 0x08,    7 /* Private */,
      10,    1,   61,    2, 0x08,    9 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, 0x80000000 | 11,    4,

       0        // eod
};

Q_CONSTINIT const QMetaObject ProjectDetails::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSProjectDetailsENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSProjectDetailsENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSProjectDetailsENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ProjectDetails, std::true_type>,
        // method 'widgetShown'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'widgetChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const int &, std::false_type>,
        // method 'doubleClick'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'closeApp'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_project_stackwidget_currentChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_task_table_doubleClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>
    >,
    nullptr
} };

void ProjectDetails::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ProjectDetails *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->widgetShown(); break;
        case 1: _t->widgetChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->doubleClick((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->closeApp(); break;
        case 4: _t->on_project_stackwidget_currentChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->on_task_table_doubleClicked((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ProjectDetails::*)();
            if (_t _q_method = &ProjectDetails::widgetShown; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ProjectDetails::*)(const int & );
            if (_t _q_method = &ProjectDetails::widgetChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ProjectDetails::*)(const QString & );
            if (_t _q_method = &ProjectDetails::doubleClick; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ProjectDetails::*)();
            if (_t _q_method = &ProjectDetails::closeApp; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject *ProjectDetails::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProjectDetails::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSProjectDetailsENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ProjectDetails::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void ProjectDetails::widgetShown()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ProjectDetails::widgetChanged(const int & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ProjectDetails::doubleClick(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ProjectDetails::closeApp()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
