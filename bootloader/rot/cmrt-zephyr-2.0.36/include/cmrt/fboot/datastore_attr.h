/*
 * Copyright (c) 2023 Cryptography Research, Inc. (CRI)
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef CMRT_DATASTORE_ATTR_H
#define CMRT_DATASTORE_ATTR_H

/* Object permissions for user and supervisor. Machine has full access. */
#define DS_U_READ (1UL << 0) /* U can read the data from keystore to memory */
#define DS_U_WRITE (1UL << 1) /* U can update object data in keystore */
#define DS_U_EXECUTE (1UL << 2) /* U can use the data within security monitor */
#define DS_U_GRANT (1UL << 3) /* U can change object attributes */
#define DS_U_ALL (DS_U_READ | DS_U_WRITE | DS_U_EXECUTE | DS_U_GRANT)

#define DS_S_READ (1UL << 4) /* S can read the data from keystore to memory */
#define DS_S_WRITE (1UL << 5) /* S can update object data in keystore */
#define DS_S_EXECUTE (1UL << 6) /* S can use the data within security monitor */
#define DS_S_GRANT (1UL << 7) /* S can change object attributes */
#define DS_S_ALL (DS_S_READ | DS_S_WRITE | DS_S_EXECUTE | DS_S_GRANT)

#define DS_ALL (DS_U_ALL | DS_S_ALL)

/* Additional flags for grant. */
#define DS_ALL_ROOTS (1UL << 31) /* apply to all roots */
#define DS_OTHER_ROOTS (1UL << 30) /* apply to all but given root root */

#endif
