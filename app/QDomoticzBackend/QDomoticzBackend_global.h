#ifndef QDOMOTICZBACKENDBACKEND_GLOBAL_H
#define QDOMOTICZBACKENDBACKEND_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QDOMOTICZBACKEND_LIBRARY)
#  define QDOMOTICZBACKENDSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QDOMOTICZBACKENDSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QDOMOTICZBACKEND_GLOBAL_H