#ifndef RMLIB_GLOBAL_H
#define RMLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(RMLIB_LIBRARY)
#  define RMLIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define RMLIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // RMLIB_GLOBAL_H
