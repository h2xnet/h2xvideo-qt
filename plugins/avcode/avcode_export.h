#ifndef AVCODE_EXPORT_H
#define AVCODE_EXPORT_H

#if defined(AVCODE_COMPONENT_BUILD)

#if defined(WIN32)

#if defined(AVCODE_IMPLEMENTATION)

#define AVCODE_EXPORT __declspec(dllexport)
#define AVCODE_EXPORT_PRIVATE __declspec(dllexport)

#else // defined(AVCODE_IMPLEMENTATION)

#define AVCODE_EXPORT __declspec(dllimport)
#define AVCODE_EXPORT_PRIVATE __declspec(dllimport)

#endif

#else // defined(WIN32)

#if defined(AVCODE_IMPLEMENTATION)

#define AVCODE_EXPORT __attribute__((visibility("default")))
#define AVCODE_EXPORT_PRIVATE __attribute__((visibility("default")))

#else

#define AVCODE_EXPORT
#define AVCODE_EXPORT_PRIVATE

#endif

#endif

#else // defined (AVCODE_COMPONENT_BUILD)

#define AVCODE_EXPORT
#define AVCODE_EXPORT_PRIVATE

#endif


#endif // AVCODE_EXPORT_H
