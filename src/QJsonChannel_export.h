
#ifndef QJSONCHANNEL_EXPORT_H
#define QJSONCHANNEL_EXPORT_H

#ifdef QJSONCHANNEL_STATIC_DEFINE
#  define QJSONCHANNEL_EXPORT
#  define QJSONCHANNEL_NO_EXPORT
#else
#  ifndef QJSONCHANNEL_EXPORT
#    ifdef QJsonChannel_EXPORTS
        /* We are building this library */
#      define QJSONCHANNEL_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define QJSONCHANNEL_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef QJSONCHANNEL_NO_EXPORT
#    define QJSONCHANNEL_NO_EXPORT 
#  endif
#endif

#ifndef QJSONCHANNEL_DEPRECATED
#  define QJSONCHANNEL_DEPRECATED __declspec(deprecated)
#endif

#ifndef QJSONCHANNEL_DEPRECATED_EXPORT
#  define QJSONCHANNEL_DEPRECATED_EXPORT QJSONCHANNEL_EXPORT QJSONCHANNEL_DEPRECATED
#endif

#ifndef QJSONCHANNEL_DEPRECATED_NO_EXPORT
#  define QJSONCHANNEL_DEPRECATED_NO_EXPORT QJSONCHANNEL_NO_EXPORT QJSONCHANNEL_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef QJSONCHANNEL_NO_DEPRECATED
#    define QJSONCHANNEL_NO_DEPRECATED
#  endif
#endif

#endif /* QJSONCHANNEL_EXPORT_H */
