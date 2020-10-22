#include "pg_filedump.h"

#include "access/tuptoaster.h"
#include "cdb/cdbvars.h"
#include "storage/lwlock.h"
#include "utils/memutils.h"

/****************************************************************************
 * src/backend/utils/init/globals.c
 ***************************************************************************/

#if GP_VERSION_NUM >= 50000
int         NBuffers = 4096;
#endif /* GP_VERSION_NUM */

/****************************************************************************
 * src/backend/storage/buffer/buf_init.c
 ***************************************************************************/

#if GP_VERSION_NUM >= 50000 && GP_VERSION_NUM < 70000
BufferDesc *BufferDescriptors;
char       *BufferBlocks;
#endif /* GP_VERSION_NUM */

/****************************************************************************
 * src/backend/storage/lmgr/lwlock.c
 ***************************************************************************/

#if GP_VERSION_NUM >= 60000
bool
LWLockHeldByMe(LWLock *l)
{
	return true;
}
#elif GP_VERSION_NUM >= 50000
bool
LWLockHeldByMe(LWLockId lockid)
{
	return true;
}
#endif /* GP_VERSION_NUM */

/****************************************************************************
 * src/backend/storage/buffer/bufmgr.c
 ***************************************************************************/

#if GP_VERSION_NUM >= 70000
bool
BufferLockHeldByMe(Page page)
{
	return true;
}
#endif /* GP_VERSION_NUM */

/****************************************************************************
 * src/backend/utils/misc/guc.c
 ***************************************************************************/

bool            assert_enabled = true;

/****************************************************************************
 * src/backend/utils/misc/guc_gp.c
 ***************************************************************************/

bool		Debug_appendonly_print_storage_headers = false;
bool        Debug_appendonly_print_verify_write_block = false;

/****************************************************************************
 * src/backend/cdb/cdbvars.c
 ***************************************************************************/

GpId        GpIdentity = {UNINITIALIZED_GP_IDENTITY_VALUE, UNINITIALIZED_GP_IDENTITY_VALUE};
bool        gp_reraise_signal = false;

#if GP_VERSION_NUM < 60000
int Gp_segment = -2;
#endif /* GP_VERSION_NUM */

/****************************************************************************
 * src/backend/access/heap/tuptoaster.c
 ***************************************************************************/

#if GP_VERSION_NUM >= 60000
Datum
toast_flatten_tuple_to_datum(HeapTupleHeader tup,
							 uint32 tup_len,
							 TupleDesc tupleDesc)
{
	return PointerGetDatum(NULL);
}
#endif /* GP_VERSION_NUM */

/****************************************************************************
 * src/backend/utils/mmgr/mcxt.c
 ***************************************************************************/

MemoryContext   CurrentMemoryContext = NULL;

#if GP_VERSION_NUM >= 70000
void
MemoryContextSetParent(MemoryContext context, MemoryContext new_parent)
{
}

void
MemoryContextDeleteImpl(MemoryContext context, const char* sfile, const char *func, int sline)
{
}
#endif /* GP_VERSION_NUM */

#if GP_VERSION_NUM < 60000
void           *
MemoryContextAllocZeroImpl(MemoryContext context, Size size, const char *sfile, const char *sfunc, int sline)
{
	void           *ptr = malloc(size);
	memset(ptr, 0, size);

	return ptr;
}

void
MemoryContextFreeImpl(void *pointer, const char *sfile, const char *sfunc, int sline)
{
	free(pointer);
}

void           *
MemoryContextAllocImpl(MemoryContext context, Size size, const char *sfile, const char *sfunc, int sline)
{
	return malloc(size);
}

void *
MemoryContextReallocImpl(void *pointer, Size size, const char *sfile, const char *sfunc, int sline)
{

	return realloc( pointer, size );
}
#endif /* GP_VERSION_NUM */

char *
MemoryContextStrdup(MemoryContext context, const char *string)
{
	char	   *nstr;
	Size		len = strlen(string) + 1;

	nstr = (char *) malloc (len);

	memcpy(nstr, string, len);

	return nstr;
}

/****************************************************************************
 * src/backend/access/heap/tuptoaster.c
 ***************************************************************************/

#if GP_VERSION_NUM < 60000
Datum
toast_flatten_tuple_attribute(Datum value,
							  Oid typeId, int32 typeMod)
{
	return PointerGetDatum(NULL);
}
#endif /* GP_VERSION_NUM */

/****************************************************************************
 * src/backend/utils/error/elog.c
 ***************************************************************************/

#if PG_VERSION_NUM <= 90600
int
errcode_for_file_access(void)
{
	return 0;
}

bool
errstart(int elevel, const char *filename, int lineno,
		 const char *funcname, const char* domain)
{
	return (elevel >= ERROR);
}

void
errfinish(int dummy,...)
{
	exit(1);
}

void
elog_start(const char *filename, int lineno, const char *funcname)
{
}

void
elog_finish(int elevel, const char *fmt,...)
{
	fprintf(stderr, "ERROR: %s\n", fmt);
	exit(1);
}

int
errprintstack(bool printstack)
{
	return 0;					/* return value does not matter */
}

int
errcode(int sqlerrcode)
{
	return 0;		/* return value does not matter */
}

int
errmsg(const char *fmt,...)
{
	fprintf(stderr, "ERROR: %s\n", fmt);
	return 0;		/* return value does not matter */
}

int
errmsg_internal(const char *fmt,...)
{
	fprintf(stderr, "ERROR: %s\n", fmt);
	return 0;		/* return value does not matter */
}

int
errdetail(const char *fmt,...)
{
	fprintf(stderr, "DETAIL: %s\n", fmt);
	return 0;		/* return value does not matter */
}

int
errdetail_log(const char *fmt,...)
{
	fprintf(stderr, "DETAIL: %s\n", fmt);
	return 0;		/* return value does not matter */
}

int
errhint(const char *fmt,...)
{
	fprintf(stderr, "HINT: %s\n", fmt);
	return 0;		/* return value does not matter */
}
#else /* PG_VERSION_NUM */
void
errcode_for_file_access(void)
{
}

bool
errstart(int elevel, const char *domain)
{
	return (elevel >= ERROR);
}

void
errfinish(const char *filename, int lineno, const char *funcname)
{
	exit(1);
}

int
errprintstack(bool printstack)
{
	return 0;					/* return value does not matter */
}

void
errcode(int sqlerrcode)
{
}

void
errmsg(const char *fmt,...)
{
	fprintf(stderr, "ERROR: %s\n", fmt);
}

void
errmsg_internal(const char *fmt,...)
{
	fprintf(stderr, "ERROR: %s\n", fmt);
}

void
errdetail(const char *fmt,...)
{
	fprintf(stderr, "DETAIL: %s\n", fmt);
}

void
errdetail_log(const char *fmt,...)
{
	fprintf(stderr, "DETAIL: %s\n", fmt);
}

void
errhint(const char *fmt,...)
{
	fprintf(stderr, "HINT: %s\n", fmt);
}
#endif /* PG_VERSION_NUM */

#if GP_VERSION_NUM < 50000
int
errOmitLocation(bool omitLocation)
{
	return 0;
}
#endif /* GP_VERSION_NUM */

/* vi: set ts=4 : */
