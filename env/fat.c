/*
 * (c) Copyright 2011 by Tigris Elektronik GmbH
 *
 * Author:
 *  Maximilian Schwerin <mvs@tigris.de>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>

#include <command.h>
#include <environment.h>
#include <linux/stddef.h>
#include <malloc.h>
#include <memalign.h>
#include <search.h>
#include <errno.h>
#include <fat.h>
#include <mmc.h>

#ifdef CONFIG_SPL_BUILD
/* TODO(sjg@chromium.org): Figure out why this is needed */
# if !defined(CONFIG_TARGET_AM335X_EVM) || defined(CONFIG_SPL_OS_BOOT)
#  define LOADENV
# endif
#else
# define LOADENV
# if defined(CONFIG_CMD_SAVEENV)
#  define CMD_SAVEENV
# endif
#endif

DECLARE_GLOBAL_DATA_PTR;

__weak const char *env_fat_get_intf(void)
{
	return (const char *)CONFIG_ENV_FAT_INTERFACE;
}

__weak const char *env_fat_get_dev_part(void)
{
	return (const char *)CONFIG_ENV_FAT_DEVICE_AND_PART;
}

#ifdef CMD_SAVEENV
static int env_fat_save(void)
{
	env_t	env_new;
	struct blk_desc *dev_desc = NULL;
	disk_partition_t info;
	int dev, part;
	int err;
	loff_t size;
	const char *ifname = env_fat_get_intf();
	const char *dev_and_part = env_fat_get_dev_part();

	err = env_export(&env_new);
	if (err)
		return err;

	part = blk_get_device_part_str(ifname,dev_and_part,
					&dev_desc, &info, 1);
	if (part < 0)
		return 1;

	dev = dev_desc->devnum;
	if (fat_set_blk_dev(dev_desc, &info) != 0) {
		printf("\n** Unable to use %s %d:%d for saveenv **\n",
		       ifname, dev, part);
		return 1;
	}

	err = file_fat_write(CONFIG_ENV_FAT_FILE, (void *)&env_new, 0, sizeof(env_t),
			     &size);
	if (err == -1) {
		printf("\n** Unable to write \"%s\" from %s%d:%d **\n",
			CONFIG_ENV_FAT_FILE, ifname, dev, part);
		return 1;
	}

	puts("done\n");
	return 0;
}
#endif /* CMD_SAVEENV */

#ifdef LOADENV
static int env_fat_load(void)
{
	ALLOC_CACHE_ALIGN_BUFFER(char, buf, CONFIG_ENV_SIZE);
	struct blk_desc *dev_desc = NULL;
	disk_partition_t info;
	int dev, part;
	int err;
	const char *ifname = env_fat_get_intf();
	const char *dev_and_part = env_fat_get_dev_part();

#ifdef CONFIG_MMC
	if (!strcmp(ifname, "mmc"))
		mmc_initialize(NULL);
#endif

	part = blk_get_device_part_str(ifname,dev_and_part,
					&dev_desc, &info, 1);
	if (part < 0)
		goto err_env_relocate;

	dev = dev_desc->devnum;
	if (fat_set_blk_dev(dev_desc, &info) != 0) {
		printf("\n** Unable to use %s %d:%d for loading the env **\n",
		       ifname, dev, part);
		goto err_env_relocate;
	}

	err = file_fat_read(CONFIG_ENV_FAT_FILE, buf, CONFIG_ENV_SIZE);
	if (err == -1) {
		printf("\n** Unable to read \"%s\" from %s%d:%d **\n",
			CONFIG_ENV_FAT_FILE, ifname, dev, part);
		goto err_env_relocate;
	}

	env_import(buf, 1);
	return 0;

err_env_relocate:
	set_default_env(NULL);

	return -EIO;
}
#endif /* LOADENV */

U_BOOT_ENV_LOCATION(fat) = {
	.location	= ENVL_FAT,
	ENV_NAME("FAT")
#ifdef LOADENV
	.load		= env_fat_load,
#endif
#ifdef CMD_SAVEENV
	.save		= env_save_ptr(env_fat_save),
#endif
};
