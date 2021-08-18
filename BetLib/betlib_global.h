#ifndef BETLIB_GLOBAL_H
#define BETLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(BETLIB_LIBRARY)
#  define BETLIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define BETLIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // BETLIB_GLOBAL_H
