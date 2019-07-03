#ifndef TTKGLOBALDEFINE_H
#define TTKGLOBALDEFINE_H

#include <QObject>

//////////////////////////////////////
///exoprt
///
///
#define TTK_EXPORT

#ifdef TTK_EXPORT
#  define TTK_EXTRAS_EXPORT Q_DECL_EXPORT
#else
#  define TTK_EXTRAS_IMPORT Q_DECL_IMPORT
#endif

#endif // TTKGLOBALDEFINE_H
