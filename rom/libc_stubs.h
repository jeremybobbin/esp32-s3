#pragma once

#include <sys/lock.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <reent.h>
#include <errno.h>

#define syscall_table_ptr_pro syscall_table_ptr
#define syscall_table_ptr_app syscall_table_ptr

struct syscall_stub_table {
	struct _reent* (*__getreent)(void);
	void* (*_malloc_r)(struct _reent *r, size_t);
	void (*_free_r)(struct _reent *r, void*);
	void* (*_realloc_r)(struct _reent *r, void*, size_t);
	void* (*_calloc_r)(struct _reent *r, size_t, size_t);
	void (*_abort)(void);
	int (*_system_r)(struct _reent *r, const char*);
	int (*_rename_r)(struct _reent *r, const char*, const char*);
	clock_t (*_times_r)(struct _reent *r, struct tms *);
	int (*_gettimeofday_r) (struct _reent *r, struct timeval *, void *);
	void (*_raise_r)(struct _reent *r);
	int (*_unlink_r)(struct _reent *r, const char*);
	int (*_link_r)(struct _reent *r, const char*, const char*);
	int (*_stat_r)(struct _reent *r, const char*, struct stat *);
	int (*_fstat_r)(struct _reent *r, int, struct stat *);
	void* (*_sbrk_r)(struct _reent *r, ptrdiff_t);
	int (*_getpid_r)(struct _reent *r);
	int (*_kill_r)(struct _reent *r, int, int);
	void (*_exit_r)(struct _reent *r, int);
	int (*_close_r)(struct _reent *r, int);
	int (*_open_r)(struct _reent *r, const char *, int, int);
	int (*_write_r)(struct _reent *r, int, const void *, int);
	int (*_lseek_r)(struct _reent *r, int, int, int);
	int (*_read_r)(struct _reent *r, int, void *, int);
	void (*_retarget_lock_init)(_LOCK_T *lock);
	void (*_retarget_lock_init_recursive)(_LOCK_T *lock);
	void (*_retarget_lock_close)(_LOCK_T lock);
	void (*_retarget_lock_close_recursive)(_LOCK_T lock);
	void (*_retarget_lock_acquire)(_LOCK_T lock);
	void (*_retarget_lock_acquire_recursive)(_LOCK_T lock);
	int (*_retarget_lock_try_acquire)(_LOCK_T lock);
	int (*_retarget_lock_try_acquire_recursive)(_LOCK_T lock);
	void (*_retarget_lock_release)(_LOCK_T lock);
	void (*_retarget_lock_release_recursive)(_LOCK_T lock);
	int (*_printf_float)(struct _reent *data, void *pdata, FILE * fp, int (*pfunc) (struct _reent *, FILE *, const char *, size_t len), va_list * ap);
	int (*_scanf_float) (struct _reent *rptr, void *pdata, FILE *fp, va_list *ap);
	void (*__assert_func) (const char *file, int line, const char * func, const char *failedexpr) __attribute__((noreturn));
	void (*__sinit) (struct _reent *r);
	void (*_cleanup_r) (struct _reent* r);
};

extern struct syscall_stub_table *syscall_table_ptr;

