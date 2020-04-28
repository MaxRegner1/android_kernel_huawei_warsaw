#ifndef _OASES_PATCH_API_H
#define _OASES_PATCH_API_H

#include <linux/types.h>

/* specify oases apis */
#define __oases_api

/* version oases framework */
#define OASES_VERSION 1

/*
 * Return value of filters, FILTER_OK indicates to invoke original function
 */
#define FILTER_OK 0
#define FILTER_NG 1

struct oases_patch_info;

struct patch_func {
	char *name;
	char *mod;
	void *filter;
};

struct patch_func_pre {
	struct patch_func common;
};

struct patch_func_post {
	struct patch_func common;
};

#if OASES_ENABLE_REPLACEMENT_HANDLER
struct patch_func_rep {
	struct patch_func common;
};
#endif

/*
 * set up a limit here just in case too much memory consumed.
 */
#define OASES_SUBFUNC_MASK_MAX 64

struct patch_subfunc {
	char *parent;
	char *pmod; /* for parent */
	char *child;
	char *cmod; /* for child */
	void *filter;
	/* mask of subfucs to hook, 0 means all */
	unsigned long mask;
};

struct patch_subfunc_pre {
	struct patch_subfunc common;
};

struct patch_subfunc_post {
	struct patch_subfunc common;
};

#if OASES_ENABLE_REPLACEMENT_HANDLER
struct patch_subfunc_rep {
	struct patch_subfunc common;
};
#endif

enum patch_type {
	OASES_FUNC_PRE  = 0x0001,
	OASES_FUNC_POST = 0x0002,
#if OASES_ENABLE_REPLACEMENT_HANDLER
	OASES_FUNC_REP = 0x0003,
#endif
	OASES_SUBFUNC_PRE  = 0x0100,
	OASES_SUBFUNC_POST = 0x0200,
#if OASES_ENABLE_REPLACEMENT_HANDLER
	OASES_SUBFUNC_REP = 0x0300,
#endif
};

struct patch_entry {
	int type;
	/* for patch_func_pre/post, patch_subfunc_pre/post... */
	void *head;
};

struct oases_patch {
	const char *name; /* vuln name */
	struct patch_entry *pe;
};

void * __oases_api oases_lookup_name(const char *mod, const char *symbol, int (*cb)(void *addr));
/* ctx is oases_patch_info */
int __oases_api oases_register_patch(struct oases_patch_info *ctx, struct oases_patch *patch);

int __oases_api oases_printk(const char *fmt, ...);

void * __oases_api oases_memset(void *s, int c, size_t count);
void * __oases_api oases_memcpy(void *dest, const void *src, size_t count);
int __oases_api oases_memcmp(const void *cs, const void *ct, size_t count);

int __oases_api oases_copy_from_user(void *to, const void __user *from, unsigned long n);
int __oases_api oases_copy_to_user(void __user *to, const void *from, unsigned long n);

int __oases_api oases_get_user_u8(u8 *value, u8 *ptr);
int __oases_api oases_put_user_u8(u8 value, u8 *ptr);
int __oases_api oases_get_user_u16(u16 *value, u16 *ptr);
int __oases_api oases_put_user_u16(u16 value, u16 *ptr);
int __oases_api oases_get_user_u32(u32 *value, u32 *ptr);
int __oases_api oases_put_user_u32(u32 value, u32 *ptr);
int __oases_api oases_get_user_u64(u64 *value, u64 *ptr);
int __oases_api oases_put_user_u64(u64 value, u64 *ptr);

void * __oases_api oases_get_current(void);
unsigned long __oases_api oases_linux_version_code(void);

#endif/* _OASES_PATCH_API_H */
