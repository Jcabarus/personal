// pthread_barrier_compat.h — macOS-compatible polyfill for pthread_barrier_*
// Works on macOS; no-ops on Linux where real barriers exist.

#ifndef PTHREAD_BARRIER_COMPAT_H
#define PTHREAD_BARRIER_COMPAT_H

#include <pthread.h>
#include <errno.h>

#if !defined(PTHREAD_BARRIER_SERIAL_THREAD)
// If the real barrier API isn't present (e.g., macOS), define a compatible one.

typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
    unsigned        count;       // number currently waiting
    unsigned        tripCount;   // number required to release
    unsigned        generation;  // barrier phase counter
} pthread_barrier_t;

// Placeholder; attributes are unused in this simple polyfill
typedef int pthread_barrierattr_t;

#define PTHREAD_BARRIER_SERIAL_THREAD 1

static int pthread_barrier_init(pthread_barrier_t *b,
                                const pthread_barrierattr_t *attr,
                                unsigned count) {
    (void)attr;
    if (count == 0) return EINVAL;
    int r;
    if ((r = pthread_mutex_init(&b->mutex, NULL))) return r;
    if ((r = pthread_cond_init(&b->cond, NULL))) {
        pthread_mutex_destroy(&b->mutex);
        return r;
    }
    b->tripCount = count;
    b->count = 0;
    b->generation = 0;
    return 0;
}

static int pthread_barrier_destroy(pthread_barrier_t *b) {
    int r1 = pthread_mutex_destroy(&b->mutex);
    int r2 = pthread_cond_destroy(&b->cond);
    return r1 ? r1 : r2;
}

// Returns 0 for waiters, PTHREAD_BARRIER_SERIAL_THREAD for the "serial" thread
static int pthread_barrier_wait(pthread_barrier_t *b) {
    pthread_mutex_lock(&b->mutex);
    unsigned gen = b->generation;

    if (++b->count == b->tripCount) {
        // Last thread arrives: advance generation, release all
        b->generation++;
        b->count = 0;
        pthread_cond_broadcast(&b->cond);
        pthread_mutex_unlock(&b->mutex);
        return PTHREAD_BARRIER_SERIAL_THREAD;
    }

    // Wait while we're still in the same generation
    while (gen == b->generation) {
        pthread_cond_wait(&b->cond, &b->mutex);
    }
    pthread_mutex_unlock(&b->mutex);
    return 0;
}

#endif // !defined(PTHREAD_BARRIER_SERIAL_THREAD)
#endif // PTHREAD_BARRIER_COMPAT_H
