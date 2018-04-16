#ifndef PTHREAD_SHORTCUT_H
#define PTHREAD_SHORTCUT_H
#define lock(a) pthread_mutex_lock(&a->mutex);
#define unlock(a) pthread_mutex_unlock(&a->mutex);
#endif
