#ifndef PTHREAD_SHORTCUT_H
#define PTHREAD_SHORTCUT_H
#include <stdio.h>
#ifdef DEBUG
#define DBG_LOCK_INFO printf("Lock: File: %s - Line: %d\n", __FILE__, __LINE__);
#define DBG_UNLOCK_INFO printf("Unlock: File: %s - Line: %d\n", __FILE__, __LINE__);
#else
#define DBG_LOCK_INFO
#define DBG_UNLOCK_INFO
#endif
#define lock(a) DBG_LOCK_INFO pthread_mutex_lock(&a->mutex);
#define unlock(a) DBG_UNLOCK_INFO pthread_mutex_unlock(&a->mutex);
#endif
