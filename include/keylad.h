/* SPDX-License-Identifier:     GPL-2.0+ */
/*
 * (C) Copyright 2025 Rockchip Electronics Co., Ltd
 */

#ifndef _CORE_KEYLAD_H_
#define _CORE_KEYLAD_H_

#include <common.h>
#include <dm.h>

enum RK_FW_KEYID {
	RK_FW_KEY0 = 0,
	RK_FW_KEYMAX
};

struct dm_keylad_ops {
	/* transfer firmware key to dst module */
	int (*transfer_fwkey)(struct udevice *dev, ulong dst,
			      enum RK_FW_KEYID fw_keyid, u32 keylen);
};

/**
 * keylad_get_device() - Get keylad device
 *
 * @return dev on success, otherwise NULL
 */
struct udevice *keylad_get_device(void);

/**
 * keylad_transfer_fwkey() - Transfer firmware key otp to dst module
 *
 * @dev: crypto device
 * @dst: dst module addr
 * @fw_keyid: firmware key id select from enum RK_FW_KEYID
 * @keylen: key length of firmware key

 * @return 0 on success, otherwise failed
 */
int keylad_transfer_fwkey(struct udevice *dev, ulong dst,
			  enum RK_FW_KEYID fw_keyid, u32 keylen);

#endif
